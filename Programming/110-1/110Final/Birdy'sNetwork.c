#include <stdio.h>
#include <stdlib.h>

struct node {
  int id;
  struct node *next;
};

struct node *read_data(int *size); // TODO: implement this function

void print_data(struct node *adj, int size) {
  if (!adj)
    return;
  for (int i = 0; i < size; ++i) {
    printf("%d -> ", adj[i].id);
    for (struct node *ptr = adj[i].next; ptr != NULL; ptr = ptr->next)
      printf("%d ", ptr->id);
    putchar('\n');
  }
}

void free_data(struct node *adj, int size) {
  if (!adj)
    return;
  for (int i = 0; i < size; ++i) {
    struct node *ptr = adj[i].next;
    while (ptr) {
      adj[i].next = ptr->next;
      free(ptr);
      ptr = adj[i].next;
    }
  }
  free(adj);
}

int main() {
  int size;
  struct node *adj = read_data(&size);
  if (!adj) {
    fprintf(stderr, "Error allocating memory.");
    exit(1);
  }
  print_data(adj, size);
  free_data(adj, size);
  return 0;
}

int cmp(const void *a, const void *b) {
    struct node *aa=(struct snack *)a;         
    struct node *bb=(struct snack *)b;
    return *aa->id > **bb->id;
}
struct node *read_data(int *size) {
    struct node * nodes = malloc ( *size * sizeof(struct node));

    char ch;
    int i=0;
    *size = 0;
    int temp;
    scanf("%d -> ", &temp);
    while( i<3 ){  //temp!=EOF
        // id
        nodes[i].id = temp;
        // printf("id= %d", temp);
        
        // ->
        scanf("%d", &temp);
        nodes[i].next = malloc (  sizeof(struct node) );
        struct node * cur = nodes[i].next;

        while(temp != 0){
            cur->id = temp;
            scanf("%d", &temp);
            if(temp==0){break;}
            cur->next = malloc (  sizeof(struct node) );
            cur = cur->next;
        }
        // printf("last temp=%d\n", temp);
        i++; //先假定用i
        *size++;


        scanf("%d -> ", &temp);
        // printf("%d", temp);
    }

    qsort(nodes, *size, sizeof(struct node), cmp);

    return nodes;
}

// 100356 -> 4 458 0
// 4 -> 458 0
// 458 -> 0

