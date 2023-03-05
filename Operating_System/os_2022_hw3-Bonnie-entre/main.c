#include <stdlib.h>
#include <string.h>
#include "include/shell.h"
#include "include/command.h"
#include "include/task.h"
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
	for(int i=0; i<8; i++)
		available_list[i] = true;
	finish_all = 0;
	g_id_num = 0;
	time_count = 0;
	qt=3;

	Q_ready = (struct Task *)malloc(sizeof(struct Task));
	Q_ready->next = NULL;
	Q_run = (struct Task *)malloc(sizeof(struct Task));
	Q_run->next = NULL;
	Q_ter = (struct Task *)malloc(sizeof(struct Task));
	Q_ter->next = NULL;
	Q_wait = (struct Task *)malloc(sizeof(struct Task));
	Q_wait->next = NULL;
	Q_ps = (struct Task *)malloc(sizeof(struct Task));
	Q_ps->order_next = NULL;

	//FCFS, RR, PP(priority-based)
	if(!strcmp(argv[1], "FCFS"))
		algorithm = 0;
	else if(!strcmp(argv[1], "PP"))
		algorithm = 1;
	else
		algorithm = 2;

	history_count = 0;
	for (int i = 0; i < MAX_RECORD_NUM; ++i)
    	history[i] = (char *)malloc(BUF_SIZE * sizeof(char));

	// initial timer
	struct itimerval v;
	signal(SIGVTALRM, timehandler);
	v.it_value.tv_sec = 0;
	v.it_value.tv_usec = 10000;
	v.it_interval.tv_sec = 0;
	v.it_interval.tv_usec = 10000;
	setitimer(ITIMER_VIRTUAL, &v, NULL);

	// initialize crl+z
	signal(SIGTSTP, crl_Z);

	shell();

	for (int i = 0; i < MAX_RECORD_NUM; ++i)
    	free(history[i]);

	return 0;
}
