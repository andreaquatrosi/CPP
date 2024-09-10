#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <stdexcept>

using namespace std;

class Book {
    private:
        int id;
        string title;
        string author;
        int copies;

    public:
        Book() : id(0), title(""), author(""), copies(0) {}
        
        Book(const int& id, const string& title, const string& author, const int& copies) {
            this->id = id;
            this->title = title;
            this->author = author;
            this->copies = copies;
        }

        // Getter
        int get_id() const { return id; }
        string get_tile() const { return title; }
        string get_author() const { return author; }
        int get_copies() const { return copies; }

        // Setter
        void set_id(const int& id) { this->id = id; }
        void set_title(const string& title) { this->title = title; }
        void set_author(const string& author) { this->author = author; }
        void set_copies(const int& copies) { this->copies = copies; }

        // Compute
        void inc_copies(size_t increment) { copies += increment; }

        void dec_copies(size_t decrement) { 

            if(copies != 0 && copies >= decrement) 
                copies -= decrement; 
            else 
                cout << "\nUnable to decrement copies...\n"; 
        }

        void display_book(Book& book) const {
            cout << "Book details: " << book;
        }

        // Friend
        friend ostream& operator<<(ostream& os, Book& book);
        friend Book& compare_NumCopies(Book& book1, Book& book2);
};

// Friend
ostream& operator<<(ostream& os, Book& book) {
    os << "\nID:" << book.id
       << "\nTitle: " << book.title
       << "\nAuthor: " << book.author
       << "\nCopies: " << book.copies
       << "\n";

    return os;
}

Book& compare_NumCopies(Book& book1, Book& book2) {

    if(book1.get_copies() > book2.get_copies())
        return book1;
    
    else if(book1.get_copies() < book2.get_copies())
        return book2;

    else {
        cout << "\nSame number of copies, returning book1...\n";
        return book1;
    }
}

class Library {
    private:
        Book* books;
        int size;

        void add_book() {

            ifstream fin("library.txt");

            size_t i = 0;
            string line;
            while(getline(fin, line) && i < size) {

                size_t pos = 0;

                // ID
                pos = line.find(";");
                string _id = line.substr(0, pos);
                int id = atoi(_id.c_str());
                line.erase(0, pos + 1);

                // Title
                pos = line.find(";");
                string title = line.substr(0, pos);
                line.erase(0, pos + 1);

                // Author
                pos = line.find(";");
                string author = line.substr(0, pos);
                line.erase(0, pos + 1);

                // Copies
                string _copies = line;
                int copies = atoi(_copies.c_str());

                books[i].set_id(id);
                books[i].set_title(title);
                books[i].set_author(author);
                books[i].set_copies(copies);

                i++;
            }
        }

        Book& find_MostCopies(Book* books, int size) {

            Book& book_MaxCopies = books[0];

            size_t i = 0;
            for(i; i < size; i++) {
                if(books[i].get_copies() > book_MaxCopies.get_copies())
                    book_MaxCopies = books[i];
            }

            return book_MaxCopies;
        }

    public:
        Library() : books(nullptr), size(0) {}
        Library(const int& size) : books(nullptr), size(size) {

            books = new Book [size];
            add_book();
        }

        ~Library() {

            delete [] books;
            books = nullptr;
        } 

        // Compute
        void inc_copies(const size_t& i, const int& increment) {
            books[i].inc_copies(increment);
        }

        void dec_copies(const size_t& i, const int& decrement) {
            books[i].dec_copies(decrement);
        }

        void mostCopies() { cout << "\nThe book with the most copies is: " << find_MostCopies(books, size); }

        void sort_Books() {

            for(size_t i = 1; i < size; i++) {
                Book temp = books[i];

                size_t j = i;
                while((j > 0) && (temp.get_copies() < books[j - 1].get_copies())) {
                    books[j] = books[j - 1];
                    j--;
                }
        
                books[j] = temp;
            }
        }

        void display_library() const {

            for(size_t i = 0; i < size; i++)
                cout << books[i] << "\n";
        }
};

int main() {

    cout << "How many books you want to add to your library? ";
    int numBooks;
    cin >> numBooks;

    Library library(numBooks);

    library.display_library();

    // function calls
    cout << "\nSorted books:";
    library.sort_Books();
    library.display_library();

    library.mostCopies();

    return 0;
}