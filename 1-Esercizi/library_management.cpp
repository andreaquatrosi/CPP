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

        // Methods

        void add_copies(int n) {
            copies += n;
        }

        void delete_copies(int n) {
            if((n > copies)||(copies == 0)) {
                cout << "\nUnable to delete copies.\n";
                exit(EXIT_FAILURE);
            } else { 
                copies -= n;
                cout << "\nCopies successfully deleted.\n";
            }
        }

        void display() {
            cout << "\nID: " << id
                << "\nTitle: " << title
                << "\nAuthor: " << author
                << "\nCopies: " << copies
                << "\n"; 
        }

        // friend :D
        friend void search_ByTitle(Book* book, int N, const char* to_search);
        friend void has_moreCopies(Book* book, int N);
        friend ostream& operator<< (ostream& os, const Book& book);
};

// friend functions
void search_ByTitle(Book* book, int N, const char* to_search) {

    cout << "\nFinding book by title '" << to_search << "':\n";

    size_t i = 0;
    bool found = false;
    do {
        if(strcmp(book[i].get_title(), to_search) == 0) {
            found = true;
            book[i].display();
            break;
        }

        i++;
    } while ((!found) && (i < N));

    if(!found)
        cout << "\nThe given title doesn't exist.\n";
}

void has_moreCopies(Book* book, int N) {
    int max_copies = book[0].get_copies();
    size_t j = 0;

    for(size_t i = 0; i < N; i++) {
        if(max_copies < book[i].get_copies()) {
            max_copies = book[i].get_copies();
            j = i;
        }
    }

    cout << "\nBook with the most copies:\n";
    book[j].display();
}

ostream& operator<< (ostream& os, Book& book) {
    os << "\nDisplaying using Operator << Overload:\n"
       << "ID: " << book.get_id()
       << "\nTitle: " << book.get_title()
       << "\nAuthor: " << book.get_author()
       << "\nCopies: " << book.get_copies()
       << "\n";

    return os;
}

// Library Class goes here...

int main() {

    int N;
    cout << "How many books do you want to add? ";
    cin >> N;
    
    Book* book = new Book [N];

    for(size_t i = 0; i < N; i++) {
        int ID, copies;
        
        cout << "\nEnter details for book " << i+1 << "\n";

        cout << "ID: ";
        cin >> ID;
        
        cin.ignore();
        cout << "Title: ";
        char* title = new char [512];
        cin.getline(title, 512);

        cout << "Author: ";
        char* author = new char [512];
        cin.getline(author, 512);

        cout << "Copies: ";
        cin >> copies;
        cin.ignore();

        new (&book[i]) Book(ID, title, author, copies);
    }

    system("CLS");
    cout << "Books in the library:\n";
    for(size_t i = 0; i < N; i++)
        book[i].display();

    // friend
    cout << "\nWich book are you searching for?\n";
    char* to_search = new char [512];
    cin.getline(to_search, 512);

    search_ByTitle(book, N, to_search);
    has_moreCopies(book, N);

    // operator << overload
    cout << book[0];

    /*Book book_copy(book[0]);  // using Copy Constructor
    cout << book_copy;*/

    // Modify the previous lines of main() by using a Library object
    // instead of a Book object

    return 0;
}