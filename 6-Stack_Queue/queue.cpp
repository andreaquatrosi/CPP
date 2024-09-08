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
        Node<T>* tail;

    public:
        List() : head(nullptr), tail(nullptr) {}

        ~List() {
            while (!is_empty())
                dequeue();
        }

        // Operazioni
        bool is_empty() { return head == nullptr; }

        void enqueue(const T value) {
            Node<T>* newNode = new Node<T>(value);

            if (is_empty()) {
                head = tail = newNode;
            } else {
                tail->set_next(newNode); // Link the current tail to the new node
                tail = newNode;           // Update tail to the new node
            }
        }

        T dequeue() {
            if (is_empty()) {
                cout << "Queue is empty!" << endl;
                exit(EXIT_FAILURE); // Or throw an exception
            }

            Node<T>* temp = head;
            T value = head->get_value();
            head = head->get_next();

            if (head == nullptr)
                tail = nullptr;

            delete temp;

            return value;
        }

        T peek() const {
            return head->get_value();
        }

        void display() const {
            Node<T>* current = head;

            while (current != nullptr) {
                cout << current->get_value() << " -> ";
                current = current->get_next();
            }

            cout << "nullptr\n";
        }
};

template <typename T>
class Queue {
    private:
        List<T> list;

    public:
        void enqueue(const T value) {
            list.enqueue(value);
        }

        void dequeue() {
            list.dequeue();
        }

        T peek() const {
            return list.peek();
        }

        void display() {
            list.display();
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

        switch (risposta) {
        case 1:
            int value;
            cout << "\nInserisci un valore: ";
            cin >> value;
            queue.enqueue(value);
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
