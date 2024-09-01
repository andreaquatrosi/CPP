#include <iostream>

using namespace std;

template <typename T>
class Node {

  private:
    T key;
    Node<T>* right;
    Node<T>* left;

  public:
    Node() : key(T()), right(nullptr), left(nullptr) {}
    Node(T key) : key(key), right(nullptr), left(nullptr) {}

    // Getter
    T get_key() const { return key; }
    Node<T>*& get_right() { return right; } 
    Node<T>*& get_left() { return left; } 

    // Setter
    void set_key(const T key) { this->key = key; }
    void set_right(Node<T>* right) { this->right = right; }
    void set_left(Node<T>* left) { this->left = left; }
};

template <typename T>
class BST {

  private:
    Node<T>* root;

    void add_node(Node<T>*& root, const T& key) {
      
      if(!root) { // setting the root
        Node<T>* newNode = new Node<T>(key);
        root = newNode;

        return;
      }

      // traversing the binary tree
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

    void inOrder(Node<T>* root) {
      
      if(!root)
        return;
      
      inOrder(root->get_left());
      cout << root->get_key() << " ";
      inOrder(root->get_right());
    }

    void preOrder(Node<T>* root) {

      if(!root)
        return;

      cout << root->get_key() << " ";
      inOrder(root->get_left());
      inOrder(root->get_right());
    }

    void postOrder(Node<T>* root) {

      if(!root)
        return;

      inOrder(root->get_left());
      inOrder(root->get_right());
      cout << root->get_key() << " ";
    }

    Node<T>* get_maxNode(Node<T>* root) {

      Node<T>* current = root;

      while(current->get_right())
        current = current->get_right();

      return current;
    }

    Node<T>* get_minNode(Node<T>* root) {

      Node<T>* current = root;

      while(current->get_left())
        current = current->get_left();

      return current;
    }

  public:
    BST() : root(nullptr) {}

    void add_node(const T& key) {
      add_node(root, key);
    }

    void delete_node(const T& key) {
      delete_node(root, key);
    }

    Node<T>* search_node(const T& key) {
      return search_node(root, key);
    }

    Node<T>* get_maxNode() {
      get_maxNode(root);
    }

    Node<T>* get_minNode() {
      get_minNode(root);
    }

    void inOrder() {
      inOrder(root);
    }

    void preOrder() {
      preOrder(root);
    }

    void postOrder() {
      postOrder(root);
    }
};

int main() {

  BST<int> bst;

  constexpr size_t N = 8;
  int nodes[N] = {10, 5, 20, 30, 4, 3, 15, 11};

  for(size_t i = 0; i < N; i++)
    bst.add_node(nodes[i]);

  Node<int>* node_tosearch = bst.search_node(11);

  cout << node_tosearch->get_key();

  cout << "\nIn-Order visit:\n";
  bst.inOrder();

  cout << "\nPre-Order visit:\n";
  bst.preOrder();

  cout << "\nPost-Order visit:\n";
  bst.postOrder();

  bst.delete_node(10);

  return 0;
}