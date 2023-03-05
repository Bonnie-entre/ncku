#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    unsigned char hour;
    unsigned char minute;
} hm_t;

typedef struct {
    const char *item_name;
    unsigned cost;
    unsigned cnt;
} item_t;

typedef struct {
    unsigned order_id;
    hm_t pick_up_time;
    unsigned total_cost;
    unsigned item_cnt;
    item_t *items;
} order_t;

const item_t avaliable_items[] = {
    {"Prod_A",  10},
    {"Prod_B",  20},
    {"Prod_C",  15},
    {"Prod_D",  30},
    {"Prod_E",  50},
    {"Prod_F",  60},
    {"Prod_G",  75},
    {"Prod_H",   5},
    {"Prod_I",  25},
    {"Prod_J",  80},
    {"Prod_K", 100},
    {"Prod_L",  90},
    {"Prod_M",  45},
    {"Prod_N",  40},
    {"Prod_O",  85},
};

const unsigned avaliable_item_cnt = 15;
#define MAX_ORDER_CNT 1024

unsigned fetch_orders(order_t orders[]);
void sum_total_costs(order_t orders[], unsigned order_cnt);
void reorder(order_t orders[], unsigned order_cnt);
void print_result(order_t orders[], unsigned order_cnt);
void clean_up(order_t orders[], unsigned order_cnt);
int cmp(const void *a, const void *b);

int main()
{
    order_t orders[MAX_ORDER_CNT];
    unsigned order_cnt = fetch_orders(orders);
    sum_total_costs(orders, order_cnt);
    reorder(orders, order_cnt);
    print_result(orders, order_cnt);
    clean_up(orders, order_cnt);
    return 0;
}

unsigned fetch_orders(order_t orders[])
{
    unsigned order_cnt;
    scanf("%u", &order_cnt);

    // Prepare the orders.
    order_t *curr = orders;
    for (unsigned i = 0; i < order_cnt; i++, curr++) {
        hm_t *curr_pu = &(curr->pick_up_time);
        scanf("%u %hhu:%hhu %u",
                                &(curr->order_id),
                                &(curr_pu->hour),
                                &(curr_pu->minute),
                                &(curr->item_cnt));

        // Create a variable length array with malloc.
        item_t *curr_items = curr->items = malloc(sizeof(item_t) * curr->item_cnt);
        for (unsigned j = 0; j < curr->item_cnt; j++) {
            char item_name[32];
            scanf("%s", item_name);
            for (unsigned k = 0; k < avaliable_item_cnt; k++) {
                if (!strcmp(item_name, avaliable_items[k].item_name)) {
                    // Copy the memory content from avaliable_items to curr_items.
                    curr_items[j] = avaliable_items[k];
                    break;
                }
            }
            scanf("%u", &(curr_items[j].cnt));
        }
    }
    return order_cnt;
}

void print_result(order_t orders[], unsigned order_cnt)
{
    for (unsigned i = 0; i < order_cnt; i++) {
        printf("#%u %u\n", orders[i].order_id, orders[i].total_cost);
    }
}

void clean_up(order_t orders[], unsigned order_cnt)
{
    for (unsigned i = 0; i < order_cnt; i++) {
        free(orders[i].items);
    }
}

void sum_total_costs(order_t orders[], unsigned order_cnt)
{
    for( unsigned i=0; i<order_cnt; i++){
        orders[i].total_cost = 0;
        for(unsigned j=0; j<orders[i].item_cnt; j++){
            for( int k=0; k<avaliable_item_cnt; k++){
                if( strcmp(orders[i].items[j].item_name, avaliable_items[k].item_name )==0 ){
                    orders[i].total_cost += avaliable_items[k].cost * orders[i].items[j].cnt;
                    k = avaliable_item_cnt;
                }
            }
        } 
    }
}

void reorder(order_t orders[], unsigned order_cnt)
{
    qsort(orders, order_cnt, sizeof( order_t ), cmp);      // qsort完全不可行嗎？

    // order_t temp_ord;
    // int time[order_cnt];
    // time[0] = atoi(orders[0].pick_up_time.hour) * 60 + atoi(orders[0].pick_up_time.minute);  
    // for( int i=1; i<order_cnt; i++){    

    // }
}

int cmp(const void *a, const void *b) {
    order_t *aa = (order_t *)a;         
    order_t *bb = (order_t *)b;
    // int time_a = aa->pick_up_time.hour * 60 + aa->pick_up_time.minute;  // 這寫法是錯的嗎？？
    // int time_b = bb->pick_up_time.hour * 60 + bb->pick_up_time.minute;
    // printf("%d \n", aa->pick_up_time.hour * 60 + aa->pick_up_time.minute);
    return ((aa->pick_up_time.hour * 60 + aa->pick_up_time.minute) < (bb->pick_up_time.hour * 60 + bb->pick_up_time.minute))?-1:1;
}