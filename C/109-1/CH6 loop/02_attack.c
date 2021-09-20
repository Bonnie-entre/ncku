#include<stdio.h>

int main(){
    int point_A, point_B, minusA, minusB;
    int attack;
    scanf("%d %d\n", &point_A , &point_B);
    
    for (;;){
    	switch (attack){
            case 0:
                scanf("%d", &minusB);
                if ((point_B-= minusB) <=0){
                    printf("A");
                    break;
                }
            case 1:
                scanf("%d", &minusA );
                if ((point_A-= minusA) <=0){
                    printf("B");
                    break;
                }
    
            
        }
    }

    return 0;
}


    /*---要計算的程式效率區域---*/
    

