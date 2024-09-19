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
        void set_value(const T& value) { this->value = value; }
        void set_next(Node<T>* next) { this->next = next; }
        void set_prev(Node<T>* prev) { this->prev = prev; }
};

// Lista con accesso semi-diretto
template <typename T>
class SDList {
    public:
        virtual SDList<T>* ins(T x) = 0;
        virtual void print() = 0;
};

template <typename T>
class MySDList : public SDList<T> {
    private:
        Node<T>* head;
        Node<T>* tail;

        Node<T>* shortcuts[10];

        void updateShortcuts() {

            Node<T>* current = head;

            size_t i = 0;
            while(current) {
                int shortcutIndex = current->get_value()/10;

                if(shortcutIndex < 10 && shortcuts[shortcutIndex] == nullptr)
                    shortcuts[shortcutIndex] = current;
                
                current = current->get_next();
            }
        }

    public:
        MySDList() : head(nullptr), tail(nullptr) {
            for(size_t i = 0; i < 10; i++)
                shortcuts[i] = nullptr;
        }

        // Operations
        bool is_empty() { return head == nullptr; }

        SDList<T>* ins(T x) {

            Node<T>* newNode = new Node<T>(x);

            if(this->is_empty() || x < head->get_value()) {
                newNode->set_next(head);    
            
                if(head != nullptr)
                    head->set_prev(newNode);
                
                head = newNode;

                if(tail == nullptr)
                    tail = newNode;
            }

            else if(x >= tail->get_value()) {
                newNode->set_prev(tail);
                tail->set_next(newNode);
                tail = newNode;
            }

            else { 
                Node<T>* current = head->get_next();

                while(current != nullptr && x > current->get_value())
                    current = current->get_next();

                newNode->set_next(current);
                newNode->set_prev(current->get_prev());

                if(current->get_prev() != nullptr)
                    current->get_prev()->set_next(newNode);
                
                current->set_prev(newNode);
            }

            updateShortcuts();

            return this;
        }

        int search(T x) {
            if(this->is_empty())
                cout << "\nEmpty List.\n";

            if(x == head->get_value())
                return 1;
            
            else if(x == tail->get_value())
                return 1;

            else {
                Node<T>* current = head->get_next();

                while(current != nullptr && x != current->get_value())
                    current = current->get_next();

                if(current == nullptr)
                    return 0;

                return 1;
            }
        }

        MySDList<T>* del(T x) {

            if(this->is_empty())
                return nullptr;
            
            Node<T>* temp = nullptr;

            if(x == head->get_value()) {
                temp = head;

                cout << "\nDeleting " << head->get_value() << "\n";
                
                head = head->get_next();
                head->set_prev(nullptr);
            }

            else if(x == tail->get_value()) {
                temp = tail;

                cout << "\nDeleting " << tail->get_value() << "\n";

                tail = tail->get_prev();
                tail->set_next(nullptr);
            }

            else {
                temp = head->get_next();

                

                while(temp != nullptr && x != temp->get_value())
                    temp = temp->get_next();

                if(temp == nullptr)
                    return nullptr;
                
                temp->get_next()->set_prev(temp->get_prev());
                temp->get_prev()->set_next(temp->get_next());

                cout << "\nDeleting " << temp->get_value() << "\n";
            }

            delete temp;
            
            return this;
        }

        // Output
        void print() {

            Node<T>* current = head;

            cout << "\nList: ";
            while(current != nullptr) {
                cout << current->get_value() << " -> ";
                current = current->get_next();
            }

            cout << "nullptr\n";
        }

        void printArray() {

            cout << "\nArray: ";
            for(size_t i = 0; i < 10; i++) {
                if(shortcuts[i])
                    cout << shortcuts[i]->get_value() << " ";
                else
                    cout << "nullptr ";
            }
            cout << "\n";
        }
};

int main() {

    MySDList<int> list;
    
    list.ins(7);
    list.ins(13);
    list.ins(2);
    list.ins(6);
    list.ins(9);
    list.ins(10);
    list.ins(21);
    list.ins(32);
    list.ins(4);
    list.ins(12);
    
    list.print();

    list.printArray();

    cout << "\nSearching... " << list.search(2) << "\n";

    list.del(7);
    list.del(4);
    list.del(32);
    list.del(10);

    list.print();

    return 0;
}