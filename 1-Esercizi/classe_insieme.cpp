/* 
    Scrivere una classe Insieme che gestisca un insieme di interi con 
    l’aiuto di una tabella di dimensione fissa (un insieme contiene un
    vettore ordinato di elementi che si caratterizza per il fatto che ogni
    elemento è unico). 
    Le operazioni da implementare sono le seguenti:
        • svuotare() svuota l’insieme;
        • aggiunge() aggiunge un intero all’insieme;
        • elimina() rimuove un intero dall’insieme;
        • unisce() unisce nell'insieme un altro;
        • membro() restituisce un valore booleano che indica se l’insieme con-
        tiene un certo intero;
        • uguale() restituisce un valore booleano che indica se un insieme è
        uguale a un altro;
        • stampa() stampa a schermo l’insieme in maniera leggibile.
*/

// SUGGERIMENTO: Supponiamo che i numeri vadano da 1 a 100

#include <iostream>

using namespace std;

class Insieme {

    private:
        int* interi;
        int dimensione;

    public:

        // Default
        Insieme() : dimensione(0), interi(nullptr) {

            cout << "\nCostruttore di Default\n";
        }

        // Parametrized
        Insieme(int N) : dimensione(N), interi(nullptr) {

            interi = new int [dimensione];
            for(size_t i = 0; i < dimensione; i++)
                interi[i] = 0;

            cout << "\nCostruttore Parametrizzato\n";
        }

        // Copy
        /*Insieme(Insieme& ins) {
            
            dimensione = ins.dimensione;
            interi = new int [dimensione];

            for(size_t i = 0; i < dimensione; i++)
                interi[i] = ins.interi[i];

            cout << "\nCostruttore di Copia\n";
        }*/

        ~Insieme() {

            delete [] interi;        
        }

        // Getter
        int* get_interi() const { return interi; }
        int get_number(size_t i) const { return interi[i]; }
        int get_dimensione() const { return dimensione; }

        // Setter
        void set_dimensione(int N) { 
            if(interi) {
                delete [] interi;
            }

            dimensione = N;
            interi = new int [dimensione];

            for(size_t i = 0; i < dimensione; i++)
                interi[i] = 0;
        }

        // Metodi
        void stampa() const {
            
            cout << "\nInsieme:\n";
            for(size_t i = 0; i < dimensione; i++)
                cout << interi[i] << " ";

            cout << "\n";
        }

        void svuotare() {

            if(interi) {
                for(size_t i = 0; i < dimensione; i++)
                    interi[i] = 0;

                cout << "\nL'insieme e' stato svuotato correttamente\n";
            } else {
                cout << "\nImpossibile usare svuotare(), l'insieme non esiste\n";
            }
        }

        void aggiunge(int element, size_t i) {

            if(interi) {
                if(i <= dimensione || interi[i] == 0)
                    interi[i] = element;
                else    // Error check
                    if(i > dimensione)
                        cout << "\nIndice troppo grande. Dimensione: " << dimensione << "\n";
                    else
                        cout << "\nE' presente un elemento in posizione " << i << ": " << interi[i] << "\n";
            } else {
                cout << "\nImpossibile usare aggiunge(), l'insieme non esiste...\n";
            }
        }

        void elimina(size_t i) {

            if(interi) {
                if(i <= dimensione || interi[i] != 0) {
                    cout << "\nElemento " << interi[i] << " eliminato correttamente\n";
                    interi[i] = 0;
                } else  // Error check
                    if(i > dimensione)
                        cout << "\nIndice troppo grande. Dimensione: " << dimensione << "\n";
                    else
                        cout << "\nNessun elemento da eliminare\n";
            } else {
                cout << "\nImpossibile usare elimina(), l'insieme non esiste...\n";
            }
        }

        void unisce(Insieme ins) {

            if(interi) {

                int* copia = new int [dimensione];

                for(size_t i = 0; i < dimensione; i++)
                    copia[i] = interi[i];

                int temp_dim = dimensione;
                ins.dimensione += temp_dim;
                set_dimensione(ins.dimensione);

                size_t j = 0;
                for(size_t i = 0; i < dimensione; i++) {
                    if(i >= temp_dim) {
                        aggiunge(ins.interi[j], i);
                        j++;
                    } else {
                        aggiunge(copia[i], i);
                    }
                } 

                delete [] copia;
            } else {
                set_dimensione(ins.dimensione);

                for(size_t i = 0; i < get_dimensione(); i++)
                    interi[i] = ins.interi[i];
            }
        }

        bool membro(int element) {
            
            if(interi) {
                for(size_t i = 0; i < dimensione; i++) {
                    if(element == interi[i]) {
                        return true;
                    }
                }

                return false;
            }
            
            cout << "\nImpossibile usare membro(), l'insieme non esiste...\n";
            
            return false; 
        }
};

int main() {

    cout << "Inserisci numero di interi: ";
    int N;
    cin >> N;

    Insieme ins(N);

    ins.stampa();
    
    ins.aggiunge(69, 0);
    ins.aggiunge(420, N-1);

    ins.stampa();

    ins.elimina(0);

    ins.stampa();

    N += 2;
    Insieme ins1(N);

    ins1.aggiunge(5, 0);
    ins1.aggiunge(10, 1);
    ins1.aggiunge(4, 10);

    ins.unisce(ins1);
    ins.stampa();

    if(ins.membro(69))
        cout << "\nElemento trovato\n";
    else
        cout << "\nElemento non trovato\n";

    ins.svuotare();

    return 0;
}