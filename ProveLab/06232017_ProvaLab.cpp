#include <iostream>

using namespace std;

class Studente {
    private:
        int v;  // voto
        int r;  // risposte corrette
        int e;  // età accademica

        Studente* right;
        Studente* left;

    public:
        Studente() : v(0), r(0), e(0) {}
        Studente(const int& v, const int& r, const int& e) : v(v), r(r), e(e) {}
        Studente(const Studente& stud) {
            this->v = stud.v;
            this->r = stud.r;
            this->e = stud.e;
            this->right = nullptr;
            this->left = nullptr;
        }

        // Getter
        int get_v() const { return v; }
        int get_r() const { return r; }
        int get_e() const { return e; }

        Studente*& get_right() { return right; }
        Studente*& get_left() { return left; }

        // Setter
        void set_v(const int& v) { this->v = v; }
        void set_r(const int& r) { this->r = r; }
        void set_e(const int& e) { this->e = e; }

        void set_right(Studente* right) { this->right = right; }
        void set_left(Studente* left) { this->left = left; }

        // Operator Overload
        bool operator>(const Studente& stud) const {
            if(this->v > stud.v)
                return true;

            else if(this->v == stud.v && this->r > stud.r)
                return true;
            
            else if((this->v == stud.v) || (this->r == stud.r && this->e < stud.e))
                return true;

            return false;
        }
};

class Valutazione {
    private:
        Studente* root;

        void add_stud(Studente*& root, const Studente& stud) {

            if(!root) {
                root = new Studente(stud);

                return;
            }

            if(stud.get_v() < root->get_v())
                add_stud(root->get_left(), stud);

            else if(stud.get_v() > root->get_v())
                add_stud(root->get_right(), stud);
        }

        Studente* search_stud(Studente*& root, const Studente& stud) {
            
            if(!root)
                exit(EXIT_FAILURE);

            if(stud.get_v() < root->get_v())
                return search_stud(root->get_left(), stud);
        
            else if(stud.get_v() > root->get_v())
                return search_stud(root->get_right(), stud);
            
            else
                return root;
        }

        void inOrder(Studente* root) const {

            if(!root)
                return;

            inOrder(root->get_left());
            cout << root->get_v() << " ";
            inOrder(root->get_right());
        }

    public:
        Valutazione() : root(nullptr) {}

        void add_stud(const Studente& stud) {
            add_stud(root, stud);
        }

        Studente* search_stud(const Studente& stud) {
            return search_stud(root, stud);
        }

        void inOrder() const {
            inOrder(root);
        }
};

int main() {

    Studente stud1(27, 5, 1);
    Studente stud2(26, 4, 3);
    Studente stud3(18, 1, 2);
    Studente stud4(23, 2, 1);
    Studente stud5(30, 7, 2);

    if(stud1 > stud2) {
       cout << "\nstud1:\n" 
            << stud1.get_v() << "\n"
            << stud1.get_r() << "\n"
            << stud1.get_e() << "\n"
            << "\n";

        cout << "\nstud2:\n" 
            << stud2.get_v() << "\n"
            << stud2.get_r() << "\n"
            << stud2.get_e() << "\n"
            << "\n";
    }

    else {
        cout << "\nstud2:\n" 
            << stud2.get_v() << "\n"
            << stud2.get_r() << "\n"
            << stud2.get_e() << "\n"
            << "\n";

        cout << "\nstud1:\n" 
            << stud1.get_v() << "\n"
            << stud1.get_r() << "\n"
            << stud1.get_e() << "\n"
            << "\n";
    }

    Valutazione bst;
    
    bst.add_stud(stud1);
    bst.add_stud(stud2);
    bst.add_stud(stud3);
    bst.add_stud(stud4);
    bst.add_stud(stud5);

    bst.inOrder();
    cout << "\n";

    Studente* stud_toSearch = bst.search_stud(stud3);
    if(stud_toSearch) {
        cout << "\nstud_toSearch:\n" 
            << stud_toSearch->get_v() << "\n"
            << stud_toSearch->get_r() << "\n"
            << stud_toSearch->get_e() << "\n"
            << "\n";
    }

    return 0;
}