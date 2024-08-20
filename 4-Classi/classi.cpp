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

        // Costruttore Default
        ContoBancario() : numeroConto(0), intestatario(nullptr), saldo(0.0) {
            intestatario = new char[1];
            intestatario[0] = '\0';
            counter++;
        }

        // Costruttore con parametri
        ContoBancario(int nc, char* i, double s): numeroConto(nc), intestatario(new char [100]), saldo(s) {
            strcpy(intestatario, i);
            counter++;
        } 

        // Metodi Getter
        int get_numeroConto() const {

            return this->numeroConto;
        }

        char* get_intestatario() const {

            return this->intestatario;
        }

        double get_saldo() const {

            return this->saldo;
        }

        // Metodi Setter
        void set_numeroConto(int numeroConto) {
            
            this->numeroConto = numeroConto;
        }

        void set_intestatario(char* intestatario) {
            
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

        // friend :D
        friend void bonus_Saldo(ContoBancario* accounts, int );

        friend ContoBancario& confronta_Saldi(ContoBancario& cb1, ContoBancario& cb2);

            // overloading output operator 
        friend ostream& operator << (ostream& os, ContoBancario& cb);

        // Distruttore
        ~ContoBancario() {
            delete [] intestatario;
        }
};  // ContoBancario{};

size_t ContoBancario::counter = 0;  // init static var

// Funzione Friend :D
void bonus_Saldo(ContoBancario* accounts, int N) {

    int ID;
    cout << "\nWich account shall receive a bonus? [Enter account ID]: ";
    cin >> ID;

    size_t i = 0;
    bool value;
    do {
        if(ID == accounts[i].get_numeroConto()) {
            cout << "\n" << accounts[i].get_intestatario() << " has received a bonus!\n";
            accounts[i].Deposito(1500);
            value = true;
        } else {
            value = false;
        }
            
        i++;
    } while(!value && i < N);

    if(!value) {
        system("CLS");
        cout << "\nThe given ID doesn't match an existing account.\n";
    }
}

ContoBancario& confronta_Saldi(ContoBancario& cb1, ContoBancario& cb2) {

    if(cb1.get_saldo() > cb2.get_saldo()) {
        return cb1;
    } else {
        return cb2;
    }
}

ostream& operator << (ostream& os, ContoBancario& cb) {
    os << "\nOverloading of <<\n" <<  cb.get_numeroConto() << " belongs to " << cb.get_intestatario() << " and it's current balance is " << cb.get_saldo() << "\n";
    return os;
}

// Functions
ContoBancario& findMaxSaldo(ContoBancario* accounts, int N) {

    ContoBancario* maxAccount = &accounts[0]; // Assume the first account is the max

    for (size_t i = 1; i < N; ++i) {
        maxAccount = &confronta_Saldi(*maxAccount, accounts[i]);
    }

    return *maxAccount;
}

void sort_Accounts(ContoBancario* accounts, int N) {

    for(size_t i = 1; i < N; i++) {
        double temp = accounts[i].get_saldo();

        size_t j = i;
        while((j > 0) && (temp < accounts[j - 1].get_saldo())) {
            accounts[j].set_saldo(accounts[j - 1].get_saldo());
            j--;
        }

        accounts[j].set_saldo(temp);
    }

    cout << "\nSorted accounts:\n";
}

void print_Accounts(ContoBancario* accounts, int N) {
    for(size_t i = 0; i < N; i++) {
        accounts[i].MostraDettagli();
    }
}

void free_memory(ContoBancario* accounts, int N, void* memory) {
    for (int i = 0; i < N; ++i) {
        accounts[i].~ContoBancario();
    }

    operator delete[](memory);

    memory = nullptr;
}

void init_accounts(ContoBancario* accounts, int N) {

    int ID;
    char* nome = new char [20];
    double saldo;

    for(size_t i = 0; i < N; i++) {
        cout << "\nEnter accounts data:";
        
        cout << "\nID: ";
        cin >> ID;
        
        cin.ignore();
        cout << "\nIntestatario: ";
        cin.getline(nome, 20);

        cout << "\nSaldo: ";
        cin >> saldo;

        new (&accounts[i]) ContoBancario(ID, nome, saldo);
    }
    
    delete [] nome;
}

// main
int main() {

    int N;
    cout << "Quanti conti bancari vuoi registrare? ";
    cin >> N;
   
    void* memory = operator new[](N * sizeof(ContoBancario));       // allocates raw memory that can contain N ContoBancario objects
    ContoBancario* accounts = static_cast<ContoBancario*>(memory);  // casting memory ptr (void*) into a ContoBancario ptr
    init_accounts(accounts, N);
    
    system("CLS");
    print_Accounts(accounts, N);

    // Operazioni con Funzione Friend
    bonus_Saldo(accounts, N);
    ContoBancario& richest_account = findMaxSaldo(accounts, N);
    cout << "\nThe richest account belongs to " << richest_account.get_intestatario() << "\n";

    cout << accounts[0]; // use of friend ostream& operator << function 

    // just functions
    sort_Accounts(accounts, N);
    print_Accounts(accounts, N);
    
    cout << "\nTotal of instances: " << accounts[0].counter;    // printing static variable "counter"

    // Freeing allocated memory
    free_memory(accounts, N, memory);

    return 0;
}