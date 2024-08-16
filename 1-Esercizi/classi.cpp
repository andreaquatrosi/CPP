#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

class ContoBancario {

    private:
        int numeroConto;
        char* intestatario;
        double saldo;
    
    public:
        ContoBancario(int nc, char* i, double s): numeroConto(nc), intestatario(new char [100]), saldo(s) {
            strcpy(intestatario, i);
        } 

        // Metodi Getter
        int get_numeroConto() const {

            return numeroConto;
        }

        char* get_intestatario() const {

            return intestatario;
        }

        double get_saldo() const {

            return saldo;
        }

        // Metodi Setter

        // Funzionamento della Classe
        void Deposito(double importo) {
            // aggiunge un importo specificato al saldo del conto
            saldo += importo;
        }

        bool Prelievo(double importo) {

            if(saldo == 0 || importo > saldo) {
                cout << "\nSaldo insufficiente\n";
                return false;
            } else {
                saldo -= importo;
                return true;
            }
        }

        void MostraSaldo() {
            cout << "\nSaldo corrente: " << saldo << "\n";
        }

        void MostraDettagli() {
            cout << "\nDettagli del Conto:"
                 << "\nID conto: " << numeroConto
                 << "\nIntestatario: " << intestatario
                 << "\nSaldo: " << saldo
                 << "\n";
        }

        ~ContoBancario() {
            delete [] intestatario;
        }
};

int main() {

    cout << "Inserisci il nome dell'intestatario: ";
    char* nome = new char [20];
    cin.getline(nome, 20);

    double saldo;
    cout << "Ciao " << nome << ", inserisci il tuo saldo: ";
    cin >> saldo;

    // Istanza della Classe
    ContoBancario cb(58886, nome, saldo);

    // Manipolazione della Classe tramite l'Oggetto
    int id;
    cout << "Inserisci l'ID del tuo conto: ";
    cin >> id;
    
    if(id != cb.get_numeroConto()) {
        cout << "\nConto non valido.";
        exit(EXIT_FAILURE);
    } else {
        cb.MostraDettagli();
    }
    
    // Deposito
    char risposta;
    double importo;
    do {
        cb.MostraSaldo();
        cout << "[Inserisci l'importo da depositare nel tuo conto]: ";
        cin >> importo;

        cout << "Vuoi inserire altri soldi? ";
        cin >> risposta;

        cb.Deposito(importo);
    } while(risposta == 'y' || risposta == 'Y');

    // Prelievo
    bool value;
    do {
        cb.MostraSaldo();
        cout << "[Inserisci l'importo da prelevare dal tuo conto]: ";
        cin >> importo;

        value = cb.Prelievo(importo);

        if(value) {
            cout << "Vuoi prelevare altri soldi? ";
            cin >> risposta; 
        } else if (!value && (!(risposta == 'y' || risposta == 'Y'))) {
            break;
        }

    } while(value);

    return 0;
}