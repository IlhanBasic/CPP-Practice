#include <iostream>
#include <string>

using namespace std;

enum VrstaSastojka { SLAN, SLADiNEUT };

class Sastojak {
private:
    string ime;
    double cenaPoKg;

public:
    Sastojak(const string& ime, double cenaPoKg)
        : ime(ime), cenaPoKg(cenaPoKg) {}

    string getIme() const {
        return ime;
    }

    double izracunajCenu(double kolicina) const {
        return cenaPoKg * kolicina / 1000.0;
    }

    friend ostream& operator<<(ostream& out, const Sastojak& s) {
        out << s.ime << "-" << s.cenaPoKg << "/kg";
        return out;
    }
};

class Jelo {
private:
    string ime;
    Sastojak* sastojci[10];
    int brojSastojaka;
    int kolicina;
    double promenaCene;
    int satFormiranjaCene;

public:
    Jelo(const string& ime, int kolicina)
        : ime(ime), brojSastojaka(0), kolicina(kolicina), promenaCene(0), satFormiranjaCene(0) {}

    void postaviPromenuCene(double promenaCene) {
        this->promenaCene = promenaCene;
    }

    void postaviSatFormiranjaCene(int satFormiranjaCene) {
        this->satFormiranjaCene = satFormiranjaCene;
    }

    void dodajSastojak(const Sastojak& sastojak, double kolicina) {
        if (brojSastojaka < 10) {
            if (sastojak.getIme() == "SLAN" && (ime == "P" || ime == "G")) {
                sastojci[brojSastojaka] = new Sastojak(sastojak);
                brojSastojaka++;
            } else if (sastojak.getIme() == "SLADiNEUT" && ime == "D") {
                sastojci[brojSastojaka] = new Sastojak(sastojak);
                brojSastojaka++;
            } else {
                throw runtime_error("Sastojak nije adekvatan za ovo jelo.");
            }
        } else {
            throw runtime_error("Jelo vec sadrzi maksimalan broj sastojaka.");
        }
    }

    string getVrstaJela() const {
        if (ime == "P") {
            return "Predjelo";
        } else if (ime == "G") {
            return "Glavno jelo";
        } else if (ime == "D") {
            return "Dezert";
        } else {
            return "Nepoznato";
        }
    }

    double izracunajCenu() const {
        double ukupnaCena = 0;
        for (int i = 0; i < brojSastojaka; i++) {
            ukupnaCena += sastojci[i]->izracunajCenu(kolicina);
        }
        if (ime == "P" && satFormiranjaCene >= 9 && satFormiranjaCene <= 12) {
            ukupnaCena *= (1 - promenaCene);
        } else if (ime == "G" && satFormiranjaCene >= 20 && satFormiranjaCene <= 23) {
            ukupnaCena *= (1 + promenaCene);
        }
        return ukupnaCena;
    }

    void ispisi() const {
        cout << ime << ":" << izracunajCenu() << endl;
        for (int i = 0; i < brojSastojaka; i++) {
            cout << *(sastojci[i]) << endl;
        }
    }

    ~Jelo() {
        for (int i = 0; i < brojSastojaka; i++) {
            delete sastojci[i];
        }
    }
};

int main() {
    Sastojak slan("SLAN", 10);
    Sastojak sladineut("SLADiNEUT", 15);

    Jelo predjelo("P", 500);
    predjelo.postaviPromenuCene(0.2);
    predjelo.postaviSatFormiranjaCene(10);
    predjelo.dodajSastojak(slan, 200);
    predjelo.dodajSastojak(sladineut, 300);

    Jelo glavnoJelo("G", 800);
    glavnoJelo.postaviPromenuCene(0.3);
    glavnoJelo.postaviSatFormiranjaCene(21);
    glavnoJelo.dodajSastojak(slan, 500);
    glavnoJelo.dodajSastojak(slan, 300);

    Jelo dezert("D", 300);
    dezert.postaviPromenuCene(0.1);
    dezert.postaviSatFormiranjaCene(14);
    dezert.dodajSastojak(sladineut, 200);

    Jelo* jelovnik[] = { &predjelo, &glavnoJelo, &dezert };

    int brojJela = sizeof(jelovnik) / sizeof(Jelo*);
    for (int i = 0; i < brojJela; i++) {
        jelovnik[i]->ispisi();
    }
    return 0;
}

