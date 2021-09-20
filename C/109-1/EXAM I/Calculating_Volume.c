#include<stdio.h>
#include<math.h>
int mode;
float length,ans,w,h,r;
double x;
int main(){
    scanf("%d",&mode);
    

    switch(mode){
        case 1:
            scanf("%f",&length);
            ans =length*length*length;
            ans = (ans*100+0.5)/100.0;
            printf("%.2f",ans);
            break;
        case 2:
            scanf("%f %f %f",&length,&w,&h);
            ans =length*w*h;
            ans = (ans*100+0.5)/100.0;
            printf("%.2f",ans);
            break;           
        case 3:
            scanf("%f %f",&r,&h);
            ans =3.14*r*r*h;
            ans = (ans*100+0.5)/100.0;
            printf("%.2f",ans);
            break;
        case 4:
            scanf("%f",&length);
            x =sqrt(2)/12*length*length*length;
            x = (x*100+0.5)/100.0;
            printf("%.2lf",x);
            break;
    }
    
    
    
    return 0;
}
