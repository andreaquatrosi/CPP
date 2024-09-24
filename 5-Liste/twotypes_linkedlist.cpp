#include <iostream>

using namespace std;

template <typename T>
class Node {
    private:
        T value;    
        Node<T>* next; 
        Node<T>* prev;  // double linked list

    public:
        Node() : value(T()), next(nullptr), prev(nullptr) {}

        Node(T value) : value(value), next(nullptr), prev(nullptr) {}

        // Getter
        T get_value() const { return value; }
        Node<T>* get_next() { return next; }
        Node<T>* get_prev() { return prev; } // double linked list

        // Setter
        void set_value(const T& value) { this->value = value; }
        void set_next(Node<T>* next) { this->next = next; }
        void set_prev(Node<T>* prev) { this->prev = prev; } // double linked list

        // Friend
        friend ostream& operator<<(ostream& os, Node<T>& node) {
            os << node.value << " ";
            
            return os;
        }
};

template <typename T>
class List {
    private:
        Node<T>* head;
        Node<T>* tail; // double linked list

    public:
        List() : head(nullptr) {}

        // Operations
        bool is_empty() const { return head == nullptr; }

        void push_head(T value) {

            Node<T>* newNode = new Node<T>(value);

            if(this->is_empty()) {
                head = tail = newNode;

                return;
            }

            newNode->set_next(head);
            head->set_prev(newNode);
            head = newNode;
        } 

        void push_tail(T value) {

            Node<T>* newNode = new Node<T>(value);

            if(this->is_empty()) {
                head = tail = newNode;

                return;
            }

            newNode->set_prev(tail);
            tail->set_next(newNode);
            tail = newNode;

            /*Node<T>* current = head;

            while(current->get_next() != nullptr)
                current = current->get_next();

            current->set_next(newNode);*/
        }

        void push_sorted(T value) {

            Node<T>* newNode = new Node<T>(value);

            if(this->is_empty() || value < head->get_value()) {
                newNode->set_next(head);

                if(head != nullptr)
                    head->set_prev(newNode);
                    
                head = newNode;

                if(tail == nullptr)
                    tail = newNode;
            }

            else if(value > tail->get_value()) {
                newNode->set_prev(tail);
                tail->set_next(newNode);
                tail = newNode;
            }

            else {
                Node<T>* current = head->get_next();

                while(current != nullptr && value > current->get_value())
                    current = current->get_next();
                
                current->get_prev()->set_next(newNode);
                newNode->set_prev(current->get_prev());

                newNode->set_next(current);
                current->set_prev(newNode);
            }
        }

        T pop_head() {

            if(this->is_empty())
                exit(EXIT_FAILURE);

            Node<T>* temp = head;
            head = head->get_next();

            T value = temp->get_value();

            delete temp;

            return value;
        }

        T pop_tail() {

            if(this->is_empty())
                exit(EXIT_FAILURE);

            /*Node<T>* current = head;
            Node<T>* prev = nullptr;

            while(current->get_next() != nullptr) {
                prev = current;
                current = current->get_next();
            }

            T value = current->get_value();

            if(prev != nullptr)
                prev->set_next(nullptr);

            delete current;*/

            Node<T>* temp = tail;
            tail = tail->get_prev();

            T value = temp->get_value();

            tail->set_next(nullptr);

            delete temp;

            return value;
        }

        bool pop_element(T value) {

            if(this->is_empty())
                exit(EXIT_FAILURE);

            if(value == head->get_value()) {
                T value = pop_head();

                return true;
            }

            else if(value == tail->get_value()) {
                T value = pop_tail();

                return true;
            }

            Node<T>* current = head->get_next();

            while(current != nullptr && value != current->get_value())
                current = current->get_next();

            if(current == nullptr)
                return false;

            /*if(prev != nullptr)
                prev->set_next(current->get_next());*/

            current->get_prev()->set_next(current->get_next());
            current->get_next()->set_prev(current->get_prev());

            delete current;

            return true;
        }

        // Output
        void printList() const {

            if(this->is_empty())    
                return;

            Node<T>* current = head;

            while(current != nullptr) {
                cout << *current;
                current = current->get_next();
            }
        }

};

int main() {

    List<int> list;

    list.push_head(10);
    list.push_head(5);
    list.push_head(8);
    list.push_sorted(15);
    list.push_sorted(20);
    list.push_head(7);

    list.printList();

    cout << "\nPopped element: " << list.pop_element(7) << "\n";

    list.printList();

    return 0;
}