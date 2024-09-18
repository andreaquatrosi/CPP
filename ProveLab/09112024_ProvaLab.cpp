#include <iostream>
#include <string>

using namespace std;

// ITEM
class Item {
    protected:
        string title;
        double publicationDate;
        int id;

        bool isAvaible;

    public:
        Item() : title(""), publicationDate(0.0f), id(0), isAvaible(true) {}

        Item(const string& title, const double& publicationDate, const int& id) : title(title), publicationDate(publicationDate), id(id), isAvaible(true) {}

        virtual void display() const {
            cout << "\ntitle: " << title << " - publication date: " << publicationDate << " - ID: " << id << "\n"; 
        }

        // Getter
        bool get_isAvaible() const { return isAvaible; }
        int get_id() const { return id; }

        // Setter
        void set_isAvaible(bool isAvaible) { this->isAvaible = isAvaible; }
};

class Book : public Item {
    private:
        string author;

    public:
        Book() : author(""), Item() {}

        Book(const string& author, const string& title, const double& publicationDate, const int& id) : author(author), Item(title, publicationDate, id) {}

        // Methods
        void display() const override {
            cout << "\nBook - " << title << " - " << author << " - " << id << "\n";
        }
};

class DVD : public Item {
    private:
        int duration;

    public:
        DVD() : duration(0), Item() {}

        DVD(const int& duration, const string& title, const double& publicationDate, const int& id) : duration(duration), Item(title, publicationDate, id) {}

        // Methods
        void display() const override {
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

        // Methods
        void borrowItem(Item* item) {

            if(currentItems < maxItems && item->get_isAvaible() && item) {
                borrowedItems[currentItems++] = item;
                item->set_isAvaible(false);

                cout << "\nBorrowed Item: ";
                item->display(); 
            }

            else if(!item->get_isAvaible()){
                cout << "\nThe item is not avaible at the moment...\n";
                item->display();
            }

            else {
                cout << "\nYou can no longer borrow any more items.\n";
            }
        }

        void returnItems(int id) {
            
            bool found = false;
            size_t j;
            for(size_t i = 0; i < currentItems; i++) {
                if(id == borrowedItems[i]->get_id()) {
                    j = i;
                    found = true;

                    borrowedItems[i]->set_isAvaible(true);
                    borrowedItems[i] = nullptr;

                    break;
                }
            }

            if(found) {
                for(size_t i = j; i < currentItems; i++) {
                    borrowedItems[i] = borrowedItems[i+1];
                }

                currentItems--;
            }

            else {
                cout << "\nThe given ID doesn't exists in your borrowed items.\n";
            }
        }

        virtual void printItems() const {

            cout << "\nCurrently borrowed items: ";
            for(size_t i = 0; i < currentItems; i++)
                borrowedItems[i]->display();
        }
};

class Student : public Person {
    public:
        Student() : Person() {}

        Student(const string& name, const string& surname, int maxItems) : Person(name, surname, maxItems) {}
};

class Professor : public Person {
    public:
        Professor() : Person() {}

        Professor(const string& name, const string& surname, int maxItems) : Person(name, surname, maxItems) {}
};

// LIBRARY
class Library {
    private:
        string name;

        Item** items;
        size_t maxItems;

        int counter_items;

    public:
        Library() : name(""), items(nullptr), maxItems(0), counter_items(0) {}

        Library(const string& name, size_t maxItems) : name(name), maxItems(maxItems), counter_items(0) {
            items = new Item* [maxItems];
            for(size_t i = 0; i < maxItems; i++) {
                items[i] = nullptr;
            }
        }

        void add_book() {
            
            if(counter_items < maxItems) {
                cout << "\nInsert title: ";
                string title;
                getline(cin, title);

                cout << "\nInsert author: ";
                string author;
                getline(cin, author);

                cout << "\nInsert publication date: ";
                double pubDate;
                cin >> pubDate;

                cout << "\nInsert id: ";
                int id;
                cin >> id;
                cin.ignore();

                items[counter_items++] = new Book(author, title, pubDate, id);
            }
        }

        void add_dvd() {
            
            if(counter_items < maxItems) {
                cout << "\nInsert title: ";
                string title;
                getline(cin, title);

                cout << "\nInsert duration: ";
                int duration;
                cin >> duration;

                cout << "\nInsert publication date: ";
                double pubDate;
                cin >> pubDate;

                cout << "\nInsert id: ";
                int id;
                cin >> id;
                cin.ignore();

                items[counter_items++] = new DVD(duration, title, pubDate, id);
            }
        }

        void borrowItem(Person* person) {

            cout << "\nWich item do you want to borrow? [Insert ID] ";
            int id;
            cin >> id;
            
            for(size_t i = 0; i < maxItems; i++) {
                if(id == items[i]->get_id()) {
                    person->borrowItem(items[i]);
                    
                    break;
                }
            }
        }

        void returnItem(Person* person) {
            cout << "\nWhich item do you want to return? [Insert ID] ";
            person->printItems();
            
            int id;
            cin >> id;

            person->returnItems(id);
        }

        void printItems() const {
            
            for(size_t i = 0; i < maxItems; i++) {
                if(items[i]->get_isAvaible())
                    items[i]->display();
            }
        }
};

// MAIN
int main() {

    cout << "\nWelcome to your library! How many items do you want to add in the library? ";
    int nItems;
    cin >> nItems;

    Library lib("Libreria", nItems);

    int response;
    for(size_t i = 0; i < nItems; i++) {
        cout << "\nDo you want to add a Book [1] or a DVD [2]? ";
        cin >> response;

        switch(response) {
            case 1:
                cin.ignore();
                lib.add_book();
                break;

            case 2:
                cin.ignore();
                lib.add_dvd();
                break;
        }
    }
    system("CLS");

    lib.printItems();

    int maxItems = 5; // 10 for Professor
    // Professor u1("Massimo", "Bossetti", maxItems);
    Student u1("Andrea", "Quatrosi", maxItems);
    
    // borrowItem() Operation
    cout << "\nHow many items do you want to borrow? [Insert number of items] ";
    cin >> nItems;

    size_t i = 0;
    while(i < nItems) {
        lib.borrowItem(&u1);
        i++;
    }

    cout << "\nLibrary items: ";
        lib.printItems();

    // returnItem() Operation
    cout << "\nDo you want to return an item? [1 = Yes, 0 = No] ";
    cin >> response;

    if(response == 1) {
        cout << "\nHow many items do you want to return? [Insert number of items] ";
        cin >> nItems;

        i = 0;
        while(i < nItems) {
            lib.returnItem(&u1);
            i++;
        }

        system("CLS");
        cout << "\nUpdated borrowed items: ";
        u1.printItems();

        cout << "\nLibrary items: ";
        lib.printItems();
    }

    else {
        system("CLS");
        cout << "\nUpdated borrowed items: ";
        u1.printItems();

        cout << "\nExiting from the library...\n";   
    }

    return 0;
}