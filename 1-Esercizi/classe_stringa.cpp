/* 
    Implementare una classe Stringa.
    Ogni oggetto della classe rappresenta una stringa di caratteri.
    I membri dato sono la lunghezza della stringa e la stringa di
    caratteri attuale.
    Inoltre, si debbono aggiungere costruttori, distruttori, funzioni di 
    accesso e funzioni per visualizzare, e anche includere una funzione
    carattere(int i)
    che restituisca il carattere situato nell’indice i della stringa
*/

#include <iostream>
#include <cstring>

using namespace std;

class Stringa {

    private:
        int lenght;
        char* stringa;

    public:
        Stringa() : lenght(1), stringa(nullptr) {
            stringa = new char [lenght];
            stringa[0] = '\0';

            cout << "\nCostruttore di Default\n";
        }

        Stringa(char* s) : lenght(strlen(s)), stringa(nullptr) {
            stringa = new char [lenght + 1];
            strcpy(stringa, s);

            cout << "\nCostruttore Parametrizzato\n";
        }

        Stringa(Stringa& str) {
            lenght = str.lenght;

            stringa = new char [lenght + 1];
            strcpy(stringa, str.stringa);

            cout << "\nCostruttore di Copia\n";
        }

        ~Stringa() {
            delete [] stringa;
        }

        // Getter
        int get_lenght() { return lenght; }
        char* get_stringa() { return stringa; }

        // Setter
        void set_stringa(const char* str) {
            delete [] stringa;

            lenght = strlen(str);
            stringa = new char [lenght + 1];
            strcpy(stringa, str);
        }

        // Metodi
        void visualizza() {
            
            if(lenght > 1) {
                cout << "\nLa stringa e': "
                    << stringa
                    << "\n";
            } else {
                cout << "\nLa stringa e' vuota...\n";
            }
        }

        char carattere(size_t i) {
            
            return (i <= lenght) ? stringa[i] : 'z';
        }
};

int main() {

    Stringa str1;                       // Default

    cout << "\nInserisci la stringa: ";
    char* stringa = new char [126];
    cin.getline(stringa, 126);
    Stringa str2(stringa);              // Parametrized

    Stringa str3(str2);                 // Copy

    str1.visualizza();
    str2.visualizza();
    str3.visualizza();

    cout << "\nLunghezza di " << str2.get_stringa() << ": " << str2.get_lenght() << "\n";
    
    cout << "\nInserisci un indice: ";
    size_t i;
    cin >> i;

    if(str2.carattere(i) != 'z')
        cout << "\nIl carattere al posto " << i << " di " << str2.get_stringa() << " e': " << str2.carattere(i);
    else
        cout << "\nL'indice non appartiene alla stringa";

    return 0;
}