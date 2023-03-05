#include <stdio.h>

int main () {
    int ingredient[7]={0}; 
    // 0 black tea (L)/ 1 White gourd (L)/ 2 Tieguanyin tea (L)/ 3 green tea (L)
    // 4 milk (L)/ 5 sugar (kg)/ 6 ice (kg)
    int num=0;
    for(int i=0; i<7; i++){
        scanf("%d", &ingredient[i]);
        ingredient[i] *=1000;
    }
    scanf("%d", &num);
    char ch;
    int i=0, earn=0, ice, sugar;
    while (i<num)
    {
        ch=getchar();   //怎麼改善這裡！
        ch=getchar();
        switch (ch)
        {
        case 'G':{
            if((ch=getchar()) == 'T'){
                ingredient[2] -= 250;
                ingredient[3] -= 250;
                earn += 45;
            }
            else{
                ingredient[3] -= 500;
                earn += 20;
            }
            break;
        }
        case 'B':       //(black tea 200mL + milk 300mL)
            if((ch=getchar()) == 'M'){
                ingredient[0] -= 200;
                ingredient[4] -= 300;
                earn += 35;
            }
            else{
                ingredient[0] -= 500;
                earn += 20;
            }
            break;
        case'T':{       //Tieguanyin tea 200mL + milk 300mL
            if((ch=getchar()) == 'M'){
                ingredient[2] -= 200;
                ingredient[4] -= 300;
                earn += 45;
            }
            else{
                ingredient[2] -= 500;
                earn += 30;
            }
            break;
        }
        case'W':{
            ch=getchar();
            if(ch == 'T'){   //Tieguanyin tea 350mL + white gourd tea 150mL
                ingredient[2] -= 350;
                ingredient[1] -= 150;
                earn += 40;
            }
            else if(ch == 'M'){  //White gourd tea 200mL + milk 300mL
                ingredient[1] -= 200;
                ingredient[4] -= 300;
                earn += 30;
            }
            else{
                ingredient[1] -= 500;
                earn += 15;
            }
            break;
        }
        
        }

        scanf("%d/%d", &sugar, &ice);
        switch (sugar)
        {
        case 2:
            ingredient[5] -= 3;
            break;
        case 3:
            ingredient[5] -= 5;
            break;
        case 4:
            ingredient[5] -= 7;
            break;
        case 5:
            ingredient[5] -= 10;
            break;
        }
        switch (ice)
        {
        case 2:
            ingredient[6] -= 30;
            break;
        case 3:
            ingredient[6] -= 50;
            break;
        case 4:
            ingredient[6] -= 70;
            break;
        case 5:
            ingredient[6] -= 100;
            break;
        }
        i++;
    }

    for( int i=0; i<7; i++){
        printf("%d ", ingredient[i]);
    }
    printf("\n%d", earn);
    return 0;
}