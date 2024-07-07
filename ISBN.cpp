#include <iostream>
#include <string.h>
#include <string>
#include <cstring>
#include <stdbool.h>
#include <stdlib.h>
using namespace std;

class ISBN {
    char isbn[14]; // make room for null terminator
  public:
    ISBN() {}
    ISBN(const char *i) {
        strncpy(isbn, i, 13);
        isbn[13] = '\0'; // add null terminator
    }
    char* getIsbn() { return isbn; }
    bool provera(ISBN *i) {
        return strcmp(isbn, i->isbn) == 0;
    }
    void Ispis() {
        cout << isbn ;
    }
};

class Knjiga {
    string Naslov;
    ISBN Isbn;
  public:
    Knjiga(){}
    Knjiga(string n, ISBN i) {
        Naslov = n;
        Isbn = i;
    }
    string getNaslov() { return Naslov; }
    ISBN getISBN() { return Isbn; }
    void Ispis() {
        cout << Naslov << "(";
        Isbn.Ispis();
        cout << ")" << endl;
    }
};

class Izdavac {
    string naziv;
    int brKnjiga;
    int kapacitet;
    Knjiga *knjige;
  public:
    Izdavac(int max) {
        naziv = "";
        kapacitet = max;
        brKnjiga = 0;
        knjige = new Knjiga[max]; // allocate memory for knjige
    }
    ~Izdavac() { delete[] knjige; } // deallocate memory in destructor
    string getNaziv()const { return naziv; }
    void setNaziv(string value){naziv=value;}
    void dodajKnjigu(Knjiga *k) {
        bool semafor = true; // initialize semafor to true
        for (int i = 0; i < brKnjiga; i++) {
            if (strcmp(knjige[i].getISBN().getIsbn(), k->getISBN().getIsbn()) == 0) {
                semafor = false; // set semafor to false if ISBN matches
                break;
            }
        }
        if (semafor) {
            if (brKnjiga < kapacitet) {
                knjige[brKnjiga] = *k;
                brKnjiga++;
            }
            else {
                cout << "Ne sme se dodavati !" << endl;
            }
        }
    }
    void Ispis() {
        cout << naziv << " " << brKnjiga << endl;
        for (int i = 0; i < brKnjiga; i++)
            knjige[i].Ispis();
    }
};

int main() {
    ISBN i1("1234567890098"), i2("0987654321123"), i3("5647382910385"), i4("3826174930261"), i5("2388337481104");
    Knjiga k1("Beograd", i1), k2("Novi Sad", i2), k3("Nis", i3), k4("Kragujevac", i4), k5("Novi Pazar", i5);
    Izdavac i(10);
    i.setNaziv("PROLETER");
    i.dodajKnjigu(&k1);
    i.dodajKnjigu(&k2);
    i.dodajKnjigu(&k3);
    i.dodajKnjigu(&k4);
    i.dodajKnjigu(&k5);
i.Ispis();
return 0;
}
