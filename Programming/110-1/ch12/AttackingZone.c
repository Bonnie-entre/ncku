#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 1024

void convert_to_polar(int *coords, int N);

int main()
{
    int N, coords[MAX_N + 1][2];
    scanf("%d", &N);
    
    for (int i = 0; i < N; i++)
        scanf("%d%d", &coords[i][0], &coords[i][1]);
    
    
    convert_to_polar((int *) coords, N);
    
    return 0;
}

//atan()
void convert_to_polar(int *coords, int N)
{
    double x=0, y=0;
    for( int i=0; i<2*N; i++){
        if( i%2==0 ){
            x = *(coords+i);
        }
        else{
            y = *(coords+i);
            if(x>=0 && y>=0){
                printf("%.2f ", atan(y/x)*180/M_PI);
            }
            else if(x<0 && y>=0){
                printf("%.2f ", 180-atan(y/fabs(x))*180/M_PI);
            }
            else if(x<0 && y<0){
                printf("%.2f ", atan(fabs(y)/fabs(x))*180/M_PI+180);
            }
            else{
                printf("%.2f ", 360-atan(fabs(y)/x)*180/M_PI);
            }
            printf("%.2f\n", sqrt(pow(x,2)+pow(y,2)));
        }
    }
}