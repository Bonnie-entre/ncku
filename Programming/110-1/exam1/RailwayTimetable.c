#include<stdio.h>

int main () {
    long long hi, mi, trainNum; //initial time
    long long a[31], h[31], m[31], time[31], mins[31], arrive[31];
    
    scanf("%2lld:%2lld %lld", &hi, &mi, &trainNum);
    mi = hi*60 + mi;

    for(int i=0; i<trainNum; i++)
    {
    	scanf("%lld %lld:%lld %lld", &a[i], &h[i], &m[i], &time[i]);
        mins[i] = h[i]*60+m[i];
        arrive[i] = mins[i]+time[i];
    }
        
    long long obj=100000;
    long long objA = 100000;
    for(int i=0; i<trainNum; i++)
    {
        if(mins[i]>=mi)
        {
            if(arrive[i]<obj)
            {
                obj = arrive[i];
                objA = i;
            }
        }
    }

    printf("%lld", a[objA]);
    
    //Debug
    //printf("\n\n%2d:%2d\n", hi, mi);
    //printf("Obj time %d\n", mi);
    //for(int i=0; i<trainNum; i++)
    //{
    //    printf("%d %d:%d %d %d %d\n", a[i], h[i], m[i], time[i], mins[i], arrive[i]);
    //}
    return 0;
}

