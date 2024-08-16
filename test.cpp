#include <iostream>

using namespace std;

int main() {

    char* nome = new char [10];

    cin.getline(nome, 10);
    cout << nome;

    return 0;
}