#include <iostream>

#define N 5  

using namespace std;

void insertion_sort(int array[]) {

    for(size_t i = 1; i < N; i++) {
        int temp = array[i];

        size_t j = i;
        while((j > 0) && (temp < array[j - 1])) {
            array[j] = array[j - 1];
            j--;
        }
        
        array[j] = temp;
    }
}

int main() {

    int array[N];

    for(size_t i = 0; i < N; i++) {
        cin >> array[i];
    }

    cout << "Unsorted Array:\n";
    for(size_t i = 0; i < N; i++) {
        cout << array[i] << " ";
    }

    insertion_sort(array);

    cout << "\n\nSorted Array:\n";
    for(size_t i = 0; i < N; i++) {
        cout << array[i] << " ";
    }

    return 0;
}