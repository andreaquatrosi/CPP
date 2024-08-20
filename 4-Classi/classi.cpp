#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

// Creazione Classe
class ContoBancario {
    private:
        int numeroConto;
        char* intestatario;
        double saldo;

    public:
        static size_t counter;

        // Costruttore di Default
        ContoBancario() : numeroConto(0), intestatario(nullptr), saldo(0.0) {
            intestatario = new char[1];
            intestatario[0] = '\0';
            counter++;
        }

        // Costruttore con parametri
        ContoBancario(int nc, const char* i, double s) : numeroConto(nc), saldo(s) {
            intestatario = new char[strlen(i) + 1];
            strcpy(intestatario, i);
            counter++;
        }

        // Costruttore di Copia
        ContoBancario(const ContoBancario& other) : numeroConto(other.numeroConto), saldo(other.saldo) {
            intestatario = new char[strlen(other.intestatario) + 1];
            strcpy(intestatario, other.intestatario);
        }

        ContoBancario& operator=(const ContoBancario& other) {
            if (this != &other) {
                delete[] intestatario; // Free existing memory

                numeroConto = other.numeroConto;
                saldo = other.saldo;
                intestatario = new char[strlen(other.intestatario) + 1];
                strcpy(intestatario, other.intestatario);
            }
            return *this;
        }   

        // Metodi Getter
        int get_numeroConto() const {
            return numeroConto;
        }

        const char* get_intestatario() const {
            return intestatario;
        }

        double get_saldo() const {
            return saldo;
        }

        // Metodi Setter
        void set_numeroConto(int numeroConto) {
            this->numeroConto = numeroConto;
        }

        void set_intestatario(const char* intestatario) {
            delete [] this->intestatario;
            
            this->intestatario = new char[strlen(intestatario) + 1];
            strcpy(this->intestatario, intestatario);
        }

        void set_saldo(double saldo) {
            this->saldo = saldo;
        }

        // Funzionamento della Classe
        void Deposito(double importo) {
            saldo += importo;
        }

        bool Prelievo(double importo) {
            if (saldo < importo) {
                cout << "\nSaldo insufficiente\n";
                return false;
            } else {
                saldo -= importo;
                return true;
            }
        }

        void MostraSaldo() const {
            cout << "\nSaldo corrente: " << saldo << "\n";
        }

        void MostraDettagli() const {
            cout << "\nDettagli del Conto:"
                << "\nID conto: " << numeroConto
                << "\nIntestatario: " << intestatario
                << "\nSaldo: " << saldo
                << "\n";
        }

        // friend :D
        friend void bonus_Saldo(ContoBancario* accounts, int N);
        friend ContoBancario& confronta_Saldi(ContoBancario& cb1, ContoBancario& cb2);
        friend ostream& operator<<(ostream& os, const ContoBancario& cb);

        // Distruttore
        ~ContoBancario() {
            delete [] intestatario;
        }
};

size_t ContoBancario::counter = 0;  // init static var

// Funzione Friend :D
void bonus_Saldo(ContoBancario* accounts, int N) {
    int ID;
    cout << "\nWhich account shall receive a bonus? [Enter account ID]: ";
    cin >> ID;

    bool found = false;
    for (int i = 0; i < N; ++i) {
        if (ID == accounts[i].get_numeroConto()) {
            cout << "\n" << accounts[i].get_intestatario() << " has received a bonus!\n";
            accounts[i].Deposito(1500);
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nThe given ID doesn't match an existing account.\n";
    }
}

ContoBancario& confronta_Saldi(ContoBancario& cb1, ContoBancario& cb2) {
    return (cb1.get_saldo() > cb2.get_saldo()) ? cb1 : cb2;
}

ostream& operator<<(ostream& os, const ContoBancario& cb) {
    os << "\nOverloading of <<\n" << cb.get_numeroConto() << " belongs to " << cb.get_intestatario() << " and its current balance is " << cb.get_saldo() << "\n";
    return os;
}

// just functions
ContoBancario& findMaxSaldo(ContoBancario* accounts, int N) {
    ContoBancario* maxAccount = &accounts[0]; // Assume the first account is the max

    for (int i = 1; i < N; ++i) {
        maxAccount = &confronta_Saldi(*maxAccount, accounts[i]);
    }

    return *maxAccount;
}

void sort_Accounts(ContoBancario* accounts, int N) {
    for (int i = 1; i < N; i++) {
        ContoBancario temp = accounts[i];

        int j = i;
        while (j > 0 && temp.get_saldo() < accounts[j - 1].get_saldo()) {
            accounts[j] = accounts[j - 1];
            j--;
        }

        accounts[j] = temp;
    }

    cout << "\nSorted accounts:\n";
}

void print_Accounts(const ContoBancario* accounts, int N) {
    for (int i = 0; i < N; i++) {
        accounts[i].MostraDettagli();
    }
}

void free_memory(ContoBancario* accounts, int N, void* memory) {
    operator delete [] (memory);
}

void init_accounts(ContoBancario* accounts, int N) {
    for (int i = 0; i < N; i++) {
        int ID;
        char nome[100];
        double saldo;

        cout << "\nEnter account data:\n";

        cout << "ID: ";
        cin >> ID;

        cin.ignore();
        cout << "Intestatario: ";
        cin.getline(nome, 100);

        cout << "Saldo: ";
        cin >> saldo;

        new (&accounts[i]) ContoBancario(ID, nome, saldo);
    }
}

// main
int main() {
    int N;
    cout << "Quanti conti bancari vuoi registrare? ";
    cin >> N;

    void* memory = operator new[](N * sizeof(ContoBancario));       // allocates raw memory that can contain N ContoBancario objects
    ContoBancario* accounts = static_cast<ContoBancario*>(memory);  // casting memory ptr (void*) into a ContoBancario ptr
    init_accounts(accounts, N);

    print_Accounts(accounts, N);

    // Operazioni con Funzione Friend
    bonus_Saldo(accounts, N);
    ContoBancario& richest_account = findMaxSaldo(accounts, N);
    cout << "\nThe richest account belongs to " << richest_account.get_intestatario() << "\n";

    cout << accounts[0]; // use of friend ostream& operator << function 

    sort_Accounts(accounts, N);
    print_Accounts(accounts, N);

    cout << "\nTotal of instances: " << ContoBancario::counter << "\n";    // printing static variable "counter"

    // Freeing allocated memory
    free_memory(accounts, N, memory);

    return 0;
}