#include<stdio.h>

int main(){
    int A,B,C,me;
    scanf("%d %d %d", &A,&B,&C);
    if (A>B && A<C) me=A;
    else if (A<B && A>C) me=A;
    else if (B>C && B<A) me=B;
    else if (B<C && B>A) me=B;
    else me=C;

    me = (A>B && A<C ? A:me);
    me = (A<B && A>C ? A:me);
    me = (B>C && B<A ? B:me);
    me = (B<C && B>A ? B:me);
    me = (C>B && C<A ? C:me);
    me = (C<B && C>A ? C:me);
    printf("%d",me);
    
    
    return 0;
}


//2020.11.11
#include<stdio.h>
int M,m,me,a,b,c;
int main(){
    scanf("%d %d %d",&a,&b,&c);
    M= (a>b? a:b);
    m= (a>b? b:a);
    if (M>c) me=(c>m? c:m);
    else me= M;
    printf("%d",me);
    return 0;
}
