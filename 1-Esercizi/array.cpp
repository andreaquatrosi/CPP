#include <iostream>
#include <cstdlib>
#include <string>
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
void write_Array(int* A, size_t N, const string fileName) {

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

    string fileName;
    cout << "Enter file name: ";
    getline(cin, fileName);

    constexpr size_t N = 8;
    int* array = init_Array(N);

    // func. calls
    print(array, N);
    write_Array(array, N, fileName);
    dealloc_Array(array);

    return 0;
}