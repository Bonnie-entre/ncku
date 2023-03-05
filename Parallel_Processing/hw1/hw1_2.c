// gg 道地一行
// d + G 全選刪掉
#include <stdio.h>     // printf()
#include <limits.h>    // UINT_MAX
#include <stdlib.h>
#include <time.h>
#include "mpi.h"



int main (int argc, char *argv[]) {
    int i;               /* loop variable (32 bits) */
   int id = 0;           /* process id */
   int numprocs;
   long long num;

   MPI_Init(&argc,&argv);
   MPI_Comm_size(MPI_COMM_WORLD,&numprocs);  //total computer num
   MPI_Comm_rank(MPI_COMM_WORLD,&id);  //which computer
   
   if(id==0){
        scanf("%lld", &num);
        for(int i=1; i<numprocs; i++){
            MPI_Send(&num,1,MPI_LONG_LONG, i ,0,MPI_COMM_WORLD);
        }
   } else{
        MPI_Recv(&num, 1, MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
   }
   
   int each_comp_p = num/ numprocs;

   // time record
   double time_start = 0.0, time_total = 0.0;
   if(id==0){
      time_start = MPI_Wtime();
   }


   // which procs
   srand(time(NULL));
   int number_in_circle = 0;
    for (int toss = 0; toss < each_comp_p; toss++){
        double x = rand();
        double y = rand();
        x = (x/RAND_MAX) *2 -1;
        y = (y/RAND_MAX) *2 -1;
        double distance_squared = x*x + y*y;
        if (distance_squared <= 1) {
            number_in_circle++;
        }
    }


   int merge_dest, merge2;
   int num_i = numprocs, temp;
   int sum=number_in_circle;    //
   while(1){
      num_i = num_i/2;
      if(id < num_i){
         merge2 = id + num_i;
         MPI_Recv(&temp, 1, MPI_LONG_LONG, merge2, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
         sum += temp;
      } else if(id < 2*num_i){
         merge_dest = id - num_i;
         MPI_Send(&sum,1,MPI_LONG_LONG,merge_dest,0,MPI_COMM_WORLD);
      } else{
         break;
      }
   }


    
    double pi_estimate = 4 * sum/((double)num);

   // record time
   if (id == 0) {
        time_total = MPI_Wtime() - time_start; 
        //printf("pi is approximately %.16f, Error is %.16f\n",
        //pi, fabs(pi - PI25DT));
        printf("\n  Pi = %f \n\n", pi_estimate);
        printf("total process time = %f\n", time_total);
        fflush(stdout);
   }

   MPI_Finalize();

   // printf ("Process %d finished.\n", id);
   // fflush (stdout);
   // printf("\nA total of %d solutions were found.\n\n", count);
   return 0;

    
}
