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
        Node<T>* get_next() { return next; }
        Node<T>* get_prev() { return prev; }

        // Setter
        void set_value(const T value) {this->value = value; }
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
            Node<T>* nextNode = nullptr;

            while(current != nullptr) {
                nextNode = current->get_next();
                delete current;
                current = nextNode;
            }

            if(nextNode)
                delete nextNode;
        }

        // Operazioni
        bool is_empty() { return head == nullptr; }

        void push_head(const T value) {
            
            Node<T>* newNode = new Node<T>(value);

            if(this->is_empty()) {
                head = tail = newNode;
                
                return;
            }

            newNode->set_next(head);
            head->set_prev(newNode);
            head = newNode;
        }

        void push_tail(const T value) {

            Node<T>* newNode = new Node<T>(value);

            if(this->is_empty()) {
                head = tail = newNode;
                
                return;
            }

            newNode->set_prev(tail);
            tail->set_next(newNode);
            tail = newNode;
        }

        void push_sorted(const T value) {
            
            Node<T>* newNode = new Node<T>(value);

            if(this->is_empty() || value < head->get_value()) {
                newNode->set_next(head);
                
                if(head != nullptr)
                    head->set_prev(newNode);
                
                head = newNode;
                
                if(tail == nullptr)
                    tail = newNode;
                
                return;
            }

            else if(value > tail->get_value()) {
                newNode->set_prev(tail);
                tail->set_next(newNode);
                tail = newNode;

                return;
            }

            Node<T>* current = head;

            while(current != nullptr && value > current->get_value())
                current = current->get_next();

            current->get_prev()->set_next(newNode);
            newNode->set_prev(current->get_prev());

            newNode->set_next(current);
            current->set_prev(newNode);
        }

        T extract_head() {
            
            if(this->is_empty())
                exit(EXIT_FAILURE);

            Node<T>* temp = head;
            T value = head->get_value();
            head = head->get_next();

            if(head != nullptr)
                head->set_prev(nullptr);
            else
                tail = nullptr;

            delete temp;

            return value;
        }

        T extract_tail() {

            if(this->is_empty())
                exit(EXIT_FAILURE);

            Node<T>* temp = tail;
            T value = tail->get_value();
            tail = tail->get_prev();

            if(tail != nullptr)
                tail->set_next(nullptr);
            else
                head = nullptr;

            delete temp;

            return value;
        }

        bool extract_element(const T value) {

            if(this->is_empty())
                exit(EXIT_FAILURE);

            if(value == head->get_value()) {
                extract_head();
                return true;
            }

            else if(value == tail->get_value()) {
                extract_tail();
                return true;
            }

            Node<T>* temp = head;
            
            while(temp != nullptr && value != temp->get_value())
                temp = temp->get_next();

            if(temp == nullptr)
                return false;

            temp->get_prev()->set_next(temp->get_next());
            temp->get_next()->set_prev(temp->get_prev());

            delete temp;

            return true;
        }
        
        void display() const {

            Node<T>* current = head; // current = tail to inverse print the list

            while(current != nullptr) {
                cout << current->get_value() << " -> ";
                current = current->get_next();  // current->get_prev()
            }

            cout << "nullptr\n";
        }
};

int main() {

    List<int> list;

    /*list.push_head(10);
    list.push_tail(5);
    list.push_head(7);
    list.push_tail(3);*/

    list.push_head(1);
    list.push_sorted(10);
    list.push_sorted(5);
    list.push_sorted(7);
    list.push_sorted(3);
    list.push_sorted(6);
    list.push_sorted(0);
    list.push_tail(11);

    list.display();

    if(list.extract_element(15))
        cout << "found\n";
    else
        cout << "not found\n";

    list.display();

    list.extract_head();
    list.display();

    list.extract_tail();
    list.display();

    return 0;
}