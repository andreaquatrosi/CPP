#include <iostream>

using namespace std;
  
template <typename T>
void _swap(T& a, T& b) { 
    T t = a;
    a = b;
    b = t;
}

template <typename T>
int partition(T* array, size_t low, size_t high) {
    
    T pivot = array[high];
    size_t i = low - 1;

    for(size_t j = low; j < high; j++) {
        if(array[j] <= pivot) {
            i++;
            _swap(array[i], array[j]);
        }
    }

    _swap(array[i + 1], array[high]);
    
    return (i + 1);
}

template <typename T>
void quickSort(T* array, size_t low, size_t high) {

    if(low < high) {
        int p = partition(array, low, high);

        quickSort(array, low, p - 1);
        quickSort(array, p + 1, high);
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