#include <iostream>
#include <string>
#include <stdbool.h>
#include <stdlib.h>
using namespace std;

enum VRSTA { BEZALKOHOLNO, ALKOHOLNO };

class Nalepnica {
    string Naziv;
public:
    static int ID;
    Nalepnica(string naziv) {
        Naziv = naziv;
        ID++;
    }
    int getID() { return ID; }
    void Ispis() {
        cout << Naziv << ":" << ID << endl;
    }
};

int Nalepnica::ID = 0;

class Flasa {
protected:
    Nalepnica nalepnica;
    float cena_bez_flase;
    float zapremina;
    VRSTA vrsta;

public:
string nadjiVrstu() {
        switch (vrsta) {
        case BEZALKOHOLNO:
            return "BEZALKOHOLNO";
        case ALKOHOLNO:
            return "ALKOHOLNO";
        }
        return "GRESKA";
    }
    Flasa(Nalepnica n, float c, float z, VRSTA v) : nalepnica(n), cena_bez_flase(c), zapremina(z), vrsta(v) {}

    Nalepnica getNalepnica() { return nalepnica; }
    float getCena_bez_flase() { return cena_bez_flase; }
    float getZapremina() { return zapremina; }
    VRSTA getVrsta() { return vrsta; }

    void setCena_bez_flase(float v) { cena_bez_flase = v; }

    virtual float cena_sa_flasom() {
        return cena_bez_flase;
    }

    bool operator ==(Flasa &f) {
        if (this == &f)
            return true;
        else {
            if (nalepnica.getID() == f.getNalepnica().getID() &&
                cena_sa_flasom() == f.cena_sa_flasom() &&
                getVrsta() == f.getVrsta())
                return true;
            else
                return false;
        }
    }

    friend ostream &operator <<(ostream &out, Flasa &f) {
        f.nalepnica.Ispis();
        out << "(" << f.cena_bez_flase << "," << f.zapremina << "," << f.nadjiVrstu() << ")" << endl;
        return out;
    }
};

class Staklena : public Flasa {
public:
    Staklena(Nalepnica n, float c, float z, VRSTA v = BEZALKOHOLNO) : Flasa(n, c, z, v) {}

    float cena_sa_flasom() {
        if (zapremina < 0.5)
            return cena_bez_flase + cena_bez_flase * (5 / 100);
        else if (zapremina < 1)
            return cena_bez_flase + cena_bez_flase * (10 / 100);
        return cena_bez_flase;
    }

    friend ostream &operator <<(ostream &out,Staklena &s) {
        s.nalepnica.Ispis();
        out << "(" << s.cena_bez_flase << "," << s.zapremina << "," << s.nadjiVrstu() << ")" << "-staklena" << endl;
        return out;
    }
};

class Plasticna : public Flasa {
public:
    Plasticna(Nalepnica n, float c, float z, VRSTA v = BEZALKOHOLNO) : Flasa(n, c, z, v) {}

    float cena_sa_flasom() {
        return cena_bez_flase;
    }

    friend ostream &operator <<(ostream &out,Plasticna &p) {
        p.nalepnica.Ispis();
        out << "(" << p.cena_bez_flase << "," << p.zapremina << "," << p.nadjiVrstu() << ")" << "-plasticna" << endl;
        return out;
    }
};
class Diskont {
private:
    string Naziv;
    Flasa** flase;
    int brFlasa;
    int MaxFlasa = 10;

public:
    Diskont(string N) {
        Naziv = N;
        brFlasa = 0;
        flase = new Flasa*[MaxFlasa];
    }

    Diskont(const Diskont&) = delete;

    Diskont& operator +=(Flasa* f) {
        if (brFlasa < MaxFlasa) {
            flase[brFlasa++] = f;
        }
        return *this;
    }

    ~Diskont() {
        for (int i = 0; i < brFlasa; i++)
            delete flase[i];
        delete[] flase;
    }

    Flasa& operator [](int i) {
        return *flase[i];
    }

    float ukupnaVrednost() {
        float suma = 0;
        for (int i = 0; i < brFlasa; i++)
            suma += flase[i]->cena_sa_flasom();
        return suma;
    }

    friend ostream& operator <<(ostream& out, const Diskont& d) {
        out << d.Naziv << endl;
        for (int i = 0; i < d.brFlasa; i++) {
            d.flase[i]->getNalepnica().Ispis();
            out << "(" << d.flase[i]->getCena_bez_flase() << "," << d.flase[i]->getZapremina()
                << "," << d.flase[i]->nadjiVrstu() << ")" << endl;
        }
        return out;
    }
};

int main() {
    Diskont d("SZTR BEJZIK");
    Nalepnica n1("Sok"), n2("Vino"), n3("Pivo");
    d += new Staklena(n1, 60, 0.5);
    d += new Staklena(n2, 1100, 0.7, ALKOHOLNO);
    d += new Plasticna(n3, 150, 2, BEZALKOHOLNO);
    cout << d << endl;
    cout << "Ukupna vrednost: " << d.ukupnaVrednost() << endl;

    return 0;
}

