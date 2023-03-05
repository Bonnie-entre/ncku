#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// #include <syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

//M*N, N*P

typedef struct my_data {
   int **m1;
   int **m2;
   int m1_r;    // M
   int m1_c;   //m1_c, N
   int m2_c;   //m2_c, P
   int **res;
} my_data;

my_data data;
int thread_num;
int **res;

// create Mutex
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

// 子執行緒函數
void *child(void *arg) {    
    // get data
    int thread_id = *(int * )arg;
    // printf("id=%d", thread_id);
    
    int M = data.m1_r;
    int N = data.m1_c;
    int P = data.m2_c;
    int res_size = M * P/ thread_num;
    // printf("num of elements=%d\n", res_size);
    
    int end_z = (thread_id+1)*res_size;
    if(thread_id==thread_num-1)     // when thread_num not the factor of M & P
        end_z = M*P;
        
    //check matrix
    // for(int i=0; i<M; i++){
    //     for(int j=0; j<N; j++)
    //         printf("%d ", data.m1[i][j]);
    //     printf("\n");
    // }

    pthread_mutex_lock( &mutex1 );      // lock

    // calcuate elements
    int i, j;
    for(int z=thread_id*res_size; z<end_z; z++){
        i = z/P;
        j = z%P;
        // printf("in child, thread_id=%d z=%d (i,j) = (%d,%d)\n",thread_id, z, i, j);
        for(int k=0; k<N; k++){
            // printf("(i,j)=%d,%d res=%d += %d * %d \n", i, j, res[i][j], data.m1[i][k], data.m2[k][j]);
            res[i][j] += data.m1[i][k] * data.m2[k][j];
        }
        // printf("result res[%d][%d]=%d\n", i, j, res[i][j]);
    }


    
    // activate proc_write
    FILE *fp = fopen("/proc/thread_info", "w");
    char buf[128] = {};
    snprintf(buf, 128, "%ld", thread_id);
    fwrite(buf, 1 , sizeof(buf) , fp );
    fclose(fp);

    // activate proc_read
    FILE *fp2;
    char buffer[1024];
    size_t numread;    
    fp2 = fopen("/proc/thread_info","r");
    numread = fread(buffer, sizeof(char), 1024, fp2);
    printf("\t%s\n", buffer);
    fclose(fp2);

    pthread_mutex_unlock( &mutex1 );    // unlock
    pthread_exit(NULL);
    
}


int main(int argc, char *argv[]) {
    struct timespec start, finish;
    double elapsed;

    clock_gettime(CLOCK_MONOTONIC, &start);


    // input parameters
    thread_num = atoi(argv[1]);
    char filename1[128];
    char filename2[128];
    snprintf(filename1, sizeof(filename1), "%s.txt", argv[2]);
    snprintf(filename2, sizeof(filename2), "%s.txt", argv[3]);    
    
    // load matrix 1
    int m1_r, m1_c, m2_r, m2_c;
    FILE *fp = NULL;
    fp = fopen(filename1, "r");
    fscanf(fp, "%d %d", &m1_r, &m1_c);
    int **matrix_1;
    matrix_1 = (int**)malloc(m1_r*sizeof(int*));
    for(int i=0;i<m1_r;i++){
        matrix_1[i]=(int*)malloc(m1_c*sizeof(int));
        for(int j=0; j<m1_c; j++)
            fscanf(fp, "%d", &matrix_1[i][j]);
    }
    fclose(fp);
    
    // load matrix 2
    fp = fopen(filename2, "r");
    fscanf(fp, "%d %d", &m2_r, &m2_c);
    int **matrix_2;
    matrix_2 = (int**)malloc(m2_r*sizeof(int*));
    for(int i=0;i<m2_r;i++){
        matrix_2[i]=(int*)malloc(m2_c*sizeof(int));
        for(int j=0; j<m2_c; j++)
            fscanf(fp, "%d", &matrix_2[i][j]);
    }
    fclose(fp);
    

    // Calculate
    res = (int**)malloc(m1_r*sizeof(int*));
    for(int i=0;i<m1_r;i++){
        res[i]=(int*)malloc(m2_c*sizeof(int));
        for(int j=0; j<m2_c; j++)
            res[i][j] = 0;
    }
    data.m1 = matrix_1;
    data.m2 = matrix_2;
    data.m1_c = m1_c;
    data.m2_c = m2_c;
    res = res;
    data.m1_r = m1_r;

    printf("PID:%d\n", getpid());

    // create Threads
    int thread_c;
    pthread_t thread[thread_num];
    int thred_id[thread_num];
    for(int i=0; i<thread_num; i++)
        thred_id[i] = i;

    for(int i=0; i<thread_num; i++){
        // printf("create thread%d\n", i);
        thread_c = pthread_create(&thread[i], NULL, child, (void*) &thred_id[i]);
        if(thread_c){
            printf("Error: thread%d unable to create", i);
        }
        
    }     

    // 等待子執行緒計算完畢
    for (int i = 0; i < thread_num; i++) {
        // printf("before check join%d\n", i);
        if (pthread_join(thread[i], NULL) != 0) {
            printf("ERROR : pthread%d join failed.\n", i);
            return (0);
        }
        // printf("after check join%d\n", i);
        
    }

    // write result     //why null
    fp = fopen("result.txt", "w");             
    fprintf(fp, "%d %d\n", m1_r, m2_c);
    for(int i=0;i<m1_r;i++){
        for(int j=0; j<m2_c; j++){
            // printf("%d ", res[i][j]);            
            fprintf(fp, "%d ", res[i][j]);
        }
        // printf("\n");
        fprintf(fp, "\n");        
    }
    fclose(fp);
     



    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Total runtime: %lf seconds\n", elapsed);
    printf("Due Date: 2022/11/25 23:59:59\r\n");
    return 0;
}


    // // check read
    // for(int i=0;i<m1_r;i++){
    //     for(int j=0; j<m1_c; j++){
    //         printf("%d ", matrix_1[i][j]);
            
    //     }
    //     printf("\n");
    // }