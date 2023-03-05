#include<stdio.h>

int main () {
    int num, cNum, objNum;
    scanf("%d", &num);
    num++;
   
    char name[num][20];
    for(int r=0; r<num; r++)
    {
        scanf("%d ", &cNum);
        name[r][0] = cNum ;
    	for(int c=1; c<=cNum; c++)
        {
            name[r][c] = getchar();

            if ( name[r][c]>='A' && name[r][c]<='Z')
                name[r][c] = name[r][c]-'A'+'a';
        }
    }

    //Debug
    for(int r=0; r<num; r++)
    {
    	for(int c=0; c<=name[r][0]; c++)
        {
            printf("%d %c, ", name[r][c], name[r][c]);
        }
        printf("\n");
    }
    //Debug

    int order=1;
    for(int r=1; r<num; r++)
    {
        if(name[0][1]> name[r][1]) {  order++; }
        else if (name[0][1] == name[r][1])
        {
            for(int k=2; k<=name[0][0]; k++)
            {
                if(name[r][k])
                {
                    if(name[0][k]> name[r][k]) 
                    {  
                        order++ ;
                        k=name[0][0];
                    }
                    else if(name[0][k]< name[r][k]) 
                    {   
                        k=name[0][0];
                    }
                }
                else 
                {
                    order++;
                    k=name[0][0];
                }
            }
        }
    }
    printf("%d", order);

    
    
    return 0;
}
//記得轉大小寫
