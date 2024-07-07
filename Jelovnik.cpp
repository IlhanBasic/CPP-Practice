#include <iostream>
#include <string>
#include <ctime>

using namespace std;

enum VrstaSastojka {
    SLAN,
    SLADiNEUT
};

class Sastojak {
private:
    string ime;
    double cenaPoKg;

public:
    Sastojak(const string& ime, double cenaPoKg) : ime(ime), cenaPoKg(cenaPoKg) {}

    string getVrstaSastojka() const {
        if (ime == "SLAN") {
            return "SLAN";
        } else if (ime == "SLADiNEUT") {
            return "SLADiNEUT";
        } else {
            return "Nepoznata vrsta";
        }
    }

    double izracunajCenu(double kolicina) const {
        return cenaPoKg * (kolicina / 1000);
    }

    friend ostream& operator<<(ostream& out, const Sastojak& s) {
        out << s.ime << "-" << s.cenaPoKg << "/kg";
        return out;
    }
};

class Jelo {
private:
    string ime;
    Sastojak sastojak;
    int kolicinaGram;
    double promenaCene;
    int satFormiranjaCene;

public:
    Jelo(const string& ime, const Sastojak& sastojak, int kolicinaGram)
        : ime(ime), sastojak(sastojak), kolicinaGram(kolicinaGram), promenaCene(0), satFormiranjaCene(0) {}

    void setPromenaCene(double promena) {
        promenaCene = promena;
    }

    void setSatFormiranjaCene(int sat) {
        satFormiranjaCene = sat;
    }

    void dodajSastojak(const Sastojak& noviSastojak, int kolicinaGram) {
        if (noviSastojak.getVrstaSastojka() != "SLAN" && noviSastojak.getVrstaSastojka() != "SLADiNEUT") {
            cout << "Greska: Sastojak nije adekvatan za jelo!" << endl;
            return;
        }

        this->sastojak = noviSastojak;
        this->kolicinaGram = kolicinaGram;
    }

    string getVrstaJela() const {
        if (ime == "P") {
            return "Predjelo";
        } else if (ime == "G") {
            return "Glavno jelo";
        } else if (ime == "D") {
            return "Dezert";
        } else {
            return "Nepoznato jelo";
        }
    }

    double izracunajCenu() const {
        double cena = sastojak.izracunajCenu(kolicinaGram);
        cena += cena * (promenaCene / 100);

        if ((satFormiranjaCene >= 9 && satFormiranjaCene <= 12 && ime == "P") ||
            (satFormiranjaCene >= 20 && satFormiranjaCene <= 23 && ime == "G")) {
            cena -= cena * 0.1; // Umanjenje cene za 10% u odredenom periodu
        }

        return cena;
    }

    friend ostream& operator<<(ostream& out, const Jelo& j) {
        out << j.ime << ":" << j.izracunajCenu() << endl;
        out << j.sastojak << ":" << j.kolicinaGram << endl;
        return out;
    }
};

int main() {
    // Kreiranje sastojaka
    Sastojak sol("SLAN", 5.0);
    Sastojak secer("SLADiNEUT", 3.0);

    // Kreiranje jela
    Jelo predjelo("P", sol, 200);
    predjelo.setPromenaCene(10);
    predjelo.setSatFormiranjaCene(10);

    Jelo glavnoJelo("G", sol, 500);
    glavnoJelo.setPromenaCene(-5);
    glavnoJelo.setSatFormiranjaCene(21);
    glavnoJelo.dodajSastojak(secer, 100);

    Jelo dezert("D", secer, 300);
    dezert.setPromenaCene(15);
    dezert.setSatFormiranjaCene(14);

    // Ispis jelovnika
    cout << "Jelovnik:" << endl;
    cout << predjelo;
    cout << glavnoJelo;
    cout << dezert;

    return 0;
}
