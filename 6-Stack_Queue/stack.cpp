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
            Node<T>* current = head;
            Node<T>* nextNode;

            while(current != nullptr) {
                nextNode = current->get_next();
                delete current;
                current = nextNode;
            }

            delete nextNode;
        }

        // Operazioni
        bool is_Empty() { return head == nullptr; }

        //   push_head
        void push(T value) {

            Node<T>* newNode = new Node<T>(value); // creazione Nodo

            newNode->set_next(head);    // newNode points to the current head
            head = newNode;             // newNode is the new head
        }

       // extract_head
        T pop() {

            if(this->is_Empty()) {
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

        void print_list() const {
            
            Node<T>* temp = head;

            while(temp != nullptr) {
                cout << temp->get_value() << " -> ";
                temp = temp->get_next();
            }

            cout << "nullptr\n";
        }
};

template <typename T>
class Stack {
    private:
        List<T> list; // Usa la lista per implementare la pila

    public:
        // Aggiunge un elemento in cima alla pila
        void push(T value) {
            list.push(value);
        }

        // Rimuove e restituisce l'elemento in cima alla pila
        T pop() {
            return list.pop();
        }

        // Controlla se la pila è vuota
        bool is_empty() const {
            return list.is_Empty();
        }

        // Stampa gli elementi nella pila
        void print_stack() const {
            list.print_list();
        }
};

int main() {
    Stack<char*> stack;
    
    cout << "Welcome to your -stack type- shopping list!\n";
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
                stack.push(item);
                break;
            
            case 2:
                cout << "\nItem cleared.\n";
                stack.pop();
                break;
            
            case 3:
                cout << "\nShopping list:\n";
                stack.print_stack();
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