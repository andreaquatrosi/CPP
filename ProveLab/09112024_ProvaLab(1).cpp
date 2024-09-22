// new solution for the same problem
// using queue for both library and user items

#include <iostream>
#include <string>

using namespace std;

// Item
class Item {    // Node of the queue
    protected:
        string title;
        double publicationDate; // Formato MM.AAAA
        int id;

        bool isAvaible;

        Item* next;

    public:
        Item() : title(""), publicationDate(0.0f), id(0), isAvaible(true), next(nullptr) {}

        Item(const string& title, const double& publicationDate, const int& id) : title(title), publicationDate(publicationDate), id(id), isAvaible(true), next(nullptr) {}

        // Getter
        int get_id() const { return id; }

        Item* get_next() { return next; }
        bool get_isAvaible() { return isAvaible; }

        // Setter
        void set_next(Item* next) { this->next = next; }
        void set_isAvaible(bool isAvaible) { this->isAvaible = isAvaible; }

        virtual void display() const {
            cout << "\nItem - " << title << " - " << publicationDate << " - " << id << "\n";
        }
};

class Book : public Item {
    private:
        string author;

    public:
        Book() : author(""), Item() {}

        Book(const string& author, const string& title, const double& publicationDate, const int& id) : author(author), Item(title, publicationDate, id) {}

        void display() const {
            cout << "\nBook - " << title << " - " << author << " - " << id << "\n";
        }
};

class DVD : public Item {
    private:
        int duration; // n-minutes

    public:
        DVD() : duration(0), Item() {}

        DVD(const int& duration, const string& title, const double& publicationDate, const int& id) : duration(duration), Item(title, publicationDate, id) {}

        void display() const {
            cout << "\nDVD - " << title << " - " << duration << " - " << id << "\n";
        }
};

// Queue of borrowed items
class Queue {
    private:
        Item* head;
        Item* tail;

        size_t size;
    public:
        Queue() : head(nullptr), tail(nullptr), size(0) {}

        // Getter
        size_t get_size() const { return size; }

        // Operations
        bool is_empty() const { return head == nullptr; }

        void enqueue(Item* item) {

            if(this->is_empty()) {
                head = tail = item;
                size++;

                return;
            }

            tail->set_next(item);
            tail = item;

            size++;
        }

        void dequeue(const int id) {
            
            if(this->is_empty())
                return;

            Item* temp = nullptr;

            if(id == head->get_id()) {
                temp = head;
                head = head->get_next();

                if(head == nullptr)
                    tail = nullptr;
            }

            else {
                temp = head->get_next();
                Item* prev = head;

                while(temp != nullptr && id != temp->get_id()) {
                    prev = temp;
                    temp = temp->get_next();
                }

                if(temp == nullptr)
                    return;

                if(prev != nullptr)
                    prev->set_next(temp->get_next());
                
                if(temp == tail)
                    tail = prev;
            }

            temp->set_isAvaible(true);
            temp->set_next(nullptr);
            size--;
        }

        Item* search_item(const int id) {

            if(this->is_empty())
                return nullptr;
  
            Item* current = head;
            
            while(current != nullptr && id != current->get_id())
                current = current->get_next();

            if(current == nullptr)
                return nullptr;
                
            return current;
        }

        void display() const {
            
            Item* current = head;

            while(current != nullptr) {
                current->display();
                current = current->get_next();
            }
        }
};

// User
class User {
    protected:
        string name;
        string surname;

        Queue borrowedItems;
        size_t maxItems;

    public:
        User() : name(""), surname(""), maxItems(0) {}

        User(const string& name, const string& surname, int maxItems) : name(name), surname(surname), maxItems(maxItems) {} 

        void borrowItems(Item* item) {

            if(item == nullptr)
                cout << "\nItem not found.\n";

            if(borrowedItems.get_size() < maxItems && item->get_isAvaible()) {
                item->set_isAvaible(false);
                borrowedItems.enqueue(item);
            }

            else {

                if(!item->get_isAvaible())
                    cout << "\nThis item is not avaible at the moment...\n";
                
                else
                    cout << "\nYou can no longer borrow any more items.\n";
            }
        }

        void returnItems(const int id) {
            borrowedItems.dequeue(id);
        }

        Item* searchBorrowedItem(int id) {
            return borrowedItems.search_item(id);
        }

        virtual void printItems() const {
            cout << "\nUser items:\n";
            borrowedItems.display();
        }
};

class Student : public User {
    public:
        Student() : User() {}
        
        Student(const string& name, const string& surname, int maxItems) : User(name, surname, maxItems) {}
};

class Professor : public User {
    public:
        Professor() : User() {}
        
        Professor(const string& name, const string& surname, int maxItems) : User(name, surname, maxItems) {}
};

// Library
class Library {
    private:
        string name;

        Queue libraryItems;

    public:
        Library() : name("") {}

        Library(const string& name) : name(name) {}

        void add_book() {
            
            cout << "\nTitle: ";
            string title;
            getline(cin, title);

            cout << "\nAuthor: ";
            string author;
            getline(cin, author);

            cout << "\nPublication Date: ";
            double publicationDate;
            cin >> publicationDate;

            cout << "\nID: ";
            int id;
            cin >> id;
            cin.ignore();

            Book* newBook = new Book(author, title, publicationDate, id);
            libraryItems.enqueue(newBook);
        }

        void add_dvd() {
            
            cout << "\nTitle: ";
            string title;
            getline(cin, title);

            cout << "\nDuration: ";
            int duration;
            cin >> duration;

            cout << "\nPublication Date: ";
            double publicationDate;
            cin >> publicationDate;

            cout << "\nID: ";
            int id;
            cin >> id;

            DVD* newDVD = new DVD(duration, title, publicationDate, id);
            libraryItems.enqueue(newDVD);
        }

        void borrowItems(User* user) {
        
            cout << "\nInput ID: ";
            int id;
            cin >> id;
            
            Item* item = libraryItems.search_item(id);
            user->borrowItems(item);
        }

        void returnItems(User* user) {

            user->printItems();
            cout << "\nWhich item do you want to return? [Input ID] ";
            int id;
            cin >> id;

            Item* borrowedItem = user->searchBorrowedItem(id);
            if(borrowedItem == nullptr) {
                cout << "\nItem not found in borrowed items.\n";
                return;
            }

            user->returnItems(id);
            borrowedItem->set_isAvaible(true);  // Mark the item as available in the library.
            cout << "\nItem returned to the library.\n";
        }

        void displayItems() const {
            cout << "\nLibrary items:\n";
            libraryItems.display();
        }
};

// MAIN
int main() {

    Library lib("Pisello's Library");
    
    cout << "\nHow many books do you want to add? ";
    int n;
    cin >> n;

    size_t i = 0;
    while(n > 0 && i++ < n) {
        cin.ignore();
        lib.add_book();
    }

    cout << "\nHow many dvds do you want to add? ";
    cin >> n;

    i = 0;
    while(n > 0 && i++ < n) {
        cin.ignore();
        lib.add_dvd();
    }

    lib.displayItems();

    system("CLS");
    Student s1("Andrea", "Quatrosi", 5);
    cout << "\nHow many items do you want to borrow? [Max 5] ";
    cin >> n;

    lib.displayItems();
    
    i = 0;
    while(i++ < n)
        lib.borrowItems(&s1);

    s1.printItems();

    lib.returnItems(&s1);

    s1.printItems();

    return 0;
}
