#include <stdio.h>                                                                                                                           
#include <stdlib.h>
#include <math.h>

int* Returns(int n); 

int main(int argc, char *argv[])
{
    int in, *out;
    scanf("%d", &in);
    out = Returns(in);
    for(int i = 0;i < in;++i) {
        printf("out[%d] = %d\n", i, out[i]);
    }   
    free(out);
    return 0;
}

int* Returns(int n) {
	int *out = malloc(n*sizeof(int));
    if(out==NULL){
    	exit(EXIT_FAILURE);
    }
    for(int i=0; i<n; i++){
    	*(out+i) = 1*pow(i,2);
    }
    
    return out;
}

