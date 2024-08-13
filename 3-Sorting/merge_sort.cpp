#include <iostream>

using namespace std;

void merge(int* A, size_t p, size_t q, size_t r) {

    size_t n1 = q-p+1; // Dimensione sotto-array L
    size_t n2 = r-q;  // Dimensione sotto-array R

    int* L = new int [n1+1];
    int* R = new int [n2+1];

    size_t i = 0, j = 0;
    
    // Inizializzo L con gli elementi di sinistra di A
    for(i = 0; i < n1; i++) {
        L[i] = A[p+i];
    }

    // Inizializzo R con gli elementi di destra di A
    for(j = 0; j < n2; j++) {
        R[j] = A[q+1+j];
    }

    i = j = 0;

    L[n1] = R[n2] = INT_MAX;  // Elementi sentinella  

    for(size_t k = p; k <= r; k++) {
        if(L[i] < R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
    }

    delete [] L;
    L = nullptr;

    delete [] R;
    R = nullptr;
}

void mergeSort(int* A, size_t p, size_t r) {

    // p = left
    // r = right

    if(p < r) {

        // q = mid
        size_t q = (p+r)/2; // suddivido l'array in due parti
        
        // applico il merge sort fino a quando i sotto-array hanno dimensione = 1
        mergeSort(A, p, q);     // suddivido ricorsivamente la prima metà
        mergeSort(A, q+1, r);   // suddivido ricorsivamente la seconda metà
        merge(A, p, q, r);      // unisco le due metà
    }
}

int main() {

    constexpr size_t N = 11;

    int array[N];

    cout << "Fill array:\n";
    for(size_t i = 0; i < N; i++)
        cin >> array[i];

    cout << "Unsorted Array:\n";
    for(size_t i = 0; i < N; i++)
        cout << array[i] << " ";

    cout << "\nSorted Array:\n";
    mergeSort(array, N-N, N);
    for(size_t i = 0; i < N; i++)
        cout << array[i] << " ";

    return 0;
}