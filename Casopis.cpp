#include <iostream>
#include <cstring>
using namespace std;

class Publikacija {
protected:
    char* naslov;
    char* ime;

public:
    Publikacija(const char* n, const char* i) {
        naslov = new char[strlen(n) + 1];
        strcpy(naslov, n);
        ime = new char[strlen(i) + 1];
        strcpy(ime, i);
    }

    ~Publikacija() {
        delete[] naslov;
        delete[] ime;
    }

    char* getNaslov() const { return naslov; }
    char* getIme() const { return ime; }

    virtual void Ispis(ostream& os) const = 0;

    friend ostream& operator<<(ostream& os, const Publikacija& p) {
        p.Ispis(os);
        return os;
    }
};

class Delo : public Publikacija {
public:
    Delo() : Publikacija(NULL,NULL) {}
    Delo(const char* n, const char* i) : Publikacija(n, i) {}

    void Ispis(ostream& os) const override {
        os << getIme() << ": " << getNaslov() << endl;
    }
};

class Knjiga : public Publikacija {
    Delo delo;

public:
    Knjiga(const char* n, const char* i, const char* dNaslov, const char* dIme)
        : Publikacija(n, i), delo(dNaslov, dIme) {}

    void Ispis(ostream& os) const override {
        os << "Knjiga sadrzi delo:" << endl;
        os << delo << endl;
    }
};

class Casopis : public Publikacija {
    Delo* dela;
    int max;
    int trenutno;

public:
    Casopis(const char* n, const char* i, int m = 10)
        : Publikacija(n, i), max(m), trenutno(0) {
        dela = new Delo[max];
    }

    ~Casopis() {
        delete[] dela;
    }

    Casopis& operator+=(const Delo& d) {
        if (trenutno < max) {
            dela[trenutno++] = d;
        } else {
            cout << "Greska, prekoracen kapacitet casopisa." << endl;
        }
        return *this;
    }

    void Ispis(ostream& os) const override {
        os << getNaslov() << " (" << getIme() << ")" << endl;
        for (int i = 0; i < trenutno; i++) {
            os << dela[i] << endl;
        }
    }
};

int main() {
    Delo d1("X5", "Kenan");
    Delo d2("X7", "Omer");
    Delo d3("X3", "Aldin");
    Delo d4("M5", "Murat");

    Casopis c("BMW", "Benjamin", 10);
    c += d1;
    c += d2;
    c += d3;
    c += d4;

    cout << c << endl;

    return 0;
}
