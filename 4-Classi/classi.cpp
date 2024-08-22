#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

// Definizione della classe
class MyClass {

    private:
        int data;
        char* name;
        static size_t counter;

    public:
        // Default
        MyClass() : data(0), name(nullptr) {
            name = new char [1];
            name[0] = '\0';
        }                      

        // Parametrized
        MyClass(int d, const char* name) : data(d), name(new char [strlen(name) + 1]) { 
            
            strcpy(this->name, name);
            counter++; 
        }     
        
        // Copy
        MyClass(MyClass& obj) {  
                               
            data = obj.get_Data();
            strcpy(name, obj.get_Name());
            counter++;
        }

        ~MyClass() {
            delete [] name;
        }

        // Getter
        int get_Data() const { return data; }

        char* get_Name() const { return name; }

        // Setter
        void set_Data(int data) { this->data = data; }

        void set_Name(const char* name) {
            delete [] this->name;

            this->name = new char [strlen(name) + 1];
            strcpy(this->name, name);
        }

        // Metodo esterno per stampare i dati
        /*virtual*/ void display() const;

        // Friend
        friend void add_data(int to_add, MyClass& obj);
};

void MyClass::display() const {

    cout << "MyClass::display()"
         << "\nData: " << data
         << "\nName: " << name
         << "\n";
}

size_t MyClass::counter = 0;

// Friend
void add_data(int to_add, MyClass& obj) {
     
    obj.data += to_add;
}

class MyDerivedClass : public MyClass {
    
    private:
        double extraData;

    public:
        // Parametrized Constructor
        // chiama il costruttore della classe base
        MyDerivedClass(int data, char* name, double extraData) : MyClass(data, name), extraData(extraData) {}

        ~MyDerivedClass() {}

        // Getter
        double get_extraData() const { return extraData; }

        // Setter
        void set_extraData(double extraData) { this->extraData = extraData; }

        // Metodo
        void display() const {

            MyClass::display();
            cout << "MyDerivedClass::display()"
                 << "\nExtra Data: " << extraData
                 << "\n";
        }
};

int main() {
    // Creazione di un oggetto della classe MyClass
    MyClass obj_b(42, "Andrea");

    // Utilizzo dei metodi della classe
    obj_b.display();

    obj_b.set_Data(100);
    cout << "\nUpdated Data: " << obj_b.get_Data() << endl;

    cout << "\nUpdated Data using add_data()\n";
    add_data(10, obj_b);  // add_data() è una funzione friend
    obj_b.display();
    
    // Creazione di un oggetto della classe MyDerivedClass
    char* name = new char [10];
    strcpy(name, "Andrea");
    cout << "\nCalling display() in the derived object\n";
    MyDerivedClass obj_d(69, name, 420.69);

    obj_d.display();

    // Ptr
    cout << "\nUsing pointer to MyDerivedClass\n";
    MyClass* ptr = &obj_d;
    ptr->display();         // Chiama MyClass::display() (binding statico)
                            // Aggiungere "virtual" alla riga 53 per chiamare MyDerivedClass::display() (binding dinamico)

    return 0;
}   