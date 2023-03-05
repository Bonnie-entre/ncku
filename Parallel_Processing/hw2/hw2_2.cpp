// gg 道地一行
// d + G 全選刪掉
// #include <stdio.h>     // printf()
// #include <limits.h>    // UINT_MAX
// #include <stdlib.h>
#include <climits>
#include <cstdlib>
// #include <time.h>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <mpi.h>
using namespace std;



int main (int argc, char *argv[]) {
    int i;               /* loop variable (32 bits) */
   int id = 0;           /* process id */
   int numprocs;
   int num;

   MPI_Init(&argc,&argv);
   MPI_Comm_size(MPI_COMM_WORLD,&numprocs);  //total computer num
   MPI_Comm_rank(MPI_COMM_WORLD,&id);  //which computer
   
    srand(time(NULL));
    int* send_a=(int*)malloc(num*sizeof(int));
    for(int i=0; i<num; i++)
        send_a[i] = rand() % 1000 + 1;
    int* recv_a=(int*)malloc(num/numprocs*sizeof(int));     //用來接收的陣列

    //每個process會接收到的陣列大小 = num/numprocs
    int* recv_count=(int*)malloc(num/numprocs*sizeof(int));     //一個 process 一個數據量
    int* disp_odd=(int*)malloc(num/numprocs*sizeof(int));       //照disp位置分給大家
    for(int i=0; i<num/numprocs; i++){
        disp_odd[i] = i * num/numprocs;
        recv_count[i] = num/numprocs;
    }
    int* disp_even=(int*)malloc(num/numprocs*sizeof(int));       //照disp位置分給大家
    for(int i=0; i<num/numprocs-1; i++)
        disp_even[i] = i * num/numprocs + 1;


    // is that right allocate number?? we need to allocate odd - even
    int step_count = 1;
    int sort_flag = 1;
    while(sort_flag){
        if(id==0){
                scanf("%d", &num);
                for(int i=1; i<numprocs; i++){
                    MPI_Send(&num,1,MPI_LONG_LONG, i ,0,MPI_COMM_WORLD);
                }
                if(step_count%2)
                    MPI_Scatterv(send_a, recv_count, disp_odd, MPI_INT, recv_a, num/numprocs, MPI_INT, 0, MPI_COMM_WORLD);
                else
                    MPI_Scatterv(send_a, recv_count, disp_even, MPI_INT, recv_a, num/numprocs, MPI_INT, 0, MPI_COMM_WORLD);
            } else{
                MPI_Recv(&num, 1, MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            }

        // sort, in each process
        sort(recv_a, recv_a+num/numprocs);


        // when to gather???


        // gather
        int* send_buf=(int*)malloc(num*sizeof(int));     //用來接收的陣列
        for(int i=0; i<num; i++)
            send_buf[i] = i;
        int* recv_buf=(int*)malloc(num*sizeof(int));     //用來接收的陣列


        if (id == 0)
        {
            // b = malloc(n * sizeof(int));
            MPI_Gather(send_a, num/numprocs, MPI_INT, recv_buf, num/numprocs, MPI_INT, 0, MPI_COMM_WORLD);
            cout << "I am result: " << endl;
            for (i = 0; i < num; i++)
            {
                cout << recv_buf[i] << " ";
            }
            cout << endl;

            // check sort 
            int pre;
            sort_flag = 0;
            for(int i=0 ;i<num; i++){
                if(pre>recv_buf[i]){
                    sort_flag = 1;
                    break;
                }
                pre = recv_buf[i];
            }

            step_count++;
        }
        else
        {
            MPI_Gather(send_a, num/numprocs, MPI_INT, recv_buf, num/numprocs, MPI_INT, 0, MPI_COMM_WORLD);
        }

        
        // if(well sort)
        //     sort = 0;

    }


    // // debug
    // for (i = 0; i < num/numprocs; i++)
    // {
    //     cout << recv_a[i];
    // }
    // cout << "this is process " << id << endl << endl ;



   // time record
   double time_start = 0.0, time_total = 0.0;
   if(id==0){
      time_start = MPI_Wtime();
   }

    // result
   if (id == 0) {
        time_total = MPI_Wtime() - time_start; 
        cout << "Sorted number: ";
        for(int i=0; i<num; i++)
            cout << recv_a[i] << " ";
        cout << endl << "total process time = " << time_total << endl;
        fflush(stdout);
   }

   MPI_Finalize();

   return 0;

    
}
