#include "../include/task.h"

void timehandler(){
    time_count += 1;
    // printf("time++: %d", time_count);

    // calculate wait time & burst time
    if(Q_run->next){
        Q_run->next->burst_time ++;                     //calculate burst time
        Q_run->next->turnaround ++;
        struct Task *temp_ready = Q_ready->next;
        while(temp_ready){                              //calculate wait time
            temp_ready->wait_time ++;
            temp_ready = temp_ready->next;
        }
    }
    
    // turnarround ++, once not Q_ter
    struct Task *tmp = Q_ready->next;
    while(tmp){
        tmp->turnaround ++;
        tmp = tmp->next;
    }
    tmp = Q_wait->next;
    while(tmp){
        tmp->turnaround ++;
        tmp->check_sleep --;
        tmp = tmp->next;
    }


    // check resource & check sleep
    int available;
    tmp = Q_wait;
    while (tmp->next)
    {
        available = 1;
        if(tmp->next->check_r){             // if available, switch from Q_wait to Q_ready

            for(int i=0; i<tmp->next->resource_len; i++){
                if(!available_list[tmp->next->resource[i]]){
                    available = 0;
                    break;
                }
            }

            if(available){
                struct Task *t = tmp->next->next;
                if(algorithm==1)
                    enqueue_sort(tmp->next, Q_ready);
                else
                    enqueue(tmp->next, Q_ready, 0);
                tmp->next = t;    //delete task from Q_wait
            }
            else
                tmp = tmp->next;
            
        }
        else if(tmp->next->check_sleep<=0){
            // printf("task %s is checking sleep(=%d)\n", tmp->next->name,tmp->next->check_sleep);
            
            struct Task *follow = tmp->next->next;
            if(algorithm==1)
                enqueue_sort(tmp->next, Q_ready);
            else
                enqueue(tmp->next, Q_ready, 0);

            tmp->next = follow;        //delete task from Q_wait
        }
        else
            tmp = tmp->next;
    }

    // check RR quantum time = 30ms
    qt--;
    if(algorithm==2){
        if(qt <= 0){
            struct Task *tmp = Q_run->next;
            if(tmp){
                enqueue(tmp, Q_ready, 0);
                Q_run->next = NULL;
                swapcontext(&tmp->context, &context_original);
            }
            else
                qt=3;
        }
    }
    // PP, run -> wait
    else if (algorithm==1)
    {
        if(Q_ready->next != NULL && Q_run->next!=NULL && (Q_ready->next->priority < Q_run->next->priority)){
            struct Task *tmp = Q_run->next;
            enqueue_sort(tmp, Q_ready);
            Q_run->next = NULL;
            swapcontext(&tmp->context, &context_original);
        }
    }
    
}


void crl_Z(){
    crl_z = 1;

    if(Q_run->next != NULL)
        swapcontext(&Q_run->next->context, &context_original);
    else
    	setcontext(&context_original);	
}


void FCFS(){

    if(crl_z )
        crl_z = 0;

    if(Q_run->next)     //for cr_z -> start
        setcontext(&Q_run->next->context);
    else if(Q_ready->next){
        Q_run->next = Q_ready->next;                        // switch to Q_run from Q_ready
        Q_ready->next = Q_ready->next->next;
        Q_run->next->next = NULL;                               // delete from Q_ready
        printf("Task %s is running.\n", Q_run->next->name);

        int avai = 1;
        if(Q_run->next->check_r){
            for(int i=0; i<Q_run->next->resource_len; i++)
                if(!available_list[Q_run->next->resource[i]]){
                    avai = 0;
                    break;
                }
            if(avai){
                Q_run->next->check_r = 0;
                get_resources(Q_run->next->resource_len, Q_run->next->resource);
                setcontext(&Q_run->next->context);  
            }
            else{
                printf("Task %s is waiting resources.\n", Q_run->next->name);
                enqueue(Q_run->next, Q_wait, 2);
                Q_run->next = NULL;
            }
        }
    }
    else{
        printf("CPU idle.\n");
        while (!Q_ready->next)
        {
            ;
        }
    }

}


void RR(){
    qt = 3;
    
    if(crl_z )
        crl_z = 0;

    if(Q_run->next)     //for cr_z -> start
        setcontext(&Q_run->next->context);
    else if(Q_ready->next){
        Q_run->next = Q_ready->next;                        // switch to Q_run from Q_ready
        Q_ready->next = Q_ready->next->next;
        Q_run->next->next = NULL;                               // delete from Q_ready
        printf("Task %s is running.\n", Q_run->next->name);

        int avai = 1;
        if(Q_run->next->check_r){
            for(int i=0; i<Q_run->next->resource_len; i++)
                if(!available_list[Q_run->next->resource[i]]){
                    avai = 0;
                    break;
                }
            if(avai){
                Q_run->next->check_r = 0;
                get_resources(Q_run->next->resource_len, Q_run->next->resource);
                setcontext(&Q_run->next->context);  
            }
            else{
                printf("Task %s is waiting resources.\n", Q_run->next->name);
                enqueue(Q_run->next, Q_wait, 2);
                Q_run->next = NULL;
            }
        } 
       
    }
    else{
        printf("CPU idle.\n");
        while (!Q_ready->next)
        {
            ;
        }
    }

}


void PP(){
    if(crl_z )
        crl_z = 0;

    if(Q_run->next)     //for crl_z -> start
        setcontext(&Q_run->next->context);
    else if(Q_ready->next){
        Q_run->next = Q_ready->next;                        // switch to Q_run from Q_ready
        Q_ready->next = Q_ready->next->next;
        Q_run->next->next = NULL;                               // delete from Q_ready
        printf("Task %s is running.\n", Q_run->next->name);


        int avai = 1;
        if(Q_run->next->check_r){
            for(int i=0; i<Q_run->next->resource_len; i++)
                if(!available_list[Q_run->next->resource[i]]){
                    avai = 0;
                    break;
                }
            if(avai){
                Q_run->next->check_r = 0;
                get_resources(Q_run->next->resource_len, Q_run->next->resource);
                setcontext(&Q_run->next->context);  
            }
            else{
                printf("Task %s is waiting resources.\n", Q_run->next->name);
                enqueue(Q_run->next, Q_wait, 2);
                Q_run->next = NULL;
            }
        }
        
    }
    else{
        printf("CPU idle.\n");
        while (!Q_ready->next)
        {
            ;
        }
    }

}



int enqueue_sort(struct Task *task, struct Task *Q_r){

    struct Task *temp = Q_r;
    while(temp->next && temp->next->priority <= task->priority)      
        temp = temp->next;

    task->state = 0;
    task->next = temp->next;
    temp->next = task;

    return 1;
}


int enqueue(struct Task *task, struct Task *Q_dest, int _state){     //also call by FCFS()
    struct Task *temp = Q_dest;
    while(temp->next){
        temp = temp->next;
    }
    task->state = _state;
    task->next = NULL;
    temp->next = task;

    return 1;
};


int dequeue(char* task_name){

    struct Task *temp_ready = Q_ready;
    struct Task *temp;

    while(temp_ready->next){
        if(!strcmp(task_name, temp_ready->next->name)){
            temp = temp_ready->next;
            temp_ready->next = temp_ready->next->next;      //delete task from original Q
            break;
        }
        temp_ready = temp_ready->next;
    }

    enqueue(temp, Q_ter, -1);                              //inqueue to Q_term

    return 1;
}



void task_sleep(int ms)
{
    printf("Task %s goes to sleep.\n", Q_run->next->name);
    Q_run->next->check_sleep = ms;

    struct Task *tmp = Q_run->next;

    enqueue(Q_run->next, Q_wait, 2);

    Q_run->next = NULL;

    swapcontext(&tmp->context, &context_original);    

    return ;
}


void task_exit()
{
    printf("Task %s has terminated.\n", Q_run->next->name);
    enqueue(Q_run->next, Q_ter, -1);

    Q_run->next = NULL;                             // clean Q_run
    finish_all++;

    setcontext(&context_original);
}
