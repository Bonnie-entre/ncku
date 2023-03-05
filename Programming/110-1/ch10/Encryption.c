#include<stdio.h>
#define SIZE 64

void Swap( char w[SIZE], int endIndex);
void Rotate( int lr, int moveNum, char w[] , int startIndex, int endIndex );
void RailFenceCipher( int key[], int keySize, char w[] , int round, int startIndex, int endIndex );
void CaesarCipher( int key, char w[], int wordSize );
void TrithemiusCipher( int key, int ad, char w[], int endIndex );
void VigenereCipher( char key[], int keySize, char w[], int startIndex, int endIndex );

int main () {
    char ch, word[SIZE];
    int encryptType, i=0;
    scanf("%d ", &encryptType);
    while ( (ch = getchar()) != '\n' )
    {
        word[i] = ch;
        i++;
    }
    
    char keyOne[4] = { 'm', 'e', 'o','w'};
    char keyFour[8] = {'v','i','g','e','n','e','r','e'};
    int railFence_keyTWO[8] = {4,3,1,2,7,6,5,8};  
    int railFence_keyThree1[4] = {3,2,4,1};   
    int railFence_keyThree2[8] = {1,8,4,3,6,5,7,2};  
    int railFence_keyFive1[8] = {3,1,7,6,4,5,2,8}; 
    int railFence_keyFive2[4] = {2,4,1,3};
    switch (encryptType)
    {
    case 1:
        Swap(word, SIZE);
        CaesarCipher( 13, word, SIZE/2 );
        VigenereCipher( keyOne, 4, word, SIZE/2, SIZE );
        Rotate( 0, 3, word , 0, SIZE );
        break;
    case 2:
        Rotate( 1, 11, word , 0, SIZE );
        TrithemiusCipher( 74, 1, word, SIZE );
        Rotate( 1, 1, word , 0, SIZE/2 );
        Rotate( 1, 3, word , SIZE/2, SIZE );
        RailFenceCipher( railFence_keyTWO, 8, word , SIZE/8, 0, SIZE );
        break;
    case 3:
        RailFenceCipher( railFence_keyThree1, 4, word , SIZE/4, 0, SIZE );
        CaesarCipher( 8, word, SIZE/2 );
        RailFenceCipher( railFence_keyThree2, 8, word , SIZE/2/8, SIZE/2, SIZE );
        Swap(word, SIZE);
        TrithemiusCipher( 602, -1, word, SIZE );
        Rotate( 1, 7, word , 0, SIZE );
        break;
    case 4:
        VigenereCipher( keyFour, 8, word, 0, SIZE/2 );
        Swap(word, SIZE/2);
        TrithemiusCipher( 3, 1, word, SIZE/2 );
        Rotate( 0, 24, word, SIZE/2, SIZE);
        Rotate( 1, 19, word, 0, SIZE);
        break;
    case 5:
        RailFenceCipher( railFence_keyFive1, 8, word , SIZE/8, 0, SIZE );
        CaesarCipher( 10, word, SIZE/2 );
        RailFenceCipher( railFence_keyFive2, 4, word , SIZE/2/4, SIZE/2, SIZE );
        Swap(word, SIZE);
        TrithemiusCipher( 52, 1, word, SIZE );
        Rotate( 1, 7, word, 0, SIZE);
        break;
    }

    for( int k=0; k<64; k++){
        printf("%c", word[k]);
    }

    return 0;
}

void VigenereCipher( char key[], int keySize, char w[], int startIndex, int endIndex ){
    int keyInt[keySize];
    //int size = endIndex - startIndex;
    for( int i=0; i<keySize; i++){
        keyInt[i] = key[i] - 'a';
    } 
    
    int  i=0, k=startIndex;
    while ( k<endIndex )
    {
        if( w[k]>='a' && w[k]<='z'){
            w[ k ] = (w[ k ] - 'a' + keyInt[i] ) % 26 +'a';
            i++;
        }
        if( w[k]>='A' && w[k]<='Z' ){
            w[ k ] = (w[ k ] - 'A' + keyInt[i] ) % 26 +'A';
            i++;
        }
        k++;
        if( i==keySize ) { i=0; }
    }
}

void TrithemiusCipher( int key, int ad, char w[], int endIndex ){
    for( int i=0; i<endIndex; i++){
        while ( key < 0)
        {
            key += 26;
        }
        
        if( w[i]>='a' && w[i]<='z'){
            w[i] = (w[i] - 'a' + key) % 26 +'a';
            key += ad;
        }
        if( w[i]>='A' && w[i]<='Z' ){
            w[i] = (w[i] - 'A' + key) % 26 +'A';
            key += ad;
        }
    }
}

void CaesarCipher( int key, char w[], int wordSize ){
    
    for( int i=0; i<wordSize; i++){
        if( w[i]>='a' && w[i]<='z'){
            w[i] = (w[i] - 'a' + key) % 26 + 'a';
        }
        if( w[i]>='A' && w[i]<='Z'){
            w[i] = (w[i] - 'A' + key) % 26 + 'A';
        }
    }
}

void RailFenceCipher( int key[], int keySize, char w[] , int round, int startIndex, int endIndex ){  
    int n=0;
    int size = endIndex - startIndex;
    char temp[size];
    while(n<round){
        //printf("\nROUND %d\n", n);
        for( int i=0; i < keySize; i++ ){
            temp[ keySize * n + key[i]-1 ] = w[ startIndex + keySize * n + i ];
        }
        n++;
    }
    for( int i=0, k = startIndex; i<size; i++, k++){
        w[k] = temp[i];
    }
}

void Rotate( int lr, int moveNum, char w[] , int startIndex, int endIndex ){
    int j;
    int size = endIndex - startIndex; 
    int k = startIndex;
    char temp[moveNum], copy[size];
    switch (lr)
    {
    case 0: //l
        j=0;
        for( int i=0; i<size; i++){
            if( i<moveNum ){
                temp[i] = w[k];
            }
            if ( i < (size-moveNum) ){
                w[k] = w[ k+moveNum];
            }
            else{
                w[k] = temp[j];
                j++;
            }
            k++;
        }
        break;
    case 1: //r
        j=0;
        for( int i=0; i<size; i++){
            copy[i] = w[k];
            if( i >= (size-moveNum) ){
                temp[j] = w[k];
                j++;
            }
            k++;
        }
        j=0;
        k=startIndex;
        for( int i=0; i<size; i++ ){
            if( i < moveNum ){
                w[k] = temp[i];
            }
            else{
                w[k] = copy[j];
                j++;
            }
            k++;
        }
        break;
    }
}

void Swap( char w[], int endIndex ){
    char temp[endIndex/2];
    for( int i=0; i<endIndex; i++){
        if( i < (endIndex/2) ){
            temp[i] = w[i];
            w[i] = w[ i + (endIndex/2) ];
        }
        else{
            w[i] = temp[ i - (endIndex/2) ];
        }
    }
}