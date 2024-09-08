#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

class Node {
    private:
        string title;
        int year;
        float score;

        Node* next;
        Node* left;
        Node* right;

    public:
        Node() : title(""), year(0), score(0.0f), next(nullptr), right(nullptr), left(nullptr) {}
        Node(const string& title, int year, float score) : title(title), year(year), score(score), next(nullptr), right(nullptr), left(nullptr) {}

        // Getter
        string get_title() { return title; }
        int get_year() { return year; }
        float get_score() { return score; }
        Node* get_next() { return next; }
        Node*& get_right() { return right; }
        Node*& get_left() { return left; }

        // Setter
        void set_title(const string& title) { this->title = title; }
        void set_year(int year) {this->year = year; }
        void set_score(float score) { this->score = score; }
        void set_next(Node* next) { this->next = next; }
        void set_right(Node* right) { this->right = right; }
        void set_left(Node* left) { this->left = left; }

        // friend
        friend ostream& operator<<(ostream& os, const Node& node);
};

// friend
ostream& operator<<(ostream& os, const Node& node) {
    
    os << "\nTitolo: " << node.title
         << "\nAnno: " << node.year
         << "\nValutazione: " << node.score
         << "\n";

    return os;
}

class List {
    private:
        Node* head;

    public:
        List() : head(nullptr) {}

        ~List() {

            Node* current = head;
            Node* nextNode = nullptr;

            while(current != nullptr) {
                nextNode = current->get_next();
                delete current;
                current = nextNode;
            }
        }

        // Operazioni
        static List create_list() {

            ifstream fin("film.txt");

            if(!fin) {
                cerr << "\nErrore while opening file...\n";
                exit(EXIT_FAILURE);
            }

            List list;

            string line;
            while(getline(fin, line)) {

                size_t pos = 0;
                string token;

                // find title
                pos = line.find(';');
                string title = line.substr(0, pos);
                line.erase(0, pos + 1);

                // find year
                pos = line.find(';');
                string _year = line.substr(0, pos);
                int year = atoi(_year.c_str());
                line.erase(0, pos + 1);

                // find score
                string _score = line;
                float score = atof(_score.c_str());

                list.push_tail(title, year, score);
            }

            return list;
        }

        bool is_empty() { return head == nullptr; }

        void push_tail(const string& title, int year, float score) {

            Node* newNode = new Node(title, year, score);

            if(this->is_empty()) {
                head = newNode;

                return;
            }

            Node* current = head;

            while(current->get_next() != nullptr)
                current = current->get_next();

            current->set_next(newNode);
        }

        Node* pop_head() {

            if(is_empty())
               return nullptr;

            Node* temp = head;
            head = head->get_next();
            
            temp->set_next(nullptr);

            return temp;
        }

        void display() const {

            Node* current = head;

            while(current != nullptr) {
                cout << *current;
                current = current->get_next();
            }
        }      
};

class BST {
    private:
        Node* root;

        void add_node(Node*& root, Node*& node) {

            if(!root) {
                root = node;

                return;
            }

            if(node->get_year() < root->get_year()) 
                add_node(root->get_left(), node);
            
            else if(node->get_year() > root->get_year())
                add_node(root->get_right(), node);
        }

        void inOrder(Node* root) {

            if(!root)
                return;

            inOrder(root->get_left());
            cout << *root;
            inOrder(root->get_right());
        }
    
    public:
        BST() : root(nullptr) {}

        void add_node(Node*& node) {
            add_node(root, node);
        }

        void inOrder() {
            inOrder(root);
        }
};

int main() {

    List list = List::create_list();
    BST bst;

    while(!list.is_empty()) {
        Node* node = list.pop_head();
        
        if(node)
            bst.add_node(node);
    }

    cout << "\nThe Binary Search Tree has been created...\n";

    cout << "\nIn-Order visit:\n";
    bst.inOrder();

    return 0;
}