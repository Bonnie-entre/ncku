#include<stdio.h>
#include<string.h>
#define Attack 10

int main () {

    // input
    int distance, blood;
    scanf("%d %d ", &distance, &blood);
    char  move_all[10000]={'\0'};
    gets(move_all);

    // compare object
    char p[24]="CHAKA CHAKA PATA PON";  //這三個可以放在同一個array裡
    char a[24]="PON PON PATA PON";
    char go[24]="PATA PATA PATA PON";

    // execute
    char *move;
    char delimit[]=",.";
    char ch, result[4]={'\0'};  
    int move_num = 0, command_num = 0;

    move = strtok(move_all, delimit);
    while( move != NULL ) {
        if( strcmp(move,p)==0 ){
            command_num++;
            distance++;
        }
        else if( strcmp(move,a)==0 ){
            command_num++;
            if(distance<=3){
                blood--;
                if(blood<=0){
                    strcpy(result,"YES");
                    break;
                }
            }
        }
        else if( strcmp(move,go)==0 ){
            command_num++;
            distance--;
            if(distance<=0){
                strcpy(result,"NO");
                command_num = blood;
                break;     
            }
        }

        move_num++;
        if(move_num==Attack){     //無論是否合法
            if( strcmp(move, p)!=0){
                strcpy(result,"NO");
                command_num = blood;
                break;    
            }
        }
        move = strtok(NULL, delimit);
   }

   if(move==NULL){
        strcpy(result,"NO");
        command_num = blood;
   }

    printf("%s %d", result, command_num);

    return 0;
}