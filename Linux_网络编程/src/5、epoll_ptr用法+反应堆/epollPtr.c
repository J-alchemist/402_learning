#include <stdio.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
/*
首先监听lfd，lfd绑定acceptconn，在acceptconn函数里accept设置cfd的结构体及callback，

*/
#define SERV_PORT 8000
char *IPSRC = "127.0.0.1";

#define BUFLEN		4096
#define MAX_EVENTS  1024

//******************自定义数据
struct My_epoll {
	
	int fd;
	int events; 
	void *arg;

	void (*call_back)(int fd, int events, void *arg);
	
	char buf[BUFLEN];	//数据存储
    int len;			//数据大小
	
	int status;			//是否上树 ：1表示该节点已经挂上树了
};
//******************
struct My_epoll gl_events[MAX_EVENTS+1];//自定义信息数组
ssize_t g_efd;		//全局树根

void recedata(int fd, int events, void *arg);//函数声明

void perr_exit(char *s)
{
	perror(s);
	exit(1);
}

void senddata(int fd, int events, void *arg)
{
	struct My_epoll *ev = arg;

	int ret = write(ev->fd, ev->buf, ev->len);//发送给客户端
	if( ret<=0 )//改为读监听
	{
		printf("write error!\n");
		return;
	}
		
	struct epoll_event epv = {0, {0}};
	
	if(ev->status == 1)	
	{
		ev->status = 0;//摘下
		epv.data.ptr = ev;
   		epoll_ctl(g_efd, EPOLL_CTL_DEL, ev->fd, &epv); 
   		
		ev->status = 1;
		ev->events = EPOLLIN | EPOLLET;
		ev->arg = arg;
		ev->fd = fd;
		ev->call_back = recedata;
		
		epv.events = EPOLLIN | EPOLLET;	//读监听
		epv.data.ptr =  ev;
		int res = epoll_ctl(g_efd, EPOLL_CTL_ADD, ev->fd, &epv); //将fd添加到g_efd树根
		if (res == -1)
		{
			printf("epoll_ctl error!\n");
		}
		    	   		
	}
	
	return;
}

void recedata(int fd, int events, void *arg)
{
	struct My_epoll *ev = arg;
	
	int len = read(ev->fd, ev->buf, sizeof(ev->buf));	//接收客户端数据
	if(len <= 0)
	{
		close(ev->fd);
		printf("fd[%d] read failed!\n", fd);
		return;
	}
		
	printf("client fd[%d] send data: \n", ev->fd);	
	ev->len = len;
	write(1, ev->buf, ev->len);//服务器向标准输出写数据
	
	for(int i=0; i< ev->len; i++)
	{
		ev->buf[i] = toupper(ev->buf[i]);//作字符转换
	}
	//摘下节点-->改为可写-->上树
	struct epoll_event epv = {0, {0}};

	if(ev->status == 1)//在树上
	{  
		ev->status = 0;                                      
		epv.data.ptr = ev;
   		epoll_ctl(g_efd, EPOLL_CTL_DEL, ev->fd, &epv); 	//摘下  
	
		ev->status = 1;
		ev->events = EPOLLOUT;
		ev->arg = arg;
		ev->fd = fd;
		ev->call_back = senddata;
		
		epv.events = EPOLLOUT;	//写监听
		epv.data.ptr =  ev;
		int res = epoll_ctl(g_efd, EPOLL_CTL_ADD, ev->fd, &epv); //将fd添加到g_efd树根
		if (res == -1)
		{
			printf("epoll_ctl error");
		}
		 
	}
	
	return ;

}


void acceptconn(int fd, int events, void *arg)
{
	
    struct sockaddr_in cin;
    socklen_t len = sizeof(cin);
    char str[INET_ADDRSTRLEN];//16
    
    int cfd,i,res;
                 
	cfd = accept(fd, (struct sockaddr *)&cin, &len);
    if (cfd < 0)
    {
    	printf("accept error!\n");
    	return;
    }
		
	
	printf("require from [%s] at PORT [%d] as fd[%d] \n", 
                        inet_ntop(AF_INET, &cin.sin_addr, str, sizeof(str)), 
                        ntohs(cin.sin_port), cfd);//打印每个连接上的客户端信息
	//二次回调
	for(i = 0; i < MAX_EVENTS; i++ )
	{
		if(gl_events[i].status != 1 )//找一个空的存放新客户端信息
			break;	
	}
	if(i==MAX_EVENTS)
	{
	    printf("gl_events[] over stack error!\n");
    	return;
	}
	
	fcntl( cfd, F_SETFL, O_NONBLOCK );	//非阻塞
		
	//初始化本次客户端的自定义结构体
	struct epoll_event epv = { 0, {0} };
	
	gl_events[i].fd = cfd;
	gl_events[i].status = 1;
	gl_events[i].arg = &gl_events[i];
	gl_events[i].events = EPOLLIN | EPOLLET;
	gl_events[i].len = 0;
	memset(gl_events[i].buf, 0, sizeof(gl_events[i].buf));
	gl_events[i].call_back = recedata;//设置cfd的回调
	
	epv.data.ptr =  &gl_events[i]; 	  //ptr指向本次自定义结构体
    epv.events = EPOLLIN | EPOLLET; 	      //lfd可读事件
    res = epoll_ctl(g_efd, EPOLL_CTL_ADD, gl_events[i].fd, &epv); //将cfd添加到g_efd树根
    if ( res < 0) {
        printf("event add failed: fd[%d], events[%d]\n", fd, events);
    }	
	
	return;
}


int main(int argc, char *argv[])
{
    int i, lfd;
    ssize_t nready, res;	//efd根节点

    struct sockaddr_in servaddr;//ip
    struct epoll_event epevts, events[MAX_EVENTS+1];//epevts设置的、events传出的

    lfd = socket(AF_INET, SOCK_STREAM, 0);
	fcntl(lfd, F_SETFL, O_NONBLOCK); 
	

    int opt = 1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));      //端口复用

    g_efd = epoll_create(MAX_EVENTS+1);       //创建epoll模型, efd指向红黑树根节点
    if (g_efd == -1)
        perr_exit("epoll_create error");
//set   gl_events[MAX_EVENTS]描述的是lfd的文件描述符和回调
	gl_events[MAX_EVENTS].fd = lfd;	
	gl_events[MAX_EVENTS].status = 1;
	gl_events[MAX_EVENTS].arg = &gl_events[MAX_EVENTS];
	gl_events[MAX_EVENTS].events = EPOLLIN;
	gl_events[MAX_EVENTS].len = 0;
	memset(gl_events[MAX_EVENTS].buf, 0, sizeof(gl_events[MAX_EVENTS].buf));
	gl_events[MAX_EVENTS].call_back = acceptconn;//最开始是lfd绑定的acceptconn

//add	
	epevts.data.ptr =  &gl_events[MAX_EVENTS]; //ptr指向自定义结构体
    epevts.events = EPOLLIN | EPOLLET; 	      //lfd可读事件,边沿触发
    res = epoll_ctl(g_efd, EPOLL_CTL_ADD, gl_events[MAX_EVENTS].fd, &epevts); //将lfd添加到g_efd树根的二叉树上
    if (res == -1)
        perr_exit("main epoll_ctl error");	
//bind
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    bind(lfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    listen(lfd, 128);
//************
	printf("waiting for connect...\n");
//------------
//ok
    for ( ; ; ) {
      
        nready = epoll_wait(g_efd, events, MAX_EVENTS+1, 1000);   //监听根节点g_efd，并传出events
        if (nready < 0){
            printf("epoll_wait error, exit\n");
            break;//终止cx
		}
        for (i = 0; i < nready; i++) {
	    
			struct My_epoll *ev = (struct My_epoll *)events[i].data.ptr;//临时变量，存储ptr返回，便于操作 1
	       
		    if (events[i].events & EPOLLIN) {           //EPOLLIN读就绪事件
				ev->call_back( ev->fd, events[i].events, ev->arg);//调用  2
				//((struct My_epoll *)(events[i].data.ptr))->call_back( ((struct My_epoll *)(events[i].data.ptr))->fd, events[i].events );//1 2 等价于此句
          	  } 
           if (events[i].events & EPOLLOUT) {          //EPOLLOUT写就绪事件
				ev->call_back( ev->fd, events[i].events, ev->arg);
           	  }		
   
        }
    }
	
    close(lfd);
    close(g_efd);

    return 0;
}

