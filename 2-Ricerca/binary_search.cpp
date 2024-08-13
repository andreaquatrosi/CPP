#include <iostream>
#include <cstdlib>
#include <time.h>

#define N 10

using namespace std;  

int* init_Array() {

    int* array = new int [N];

    cout << "Enter array elements:\n";
    for(size_t i = 0; i < N; i++)
        cin >> array[i];

    return array;
}

void print_Array(int* array) {

    cout << "\nArray:\n";
    for(size_t i = 0; i < N; i++) {
        cout << array[i] << " ";
    }

    cout << endl;
}

void sort_Array(int* array) {

    int temp = 0;

    for(size_t i = 0; i < N; i++) {
        for(size_t j = i + 1; j < N; j++) {
        if(array[j] < array[i]) {
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
        }
    }
}

void binary_Search(int *array, int key) {

    bool found = false;

    // array lenght
    int start = 0;
    int end = N - 1;

    while((found == false) && (start != end)) {
        int midpoint = (start + end)/2;
        
        if (array[midpoint] == key) {
            found = true;
        } else if (key < array[midpoint]) {
            end = midpoint;
        } else {
            start = midpoint + 1;
        }
    }

    if(found) {
        cout << key << " found.";
    } else {
        cout << key << " not found.";
    }
}

int main() {
    
    int *a = init_Array();
    cout << "Unsorted Array:\n";
    print_Array(a);
    
    cout << "Sorted Array:\n";
    sort_Array(a);
    print_Array(a);

    int key;
    cout << "\nEnter key:\n";
    cin >> key;
    binary_Search(a, key);  

    delete [] a;

    return 0;
}