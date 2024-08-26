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

        void push_head(T value) {

            Node<T>* newNode = new Node<T>(value); // creazione Nodo

            newNode->set_next(head);    // newNode points to the current head
            head = newNode;             // newNode is the new head
        }

        void push_tail(T value) {

            Node<T>* newNode = new Node<T>(value);

            if(this->is_Empty()) {
                newNode->set_next(head);
                head = newNode;
            } else {
                Node<T>* temp = head;

                while(temp->get_next() != nullptr)      // going through the list 'till the last but one node
                    temp = temp->get_next();

                temp->set_next(newNode);                // setting the last but one node to points to the newNode
            }
        }

        void push_sorted(T value) {
            
            Node<T>* newNode = new Node<T>(value);

            if(this->is_Empty() || value < head->get_value()) {
                newNode->set_next(head);
                head = newNode;
            } else {
                Node<T>* current = head;
                Node<T>* prev = nullptr;

                while(current != nullptr && current->get_value() < value) {
                    prev = current;
                    current = current->get_next();
                }

                newNode->set_next(current);
                if(prev != nullptr)
                    prev->set_next(newNode);
            }
        }

        T extract_head() {

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

        T extract_tail() {

            if(this->is_Empty()) {
                cout << "\nEmpty list!\n";
                exit(EXIT_FAILURE);
            } else {
                Node<T>* temp = head;
                Node<T>* prev = nullptr;

                while(temp->get_next() != nullptr) {
                    prev = temp;
                    temp = temp->get_next();
                }

                T value = temp->get_value();

                if(prev != nullptr)
                    prev->set_next(nullptr);
                else
                    head = nullptr; // the list has only one element

                delete temp;

                return value;
            }
        }

        bool extract_element(T value) {

            if(this->is_Empty()) {
                cout << "\nEmpty list!\n";
                exit(EXIT_FAILURE);
            } else {

                if(value == head->get_value()) {
                    extract_head();
                    return true;
                }

                Node<T>* temp = head;
                Node<T>* prev = nullptr;

                while(temp != nullptr && value != temp->get_value()) {
                    prev = temp;
                    temp = temp->get_next();
                }

                if(temp == nullptr)
                    return false;

                if(prev == nullptr)
                    head = head->get_next();
                else    
                    prev->set_next(temp->get_next());
                    
                delete temp;

                return true;
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
            list.push_head(value);
        }

        // Rimuove e restituisce l'elemento in cima alla pila
        T pop() {
            return list.extract_head();
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
    Stack<int> stack;
    
    stack.push(10);
    stack.push(20);
    stack.push(30);

    stack.print_stack();

    cout << "Elemento rimosso: " << stack.pop() << endl;
    stack.print_stack();

    return 0;
}