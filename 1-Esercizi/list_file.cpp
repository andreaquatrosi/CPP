#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
class Node {

    private:
        T value;
        Node<T>* next;
        Node<T>* prev;
    
    public:
        Node() : value(T()), next(nullptr), prev(nullptr) {}
        Node(T value) : value(value), next(nullptr), prev(nullptr) {}

        // Getter
        T get_value() const { return value; }
        Node<T>* get_next() const { return next; }
        Node<T>* get_prev() const { return prev; }

        // Setter
        void set_value(T value) { this->value = value; }
        void set_next(Node<T>* next) { this->next = next; }
        void set_prev(Node<T>* prev) { this->prev = prev; }
};

template <typename T>
class List {

    private:
        Node<T>* head;
        Node<T>* tail;

    public:
        List() : head(nullptr), tail(nullptr) {}

        ~List() {

            Node<T>* temp = head;
            Node<T>* nextNode;

            while(temp != nullptr) {
                nextNode = temp;
                delete temp;
                temp = temp->get_next();
            }
        }

        // Operazioni
        bool is_empty() { return head == nullptr; }

        void push_head(T value) {

            Node<T>* newNode = new Node<T>(value);

            if(this->is_empty()) {
                head = newNode;
                return;
            }

            newNode->set_next(head);
            head->set_prev(newNode);
            head = newNode;
        }

        void push_tail(T value) {

            Node<T>* newNode = new Node<T>(value);

            if(this->is_empty()) {
                head = newNode;
                return;
            }

            Node<T>* temp = head;

            while(temp->get_next() != nullptr)
                temp = temp->get_next();

            temp->set_next(newNode);
            newNode->set_prev(temp);
        }

        void push_sorted(T value) {

            Node<T>* newNode = new Node<T>(value);

            if(this->is_empty() || value < head->get_value()) {
                newNode->set_next(head);

                if(head != nullptr)
                    head->set_prev(newNode);

                head = newNode;
                return;
            }

            Node<T>* temp = head;
            
            while(temp->get_next() != nullptr && value > temp->get_next()->get_value())
                temp = temp->get_next();
            
            newNode->set_next(temp->get_next());

            if(temp->get_next() != nullptr)
                temp->get_next()->set_prev(newNode);

            temp->set_next(newNode);
            newNode->set_prev(temp);
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

int main() {

    List<int> list;

    ifstream fin("text.txt");

    if(!fin) {
        cerr << "\nError while opening the file...\n";
        return -1;
    }

    int value;
    while(fin >> value)
        list.push_sorted(value);

    list.display();

    return 0;
}