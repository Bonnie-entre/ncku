#include <stdio.h>
#include <stdlib.h>

struct node {
    int val;
    struct node* next;
};
struct node* head = NULL;
struct node* tail = NULL;
void MoveToTail();

int main(void) { 
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        struct node* tmp = malloc(sizeof(struct node));
        scanf("%d", &tmp->val);
        tmp->next = NULL;
        if(i == 1)
            head = tmp;
        else
            tail->next = tmp;
        tail = tmp;
    }
    MoveToTail();
    for(struct node* cur = head; cur != NULL; cur = cur->next)
        printf("%d ", cur->val); 
    return 0;
}

void MoveToTail() {
    // "struct node* head" and "struct node* tail" are in global
    // you can use this two pointers to do this problem
    
    // find max number
    int max = 0;
    for(struct node* cur = head; cur != NULL; cur = cur->next){
        if( cur->val > max ){
            max = cur->val;
        }
    }
    
    // swap to tail
    for(struct node* cur = head, *pre=NULL; cur != tail; pre = cur, cur = cur->next){   // tail omit
        if( cur->val==max ){
            if( pre==NULL){     // object is head
                head = cur->next;
            }
            else{
                pre->next = cur->next;
            }
            cur->next = tail->next;
            tail->next = cur;
            tail = cur;
            return;
        }
    }
}