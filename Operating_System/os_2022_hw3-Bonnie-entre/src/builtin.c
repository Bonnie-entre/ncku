#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include "../include/builtin.h"
#include "../include/command.h"
#include "../include/task.h"
#include "../include/function.h"
#include <ucontext.h>
#include <signal.h>
#include <sys/time.h>


#define STACKSIZE 102400

int help(char **args)
{
	int i;
    printf("--------------------------------------------------\n");
  	printf("My Little Shell!!\n");
	printf("The following are built in:\n");
	for (i = 0; i < num_builtins(); i++) {
    	printf("%d: %s\n", i, builtin_str[i]);
  	}
	printf("%d: replay\n", i);
    printf("--------------------------------------------------\n");
	return 1;
}

int cd(char **args)
{
	if (args[1] == NULL) {
    	fprintf(stderr, "lsh: expected argument to \"cd\"\n");
  	} else {
    	if (chdir(args[1]) != 0)
      		perror("lsh");
	}
	return 1;
}

int echo(char **args)
{
	bool newline = true;
	for (int i = 1; args[i]; ++i) {
		if (i == 1 && strcmp(args[i], "-n") == 0) {
			newline = false;
			continue;
		}
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
	}
	if (newline)
		printf("\n");

	return 1;
}

int exit_shell(char **args)
{
	return 0;
}

int record(char **args)
{
	if (history_count < MAX_RECORD_NUM) {
		for (int i = 0; i < history_count; ++i)
			printf("%2d: %s\n", i + 1, history[i]);
	} else {
		for (int i = history_count % MAX_RECORD_NUM; i < history_count % MAX_RECORD_NUM + MAX_RECORD_NUM; ++i)
			printf("%2d: %s\n", i - history_count % MAX_RECORD_NUM + 1, history[i % MAX_RECORD_NUM]);
	}
	return 1;
}

bool isnum(char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
    	if(str[i] >= 48 && str[i] <= 57)
			continue;
        else
		    return false;
  	}
  	return true;
}

int mypid(char **args)
{
	char fname[BUF_SIZE];
	char buffer[BUF_SIZE];
	if(strcmp(args[1], "-i") == 0) {

	    pid_t pid = getpid();
	    printf("%d\n", pid);
	
	} else if (strcmp(args[1], "-p") == 0) {
	
		if (args[2] == NULL) {
      		printf("mypid -p: too few argument\n");
      		return 1;
    	}

    	sprintf(fname, "/proc/%s/stat", args[2]);
    	int fd = open(fname, O_RDONLY);
    	if(fd == -1) {
      		printf("mypid -p: process id not exist\n");
     		return 1;
    	}

    	read(fd, buffer, BUF_SIZE);
	    strtok(buffer, " ");
    	strtok(NULL, " ");
	    strtok(NULL, " ");
    	char *s_ppid = strtok(NULL, " ");
	    int ppid = strtol(s_ppid, NULL, 10);
    	printf("%d\n", ppid);
	    
		close(fd);

  	} else if (strcmp(args[1], "-c") == 0) {

		if (args[2] == NULL) {
      		printf("mypid -c: too few argument\n");
      		return 1;
    	}

    	DIR *dirp;
    	if ((dirp = opendir("/proc/")) == NULL){
      		printf("open directory error!\n");
      		return 1;
    	}

    	struct dirent *direntp;
    	while ((direntp = readdir(dirp)) != NULL) {
      		if (!isnum(direntp->d_name)) {
        		continue;
      		} else {
        		sprintf(fname, "/proc/%s/stat", direntp->d_name);
		        int fd = open(fname, O_RDONLY);
        		if (fd == -1) {
          			printf("mypid -p: process id not exist\n");
          			return 1;
        		}

        		read(fd, buffer, BUF_SIZE);
        		strtok(buffer, " ");
        		strtok(NULL, " ");
        		strtok(NULL, " ");
		        char *s_ppid = strtok(NULL, " ");
		        if(strcmp(s_ppid, args[2]) == 0)
		            printf("%s\n", direntp->d_name);

        		close(fd);
     		}
	   	}
    	
		closedir(dirp);
	
	} else {
    	printf("wrong type! Please type again!\n");
  	}
	
	return 1;
}

int add(char **args)	//add {task_name} {function_name} {priiority}
{
	printf("Task %s is ready.\n", args[1]);

	struct Task *task = (struct Task *)malloc(sizeof(struct Task));	//id start from 1
	task->id = ++g_id_num;
	strcpy(task->name, args[1]);
	task->burst_time = task->wait_time = 0;
	task->turnaround = 0;
	task->check_r = 0;
	task->check_sleep = 0;
	task->resource[0] = -1;
	for(int i=0; i<8; i++)
		task->occupied_resource[i] = 0;
	task->resource_len = 0;
	task->priority = -1;
	char *stack;
	stack = (char *)malloc(sizeof(char) * (STACKSIZE));
	task->context.uc_stack.ss_sp = stack;
    task->context.uc_stack.ss_size = STACKSIZE;
	task->context.uc_stack.ss_flags = 0;
	task->context.uc_link = &context_original;	// when use swap, maybe
	getcontext(&(task->context));	//??

	// function name
	if(args[3]!=NULL)
		task->priority = atoi(args[3]);
	else	
		task->priority = -1;
	

	//make context, store it
	if(!strcmp(args[2], "task1"))
		makecontext(&task->context, task1, 0);
	else if(!strcmp(args[2], "task2"))
		makecontext(&task->context, task2, 0);
	else if(!strcmp(args[2], "task3"))
		makecontext(&task->context, task3, 0);
	else if(!strcmp(args[2], "task4"))
		makecontext(&task->context, task4, 0);
	else if(!strcmp(args[2], "task5"))
		makecontext(&task->context, task5, 0);
	else if(!strcmp(args[2], "task6"))
		makecontext(&task->context, task6, 0);
	else if(!strcmp(args[2], "task7"))
		makecontext(&task->context, task7, 0);
	else if(!strcmp(args[2], "task8"))
		makecontext(&task->context, task8, 0);
	else if(!strcmp(args[2], "task9"))
		makecontext(&task->context, task9, 0);
	else if(!strcmp(args[2], "test_exit"))
		makecontext(&task->context, test_exit, 0);
	else if(!strcmp(args[2], "test_resource1"))
		makecontext(&task->context, test_resource1, 0);
	else if(!strcmp(args[2], "test_resource2"))
		makecontext(&task->context, test_resource2, 0);
	else
		makecontext(&task->context, test_sleep, 0);

	
	if(algorithm==1)
		enqueue_sort(task, Q_ready);
	else
		enqueue(task, Q_ready, 0);

	struct Task *temp = Q_ps;
    while(temp->order_next){
        temp = temp->order_next;
    }
	temp->order_next = task;
	return 1;
}

int del(char **args)	// del {task_name}
{
	printf("del %s\n", args[1]);
	finish_all++;
	dequeue(args[1]);

	return 1;
}

int ps(char **args)
{
	printf(" TID|   name|     state| running| waiting| turnaround| resources| priority\n");
	printf("------------------------------------------------------------------------\n");

	//ready:0, running:1, waiting:2, terminated:-1
	int r_none = 1;
	struct Task *tmp = Q_ps->order_next;
	for(int i=1; i<=g_id_num; i++){
		printf("%4d|     %s|", i, tmp->name);
		switch(tmp->state){
			case 0:
				printf("      READY|");
				break;
			case 1:
				printf("    RUNNUNG|");
				break;
			case 2:
				printf("    WAITING|");
				break;
			case -1:
				printf("  TERMINATED|");
				break;
			default:
				printf("no match");
		}
		printf("%8d|%8d|", tmp->burst_time, tmp->wait_time);
		if(tmp->state==-1)
			printf("%10d|", tmp->turnaround);
		else	
			printf("      none|");
		for(int k=0; k<8; k++){
			if(tmp->occupied_resource[k]){
				printf(" %d", k);
				r_none = 0;
			}
			else
				printf(" ");
		}
		if(r_none)
			printf("none");
		printf("|");
		if(tmp->priority>-1)
			printf("%10d\n", tmp->priority);
		else
			printf("\n");


		tmp = tmp->order_next;
	}
	return 1;
}

int start(char **args)
{
	crl_z = 0;
	printf("Start simulation\n");
	
	getcontext(&context_original);
	if(crl_z)
		return 1;
	if(finish_all==g_id_num){
		printf("Simulation Over.\n");
		return 1;
	}
	if(algorithm==0)
		FCFS();
	else if(algorithm==2)
		RR();
	else{
		PP();
	}

	setcontext(&context_original);	
	return 1;
}

const char *builtin_str[] = {
 	"help",
 	"cd",
	"echo",
 	"exit",
 	"record",
	"mypid",
	"add",
	"del",
	"ps",
	"start"
};

const int (*builtin_func[]) (char **) = {
	&help,
	&cd,
	&echo,
	&exit_shell,
  	&record,
	&mypid,
	&add,
	&del,
	&ps,
	&start
};

int num_builtins() {
	return sizeof(builtin_str) / sizeof(char *);
}
