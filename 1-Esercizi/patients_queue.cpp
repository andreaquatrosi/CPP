#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

template <typename T>
class Node {
    private:
        T value;
        string priority;
        Node<T>* next;

    public:
        Node() : value(T()), priority(""), next(nullptr) {}
        Node(T value, string priority) : value(value), priority(priority), next(nullptr) {}

        // Getter
        T get_value() const { return value; }
        string get_priority() { return priority; }
        Node<T>* get_next() { return next; }

        // Setter
        void set_value(const T value) { this->value = value; }
        void get_priority(const string priority) { this->priority = priority; }
        void set_next(Node<T>* next) { this->next = next; }
};

template <typename T>
class Queue {
    private:
        Node<T>* head;
        Node<T>* tail;

    public:
        Queue() : head(nullptr), tail(nullptr) {}

        ~Queue() {
            while(!is_empty())
                dequeue();
        }

        // Operazioni
        bool is_empty() { return head == nullptr; }

        void enqueue(const T& value, const string& priority) {

            Node<T>* newNode = new Node<T>(value, priority);

            if(priority == "Green") {
                
                if(is_empty()) {
                    head = tail = newNode;

                    return;
                }

                tail->set_next(newNode);
                tail = newNode;
            }

            else if(priority == "Red") {

                Node<T>* current = head;
                Node<T>* prev = nullptr;

                while(current != nullptr && current->get_priority() != "Green") {
                    prev = current;
                    current = current->get_next();
                }

                if(prev == nullptr) {
                    newNode->set_next(head);
                    head = newNode;

                    return;
                }

                else {
                    prev->set_next(newNode);
                    newNode->set_next(current);
                }

                if(newNode->get_next() == nullptr)
                    tail = newNode;
            }
        }

        T dequeue() {

            if(is_empty())
                exit(EXIT_FAILURE);

            Node<T>* temp = head;
            T value = head->get_value();
            head = head->get_next();

            delete temp;

            return value;
        }

        T peek() const {

            return head->get_value();
        }

        void display() const {

            Node<T>* current = head;

            while(current != nullptr) {
                cout << current->get_value() << " -> ";
                current = current->get_next();
            }

            cout << "nullptr\n";
        }
};

int main() {
    
    Queue<int> queue;

    int risposta;

    do {
        cout << "Scegli un'opzione [Inserire -1 per uscire]:";
        cout << "\n[1] Enqueue: "
             << "\n[2] Dequeue: "
             << "\n[3] Peek: "
             << "\n[4] Display: "
             << "\n";
        cin >> risposta;

        system("CLS");

        string priority;
        switch (risposta) {
        case 1:
            int value;
            cout << "\nInserisci un valore: ";
            cin >> value;
            cout << "\nInserisci la priorita': ";
            cin >> priority;

            queue.enqueue(value, priority);
            break;
        case 2:
            queue.dequeue();
            break;
        case 3:
            cout << "\nLa coda e': " << queue.peek() << "\n";
            break;
        case 4:
            queue.display();
            break;
        default:
            cout << "\nNow exiting...\n";
        }
    } while (risposta != -1);

    return 0;
}