#include <iostream>

using namespace std;

template <typename T>
class Node {

    private:
        T value;
        Node<T>* next;

    public:
        Node() : value(T()), next(nullptr) {}
        Node(T value) : value(value), next(nullptr) {}

        // Getter
        T get_value() const { return value; }
        Node<T>* get_next() const { return this->next; }

        // Setter
        void set_next(Node<T>* next) { this->next = next; }
};

template <typename T>
class List {

    private:
        Node<T>* head;

    public:
        List() : head(nullptr) {}

        ~List() {
            while(!is_empty())
                dequeue();
        }

        // Operazioni
        bool is_empty() { return head == nullptr; }

        //   push_tail
        void enqueue(T value) { 

            Node<T>* newNode = new Node<T>(value);

            if(this->is_empty()) {
                newNode->set_next(head);
                head = newNode;
            } else {
                Node<T>* temp = head;

                while(temp->get_next() != nullptr)      // going through the list 'till the last but one node
                    temp = temp->get_next();

                temp->set_next(newNode);                // setting the last but one node to points to the newNode
            }
        }

       // extract_head
        T dequeue() {   

            if(this->is_empty()) {
                cout << "\nEmpty list!\n";
                exit(EXIT_FAILURE);
            } else {
                Node<T>* temp = head;
                T value = head->get_value();
                head = head->get_next();

                delete temp;
                
                return value;
            }
        }

        void display() const {
            
            Node<T>* temp = head;

            while(temp != nullptr) {
                cout << temp->get_value() << " -> ";
                temp = temp->get_next();
            }

            cout << "nullptr\n";
        }
};

template <typename T>
class Queue {
    private:
        List<T> list; // Usa la lista per implementare la coda

    public:

        // Aggiunge un elemento in fondo alla coda
        void enqueue(T value) {
            list.enqueue(value);
        }

        // Rimuove e restituisce l'elemento all'inizio della coda
        T dequeue() {
            return list.dequeue();
        }

        // Controlla se la coda è vuota
        bool is_empty() const {
            return list.is_empty();
        }

        // Stampa gli elementi nella coda
        void print_queue() const {
            list.display();
        }
};

int main() {
    Queue<char*> queue;
    
    cout << "Welcome to your -queue type- shopping list!\n";
    int response;

    do {
        cout << "\nChoose your operation:\n"
             << "1. Add item\n"
             << "2. Clear item\n"
             << "3. Print shopping list\n"
             << "-1. Exit\n";
        
        cin >> response;

        char* item = new char [126];
        switch (response) {
            case 1:
                cin.ignore();
                cin.getline(item, 126);
                queue.enqueue(item);
                break;
            
            case 2:
                cout << "\nItem cleared.\n";
                queue.dequeue();
                break;
            
            case 3:
                cout << "\nShopping list:\n";
                queue.print_queue();
                break;
            
            case -1:
                cout << "\nNow exiting...\n";
                break;

            default:
                cout << "\nInvalid option...\n";
                break;
        }
    } while(response != -1);

    return 0;
}
