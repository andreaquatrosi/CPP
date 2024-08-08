#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

// Inizializza Matrice
int** init_Matrix(size_t N, size_t M) {

    int** mtx = new int* [N];
    for(size_t i = 0; i < N; i++) {
        mtx[i] = new int [M];
    }

    cout << "Enter matrix elements:\n";
    for(size_t i = 0; i < N; i++) {
        for(size_t j = 0; j < M; j++) {
            cin >> mtx[i][j];
        }
    }

    return mtx;
}

// Stampa Matrice
void print(int** mtx, size_t N, size_t M) {

    cout << "\nMatrix:\n";
    for(size_t i = 0; i < N; i++) {
        for(size_t j = 0; j < M; j++) {
            cout << mtx[i][j] << " ";
        }
        
        cout << "\n";
    }
}

// Scrive Matrice su File
void write_Matrix(int** mtx, size_t N, size_t M, const char* fileName) {

    ofstream fout(fileName, ios::app);

    if(!fout) {
        cerr << "Error while opening the file.\n";
        return;
    }

    for(size_t i = 0; i < N; i++) {
        for(size_t j = 0; j < M; j++) {
            fout << mtx[i][j] << " ";
        }
        
        fout << "\n";
    }

    fout.close();
}

// Libera spazio occupato dalla Matrice
void dealloc_Matrix(int** mtx, size_t N) {

    for(size_t i = 0; i < N; i++) {
        delete [] mtx[i];
    }

    delete [] mtx;
    mtx = nullptr;

    if(mtx == nullptr) {
        cout << "\nmtx = nullptr\n";
    } else {
        cerr << "Error while freeing matrix.\n";
        return;
    }
}

// --
int main() {

    char* fileName = new char [100];
    cout << "Enter file name: ";
    cin.getline(fileName, 100);

    size_t N = 2, M = 3;
    int** matrix = init_Matrix(N, M);

    // func. calls
    print(matrix, N, M);
    dealloc_Matrix(matrix, N);
    write_Matrix(matrix, N, M, fileName);

    return 0;
}