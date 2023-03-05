#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

bool inarray(int num, int array[], int size){
	bool in=false;
	int i=0;
	while(i<=size && !in){
	   in=array[i]==num;
	   i++;	
	}
return in;	
}
	
void RandomArrayGen(int numarray[], int size){
	int num=0;
	for(int i=0; i<size; i++){
		do{
			num= 1+rand()%RAND_MAX;
		}while (inarray(num,numarray,i-1));
		numarray[i]=num;
	}
}

void printArray(int a[], int size)
{
   int i;
   printf("\n");
   for (i = 0; i <= size - 1; i++) {
      if (i % 20 == 0) {printf("\n");}
      printf("\t");
      printf("%6d", a[i]);
   }
}


void swap(int *index1, int *index2)
{
   int temp;

   temp = *index1;
   *index1 = *index2;
   *index2 = temp;
}

void insertionsort(int array[], int arraysize){
	int insert;
	for ( int next = 1; next < arraysize; next++ ){
      	insert = array[ next ]; // store the value in the current element
      	int moveItem = next; // initialize location to place element
	  	// search for the location in which to put the current element      
      //不斷向左比較，直到next以左都排序正確
      	while ( ( moveItem > 0 ) && ( array[ moveItem - 1 ] > insert ) ){
         // shift element one slot to the right
         array[ moveItem ] = array[ moveItem - 1 ];
         array[ moveItem-1 ] = insert;
         moveItem--;
        }
} // end while}
}
   
int linearSearch( const int array[], int sizeOfArray, int key  ){          //這裡怪怪的！第二第三感覺反了～～～
   for ( int j = 0; j < sizeOfArray; j++ )
      if ( array[ j ] == key ) // if found, 
         return j; // return location of key
   return -1; // key not found
} // end function linearSearch

//Implement the following three functions. 

// Cool binarySearch coding   // Recursion one!!
int binarySearch(int a[], int value, int left, int right){
    if (right<left) { return -1; }
    int mid;
    mid = (left+right)/2;
    if (a[mid]==value)  { return mid; }
    else if (a[mid]<value) { return binarySearch(a, value, mid+1, right);}
    else { return binarySearch( a,  value, left, mid-1);}
}

int partition(int a[], int first, int last) {   //, int pivotIndex
    int pivotValue, storeIndex;
    pivotValue = a[last];  
    //是pivotIndex出問題，所以不能一次取最右？？？ //後來直接註解掉，不用設定pivotIndex!！
    storeIndex = first;
    for (int i=first; i<last; i++){
        if(a[i]<=pivotValue){
            swap(a[i],a[storeIndex]);
            storeIndex++;
        }
    }
    swap(a[last],a[storeIndex]);
    return storeIndex;
}

void quicksort(int array[], int first, int last){
    int pivotIndex, pivotNewIndex;    
    if (last>first){      
        //pivotIndex = array[last];       
        pivotNewIndex = partition(array, first, last);     //, pivotIndex
        quicksort( array, first, pivotNewIndex-1);        // Recursion ones!!
        quicksort( array, pivotNewIndex+1, last);
    }
    return;
}

 
int main(){
	const int numbers=2000;
	const int searchTimes=10000;
	clock_t time1=0.0, time2=0.0, time3=0.0, time4=0.0;
	int position=0,searchkey;
	int numarray[numbers]={};
	int numarray2[numbers]={};
	srand(time(0));	
	
	RandomArrayGen(numarray, numbers);
	searchkey=1+rand()%RAND_MAX; // Generate a search key randomly.
    
//linearSearch
	time1=clock(); 
	for (int i=0; i < searchTimes; i++) position=linearSearch(numarray, numbers, searchkey);
	time2=clock(); 
    cout << "time1:" << time1 << "\ttime2:" << time2 << endl;
	if (position>0)
	     cout << "Found " << searchkey << " at:" << position << " in " << (double)(time2-time1)/CLOCKS_PER_SEC << " seconds" << endl;
	else cout << "Not found " << searchkey << " after:" << (double)(time2-time1)/CLOCKS_PER_SEC << " seconds for linear search." << endl;
  //printArray(numarray, numbers);      // Uncomment for checking
	
//insertionsort
	time1=clock(); 
	insertionsort(numarray, numbers);
	time2=clock();
	//printArray(numarray, numbers);      // Uncomment for checking

//binarySearch
	searchkey=1+rand()%RAND_MAX; // Generate a search key randomly. 
	time3=clock();
	for (int i=0; i < searchTimes; i++) position=binarySearch(numarray, searchkey, 0, numbers);
	time4=clock();
    cout << "time3:" << time3 << "\ttime4:" << time4 << endl;
	if (position>0)
	     cout << "Found " << searchkey << " at:" << position << " in " << (double)(time4-time3)/CLOCKS_PER_SEC <<" seconds" << endl;
	else cout << "Not found " << searchkey << " after:" << (double)(time4-time3)/CLOCKS_PER_SEC <<" seconds for binary search." << endl;
  
  RandomArrayGen(numarray2, numbers);

//quicksort
	time3=clock(); 
	quicksort(numarray2, 0, numbers-1);
	time4=clock();
  
    
    
//	printArray(numarray2, numbers);      // Uncomment for checking
	cout << "time1:" << time1 << "\ttime2:" << time2 << "\ttime3:" << time3 << "\ttime4:" << time4 << "\t clocks per second" << CLOCKS_PER_SEC << endl;
  cout << setprecision(6) <<(double)(time2-time1)/ CLOCKS_PER_SEC << " seconds for insertion sort \n";
  cout << setprecision(6) <<(double)(time4-time3)/ CLOCKS_PER_SEC << " seconds for quick sort \n"; 

}
