#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <unistd.h>

void  timer_handler(void)
{
	return;
}

void main(){

	unsigned int period=100;
	struct itimerval it_val;	/* for setting itimer */
	int i=0;

	if (signal(SIGALRM, (void (*)(int)) timer_handler) == SIG_ERR)
	{
		perror("Unable to catch SIGALRM");
		return;
	}
	it_val.it_value.tv_sec =  0;
	it_val.it_value.tv_usec = period;
	it_val.it_interval = it_val.it_value;
	if (setitimer(ITIMER_REAL, &it_val, NULL) == -1)
	{
		perror("error calling setitimer()");
		return ;
	}

	printf("test started period=%d\n", period);
	while(1){
		usleep(1000);
		if((i%10000)==0) printf("%s: hello, i=%d\n", __func__, i);
		i++;
	}
	printf("exited.\n");
	return ;
}


