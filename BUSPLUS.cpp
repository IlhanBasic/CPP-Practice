#include <iostream>
#include <string>
using namespace std;

class Datum {
    int mesec;
    int godina;

public:
    Datum() {
        mesec = 10;
        godina = 2023;
    }

    Datum(int m, int g) {
        mesec = m;
        godina = g;
    }

    int getMesec() { return mesec; }
    int getGodina() { return godina; }

    void setMesec(int m) { mesec = m; }
    void setGodina(int g) { godina = g; }

    friend bool operator==(Datum& d1, Datum& d2) {
        return (d1.mesec == d2.mesec && d1.godina == d2.godina);
    }

    friend bool operator!=(Datum& d1, Datum& d2) {
        return !(d1 == d2);
    }

    friend ostream& operator<<(ostream& os, Datum& d) {
        os << d.mesec << "/" << d.godina << endl;
        return os;
    }
};

class Karta {
protected:
    int ID;
    float cenaVoznje;
    Datum datum;

public:
    Karta(float c, Datum d) {
        cenaVoznje = c;
        datum = d;
        brojac++;
        ID = brojac;
    }

    static int brojac;

    virtual bool Provera(float c, Datum d) = 0;

    Karta(const Karta& k) = delete;

    virtual void Ispis(ostream& os) = 0;

    friend ostream& operator<<(ostream& os, Karta& k) {
        k.Ispis(os);
        return os;
    }
};

int Karta::brojac = 0;

class Mesecna : public Karta {
    string Ime;

public:
    Mesecna(string I, Datum d, float cena) : Karta(cena, d) {
        Ime = I;
    }

    void ProduziVazenje(Datum d) {
        datum.setMesec(d.getMesec());
        datum.setGodina(d.getGodina());
    }

    bool Provera(float c, Datum d) {
        if (datum.getMesec() < d.getMesec() || datum.getGodina() < d.getGodina())
            return false;
        else
            return true;
    }

    void Ispis(ostream& os) {
        os << Ime << "(";
        Karta::Ispis(os);
        os << ")" << datum << endl;
    }
};

class Pojedinacna : public Karta {
    float iznos;

public:
    Pojedinacna(float c, Datum d) : Karta(c, d) {
        iznos = 50;
    }

    void dopuni(float i) {
        iznos += i;
    }

    void Provera() {
        if (datum.getMesec() < datum.getMesec() && datum.getGodina() <= datum.getGodina() && cenaVoznje < iznos)
            iznos -= cenaVoznje;
    }

    bool Provera(float c, Datum d) {
        if (datum.getMesec() < d.getMesec() && datum.getGodina() <= d.getGodina() && cenaVoznje < iznos)
            return true;
        else
            return false;
    }

    void Ispis(ostream& os) {
        os << iznos << "(";
        Karta::Ispis(os);
        os << ")" << endl;
    }
};

template <class T>
class Zbirka {
    public:
    T** nizKarti;
    int trenutno;
    int maxKarti;

public:
    Zbirka(int max) {
        maxKarti = max;
        trenutno = 0;
        nizKarti = new T*[maxKarti];
    }

    Zbirka& operator<<(T* k) {
        if (trenutno < maxKarti) {
            nizKarti[trenutno++] = k;
        }
        else {
            T** pom = new T*[maxKarti];
            for (int i = 0; i < trenutno; i++)
                pom[i] = nizKarti[i];

            for (int i = 0; i < trenutno; i++)
                delete nizKarti[i];

            delete[] nizKarti;

            maxKarti++;

            nizKarti = new T*[maxKarti];

            for (int i = 0; i < maxKarti - 1; i++) {
                nizKarti[i] = pom[i];
                trenutno++;
            }

            nizKarti[trenutno++] = k;

            delete[] pom;
        }

        return *this;
    }

    Zbirka& operator>>(T& k) {
        if (trenutno > 0) {
            for (int i = 0; i < trenutno; i++) {
                if (*nizKarti[i] == k) {
                    delete nizKarti[i];
                    maxKarti--;

                    for (int j = i; j < maxKarti; j++) {
                        nizKarti[j] = nizKarti[j + 1];
                    }
                }
            }
        }

        return *this;
    }

    Zbirka(const Zbirka& z) {
        trenutno = z.trenutno;
        nizKarti = new T*[trenutno];

        for (int i = 0; i < trenutno; i++) {
            if (z.nizKarti[i] != nullptr) {
                nizKarti[i] = new T(*z.nizKarti[i]);
            }
        }
    }
};
class Aparat {
    public:
    Zbirka<Karta> zbirka;
    Aparat() : zbirka(10) {}

    Aparat& operator+=(Karta* k) {
        zbirka << k;
        return *this;
    }

    void ProveraKarti(float cena, Datum datum) {
        for (int i = 0; i < zbirka.trenutno; i++) {
            Karta* karta = zbirka.nizKarti[i];
            bool valjana = karta->Provera(cena, datum);
            cout << "Karta " << *karta << (valjana ? "valjana" : "nije valjana") << endl;
        }
    }

    friend ostream& operator<<(ostream& os, const Aparat& aparat) {
        for (int i = 0; i < aparat.zbirka.trenutno; i++) {
            os << *aparat.zbirka.nizKarti[i] << endl;
        }
        return os;
    }

    Aparat(const Aparat& aparat) = delete;
};



int main() {
    Datum d1(5, 2023);
    Datum d2(7, 2023);

    Mesecna m1("Marko", d1, 100.0);
    Mesecna m2("Ana", d2, 150.0);

    Pojedinacna p1(75.0, d1);
    Pojedinacna p2(100.0, d2);

    Zbirka<Karta> zbirka(10);
    zbirka << &m1 << &m2 << &p1 << &p2;

    cout << "Zbirka: " << endl;
    cout << zbirka << endl;

    zbirka >> m1;
    zbirka >> p2;

    cout << "Zbirka nakon uklanjanja karata: " << endl;
    cout << zbirka << endl;

    return 0;
}

