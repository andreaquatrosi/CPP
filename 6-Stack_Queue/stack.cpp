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
        Node<T>* get_next() { return next; }

        // Setter
        void set_value(T value) { this->value = value; }
        void set_next(Node<T>* next) { this->next = next; } 
};

template <typename T>
class List {
    private:
        Node<T>* head;

    public:
        List() : head(nullptr) {}

        ~List() {
            if(!is_empty())
                pop();
        }

        // Operazioni
        bool is_empty() { return head == nullptr; }

        void push(const T value) {

            Node<T>* newNode = new Node<T>(value);

            if(is_empty()) {
                head = newNode;

                return;
            }

            newNode->set_next(head);
            head = newNode;
        }

        T pop() {

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

            Node<T>* temp = head;

            while(temp != nullptr) {
                cout << temp->get_value() << "\n";
                temp = temp->get_next();
            }

            cout << "\n";
        }
};

template <typename T>
class Stack {
    private:
        List<T> list;

    public:
        void push(const T value) {
            list.push(value);
        }

        T pop() {
            return list.pop();
        }

        T peek() {
            return list.peek();
        }

        void display() const {
            list.display();
        }
};

int main() {

    Stack<int> stack;

    int risposta;

    do {
        cout << "Scegli un opzione [Inserire -1 per uscire]:";
        cout << "\n[1] Push: "
             << "\n[2] Pop: "
             << "\n[3] Peek: "
             << "\n[4] Display: "
             << "\n";
        cin >> risposta;

        system("CLS");

        switch(risposta) {
            case 1:
                int value;
                cout << "\nInserisci un valore: ";
                cin >> value;

                stack.push(value);
                break;
            case 2:
                stack.pop();
                break;
            case 3:
                cout << "\nLa testa e': " << stack.peek() << "\n";
                break;
            case 4:
                stack.display();
                break;
            default:
                cout << "\nNow exiting...\n";
        }
    } while(risposta != -1);

    return 0;
}