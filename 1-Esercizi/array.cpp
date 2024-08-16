#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

// Inizializza Array
int* init_Array(size_t N) {

    int* A = new int [N];

    cout << "Enter array elements:\n";
    for(size_t i = 0; i < N; i++)
        cin >> A[i];

    return A;
}

// Stampa array
void print(int* A, size_t N) {

    cout << "\nArray: \n";

    for(size_t i = 0; i < N; i++) 
        cout << A[i] << " ";

    cout << "\n";
}

// Scrive Array su File
void write_Array(int* A, size_t N, const char* fileName) {

    ofstream fout(fileName, ios::app);

    if(!fout) {
        cerr << "Error while opening the file.\n";
        return;
    }

    for(size_t i = 0; i < N; i++) {
        fout << A[i] << " ";

        if(i == N-1) {
            fout << "\n";
        }
    }

    fout.close();
}

// Libera spazio occupato dall'Array
void dealloc_Array(int* A) {
    
    delete [] A;
    A = nullptr;

    if(A) {
        cerr << "\nError while deallocating the array.\n";
        return;
    }
}

int main() {

    char* fileName = new char [100];
    cout << "Enter file name: ";
    cin.getline(fileName, 100);

    constexpr size_t N = 8;

    int* array = init_Array(N);

    // func. calls
    print(array, N);
    write_Array(array, N, fileName);
    dealloc_Array(array);

    return 0;
}