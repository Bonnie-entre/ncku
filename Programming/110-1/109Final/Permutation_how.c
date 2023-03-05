#include <stdio.h>
#include <string.h>
#define SWAP(a,b,t) ((t)=(a),(a)=(b),(b)=(t))//巨集函式
void perm(char *list,int k,int j);
void swap(char *a, char *b){
    char temp;
    temp = *a;
    *a = *b;
    *b = temp;
    
}
int main(void)
{
	char list[6];
    gets(list);
    // order the input
    for( int i=1; i<strlen(list); i++){
        if( strcmp(&list[i-1], &list[i])>0 ){
            swap(&list[i], &list[i-1]);
        }
    }
    // printf("%s", list);

	perm(list,0,strlen(list)-1);
    return 0;
}

void perm(char *list,int k,int j)//k，j為開始結束位置
{
	char temp;
	int i;
	if(k==j)
	{
		printf("%s\n",list);
	}
	else
	{
		for(i=k;i<=j;i++)
		{
			SWAP(list[i],list[k],temp);//換到開頭

            // order befor perm
            // for( int p=k+2; p<j; p++){                   // 沒成功！
            //     if( strcmp(&list[p-1], &list[p])>0 ){
            //         swap(&list[p], &list[p-1]);
            //     }
            // }

			perm(list,k+1,j);//遞迴呼叫
			/*
			遞迴呼叫，只有k變，可以理解成先把a放在開頭，把bc全排列，bc全排列的時候又要把b放在bc的開頭，把c全排列，以此類推。
			當a在開頭時所有全排列完畢，也就是k=j時第三層遞迴結束進行第一層遞迴的第二次迴圈，也就是進行下一次for迴圈，把b放在開頭，全排列ac.....如此進行
			*/
			SWAP(list[i],list[k],temp);//恢復位置
		}
	}
}

// 先存 array, 再sort