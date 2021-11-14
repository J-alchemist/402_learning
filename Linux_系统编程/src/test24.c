#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*执行完程序，ps -aux查看该进程的控制终端为？，说明该守护进程正常执行*/
//.bashrc文件配置shell终端，PS1为配置终端提示符的环境变量
int main(void)
{
	pid_t pid, sid;
	int ret;

	pid = fork();
	if(pid <0 ){
		perror("fork error");
		exit(1);
	}else if( pid==0 ){//子，创建会话不能是父进程
		
		sid = setsid();//以自己的id设置进程组id，也是设置会话id	
		if(sid == -1){
			perror("setsid error");
			exit(1);
		}

		ret = chdir("/home/gj");  //改变进程的工作目录
		if(ret <0 ){
			perror("chdir error");
			exit(1);
		}
		umask(0002);//指定以后创建的文件的权限  其他人-可写
		close(0);//关闭0号文件描述符，标准输入
		open("/dev/null", O_RDWR);//现在/dev/null的文件描述符占用0
		
		dup2(0,1);//将标准输出指向/dev/null
		dup2(0,2);//将标准错误指向/dev/null

		while(1){
			//守护进程的要做的
		}
		
	}else if( pid>0 )//父进程直接退出
		{
			exit(0);
		}

                
	return 0;

}





