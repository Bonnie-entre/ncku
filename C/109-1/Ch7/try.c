#include<stdio.h>
int year,age, weight;
float BMI,x,height;
int main(){
    scanf("%d %f %d",&year,&height,&weight);
    x=(float)(weight*10000/height/height);
    BMI= (int)(10*x+0.5)/10.0;
    printf("Age = %d\nHeight = %dcm\nWeight = %dkg\nBMI = %.1f\n",age=2020-year+1,(int)height,weight,x);
    
    if (age<19||age>36){
        printf("Not a Draftee (age < 19 or age > 36 years old)\nNo need to perform Military Service");
    }
    else if (BMI<=31 && BMI>=17) {
        printf("Physical Status of Regular Service Draftees\n");
        if (year<=1993) {printf("1 year of Regular Service");}
        else {printf("4 months of Regular Service");}
    }
    else if ((BMI<17 && BMI>=16.5)||(BMI<=31.5 && BMI>31)){
        printf("Physical Status of Substitute Service Draftees\n");
        if (year<=1993){ printf("Substitute Services");}
        else {printf("Replacement Service");}
    }
    
    else{
        printf("Physical Status of Military Service Exemption\nExemption from Military Service");
    }
    
    return 0;
}
