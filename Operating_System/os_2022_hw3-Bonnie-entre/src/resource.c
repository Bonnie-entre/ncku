#include "../include/resource.h"
#include "../include/task.h"
#include <stdio.h>
#include <stdbool.h>


void get_resources(int count, int *resources)
{
    // check available
    int available = 1;
    int arr_size = count;
    for(int i=0; i<arr_size; i++)
        if(!available_list[resources[i]]){
            available = 0;
            break;
        }
        
    Q_run->next->resource_len = count;  

    // assign resource or not
    if(available){
        for(int i=0; i<arr_size; i++){
            printf("Task %s gets resource %d\n",Q_run->next->name, resources[i]);
            available_list[resources[i]] = false;
            Q_run->next->occupied_resource[resources[i]] = 1;
            Q_run->next->resource[i] = -1;
        }
    }
    else{
        printf("Task %s is waiting resources.\n", Q_run->next->name);

        Q_run->next->check_r = 1;                        // check resource
        for(int i=0; i<arr_size; i++)
            Q_run->next->resource[i] = resources[i];
        
        struct Task *tmp = Q_run->next;
        enqueue(Q_run->next, Q_wait, 2);
        Q_run->next = NULL;

        swapcontext(&tmp->context, &context_original);
    }

    return ;
}

void release_resources(int count, int *resources)
{
    
    for(int i=0; i<count; i++){
        printf("Task %s releases resource %d.\n", Q_run->next->name, resources[i]);
        available_list[resources[i]] = true;
        Q_run->next->occupied_resource[resources[i]] = 0;
    }

    Q_run->next->resource_len = -1;     //for ps

}
