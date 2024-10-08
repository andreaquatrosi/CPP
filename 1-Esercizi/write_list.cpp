#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

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
            Node<T>* current = head;
            Node<T>* nextNode = nullptr;

            while(current != nullptr) {
                nextNode = current->get_next();
                delete current;
                current = nextNode;
            }

            if(nextNode != nullptr)
                delete nextNode;
        }

        // Operazioni
        bool is_empty() { return head == nullptr; }

        void push_head(const T value) {

            Node<T>* newNode = new Node<T>(value);

            if(this->is_empty()) {
                head = newNode;

                return;
            }

            newNode->set_next(head);
            head = newNode;
        }

        void push_tail(const T value) {

            Node<T>* newNode = new Node<T>(value);

            if(this->is_empty()) {
                head = newNode;

                return;
            }

            Node<T>* current = head;

            while(current->get_next() != nullptr)
                current = current->get_next();

            current->set_next(newNode);
        }

        void push_sorted(const T value) {
            
            Node<T>* newNode = new Node<T>(value);

            if(this->is_empty() || value < head->get_value()) {
                if(head != nullptr)
                    newNode->set_next(head);

                head = newNode;

                return;
            }

            Node<T>* current = head;
            Node<T>* prev = nullptr;

            while(current != nullptr && value > current->get_value()) {
                prev = current;
                current = current->get_next();
            }

            newNode->set_next(current);

            if(prev != nullptr)
                prev->set_next(newNode);
        }

        T extract_head() {

            if(this->is_empty())
                exit(EXIT_FAILURE);

            Node<T>* temp = head;
            
            T value = head->get_value();
            head = head->get_next();

            delete temp;

            return value;
        }

        T extract_tail() {

            if(this->is_empty())
                exit(EXIT_FAILURE);

            Node<T>* temp = head;
            Node<T>* prev = nullptr;

            while(temp->get_next() != nullptr) {
                prev = temp;
                temp = temp->get_next();
            }

            T value = temp->get_value();

            if(prev != nullptr)
                prev->set_next(nullptr);
            
            delete temp;

            return value;
        }

        bool extract_element(const T value) {

            if(this->is_empty())
                exit(EXIT_FAILURE);

            Node<T>* temp = head;
            Node<T>* prev = nullptr;

            while(temp != nullptr && value != temp->get_value()) {
                prev = temp;
                temp = temp->get_next();
            }

            if(temp != nullptr) {
                if(prev != nullptr)
                    prev->set_next(temp->get_next());

                delete temp;
                
                return true;
            }

            return false;
        }

        void writeList(List<T> list, const string fileName) {

            if(is_empty())
                return;

            ofstream fout(fileName, ios::app);

            string line;
            while(!list.is_empty())
                fout << list.extract_head() << " -> ";

            fout << "nullptr\n";

            fout.close();
        }

        void display_list() const {

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

    list.push_head(5);
    list.push_head(7);
    list.push_head(1);
    list.push_head(4);
    list.push_head(9);

    list.display_list();

    list.extract_head();
    list.display_list();

    list.extract_tail();
    list.display_list();

    list.extract_element(1);
    list.display_list();

    list.push_sorted(5);
    list.push_sorted(1);
    list.push_sorted(9);

    list.display_list();

    string fileName;
    cout << "\nInput file name: ";
    cin >> fileName;

    list.writeList(list, fileName);

    return 0;
}