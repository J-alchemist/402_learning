#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

/*         man setitimer
struct itimerval {
                  struct timeval it_interval; // Interval for periodic timer 
                  struct timeval it_value;    // Time until next expiration 
                 };

struct timeval {
               time_t      tv_sec;        // seconds 
               suseconds_t tv_usec;       // microseconds 
             };
*/
int main(void)
{
	int ret=0,i=0;

	struct itimerval it,oldit;
	//总定时1s+1us
	it.it_value.tv_sec = 1;	//第一次定时1s	
	it.it_value.tv_usec = 1;//第一次定时1us
	it.it_interval.tv_sec = 0;//过多久开启下一次秒定时
	it.it_interval.tv_usec = 0;//过多久开启下一次微秒定时
	
	ret = setitimer(ITIMER_REAL, &it, &oldit);//oldit返回定时剩余的时间
	if(ret == -1){
		perror("setitimer error!");
		exit(-1);
	}
	
	for(i=0;;i++)
		printf("%d\n",i);

	return 0;

}
