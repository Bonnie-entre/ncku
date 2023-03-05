#include <iostream>
#include < iomanip>
using namespace std;

void selectionSort(int [], const int, boool (*)(int, int))
void swap( int * const, int * const);
bool ascending( int, int)
bool descending( int, int)

int main( int argc, char** argv ){

    cout << "You have entered " << argc << " arguments:" << "\n";
    for (int i = 0; i < argc; ++i)
        cout << argv[i] << "\n";

    const int arraySize = 10;
    int order;
    int counter;
    int a[arraySize] = { 2, 6, 4, 8, 10, 12, 89, 68, 45, 37};

    string input = argv[1];
    string s1 = "ascending";
    string s2 = "descending";

    cout << "Data items in original order\n";
    for (counter = 0; counter< arraySize; counter++)
        cout<< setw(4)<< a[counter];
    
    if ( argv[1]== s1){
        selectionSort(a, arraySize, ascending);
        cout<< "Data items in ascending order\n";
    }
    else{
        selectionSort(a, arraySize, descending);
        cout<< "Data items in descending order\n";
    }

    for (counter = 0; counter< arraySize; counter++)
        cout<< setw(4)<< a[counter];
    
    cout<< endl;
}

void SelectionSort( int work[], const int size, bool (*compare)(int,int)){
    int smallestOrlargest;

    for (int i=0; i<size-1, i++){
        smallestOrlargest = i;
        for (int index=i+1 ; index < size, index++){
            if ( !(*compare)(work[smallestOrlargest], work[index]))
                smallestOrlargest = index;
        }
        swap ( &work[smallestOrlargest], &work[i]);
    }
}

void swap( int * const p1, int * const p2){
    int hold = *p1;
    *p1 = *p2;
    *p2 = hold;
}

bool ascending(int a, int b){
    return a<b;
}

bool descending(int a, int b){
    return a>b;
}
