#include <iostream>

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
            Node<T>* current = head;
            Node<T>* nextNode;

            while (current != nullptr) {
                nextNode = current->get_next();
                delete current;
                current = nextNode;
            }
        }

        // Operazioni
        bool is_Empty() const { return head == nullptr; }

        void push_head(T value) {

            Node<T>* newNode = new Node<T>(value);

            if(this->is_Empty()) {
                head = newNode;
            } else {
                newNode->set_next(head);
                head->set_prev(newNode);
                head = newNode;
            }
        }

        void push_tail(T value) {

            Node<T>* newNode = new Node<T>(value);

            if(this->is_Empty()) {
                head = newNode;
            } else {
                Node<T>* temp = head;

                while(temp->get_next() != nullptr)
                    temp = temp->get_next();
                
                temp->set_next(newNode);
                newNode->set_prev(temp);
            }
        }

        void push_sorted(T value) {
            
            Node<T>* newNode = new Node<T>(value);

            if(this->is_Empty() || value < head->get_value()) {
                newNode->set_next(head);

                if(head != nullptr)
                    head->set_prev(newNode);
                
                head = newNode;
            } else {
                Node<T>* current = head;

                while(current->get_next() != nullptr && value > current->get_next()->get_value())
                    current = current->get_next();

                newNode->set_next(current->get_next());

                if(current->get_next() != nullptr)
                    current->get_next()->set_prev(newNode);

                current->set_next(newNode);
                newNode->set_prev(current);
            }       
        }

        T extract_head() {

            if(this->is_Empty()) {
                cout << "\nThe list's empty!\n";
                exit(EXIT_FAILURE);
            } else {

                Node<T>* temp = head;
                T value = head->get_value();
                head = head->get_next();

                if(head != nullptr)
                    head->set_prev(nullptr);

                delete temp;

                return value;
            }
        }

        T extract_tail() {

            if(this->is_Empty()) {
                cout << "\nThe list's empty!\n";
                exit(EXIT_FAILURE);
            } else {

                Node<T>* temp = head;

                while(temp->get_next() != nullptr)
                    temp = temp->get_next();
                
                T value = temp->get_value();

                if(temp->get_prev() != nullptr)
                    temp->get_prev()->set_next(nullptr);
                else
                    head = nullptr;
                
                delete temp;

                return value;
            }
        }

        bool extract_element(T value) {

            if(this->is_Empty()) {
                cout << "\nThe list's empty\n";
                exit(EXIT_FAILURE);
            } else {

                Node<T>* temp = head;

                while(temp != nullptr && value != temp->get_value())
                    temp = temp->get_next();

                if(temp == nullptr)
                    return false;
                
                if(temp->get_prev() != nullptr)
                    temp->get_prev()->set_next(temp->get_next());
                else    head = temp->get_next();    // element is in the head

                if(temp->get_next() != nullptr)
                    temp->get_next()->set_prev(temp->get_prev());
                
                delete temp;

                return true;
            }
        }

        void print() const {

            Node<T>* current = head;

            while(current != nullptr) {
                cout << current->get_value() << " -> ";
                current = current->get_next();
            }

            cout << "nullptr\n";
        }
};

int main() {

    List<int> list;
    /*
    list.push_head(69);
    list.push_tail(420);
    list.push_head(90);
    list.push_tail(45);
    */

    list.push_sorted(50);
    list.push_sorted(20);
    list.push_sorted(60);
    list.push_sorted(30);
    list.push_sorted(40);

    list.print();

    list.extract_head();
    list.extract_tail();
    list.extract_element(30);

    list.print();

    return 0;
}