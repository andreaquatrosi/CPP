#include <iostream>
#include <string>

using namespace std;

// ITEM
class Item {
    protected:
        string title;
        double publicationDate; // MM.YYYY
        int id;

        bool isAvaible;
    
    public:
        Item() : title(""), publicationDate(0.0f), id(0), isAvaible(true) {}

        Item(const string& title, const double& publicationDate, const int& id) : title(title), publicationDate(publicationDate), id(id), isAvaible(true) {}

        // Getter
        int get_id() const { return id; }
        bool get_isAvaible() const { return isAvaible;}

        // Setter
        void set_isAvaible(bool isAvaible) { this->isAvaible = isAvaible; }

        // Methods
        virtual void printItem() const {
            
            cout << "\nTitle: " << title
                 << "\nPublication Date: " << publicationDate
                 << "\nID: " << id
                 << "\n";
        }
};

class Book : public Item {
    private:
        string author;

    public:
        Book() : author(""), Item() {}

        Book(const string& author, const string& title, const double& publicationDate, const int& id) : author(author), Item(title, publicationDate, id) {}

        // Methods
        void printItem() const override {

            cout << "\nBook - " << title << " - " << author << " - " << id << "\n";
        }
};

class DVD : public Item {
    private:
        int duration;   // n-minutes

    public:
        DVD() : duration(0), Item() {}

        DVD(const int& duration, const string& title, const double& publicationDate, const int& id) : duration(duration), Item(title, publicationDate, id) {}

        // Methods
        void printItem() const override {

            cout << "\nDVD - " << title << " - " << duration << " - " << id << "\n";
        }
};

// PERSON
class Person {
    protected:
        string name;
        string surname;

        Item** borrowedItems;
        size_t currentItems;
        int maxItems;

    public:
        Person() : name(""), surname(""), borrowedItems(nullptr), currentItems(0), maxItems(0) {}

        Person(const string& name, const string& surname, int maxItems) : name(name), surname(surname), currentItems(0), maxItems(maxItems) {
            borrowedItems = new Item* [maxItems];
            for(size_t i = 0; i < maxItems; i++)
                borrowedItems[i] = nullptr;
        }

        void borrowItem(Item* item) {
            if(currentItems < maxItems && item->get_isAvaible()) {
                borrowedItems[currentItems++] = item;

                item->set_isAvaible(false);
            }

            else {
                if(!item->get_isAvaible())
                    cout << "\nItem " << item->get_id() << " is not avaible at the moment.\n";
                else
                    cout << "\nYou can no longer take any more products.\n";
            }
        }

        void returnItem(Item* item) {
            
            bool itemFound = false;
            size_t j = 0;

            for (size_t i = 0; i < currentItems; i++) {
                if (item->get_id() == borrowedItems[i]->get_id()) {
                    item->set_isAvaible(true);
                    j = i;
                    itemFound = true;

                    break;
                }
            }

            if(itemFound) {
                
                for(size_t i = j; i < currentItems - 1; i++) {
                    borrowedItems[i] = borrowedItems[i + 1];
                }
                borrowedItems[currentItems - 1] = nullptr;  
                currentItems--; 
            } 
            
            else {
                cout << "\nYou don't have this item.\n";
            }
        }

        // Methods
        virtual void printItems() const {
            
            cout << "\nItems borrowed:\n";
            for(size_t i = 0; i < currentItems; i++) {
                borrowedItems[i]->printItem();
            }
        }
};

class Student : public Person {
    public:
        Student() : Person() {}

        Student(const string& name, const string& surname) : Person(name, surname, 5) {}
};

class Professor : public Person {
    public:
        Professor() : Person() {}

        Professor(const string& name, const string& surname) : Person(name, surname, 10) {}
};

// LIBRARY
class Library {
    private:
        string name;

    public:
        Library() : name("") {}
        
        Library(const string& name, const int& numStud, const int& numProf) : name(name) {}

        // Methods
        void borrowItem(Person* person, Item* item) {
            person->borrowItem(item);
        }

        void returnItem(Person* person, Item* item) {
            person->returnItem(item);
        }
};

// MAIN
int main() {

    Library lib("Library", 3, 2);

    Book b1("A", "A", 1.2024, 1111);
    Book b2("B", "B", 2.2024, 2222);
    Book b3("C", "C", 3.2024, 3333);
    Book b4("D", "D", 4.2024, 4444);
    Book b5("E", "E", 5.2024, 5555);

    DVD d1(111, "F", 6.2024, 6666);
    DVD d2(111, "G", 7.2024, 7777);
    DVD d3(111, "H", 8.2024, 8888);
    DVD d4(111, "I", 9.2024, 9999);
    DVD d5(111, "J", 10.2024, 0000);
    
    Student s1("Andrea", "Quatrosi");

    lib.borrowItem(&s1, &b1);
    lib.borrowItem(&s1, &b2);
    lib.borrowItem(&s1, &b3);
    lib.borrowItem(&s1, &d1);
    lib.borrowItem(&s1, &d3);
    lib.borrowItem(&s1, &d5);

    Professor p1("Massimo", "Bossetti");
    
    lib.borrowItem(&p1, &d1);
    lib.borrowItem(&p1, &d2);
    lib.borrowItem(&p1, &b4);

    cout << "\nStudent items:\n";
    s1.printItems();

    cout << "\nProfessor items:\n";
    p1.printItems();

    lib.returnItem(&s1, &d1);

    lib.borrowItem(&p1, &d1);

    cout << "\nStudent items:\n";
    s1.printItems();

    cout << "\nProfessor items:\n";
    p1.printItems();

    return 0;
}