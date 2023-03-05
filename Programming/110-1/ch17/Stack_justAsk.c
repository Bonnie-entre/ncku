#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct element {
    int data;
    struct element *next;
};

void print_stack(struct element *top);
void push(struct element **top_p, int data);
struct element *pop(struct element **top_p);

int main(void) {
    struct element *top = NULL;
    int num, data;
    char command[5];
    scanf("%d", &num);
    while (num--) {
        scanf("%4s", command);
        if (strcmp(command, "push") == 0) {
            scanf("%d", &data);
            push(&top, data);
            // print_stack(top);
        }
        else if (strcmp(command, "pop") == 0) {
            struct element *e = pop(&top);
            free(e);
        }
    }
    print_stack(top);
    while (top) {
        struct element *ptr = top;
        top = top->next;
        free(ptr);
    }
    return 0;
}

void print_stack(struct element *top) {
    int size = 0;
    for (struct element *ptr = top; ptr != NULL; ptr = ptr->next)
        size++;
    printf("%d\n", size);
    for (struct element *ptr = top; ptr != NULL; ptr = ptr->next)
        printf("%d ", ptr->data);
}

void push(struct element **top_p, int data) {
    struct element * e = malloc(sizeof(struct element));
    if( e==NULL){
        printf("fail allocate");
    }
    e->data = data;
    e->next = *top_p;
    *top_p = e;
    // free(e);     //不能 free掉！
}

struct element *pop(struct element **top_p) {
    struct element * e = malloc(sizeof(struct element));     // e won't exist after f returns
    if( e==NULL){
        printf("fail allocate");
    }
    e = *top_p;
    *top_p = (*top_p)->next;
    // printf("%d %d\n", e->data, (*top_p)->next->data);    //為什麼不能print?? //  可能遇到NULL
    return e;
}