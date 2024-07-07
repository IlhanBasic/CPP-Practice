#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Artikal {
private:
string naziv;
float cena;
int popust;

public:
Artikal(string n = "", float c = 0, int p = 0) : naziv(n), cena(c), popust(p) {}
friend ostream& operator<<(ostream& os, Artikal& a) {
    os << "Podaci o artiklu:"<< a.naziv << "(" << a.cena + (a.cena * a.popust) / 100 << ")";
    return os;
}

float getCena() { return cena; }
};

class Stavka {
private:
Artikal artikal;
int kolicina;
int redBr;

public:
static int brojac;
Stavka(Artikal a, int k) : artikal(a), kolicina(k), redBr(brojac++) {}

float iznosStavke() {
    return artikal.getCena() * kolicina;
}

Stavka(const Stavka& s) : artikal(s.artikal), kolicina(s.kolicina), redBr(brojac++) {}

friend ostream& operator<<(ostream& os, Stavka& s) {
    os << s.redBr << "(" << s.artikal << "):" << s.kolicina << "|" << s.iznosStavke();
    return os;
}
};

int Stavka::brojac = 0;

class Racun {
private:
struct Elem {
Elem* sled;
Stavka* stavke;
int dodatniPopust;
    Elem(Stavka* st, int dp = 0, Elem* sl = NULL) : sled(sl), stavke(st), dodatniPopust(dp) {}

    ~Elem() {
        delete stavke;
    }
};

Elem* prvi = NULL;
Elem* posled = NULL;
int dodatniPopust;
public:
Racun() {
dodatniPopust = 0;
}
void setDodatniPopust(int value) {
    dodatniPopust = value;
}

Racun& operator+=(Stavka* st) {
    Elem* novi = new Elem(st);
    if (!prvi) {
        prvi = novi;
        posled = novi;
    } else {
        posled->sled = novi;
        posled = novi;
    }
    return *this;
}

float iznosRacuna() {
    float suma = 0;
    Elem* trenutno = prvi;
    while (trenutno != NULL) {
        suma += trenutno->stavke->iznosStavke();
        if (trenutno->dodatniPopust != 0) {
            suma -= (trenutno->stavke->iznosStavke() * trenutno->dodatniPopust) / 100;
        }
        trenutno = trenutno->sled;
    }
    return suma;
}

friend ostream& operator<<(ostream& os, Racun& ra) {
    os << "Racun:" << ra.iznosRacuna() << endl;
    Racun::Elem* trenutno = ra.prvi;
    while (trenutno != NULL) {
        os << *(trenutno->stavke) << "[" << (trenutno->stavke->iznosStavke() + (trenutno->dodatniPopust * trenutno->stavke->iznosStavke()) / 100) << "]" << endl;
        trenutno = trenutno->sled;
    }
    return os;
}

~Racun() {
    Elem* trenutni = prvi;
    while (trenutni != NULL) {
        Elem* stari = trenutni;
        trenutni = trenutni->sled;
        delete stari;
    }
    prvi = NULL;
    posled = NULL;
}
};

int main() {
Artikal a1("Hleb", 60), a2("DolceGabana parfem 60ml", 12000, 5), a3("Sladoled Quatro ", 500), a4("Knjaz Milos 1,5L", 60), a5("Autic", 3400, 10);
Stavka s1(a1, 2), s2(a2, 1), s3(a3, 3), s4(a4, 6), s5(a5, 2);
Racun r1;
r1 += &s1;
r1 += &s2;
r1 += &s3;
r1 += &s4;
r1 += &s5;
cout << r1 << endl;
return 0;
}
