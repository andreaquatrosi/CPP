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
        Node<T>* get_next() const { return next; }

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
        bool is_empty() { return head == nullptr; }

        void push_head(T value) {

            Node<T>* newNode = new Node<T>(value);

            if(this->is_empty()) {
                head = newNode;
            } else {

                newNode->set_next(head);
                head = newNode;
            }
        }

        T extract_head() {

            if(this->is_empty()) {
                cout << "\nList's empty...\n";
                exit(EXIT_FAILURE);
            } else {
                Node<T>* temp = head;
                T value = head->get_value();
                head = head->get_next();

                delete temp;

                return value;
            }
        }

        void peek_head() const { cout << "Head of the list: " << head->get_value() << "\n"; }

        bool extract_element(T value) {

            if(this->is_empty()) {
                cout << "\nList's empty...\n";
                exit(EXIT_FAILURE);
            } else {
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

        void print() const {

            Node<T>* current = head;

            while(current != nullptr) {
                cout << current->get_value()
                     << " -> ";
                current = current->get_next();
            }

            cout << "nullptr\n";
        }
};

int main(int argc, char** argv) {

    List<int> list;

    list.push_head(69);
    list.push_head(420);
    list.push_head(90);
    list.push_head(69);

    list.print();

    list.peek_head();

    // list.extract_head();
    list.extract_element(69);

    list.print();

    return 0;
}