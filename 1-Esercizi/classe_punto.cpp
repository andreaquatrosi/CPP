/* 
    Implementare una classe Punto che
    rappresenti punti in tre dimensioni (x, y, z).
    Includere un costruttore di default, un
    costruttore di copia, una funzione negare()
    che trasformi il punto nel suo contrario
    (negativo), una funzione norma() che ritorni
    la distanza dal punto all’origine (0,0,0) e
    una funzione visualizzare() .
*/

#include <iostream>
#include <cmath>

using namespace std;

class Punto {

    private:
        int x, y, z;

    public:
        // Default
        Punto() : x(0), y(0), z(0) { cout << "Costruttore di Default\n"; }
        
        // Parametrized
        Punto(int x, int y, int z) : x(x), y(y), z(z) { cout << "Costruttore Parametrizzato\n"; }

        // Copy
        Punto(const Punto& p) {
            x = p.x;
            y = p.y;
            z = p.z;

            cout << "Costruttore di Copia\n";
        }

        // Getter
        int get_x() const { return x; }
        int get_y() const { return y; }
        int get_z() const { return z; }

        // Setter
        void set_x(int x) { this->x = x; }
        void set_y(int y) { this->y = y; }
        void set_z(int z) { this->z = z; }

        // Methods
        void visualizzare() {

            cout << "\nCoordinate del Punto:\n"
                 << "(" << x << ", " << y << ", " << z << ")"
                 << "\n";
        }

        void negare() {
        
            x = -x;
            y = -y;
            z = -z;
        }

        double norma() { return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)); }
};

int main() {

    Punto p1;         // Default
    Punto p2(1, 3, 5);  // Parametrized
    Punto p3(p2);       // Copy

    p1.visualizzare();
    p2.visualizzare();
    p3.visualizzare();

    cout << "\nNegare il punto p2:\n";
    p2.negare();
    p2.visualizzare();

    cout << "\nLa distanza del punto p3: " << p3.norma();

    return 0;
}