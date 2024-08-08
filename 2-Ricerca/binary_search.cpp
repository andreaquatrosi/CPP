/*
    For some unknown reason this code do not produce any output
*/

#include <iostream>
#include <cstdlib>
#include <time.h>

#define N 10

using namespace std;  

int* init_Array() {

    int* array = new int [N];

    for(size_t i = 0; i < N; i++) {
    
        bool is_unique = true;

        do {
            array[i] = rand() % 20;
        
            // Check for duplicates
            for (size_t j = 0; j < i; ++j) {
        
                if (array[j] == array[i]) {
                is_unique = false;
                break;
                }
            }
        } while (!is_unique);
    }

    return array;
}

void print_Array(int* array) {

    for(size_t i = 0; i < N; i++) {
        cout << array[i] << "\t";
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
        end = midpoint - 1;
        } else {
        start = midpoint + 1;
        }
    }

    if(found) {
        cout << key << "found.";
    } else {
        cout << key << "not found.";
    }
}

int main() {

    srand(static_cast<unsigned>(time(NULL)));
    
    int *a = init_Array();
    cout << "Unsorted Array:\n";
    print_Array(a);
    
    cout << "Sorted Array:\n";
    sort_Array(a);
    print_Array(a);

    int key;
    cin >> key;

    binary_Search(a, key);  

    delete [] a;

    return 0;
}