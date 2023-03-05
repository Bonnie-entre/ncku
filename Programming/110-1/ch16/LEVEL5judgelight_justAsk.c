#include <stdio.h>
#include <stdlib.h>

struct ESPer {
    char name[64];
    int level;
};

int cmp(const void *a, const void *b);
void sort_level(struct ESPer *arr, int length);

int main()
{
    int n;
    struct ESPer tokiwadai[100];

    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        scanf("%d %s", &(tokiwadai[i].level), tokiwadai[i].name);
    }

    sort_level(tokiwadai, n);

    for(int i = 0;i < n;++i) {
        printf("%d %s\n", tokiwadai[i].level, tokiwadai[i].name);
    }

    return 0;
}

int cmp(const void *a, const void *b) {
    struct ESPer *aa=(struct ESPer *)a;          //不懂為什麼要加括弧內的，固定用法嗎？ //因為void
    struct ESPer *bb=(struct ESPer *)b;
    return aa->level > bb->level;   // 大於 return 1; 小於 －１
    
    // return *(int *)a > *(int *)b;     //不懂括弧內的是什麼
}

void sort_level(struct ESPer *arr, int length) {
    qsort(arr, length,sizeof(struct ESPer), cmp);
}

