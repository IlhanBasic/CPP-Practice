#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Merljiv {
public:
    virtual double getTezina() const = 0;
    virtual string getNaziv() const = 0;
    friend ostream& operator<<(ostream& os, const Merljiv& m) {
        os << m.getNaziv() << "(" << m.getTezina() << ")";
        return os;
    }
};

class MerljivaOsoba : public Merljiv {
private:
    string ime;
    double tezina;
public:
    MerljivaOsoba(const string& i, double t) : ime(i), tezina(t) {}
    double getTezina() const override {
        return tezina;
    }
    string getNaziv() const override {
        return ime;
    }
};

class MerljivTeretniKontejner : public Merljiv {
private:
    static int nextRegBroj;
    int regBroj;
    double tezina;
public:
    MerljivTeretniKontejner(double t) : tezina(t) {
        regBroj = nextRegBroj++;
    }
    double getTezina() const override {
        return tezina;
    }
    string getNaziv() const override {
        return "Kontejner";
    }
    friend ostream& operator<<(ostream& os, const MerljivTeretniKontejner& kont) {
        os << "K" << kont.regBroj << "(" << kont.getTezina() << ")";
        return os;
    }
    void operator+=(double teret) {
        tezina += teret;
    }
    void operator-=(double teret) {
        if (teret > tezina) {
            std::cout << "Greska: Ne moze se izvaditi teret vece tezine od trenutne tezine kontejnera." << std::endl;
        } else {
            tezina -= teret;
        }
    }
};

int MerljivTeretniKontejner::nextRegBroj = 1;

template <typename T>
class GenNiz {
private:
    T* niz;
    int duzina;
public:
    GenNiz(int size = 10) {
        duzina = size;
        niz = new T[duzina];
    }
    ~GenNiz() {
        delete[] niz;
    }
    int getDuzina() const {
        return duzina;
    }
    T& operator[](int index) {
        if (index < 0 || index >= duzina) {
            cerr << "Greska: Indeks van opsega" << endl;
            exit(1);
        }
        return niz[index];
    }
};

class AbstraktanAvion {
private:
    string oznaka;
    double maxTezina;
    double praznaTezina;
    Merljiv** pojamNiz;
    int brojPojava;
public:
    AbstraktanAvion(const string& o, double maxT, double praznaT, int br) : oznaka(o), maxTezina(maxT), praznaTezina(praznaT), brojPojava(br) {
        pojamNiz = new Merljiv*[brojPojava];
        for (int i = 0; i < brojPojava; i++) {
            pojamNiz[i] = nullptr;
        }
    }
    AbstraktanAvion(const AbstraktanAvion& avion) = delete;
    void stavi(int index, Merljiv* pojam) {
        if (index < 0 || index >= brojPojava) {
            cerr << "Greska: Indeks van opsega" << endl;
            exit(1);
        }
        if (pojamNiz[index] != nullptr) {
            cerr << "Greska: Mesto vec popunjeno" << endl;
            exit(1);
        }
        pojamNiz[index] = pojam;
    }
    void ukloni(int index) {
        if (index < 0 || index >= brojPojava) {
            cerr << "Greska: Indeks van opsega" << endl;
            exit(1);
        }
        if (pojamNiz[index] == nullptr) {
            cerr << "Greska: Nista za uklanjanje" << endl;
            exit(1);
        }
        pojamNiz[index] = nullptr;
    }
    double izracunajTrenutnuTezinu() const {
        double suma = praznaTezina;
        for (int i = 0; i < brojPojava; i++) {
            if (pojamNiz[i] != nullptr) {
                suma += pojamNiz[i]->getTezina();
            }
        }
        return suma;
    }
    friend ostream& operator<<(ostream& os, const AbstraktanAvion& avion) {
        os << avion.oznaka << "(" << avion.izracunajTrenutnuTezinu() << ")[";
        for (int i = 0; i < avion.brojPojava; i++) {
            if (avion.pojamNiz[i] != nullptr) {
                os << *avion.pojamNiz[i];
                if (i != avion.brojPojava - 1) {
                    os << ",";
                }
            }
        }
        os << "]";
        return os;
    }
};

class PutnickiAvion : public AbstraktanAvion {
public:
    PutnickiAvion() : AbstraktanAvion("Putnicki", 5000, 1000, 3) {}
};

class TeretniAvion : public AbstraktanAvion {
public:
    TeretniAvion() : AbstraktanAvion("Teretni", 10000, 500, 2) {}
};

int main() {
    PutnickiAvion putnickiAvion;
    putnickiAvion.stavi(0, new MerljivaOsoba("Marko", 70));
    putnickiAvion.stavi(1, new MerljivaOsoba("Ana", 60));
    putnickiAvion.stavi(2, new MerljivaOsoba("Jovan", 80));

    TeretniAvion teretniAvion;
    teretniAvion.stavi(0, new MerljivTeretniKontejner(2000));
    teretniAvion.stavi(1, new MerljivTeretniKontejner(3000));

    cout << putnickiAvion << endl;
    cout << teretniAvion << endl;

    return 0;
}


