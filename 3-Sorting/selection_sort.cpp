#include <iostream>

#define N 5  

using namespace std;

void swap(int& a, int& b) {

    int t = a;
    a = b;
    b = t;
}

void selection_sort(int array[]) {

    for(size_t i = 0; i < N; i++) {
        size_t index_min = i;

        for(size_t j = i + 1; j < N; j++) {
            if(array[j] < array[index_min]) {
                index_min = j;
            }
        }

        swap(array[i], array[index_min]);
    }
}

int main() {

    int array[N];  

    cout << "Enter array elements:\n";
    for(size_t i = 0; i < N; i++) {
        cin >> array[i];
    }

    cout << "Unsorted Array:\n";
    for(size_t i = 0; i < N; i++) {
        cout << array[i] << " ";
    }

    selection_sort(array);

    cout << "\nSorted Array:\n";
    for(size_t i = 0; i < N; i++) {
        cout << array[i] << " ";
    }

    return 0;
}