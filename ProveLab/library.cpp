/* Possibile Soluzione Prova d'Esame 11/09/2024 */

#include <iostream>
#include <string>

using namespace std;

class Item {
    protected:
        string title;
        float publicationDate;  // formato MM.AAAA
        int id;
        bool borrow;

    public:
        Item() : title(""), publicationDate(0.0f), id(0), borrow(false) {}
        Item(const string& title, const float& publicationDate, const int& id) : title(title), publicationDate(publicationDate), id(id), borrow(false) {}

        // Getter
        string get_title() const { return title; }
        float get_pubDate() const { return publicationDate; }
        int get_id() const { return id; }
        bool get_borrow() const { return borrow; }

        // Setter
        void set_title(const string& title) { this->title = title; }
        void set_pubDate(const float& pubDate) { publicationDate = pubDate; }
        void set_id(const int& id) { this->id = id; }
        void set_borrow(const bool borrow) { this->borrow = borrow; }

        // Print Function
        virtual void display() const {
            
            cout << "\nTitle: " << title
                 << "\nPub. Date: " << publicationDate
                 << "\nID: " << id
                 << "\n"; 
        }
};

class Book : public Item {
    private:
        string author;
    
    public:
        Book() : Item(), author("") {}
        Book(const string& author, const string& title, const float& publicationDate, const int& id) : author(author), Item(title, publicationDate, id) {}

        // Getter
        string get_author() const { return author; }

        // Setter
        void set_author(const string& author) { this->author = author; }

        void display() const override {
            
            cout << "\nTitle: " << title
                 << "\nAuthor: " << author
                 << "\nPub. Date: " << publicationDate
                 << "\nID: " << id
                 << "\n";
        }
};

class DVD : public Item {
    private:
        int duration;
    
    public:
        DVD() : Item(), duration(0) {}
        DVD(const int& duration, const string& title, const float& publicationDate, const int& id) : duration(duration), Item(title, publicationDate, id) {}

        // Getter
        int get_duration() const { return duration; }

        // Setter
        void set_duration(const int& duration) { this->duration = duration; }

        void display() const override {
            
            cout << "\nTitle: " << title
                 << "\nDuration: " << duration << " minutes"
                 << "\nPub. Date: " << publicationDate
                 << "\nID: " << id
                 << "\n";
        }
};

class Student {
    private:
        string name;
        string surname;

        Book books[5];
        size_t numBooks;

        DVD dvds[5];
        size_t numDVDs;

        size_t item_count;

    public:
        Student() : name(""), surname("") {
            numBooks = 0;
            numDVDs = 0;
            item_count = 0;
        }

        Student(const string& name, const string& surname) : name(name), surname(surname) {
            numBooks = 0;
            numDVDs = 0;
            item_count = 0;
        }

        // Methods

        void add_book(Book& book) {
            
            if(item_count < 5) {
                item_count++;
                
                books[numBooks].set_title(book.get_title());
                books[numBooks].set_author(book.get_author());
                books[numBooks].set_pubDate(book.get_pubDate());
                books[numBooks].set_id(book.get_id());

                numBooks++;
            }

            else {
                cout << "\nMaximum amount of borrowed items reached.\n";
            }
        } 

        void add_dvd(DVD& dvd) {

            if(item_count < 5) {
                item_count++;
                
                dvds[numDVDs].set_title(dvd.get_title());
                dvds[numDVDs].set_duration(dvd.get_duration());
                dvds[numDVDs].set_pubDate(dvd.get_pubDate());
                dvds[numDVDs].set_id(dvd.get_id());

                numDVDs++;
            }

            else {
                cout << "\nMaximum amount of borrowed items reached.\n";
            }
        }

        void remove_book(size_t id) {
            
            size_t i = 0;
            bool found = false;

            while(!found && i < numBooks) {
                if(id == books[i].get_id()) {
                    found = true;

                    for(size_t j = i; j < numBooks; j++) {
                        books[j] = books[j+1];
                    }

                    numBooks--;
                }

                i++;
            }
        }

        void remove_dvd(size_t id) {
            
            size_t i = 0;
            bool found = false;

            while(!found && i < numDVDs) {
                if(id == dvds[i].get_id()) {
                    found = true;

                    for(size_t j = i; j < numDVDs; j++) {
                        dvds[j] = dvds[j+1];
                    }

                    numDVDs--;
                }

                i++;
            }
        }

        void printItems() const {

            for(size_t i = 0; i < numBooks; i++)
                books[i].display();

            for(size_t i = 0; i < numDVDs; i++)
                dvds[i].display();
        }

        // Getter
        size_t get_numBooks() const { return numBooks; }
        size_t get_numDVDs() const { return numDVDs; }
};

class Professor {
    private:
        string name;
        string surname;

        Book books[10];
        size_t numBooks;

        DVD dvds[10];
        size_t numDVDs;

        size_t item_count;

    public:
        Professor() : name(""), surname("") {
            numBooks = 0;
            numDVDs = 0;
            item_count = 0;
        }

        Professor(const string& name, const string& surname) : name(name), surname(surname) {
            numBooks = 0;
            numDVDs = 0;
            item_count = 0;
        }

        // Methods

        void add_book(Book& book) {
            
            if(item_count < 10) {
                item_count++;
                
                books[numBooks].set_title(book.get_title());
                books[numBooks].set_author(book.get_author());
                books[numBooks].set_pubDate(book.get_pubDate());
                books[numBooks].set_id(book.get_id());

                numBooks++;
            }

            else {
                cout << "\nMaximum amount of borrowed items reached.\n";
            }
        } 

        void add_dvd(DVD& dvd) {

            if(item_count < 10) {
                item_count++;
                
                dvds[numDVDs].set_title(dvd.get_title());
                dvds[numDVDs].set_duration(dvd.get_duration());
                dvds[numDVDs].set_pubDate(dvd.get_pubDate());
                dvds[numDVDs].set_id(dvd.get_id());

                numDVDs++;
            }

            else {
                cout << "\nMaximum amount of borrowed items reached.\n";
            }
        }

        void remove_book(size_t id) {
            
            size_t i = 0;
            bool found = false;

            while(!found && i < numBooks) {
                if(id == books[i].get_id()) {
                    found = true;

                    for(size_t j = i; j < numBooks; j++) {
                        books[j] = books[j+1];
                    }

                    numBooks--;
                }

                i++;
            }
        }

        void remove_dvd(size_t id) {
            
            size_t i = 0;
            bool found = false;

            while(!found && i < numDVDs) {
                if(id == dvds[i].get_id()) {
                    found = true;

                    for(size_t j = i; j < numDVDs; j++) {
                        dvds[j] = dvds[j+1];
                    }

                    numDVDs--;
                }

                i++;
            }
        }

        void printItems() const {

            for(size_t i = 0; i < numBooks; i++)
                books[i].display();

            for(size_t i = 0; i < numDVDs; i++)
                dvds[i].display();
        }

        // Getter
        size_t get_numBooks() const { return numBooks; }
        size_t get_numDVDs() const { return numDVDs; }
};

class Library {
    private:
        string name;

        Book books[100];
        size_t numBooks;

        DVD dvds[100];
        size_t numDVDs;

    public:
        Library() : name("") {
            numBooks = 0;
            numDVDs = 0;
        }

        Library(const string& name) : name(name) {
            numBooks = 0;
            numDVDs = 0;
        }

        // Methods
        void add_book(Book& book) {

            books[numBooks].set_title(book.get_title());
            books[numBooks].set_author(book.get_author());
            books[numBooks].set_pubDate(book.get_pubDate());
            books[numBooks].set_id(book.get_id());

            numBooks++;
        }

        void add_dvd(DVD& dvd) {

            dvds[numDVDs].set_title(dvd.get_title());
            dvds[numDVDs].set_duration(dvd.get_duration());
            dvds[numDVDs].set_pubDate(dvd.get_pubDate());
            dvds[numDVDs].set_id(dvd.get_id());

            numDVDs++;
        }
        
        void borrowItem_student(size_t id, Student& student) {

            size_t i = 0;
            bool found = false;

            // Book
            while(!found && i < numBooks) {  // Only iterate over the number of actual books
                
                if(id == books[i].get_id() && books[i].get_borrow() == false) {
                    found = true;
                    student.add_book(books[i]);  // Add the correct book
                    books[i].set_borrow(true);
                }

                i++;
            }

            // DVD
            i = 0;
            found = false;

            while(!found && i < numDVDs) {
                
                if(id == dvds[i].get_id() && dvds[i].get_borrow() == false) {
                    found = true;
                    student.add_dvd(dvds[i]);
                    dvds[i].set_borrow(true);
                }

                i++;
            }
        }

        void borrowItem_professor(size_t id, Professor& professor) {

            size_t i = 0;
            bool found = false;

            // Book
            while(!found && i < numBooks) {  // Only iterate over the number of actual books
                
                if(id == books[i].get_id() && books[i].get_borrow() == false) {
                    found = true;
                    professor.add_book(books[i]);  // Add the correct book
                    books[i].set_borrow(true);
                }

                i++;
            }

            // DVD
            i = 0;
            found = false;

            while(!found && i < numDVDs) {
                
                if(id == dvds[i].get_id() && dvds[i].get_borrow() == false) {
                    found = true;
                    professor.add_dvd(dvds[i]);
                    dvds[i].set_borrow(true);
                }

                i++;
            }
        }

        void returnItem_student(size_t id, Student& student) {
            
            size_t i = 0;
            bool found = false;

            while(!found && i < numBooks) {
                if(id == books[i].get_id()) {
                    books[i].set_borrow(false);
                    student.remove_book(id);

                    found = true;

                    cout << "\nBook successfully removed\n";
                }

                i++;
            }

            i = 0;
            found = false;

            while(!found && i < numDVDs) {
                if(id == dvds[i].get_id()) {
                    dvds[i].set_borrow(false);
                    student.remove_dvd(id);

                    found = true;

                    cout << "\nDVD successfully removed\n";
                }

                i++;
            }
        }

        void returnItem_professor(size_t id, Professor& prof) {
            
            size_t i = 0;
            bool found = false;

            while(!found && i < numBooks) {
                if(id == books[i].get_id()) {
                    books[i].set_borrow(false);
                    prof.remove_book(id);

                    found = true;

                    cout << "\nBook successfully removed\n";
                }

                i++;
            }

            i = 0;
            found = false;

            while(!found && i < numDVDs) {
                if(id == dvds[i].get_id()) {
                    dvds[i].set_borrow(false);
                    prof.remove_dvd(id);

                    found = true;

                    cout << "\nDVD successfully removed\n";
                }

                i++;
            }
        }
};

int main() {

    Book book1("Nome", "Titolo", 10.2024, 1012);
    Book book2("The Great Escape", "Adventures Await", 11.2024, 2023);
    Book book3("Journey's End", "A Tale of Travel", 01.2025, 2045);
    Book book4("Mystery of the Lost City", "Thrills and Chills", 02.2024, 3012);
    Book book5("Cooking with Love", "Delicious Recipes", 03.2024, 4050);
    Book book6("The Forgotten Realm", "Fantasy Adventures", 04.2024, 5067);

    DVD dvd1(120, "Titolone", 12.2024, 1010);
    DVD dvd2(150, "Epic Saga", 11.2024, 3202);
    DVD dvd3(95, "Laugh Out Loud", 12.2024, 4520);
    DVD dvd4(120, "Action Heroes", 01.2025, 2103);
    DVD dvd5(110, "Romantic Comedy", 02.2025, 2576);
    DVD dvd6(130, "Historical Drama", 03.2025, 5678);

    // Adding Books and DVDs to the library
    Library library("UniCT Library");
    library.add_book(book1);
    library.add_book(book2);
    library.add_book(book3);
    library.add_book(book4);
    library.add_book(book5);
    library.add_book(book6);

    library.add_dvd(dvd1);
    library.add_dvd(dvd2);
    library.add_dvd(dvd3);
    library.add_dvd(dvd4);
    library.add_dvd(dvd5);
    library.add_dvd(dvd6);
    
    // Borrowing Items from the library
    Student student("Andrea", "Quatrosi");
    library.borrowItem_student(1012, student);
    library.borrowItem_student(5067, student);
    library.borrowItem_student(2045, student);
    
    cout << "\nStudent:\n";
    student.printItems();

    Professor prof("Massimo", "Bossetti");
    library.borrowItem_professor(2023, prof);
    library.borrowItem_professor(1012, prof);
    library.borrowItem_professor(4520, prof);
    library.borrowItem_professor(2103, prof);
    library.borrowItem_professor(5067, prof);
    library.borrowItem_professor(1010, prof);
    library.borrowItem_professor(5678, prof);
    library.borrowItem_professor(2576, prof);
    library.borrowItem_professor(3202, prof);
    library.borrowItem_professor(3012, prof);
    library.borrowItem_professor(2576, prof);

    cout << "\nProf:\n";
    prof.printItems();

    library.returnItem_student(5067, student);

    cout << "\nUpdated Student's items:\n";
    student.printItems();

    library.returnItem_professor(5678, prof);
    library.returnItem_professor(2023, prof);
    library.returnItem_professor(1010, prof);

    cout << "\nUpdated Professor's items:\n";
    prof.printItems();

    return 0;
}