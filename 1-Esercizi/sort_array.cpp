/* 
    Ordinare il vettore
    42, 57, 14, 40, 96, 19, 08, 68
    mediante i metodi: 
        (a) bubblesort; 
        (b) selezione; 
        (c) inserimento
*/

#include <iostream>

using namespace std;

template <typename T>
void swap_elements(T& a, T& b) {

    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
void display(T* array, int N) {

    cout << "Sorted array:\n";
    for(size_t i = 0; i < N; i++)
        cout << array[i] << " ";

    cout << "\n";
}

// sorting algorithms
template <typename T>
void bubblesort(T* array, int N) {
    
    for(size_t i = 0; i < N; i++) {
        for(size_t j = i + 1; j < N; j++) {
            if(array[i] > array[j]) {
                swap_elements(array[i], array[j]);
            }
        }
    }

    cout << "\nBubble Sort\n";
}

template <typename T>
void selectionsort(T* array, int N) {

    
    for(size_t i = 0; i < N; i++) {
        size_t index_min = i;

        for(size_t j = i+1; j < N; j++) {
            if(array[j] < array[index_min])
                index_min = j;
        }

        swap_elements(array[i], array[index_min]);
    }

    cout << "\nSelection Sort\n";
}

template <typename T>
void insertionsort(T* array, int N) {

    for(size_t i = 1; i < N; i++) {
        T temp = array[i];

        size_t j = i;
        while(j > 0 && temp < array[j-1]) {
            array[j] = array[j-1];
            j--;
        }

        array[j] = temp;
    }

    cout << "\nInsertion Sort\n";
}

int main() {

    int a[] = {42, 57, 14, 40, 96, 19, 8, 68};
    int b[] = {42, 57, 14, 40, 96, 19, 8, 68};
    int c[] = {42, 57, 14, 40, 96, 19, 8, 68};

    int N = sizeof(a) / sizeof(a[0]);

    // Bubble Sort (a)
    bubblesort<int>(a, N);
    display<int>(a, N);

    // Selection Sort (b)
    selectionsort<int>(b, N);
    display<int>(b, N);

    // Insertion Sort (c)
    insertionsort<int>(c, N);
    display<int>(c, N);

    return 0;
}