#include <iostream>

using namespace std;
  
void swap(int& a, int& b) {

    int t = a;
    a = b;
    b = t;
}

int partition(int* A, size_t p, size_t r) {

    size_t i = p-1;
    size_t j = p;

    int& pivot = A[r];

    while(j < r) {
        if(A[j] <= pivot) {
            i++;
            swap(A[i], A[j]);
        }
    
        j++;
    }

    swap(pivot, A[i+1]);

    return i+1;
}

void quickSort(int* A, size_t p, size_t r) {

    if(p < r) {
        int q = partition(A, p, r);
    
        quickSort(A, p, q-1);
        quickSort(A, q+1, r);
    }
}

int main() {

    constexpr size_t N = 8;

    int array[N];
  
    cout << "Fill array:\n";
    for(size_t i = 0; i < N; i++)
        cin >> array[i];

    cout << "Unsorted Array:\n";
    for(size_t i = 0; i < N; i++)
        cout << array[i] << " ";

    cout << "\nSorted Array:\n";
    quickSort(array, N-N, N);
    for(size_t i = 0; i < N; i++)
        cout << array[i] << " ";

    return 0;
}