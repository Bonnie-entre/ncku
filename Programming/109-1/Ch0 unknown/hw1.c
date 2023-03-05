#include <stdio.h>
int main(void)
{
    int A, B, C, D;

    scanf("%d %d %d %d", &A, &B, &C, &D);

    printf("%04d %04d %04d",A,(A-B+C),(A-B+C-D));

    return 0;
}
