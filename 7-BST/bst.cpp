#include <iostream>

using namespace std;

template <typename T>
class Node {
    
    private:
        T key;
        Node<T>* left;
        Node<T>* right;

    public:
        Node() : key(T()), left(nullptr), right(nullptr) {}
        Node(T key) : key(key), left(nullptr), right(nullptr) {}

        // Getter
        T get_key() const { return key; }
        Node<T>*& get_left() { return left; }
        Node<T>*& get_right() { return right; }

        // Setter
        void set_key(const T key) { this->key = key; }
        void set_left(Node<T>* left) { this->left = left; }
        void set_right(Node<T>* right) { this->right = right; }
};

template <typename T>
class BST { 

    private:
        Node<T>* root;

        void add_node(Node<T>*& root, const T& key) {

            if(!root) {
                Node<T>* newNode = new Node<T>(key);
                root = newNode;

                return;
            }

            if(key < root->get_key())
                add_node(root->get_left(), key);

            else if(key > root->get_key())
                add_node(root->get_right(), key);
        }

        void delete_node(Node<T>*& root, const T& key) {

            if (!root) 
                return;

            if (key < root->get_key())
                delete_node(root->get_left(), key);
            else if (key > root->get_key())
                delete_node(root->get_right(), key);
            else {
                Node<T>* toDelete = nullptr;

                if (!root->get_right() && !root->get_left()) {     // node has no children (leaf)
                    delete root;
                    root = nullptr;
                }

                else if (!root->get_left()) {                      // node has only right children
                    toDelete = root;
                    root = root->get_right();

                    delete toDelete;
                }

                else if (!root->get_right()) {                    // node has only left children
                    toDelete = root;
                    root = root->get_left();

                    delete toDelete;
                }

                else {                                            // node has both left and right children
                    Node<T>* smallestRight = get_minNode(root->get_right());

                    root->set_key(smallestRight->get_key());
                    delete_node(root->get_right(), smallestRight->get_key());
                }
            }
        }

        Node<T>* get_maxNode(Node<T>* root) {
            
            Node<T>* current = root;

            /* since it's a BST, all (key > root) will be the right node*/
            while(current->get_right())
                current = current->get_right();

            return current;
        }

        Node<T>* get_minNode(Node<T>* root) {
            
            Node<T>* current = root;

            /* since it's a BST, all (key < root) will be the left node*/
            while(current->get_left())
                current = current->get_left();

            return current;
        }

        void inOrder(Node<T>* root) const {
            
            if(!root)
                return;

            inOrder(root->get_left());
            cout << root->get_key() << " ";
            inOrder(root->get_right());
        }

        void preOrder(Node<T>* root) const {

            if(!root)
                return;

            cout << root->get_key() << " ";
            preOrder(root->get_left());
            preOrder(root->get_right());
        }

        void postOrder(Node<T>* root) const {

            if(!root)
                return;
            
            postOrder(root->get_left());
            postOrder(root->get_right());
            cout << root->get_key() << " ";
        }

        Node<T>* search_node(Node<T>*& root, const T& key) {

            if(!root)
                return nullptr;

            if(key < root->get_key())
                return search_node(root->get_left(), key);
            else if(key > root->get_key())
                return search_node(root->get_right(), key);
            else
                return root;
        }

    public:
        BST() : root(nullptr) {}

        // Methods
        void add_node(const T& key) {
            add_node(root, key);
        }

        void delete_node(const T& key) {
            delete_node(root, key);
        }

        void inOrder() const {
            inOrder(root);
        }

        void preOrder() const {
            preOrder(root);
        }

        void postOrder() const {
            postOrder(root);
        }
};

int main() {

    BST<int> bst;

    constexpr size_t N = 8;
    int nodes[N] = {1, 5, 2, 4, 10, 8, 3, 9};

    for(size_t i = 0; i < N; i++)
        bst.add_node(nodes[i]);
    
    cout << "\nIn-Order visit:\n";
    bst.inOrder();

    // bst.delete_node(1);
    
    cout << "\nPre-Order visit:\n";
    bst.preOrder();

    cout << "\nPost-Order visit:\n";
    bst.postOrder();

    cout << "\nAfter deleting: " << nodes[2] << " and " << nodes[1] << ":\n";
    bst.delete_node(2);
    bst.delete_node(5);

    bst.inOrder();

    return 0;
}