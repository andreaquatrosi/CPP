#include <iostream>
#include <string>

using namespace std;

class Patient {
    private:
        static size_t size;
        int id;
        string name;
        string condition;
        string priority;

        Patient* next;

    public:
        Patient() : name(""), condition(""), priority(""), id(0), next(nullptr) {}

        Patient(const string name, const string condition, int id) : name(name), condition(condition), priority("No"), id(id), next(nullptr) {
            size++;
        }

        Patient(const string name, const string condition, string priority, int id) : name(name), condition(condition), priority(priority), id(id), next(nullptr) {
            size++;
        }

        // Getter
        string get_name() const { return name; }
        string get_condition() const { return condition; }
        string get_priority() const { return priority; }
        int get_id() { return id; }
        size_t get_size() { return size; }
        Patient* get_next() { return next; }

        // Setter
        void set_name(const string name) { this->name = name; }
        void set_condition(const string condition) { this->condition = condition; }
        void set_priority(const string priority) { this->priority = priority; }
        void set_id(int id) { this->id = id; }
        void set_next(Patient* next) { this->next = next; }

        // Friend
        friend ostream& operator<<(ostream& os, Patient& patient) {
            
            os << "\nID: " << patient.id
               << "\nName: " << patient.name
               << "\nCondition: " << patient.condition
               << "\nPriority: " << patient.priority
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

        void enqueuePriority(const string priority, const string name, const string condition, int id) {

            Patient* patient = new Patient(name, condition, priority, id);

            if(is_empty()) {
                head = tail = patient;

                return;
            }

            Patient* current = head;
            Patient* prev = nullptr;
            
            size_t pos;
            do {
                cout << "Quante posizioni guadagna? [Fino a 3] ";
                cin >> pos;
            } while(pos < 1 || pos > 3);

            size_t i = 1;
            while(current != nullptr && i != current->get_size()-pos) {
                prev = current;
                current = current->get_next();
                i++;
            }

            if(current == nullptr) {
                tail->set_next(patient);
                tail = patient;

                return;
            }

            prev->set_next(patient);
            patient->set_next(current);

            if(patient->get_next() == nullptr)
                tail = patient;
        }

        Patient* dequeue() {

            if(is_empty())
                return nullptr;

            Patient* temp = head;
            head = head->get_next();
            temp->set_next(nullptr);

            Patient* toDelete = temp;
            delete toDelete;

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
    string name, condition, priority;

    do {
        cout << "\nScegli operazione:\n";
        cout << "[1] Enqueue: \n"
             << "[2] Enqueue Priority: \n"
             << "[3] Dequeue: \n"
             << "[4] Display: \n"
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
                cout << "\nInserisci l'ID del paziente: ";
                cin >> id;

                cin.ignore();
                cout << "\nInserisci il nome del paziente " << id << ": ";
                getline(cin, name);

                cout << "\nInserisci la condizione del paziente " << name << " con ID " << id << ": ";
                getline(cin, condition);

                cout << "\nQual e' la sua priorita'? ";
                getline(cin, priority);

                queue.enqueuePriority(name, condition, priority, id);

                break;
            case 3:
                queue.dequeue();
                break;
            case 4:
                queue.display();
                break;
            default:
                cout << "\nNow exiting...\n";
        }
    } while(risposta != -1);

    return 0;
}