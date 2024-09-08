#include <iostream>
#include <string>

using namespace std;

/* aggiungere funzione enqueuePriority() */

class Patient {
    private:
        static size_t size;
        int id;
        string name;
        string condition;

        Patient* next;

    public:
        Patient() : name(""), condition(""), id(0), next(nullptr) {}
        Patient(const string name, const string condition, int id) : name(name), condition(condition), id(id), next(nullptr) {
            size++;
        }

        // Getter
        string get_name() const { return name; }
        string get_condition() const { return condition; }
        int get_id() { return id; }
        Patient* get_next() { return next; }

        // Setter
        void set_name(const string name) { this->name = name; }
        void set_condition(const string condition) { this->condition = condition; }
        void set_id(int id) { this->id = id; }
        void set_next(Patient* next) { this->next = next; }

        // Friend
        friend ostream& operator<<(ostream& os, Patient& patient) {
            
            os << "\nID: " << patient.id
               << "\nName: " << patient.name
               << "\nCondition: " << patient.condition
               << "\n";

            return os;
        }
};

size_t Patient::size = 0;

template <typename T>
class Queue {
    private:
        Patient* head;
        Patient* tail;

    public:
        Queue() : head(nullptr), tail(nullptr) {}
        ~Queue() {
            while(!is_empty())
                dequeue();
        }

        bool is_empty() { return head == nullptr; }

        void enqueue(const string name, const string condition, int id) {
            
            Patient* patient = new Patient(name, condition, id);

            if(is_empty()) {
                head = tail = patient;

                return;
            }

            tail->set_next(patient);
            tail = patient;
        }

        Patient* dequeue() {

            if(is_empty())
                return nullptr;

            Patient* temp = head;
            head = head->get_next();
            temp->set_next(nullptr);

            return temp;
        }

        void display() const {

            Patient* current = head;

            while(current != nullptr) {
                cout << *current;
                current = current->get_next();
            }
        }
};

int main() {

    Queue<Patient> queue;
    
    int id, risposta;
    string name, condition;

    do {
        cout << "\nScegli operazione:\n";
        cout << "[1] Enqueue: \n"
             << "[2] Dequeue: \n"
             << "[3] Display: \n"
             << "[-1] Exit: \n";
        cin >> risposta;

        system("CLS");

        switch(risposta) {
            case 1:
                
                cout << "\nInserisci l'ID del paziente: ";
                cin >> id;

                cin.ignore();
                cout << "\nInserisci il nome del paziente " << id << ": ";
                getline(cin, name);

                cout << "\nInserisci la condizione del paziente " << name << " con ID " << id << ": ";
                getline(cin, condition);

                queue.enqueue(name, condition, id);

                break;
            case 2:
                queue.dequeue();
                break;
            case 3:
                queue.display();
                break;
            default:
                cout << "\nNow exiting...\n";
        }
    } while(risposta != -1);

    return 0;
}