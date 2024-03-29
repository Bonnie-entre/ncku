#include <stdio.h>
#include <stdlib.h>
#define MESSAGE_LENGTH 64
#define NAME_LENGTH 10

struct timestamp {
    int hour, minute;
};

struct message_info {
    struct timestamp time;
    char name[NAME_LENGTH];
    char message[MESSAGE_LENGTH];
};

int cmp(const void *a, const void *b);
void sort_message(struct message_info *m, int *total);

int main(void) {
    struct message_info m[100];
    int total;
    scanf("%d", &total);
    for(int i = 0; i < total; i++)
        scanf("%d:%d %s %[^\n]", &m[i].time.hour, &m[i].time.minute, m[i].name, m[i].message);
    sort_message(m, &total);
    for(int i = 0; i < total; i++)
        printf("%02d:%02d %s %s\n", m[i].time.hour, m[i].time.minute, m[i].name, m[i].message);
    return 0;
}

int cmp(const void* a, const void* b) {
    struct message_info *aa=(struct message_info *)a;         
    struct message_info *bb=(struct message_info *)b;
    if((aa->time.hour*60+aa->time.minute) > (bb->time.hour*60+bb->time.minute)){
        return 1;
    }

    return -1;
}

void sort_message(struct message_info *m, int *total) {
// m is array of each message information wrapped in a struct
// total is the number of total message

    qsort(m, *total, sizeof(struct message_info), cmp);
}