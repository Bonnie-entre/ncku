#include<stdio.h>
int m,days,n,i,x;
int main(){
    scanf("%d",&m);
   
    printf("Sun Mon Tue Wed Thu Fri Sat \n");
    
    switch(m){
    	case 1:case 7:
            x =12;
            printf("            ");
            days =31;
            break;
        case 3:
            x =0;
            days =31;
            break;
        case 5:
            x =20;
            printf("                    ");
            days =31;
            break;     
        case 8: 
            x =24;
            printf("                        ");
            days =31;
            break;
        case 10: 
            x =16;
            days =31;
            printf("                ");
            break;
        case 12:
            x =8;
            days =31;
            printf("        ");
            break;
        case 2:
            x =24;
            days =29;
            printf("                        ");
            break;
        case 4:
        	x=12;
            days =30;
            printf("            ");
            break;
        case 6:
            x =4;
        	days =30;
            printf("    ");
            break;
        case 9:
            x =8;
        	days =30;
            printf("        ");
            break;
        case 11:
            x =0;
            days =30;
            break;
    }
    for (n=0+x,i=0;n<=days*4+x && i<=days;i++){
        if (n==28) printf("\n");
        if (n==56) printf("\n");
        if (n==84) printf("\n");
        if (n==112) printf("\n");
        if (n==140) printf("\n");
        switch(i){
            case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 8:case 9:
                printf("  %d ", i);
                n+=4;
                break;
            case 10:case 11:case 12:case 13:case 14:case 15:case 16:case 17:case 18:case 19:
            case 20:case 21:case 22:case 23:case 24:case 25:case 26:case 27:case 28:case 29:
            case 30:case 31:
                printf(" %d ", i); 
                n+=4;
                break;
        }
    }
    return 0;
}


//2020.11.11
#include<stdio.h>
int month,i,day,s;
int main(){
    scanf("%d",&month);
    printf("Sun Mon Tue Wed Thu Fri Sat \n");
    s=0;
    switch(month){
        case 1: case 7:  
            printf("            ");s+=12; day=31; break; 
        case 3: day=31; break;
        case 5: printf("                    ");s+=20; day=31; break;
        case 8: printf("                        ");s+=24; day=31; break;
        case 10: printf("                ");s+=16; day=31; break;
        case 12: printf("        ");s+=8; day=31; break;
        case 2: printf("                        ");s+=24;day=29; break;
        case 4: printf("            ");s+=12; day=30; break;
        case 6: printf("    ");s+=4; day=30; break;
        case 9: printf("        ");s+=8; day=30; break;
        case 11: day=30; break;   
    }
    for (i=1;i<=day;i++,s+=4){
        if (s==28||s==56||s==84||s==112||s==140) {printf("\n");}
        printf("%3d ",i);
    }
    return 0;
}



