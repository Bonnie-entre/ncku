#include <stdio.h>
int *report_card (int *s) ;

int main () {
    int score[1001];
    int *show;
    int count = 0;

    do {
        scanf("%d", &score[count++]);
    } while (score[count - 1] != -1);

    show = report_card(score);

    count = 0;
    while (*(show + count) != -1) {
        printf("%d ", *(show + count));
        count++;
    }
}

int *report_card (int *s) {
    int index[1024][3];     // 這結構可以改成 struct
    for( int i=0; i<1024; i++){
        index[i][0] = 0;    // index
        index[i][1] = 0;    // consecutive num
        index[i][2] = 0;    // sum of those consecutive number
    }

    int i = 0, index_i = 0;
    while(1){    
        if(*(s+i)>=60){
            index[index_i][0] = i;
            index[index_i][1]++;
            index[index_i][2] += *(s+i);

            i++;
            while(*(s+i)>=60 && *(s+i)!=-1){
                index[index_i][1]++;
                index[index_i][2] += *(s+i);
                i++;
            }
            index_i++;
            i--;
        }
        i++;
        if(*(s+i)==-1) break;
    }


    int max = 0, sel = 0;
    for(int i=0; i<index_i; i++){
        if(index[i][1]>max){    //比count數量
            sel = i;
            max = index[i][1];
        }
        else if(index[i][1]==max){
            if(index[sel][2]<index[i][2]){  //比合計
                sel = i;
            }    
        }
    }

    i = 0;
    for( ; i<index[sel][1]; i++){
        *(s+i) = *(s + index[sel][0] + i);  //swap and make result array
    }
    *(s+i) = -1;    // 最後補-1

    return s;
}