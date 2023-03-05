#include<stdio.h>

int ascii[16]={48, 49, 50 ,51, 52, 53, 54, 55, 56, 57, 97, 98, 99, 100, 101, 102 }; //index 即decimal

void ToDecending( int array[], int digits ){
    int temp[digits];   // array[0]=位數
    for(int i=0, j=digits-1;  j>=0; i++, j--){
        temp[i] = array[j];
        //printf("%d ", array[j]);
    }
    
    //printf("\n--- In the HexarrayToDecarray function ---\n");
    for(int i=0; i<digits; i++){
        array[i] = temp[i];
        //printf("%d ", array[i]);
    }
}

int DecToHex( int array[], int dec ){
    int i=0;
    while(dec){
        array[i] = dec%16;  //index=0, 16進制的“個位數”
        dec/=16;
        i++;
    }

    int digits = i; //位數
    ToDecending(array, digits);
    return digits;
}

void Calculate( int array[], int count ){      //count = 位數
    //計算總和

    int sumEven=0, sumOdd=0;
    int digitEven=0, digitOdd=0;
    int even[10001]={0}, odd[10001]={0};    //sumToHex

    for(int i=0; i<count; i++){
        if(i%2==0) { sumEven+=array[i]; }
        else { sumOdd+=array[i]; }
    }

    //printf("sumOdd=%d sumEven=%d\n", sumOdd, sumEven);

    //轉 16進制，確認位數   //怎麼計算位數？ 16進制也有可能為零 => 在function裡做好，存在index=0
    if(sumOdd>0) { digitOdd = DecToHex( odd, sumOdd ); }
    else { digitOdd=1; }
    if(sumEven>0) { digitEven = DecToHex( even, sumEven ); }
    else { digitEven=1; }
    
    

    // printf("\ndigitOdd=%d\t", digitOdd);
    // // //printf("\n---16進制輸出---\n");
    // for(int i=0; i<digitOdd; i++){
    //     printf("%x ", odd[i]);
    // }
    // printf("\n");
    // printf("digitEven=%d\t", digitEven);
    // //printf("\n---16進制輸出---\n");
    // for(int i=0; i<digitEven; i++){
    //     printf("%x ", even[i]);
    // }
    // printf("\n");
     

     if(digitOdd>1) { Calculate( odd, digitOdd ); }  
     else printf("%x", odd[0] ) ;
     if(digitEven>1) { Calculate( even, digitEven ); }  
     else printf("%x", even[0] );    
}

//EOF , crl+d
int main () {
    int a[10001]={0}, count=0;
    
    while(scanf("%1x", &a[count])!=EOF){    //!!!!
        count++;
    }

    // for(int i=0; i<count; i++){
    //     printf("%d ", a[i]);
    // }

    if(count==0) { 
        printf("aa");
        printf("%d", a[0]); 
        return 0;
    }
    Calculate(a,count);
    // Result
    // print hex形式



    // // Debug 
    // printf("\n---Debug---\n");
    // for(int i=0; i<count;i++){
    //     printf("%d " ,a[i]) ;
    // }

    return 0;
}

//a怪怪的