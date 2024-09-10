#include <iostream>

using namespace std;

template <typename T>
void merge(T* array, size_t left, size_t mid, size_t right) {
    
    int n1 = mid - left + 1;
    int n2 = right - mid;

    T* L = new T [n1];
    T* R = new T [n2];

    size_t i = 0;
    for(i; i < n1; i++)
        L[i] = array[left + i];
    
    size_t j = 0;
    for(j; j < n2; j++)
        R[j] = array[mid + 1 + j];

    i = j = 0;
    size_t k = left;

    while(i < n1 && j < n2) {
        if(L[i] <= R[j])
            array[k++] = L[i++];
        else
            array[k++] = R[j++];
    }

    while(i < n1)
        array[k++] = L[i++];

    while(j < n2)
        array[k++] = R[j++];

    delete [] L;
    delete [] R;
}

template <typename T>
void mergeSort(T* array, size_t left, size_t right) {

    if(left < right) {
        size_t mid = left + (right - left)/2;

        mergeSort(array, left, mid);
        mergeSort(array, mid + 1, right);

        merge(array, left, mid, right);
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