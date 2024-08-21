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

        // Operator = Overloading
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
            
            /*
                it's important to delete [] previous pointers
                to avoid memory leaks or undefined behaviours
            */
            delete [] this->title;

            this->title = new char [strlen(title) + 1];
            strcpy(this->title, title);
        }
        void set_author(const char* author) {

            /*
                same thing here
            */
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
};

// Library {};
class Library {

    private:
        /*
            the instance below allows me to manage more objects of the class Book
            by using their properties and methods
        */
        Book* books;
        int numBooks;

    public:
        // Default
        Library() : books(nullptr), numBooks(0) {
            books = new Book [0];
        }

        // Parametrized
        Library(int numBooks) : numBooks(numBooks) {
            books = new Book [numBooks];
        }

        ~Library() {
            delete [] books;
        }

        // Methods
        void add_book(size_t i, Book book) {
            
            /*
                this function allows to add a book in the Book's array
                that already exists within the Library class
                by copying the book parameter into it's place (i) in the array
            */
            if(i < numBooks) {
                books[i] = book;
            } else {
                cout << "\nInvalid index.\n";
            }
        }

        void inc_copies(int id, int n) {
            
            size_t i = 0;
            bool found = false;
            do {
                if(books[i].get_id() == id) {   // get_copies() is Book's method
                    books[i].add_copies(n);     // add_copies() is Book's method
                    found = true;

                    cout << "Incrementing copies of book ID " << id << "...\n";
                    cout << "Copies updated!\n";
                    books[i].display();         // display() is Book's method

                    break;
                }

                i++;
            } while(!found);
        }

        void remove_ByID(int id) {
            
            if(numBooks != 0) {
                size_t i = 0;
                bool found = false;
                do {
                    if(id == books[i].get_id()) {
                        for(size_t j = i; j > numBooks; j--) {
                            books[j] = books[j - 1];
                        }

                        numBooks--;
                        found = true;

                        cout << "\nFinding book by ID " << id << ":\n";
                        books[i].display(); // display() is Book's method
                    }
                } while(!found);

                if(!found)
                    cout << "\nThe given ID doesn't match an existing one.\n";
            }
        }

        void display_books() {
            
            cout << "\nBooks in the library:\n";
            for(size_t i = 0; i < numBooks; i++)
                books[i].display(); // display() is Book's method
        }

        void sort_books() {
            
            /*
                this functions sorts the elements by using insertion sort
            */
            for(size_t i = 1; i < numBooks; i++) {

                Book temp = books[i];

                size_t j = i;
                while((j > 0)&&(temp.get_copies() < books[j - 1].get_copies())) {
                    books[j] = books[j - 1],
                    j--;
                }

                books[j] = temp;
            }

            cout << "\nSorted book";
        }

        void search_ByTitle(const char* to_search)   {

            cout << "\nFinding book by title '" << to_search << "':\n";

            size_t i = 0;
            bool found = false;
            do {
                if(strcmp(books[i].get_title(), to_search) == 0) {  // get_title() is Book's method
                    found = true;
                    books[i].display(); // display() is Book's method
                    break;
                }

                i++;
            } while ((!found) && (i < numBooks));

            if(!found)
                cout << "\nThe given title doesn't exist.\n";
        }

        void has_moreCopies() {

            int max_copies = books[0].get_copies();     // get_copies() is Book's method
            size_t j = 0;

            for(size_t i = 0; i < numBooks; i++) {
                if(max_copies < books[i].get_copies()) {
                    max_copies = books[i].get_copies();
                    j = i;
                }
            }

            cout << "\nBook with the most copies:\n";
            books[j].display();
        }

        // friend
        friend ostream& operator<< (ostream& os, Book& book);
};

// friend
ostream& operator<< (ostream& os, Book& book) {
    
    os << "\nDisplaying using Operator << Overload:\n"
        << "ID: " << book.get_id()
        << "\nTitle: " << book.get_title()
        << "\nAuthor: " << book.get_author()
        << "\nCopies: " << book.get_copies()
        << "\n";

    return os;
}

int main() {

    int N;
    cout << "How many books do you want to add? ";
    cin >> N;
    
    /*
        this is an instance of library
        i'm calling it's Parametrized Constructor to initialize
        numBooks with N and
        allocating space for Book* books
    */
    Library library(N);
    
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
        
        // Adding book to the library
        Book book(ID, title, author, copies);
        library.add_book(i, book);
    }

    // Functions Calls
    system("CLS");
    library.display_books();
    
    cout << "\nWich book are you searching for? [Title]\n";
    char* to_search = new char [512];
    cin.getline(to_search, 512);
    
    library.search_ByTitle(to_search);
    
    cout << "\nOf wich book would you like to add copies? [ID]\n";
    int id;
    cin >> id;

    cout << "\nHow many? ";
    int n;
    cin >> n;

    library.inc_copies(id, n);
    
    library.has_moreCopies();

    library.sort_books();
    library.display_books(); 

    return 0;
}