#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class Book {

    private:
        int id;         // book's ID
        char* title;    // book's title
        char* author;   // book's author
        int copies;     // book's copies in the library

    public:
        // Default
        Book() : id(0), title(nullptr), author(nullptr), copies(0) {
            title = new char [1];
            title[0] = '\0';
            
            author = new char [1];
            author[0] = '\0';
        }

        // Parameterized
        Book(int i, const char* t, const char* a, int c) : id(i), title(new char [strlen(t) + 1]), author(new char [strlen(a) + 1]), copies(c) {
            strcpy(title, t);
            strcpy(author, a);
        }

        // Copy
        Book(const Book& book) {
            id = book.id;
            
            title = new char [strlen(book.title) + 1];
            strcpy(title, book.title);

            author = new char [strlen(book.author) + 1];
            strcpy(author, book.author);

            copies = book.copies;
        }

        Book& operator= (const Book& book) {
            if(this != &book) {
                delete [] title;
                delete [] author;

                id = book.id;
            
                title = new char [strlen(book.title) + 1];
                strcpy(title, book.title);

                author = new char [strlen(book.author) + 1];
                strcpy(author, book.author);

                copies = book.copies;
            }

            return *this;
        }

        ~Book() {
            delete [] title;
            delete [] author;
        }

        // Getter
        const int get_id() { return id; }
        const char* get_title() { return title; }
        const char* get_author() { return author; }
        const int get_copies() { return copies; }

        // Setter
        void set_id(int id) { this->id = id; }
        void set_title(const char* title) {
            delete [] this->title;

            this->title = new char [strlen(title) + 1];
            strcpy(this->title, title);
        }
        void set_author(const char* author) {
            delete [] this->author;

            this->author = new char [strlen(author) + 1];
            strcpy(this->author, author);
        }
        void set_copies(int copies) { this->copies = copies; }
};

int main() {

    int N;
    cout << "How many books do you want to add? ";
    cin >> N;
    
    Book* book = new Book [N];

    for(size_t i = 0; i < N; i++) {
        int ID, copies;

        cin >> ID;
        
        cin.ignore();
        char* title = new char [512];
        cin.getline(title, 512);

        char* author = new char [512];
        cin.getline(author, 512);

        cin >> copies;
        cin.ignore();

        new (&book[i]) Book(ID, title, author, copies);
    }

    for(size_t i = 0; i < N; i++) {
        cout << "\nID: " << book[i].get_id()
             << "\nTitle: " << book[i].get_title()
             << "\nAuthor: " << book[i].get_author()
             << "\nCopies: " << book[i].get_copies()
             << "\n"; 
    }
}