#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{
	pid_t pid;
	
	pid = fork();
	if(pid <0 ){
		perror("fork error");
		exit(1);
	}else if( pid==0 ){//子，创建会话不能是父进程
		
		printf("\nchild PID == %d\n", getpid());
		printf("child Group ID == %d\n", getpgid(0));//组id 等价于下面
		printf("child Session ID == %d\n", getsid(0));
		
		sleep(3);
		setsid();//以自己的id设置进程组id，也是设置会话id
		printf("Changed:\n");
		

		printf("child PID == %d\n", getpid());
		printf("child Group ID == %d\n", getpgid(0));
		printf("child Session ID == %d\n", getsid(0));
		
		sleep(5);
		
		exit(0);
		
	}
                
	return 0;

}





