#include <stdio.h>     // printf()
#include <limits.h>    // UINT_MAX
#include "mpi.h"

int checkCircuit (int, int);

int main (int argc, char *argv[]) {
   int i;               /* loop variable (32 bits) */
   int id = 0;           /* process id */
   int count = 0;        /* number of solutions */
   int numprocs;

   MPI_Init(&argc,&argv);
   MPI_Comm_size(MPI_COMM_WORLD,&numprocs);  //total computer num
   MPI_Comm_rank(MPI_COMM_WORLD,&id);  //which computer
   
   int each_comp_p = 65536/ numprocs;

   // time record
   double time_start = 0.0, time_total = 0.0;
   if(id==0){
      time_start = MPI_Wtime();
   }

   // which procs
   for (i = each_comp_p*id; i <= each_comp_p*(id+1); i++) {
      count += checkCircuit (id, i);
   }

   int merge_dest, merge2;
   int num_i = numprocs, temp;
   int sum=count;
   while(1){
      num_i = num_i/2;
      if(id < num_i){
         merge2 = id + num_i;
         MPI_Recv(&temp, 1, MPI_INT, merge2, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
         sum += temp;
      } else if(id < 2*num_i){
         merge_dest = id - num_i;
         MPI_Send(&sum,1,MPI_INT,merge_dest,0,MPI_COMM_WORLD);
      } else{
         break;
      }
   }

   // record time
   if (id == 0) {
        time_total = MPI_Wtime() - time_start; 
        //printf("pi is approximately %.16f, Error is %.16f\n",
        //pi, fabs(pi - PI25DT));
        printf("\nA total of %d solutions were found.\n\n", sum);
        printf("total process time = %f\n", time_total);
        fflush(stdout);
   }

   MPI_Finalize();

   // printf ("Process %d finished.\n", id);
   // fflush (stdout);
   // printf("\nA total of %d solutions were found.\n\n", count);
   return 0;
}

/* EXTRACT_BIT is a macro that extracts the ith bit of number n.
 *
 * parameters: n, a number;
 *             i, the position of the bit we want to know.
 *
 * return: 1 if 'i'th bit of 'n' is 1; 0 otherwise 
 */

#define EXTRACT_BIT(n,i) ( (n & (1<<i) ) ? 1 : 0)


/* checkCircuit() checks the circuit for a given input.
 * parameters: id, the id of the process checking;
 *             bits, the (long) rep. of the input being checked.
 *
 * output: the binary rep. of bits if the circuit outputs 1
 * return: 1 if the circuit outputs 1; 0 otherwise.
 */

#define SIZE 16

int checkCircuit (int id, int bits) {
   int v[SIZE];        /* Each element is a bit of bits */
   int i;

   for (i = 0; i < SIZE; i++)
     v[i] = EXTRACT_BIT(bits,i);

   if (  (v[0] || v[1]) && (!v[1] || !v[3]) && (v[2] || v[3])
       && (!v[3] || !v[4]) && (v[4] || !v[5])
       && (v[5] || !v[6]) && (v[5] || v[6])
       && (v[6] || !v[15]) && (v[7] || !v[8])
       && (!v[7] || !v[13]) && (v[8] || v[9])
       && (v[8] || !v[9]) && (!v[9] || !v[10])
       && (v[9] || v[11]) && (v[10] || v[11])
       && (v[12] || v[13]) && (v[13] || !v[14])
       && (v[14] || v[15])  )
   {
      printf ("%d) %d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d \n", id,
         v[15],v[14],v[13],v[12],
         v[11],v[10],v[9],v[8],v[7],v[6],v[5],v[4],v[3],v[2],v[1],v[0]);
      fflush (stdout);
      return 1;
   } else {
      return 0;
   }
}