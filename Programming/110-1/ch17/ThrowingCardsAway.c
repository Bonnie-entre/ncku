#include<stdio.h>
#include<stdlib.h>

struct card
{
    int val;
    struct card * last;
    struct card * next;
};

int main(){
    int num, times;
    scanf("%d %d", &num, &times);
    struct card * cards = malloc(num * sizeof(struct card ));   
    // 宣告出空間存取 struct card 形式，cards 是 pointer，但是存取的內容不是 => cards[0] is struct card
    
    for(int i=0; i<num; i++){
        cards[i].val = i+1;
        if(i==0){
            cards[i].last = &cards[num-1];  
            cards[i].next = &cards[i+1];
        }
        else if(i==num-1){
            cards[i].last = &cards[num-2];
            cards[i].next = &cards[0];
        }
        else{
            cards[i].last = &cards[i-1];
            cards[i].next = &cards[i+1];
        }
    }

    int count = 0;
    for(struct card * cur = &cards[0]; count<times ; count++, cur = cur->next->next){
        printf("%d ", cur->val);
        // struct card * e = malloc( sizeof(struct card) );     // 這題用 times 就好，不用e
        // e = cur;
        cur->last->next = cur->next;
        cur->next->last = cur->last;
        // free(e);
    }
    return 0;
}