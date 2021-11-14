#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int n =0, flag = 0;
/*
全局变量异步io问题：进程间使用信号通讯，对全局变量产生的影响，导致时序错误，
后面可以使用锁机制解决！
*/
void do_sig_child(int num)
{
	printf("%d child  count: %d\n", getpid(), n);
	n += 2;
	flag=1;
	sleep(1);
}

void do_sig_parent(int num)
{
	printf("%d parent count: %d\n", getpid(), n);
	n += 2;
	flag=1;
	sleep(1);
}

int main()
{
	pid_t pid;
        struct sigaction act;
        
        pid = fork();
        if(pid < 0){
                perror("fork error!");
                exit(1);
        }else if(pid > 0){//父
                
                 n=1;
                 sleep(1);//等待子进程注册完函数
                 
                 act.sa_handler = do_sig_parent;
                 sigemptyset(&act.sa_mask);
                 act.sa_flags = 0;
                 sigaction(SIGUSR2, &act, NULL);
                 
                 do_sig_parent(0);
                 
                 while(1){
                        
                        if(flag==1){
                                kill(pid, SIGUSR1);/*注意再此处有问题，若在kill函数执行后，此进程失去cpu，则回导致flag无法置0,程序卡死*/
                                flag = 0;
                        }
                 }
                 
                }else if(pid == 0){//子
                
                        n=2;
                        act.sa_handler = do_sig_child;
                        sigemptyset(&act.sa_mask);
                        act.sa_flags = 0;
                        sigaction(SIGUSR1, &act, NULL);               
                        
                        while(1){
                        
                                if(flag==1){
                                        kill(getppid(), SIGUSR2);
                                        flag = 0;
                                }                       
                                
                        
                        }
                
                }
                
                
	return 0;

}





