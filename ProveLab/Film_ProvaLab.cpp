/*
    Esercizio 1
    Nel file film.txt sono presenti dei film. In ogni riga sono presenti le seguenti informazioni:
    TITOLO;ANNO;VALUTAZIONE
    Ad esempio:
    TITANIC;1997;7.9
    Si legga il file e si inseriscano gli elementi in una lista semplicemente linkata, modellando gli
    elementi con una opportuna classe, che ridefinisca anche l’operatore <<.
    Si rimuovano quindi gli elementi dalla lista e si inseriscano in un BST, che dovrà implementare le
    funzionalità di:
    • Inserimento di un nuovo nodo
    • Visualizzazione degli elementi
    Scrivere un main che permetta di eseguire tutte le operazioni previste.
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Node {
    private:
        string title;
        int year;
        float score;

        // For the List
        Node* next;

        // For the BST
        Node* right;
        Node* left;

    public:
        Node() : title(""), year(0), score(0.0f), next(nullptr), right(nullptr), left(nullptr) {}

        Node(const string& title, const int& year, const float& score) : title(title), year(year), score(score), next(nullptr), right(nullptr), left(nullptr) {}

        // Getter
        float get_score() const { return score; }

        Node* get_next() { return next; }

        Node*& get_right() { return right; }
        Node*& get_left() { return left; }        

        // Setter   
        void set_next(Node* next) { this->next = next; }

        void set_right(Node* right) { this->right = right; }
        void set_left(Node* left) { this->left = left; }

        friend ostream& operator<<(ostream& os, const Node& node) {
            os << "\n" << node.title << ", " << node.year << ", " << node.score << "\n";

            return os;
        }
};

class List {
    private:
        Node* head;
        size_t size;

    public:
        List() : head(nullptr), size(0) {}

        // Getter
        size_t get_size() const { return size; }

        // Operations
        bool is_empty() const { return head == nullptr; }

        void insert_head() {

            ifstream fin("C:/CPP/1-Esercizi/film.txt");
            
            if(!fopen) {
                cerr << "\nUnable to open the file.\n";
                return;
            }

            string buffer;
            while(getline(fin, buffer)) {
                int pos = 0;

                pos = buffer.find(';');
                string title = buffer.substr(0, pos);
                buffer.erase(0, pos + 1);

                pos = buffer.find(';');
                string _year = buffer.substr(0, pos);
                int year = atoi(_year.c_str());
                buffer.erase(0, pos + 1);

                pos = buffer.find(';');
                string _score = buffer.substr(0, pos);
                float score = atof(_score.c_str());
                buffer.erase(0, pos + 1);

                Node* newNode = new Node(title, year, score);

                if(this->is_empty()) {
                    head = newNode;
                }

                else {
                    Node* current = head;

                    while(current->get_next() != nullptr)
                        current = current->get_next();

                    if(current != nullptr)
                        current->set_next(newNode);
                }

                size++;
            }
        }

        Node* extract_head() {

            if(this->is_empty())
                exit(EXIT_FAILURE);

            Node* temp = head;

            head = head->get_next();
            temp->set_next(nullptr);

            return temp;
        }

        void print() const {
            
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

        void add_node(Node*& root, Node*& key) {
            
            if(!root) {
                root = key;

                return;
            }

            if(key->get_score() < root->get_score())
                add_node(root->get_left(), key);
            
            else if(key->get_score() > root->get_score())
                add_node(root->get_right(), key);
        }

        void inOrder(Node* root) const {

            if(!root)
                return;

            inOrder(root->get_left());
            cout << *root;
            inOrder(root->get_right());
        }

    public:
        BST() : root(nullptr) {}
        
        void add_node(Node*& key) {
            add_node(root, key);
        }

        void inOrder() const {
            inOrder(root);
        }
};

int main() {

    List list;

    list.insert_head();

    cout << "\nList:\n";
    list.print();

    BST bst;
    while(!list.is_empty()) {
        Node* newNode = list.extract_head();

        bst.add_node(newNode);
    }

    cout << "\nBST:\n";
    bst.inOrder();

    return 0;
}