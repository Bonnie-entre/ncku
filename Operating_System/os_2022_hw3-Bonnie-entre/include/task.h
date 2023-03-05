#include <ucontext.h>
#include <signal.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include "./resource.h"

#ifndef TASK_H
#define TASK_H


struct Task
{
    int id;
    char name[10];
    struct Task *next;
    struct Task *order_next;
    
    int state;          //ready:0, running:1, waiting:2, terminated:-1
    int turnaround;     // = wait_time(in Q_ready) + burst_time(in Q_run) + (in Q_wait);
    int wait_time;      // not finish: -1
    int burst_time;     // not finish: -1
    int priority;
    int resource[8];
    int occupied_resource[8];
    int resource_len;
    int check_r;          // resource: -1, time = ms
    int check_sleep;
    ucontext_t context;
};


// global variables
int crl_z;
int finish_all;
ucontext_t context_original;
// char *algorithm;
int algorithm;
int g_id_num;
struct Task *Q_run;
struct Task *Q_ready;
struct Task *Q_wait;
struct Task *Q_ter;
struct Task *Q_ps;

int time_count;               
int qt;                 // for RR - 3 * 10ms

bool available_list[8];

// function
void crl_Z();
void timehandler();

void FCFS();
void RR();
void PP();
int dequeue(char* task_name);

int enqueue_sort(struct Task *task, struct Task *Q_r);
int enqueue(struct Task *task, struct Task *Q_dest, int _state);     //struct Queue *queue, 

void task_sleep(int);
void task_exit();

#endif
