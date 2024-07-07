#include <iostream>
#include <string>

using namespace std;

class Let {
protected:
    string polaznaDestinacija;
    string dolaznaDestinacija;
    string datumVremePoletanja;
    int brRezervisanihMestaAvion;

public:
    Let(string pd, string dd, string dvp, int brma) {
        polaznaDestinacija = pd;
        dolaznaDestinacija = dd;
        datumVremePoletanja = dvp;
        brRezervisanihMestaAvion = brma;
    }

    virtual void dodajRezervaciju() = 0;
    virtual void Ispis() = 0;

    string getPolazna() const {
        return polaznaDestinacija;
    }

    string getDolazna() const {
        return dolaznaDestinacija;
    }

    string getVreme() const {
        return datumVremePoletanja;
    }
};

class Redovan : public Let {
protected:
    int brMestaAvion;

public:
    Redovan(string pd, string dd, string dvp, int brma, int bma) : Let(pd, dd, dvp, brma) {
        brMestaAvion = bma;
    }

    void dodajRezervaciju() {
        if (brRezervisanihMestaAvion < brMestaAvion) {
            brRezervisanihMestaAvion++;
            brMestaAvion--;
        }
    }

    void Ispis() {
        cout << "Podaci o redovnom letu:" << endl;
        cout << "Polazna destinacija: " << polaznaDestinacija << endl;
        cout << "Dolazna destinacija: " << dolaznaDestinacija << endl;
        cout << "Datum i vreme poletanja: " << datumVremePoletanja << endl;
        cout << "Broj mesta u avionu: " << brMestaAvion << endl;
        cout << "Broj rezervisanih mesta: " << brRezervisanihMestaAvion << endl;
        cout << endl;
    }
};

class Carter : public Let {
protected:
    int brRedovanMestaAvion;
    int brVanredanMestaAvion;

public:
    Carter(string pd, string dd, string dvp, int brma, int _brma, int bvma) : Let(pd, dd, dvp, brma) {
        brRedovanMestaAvion = _brma;
        brVanredanMestaAvion = bvma;
    }

    void dodajRezervaciju() {
        if (brRezervisanihMestaAvion < brRedovanMestaAvion + brVanredanMestaAvion) {
            brRezervisanihMestaAvion++;
            if (brRezervisanihMestaAvion <= brRedovanMestaAvion)
                brRedovanMestaAvion--;
            else
                brVanredanMestaAvion--;
        }
    }

    void Ispis() {
        cout << "Podaci o carter letu:" << endl;
        cout << "Polazna destinacija: " << polaznaDestinacija << endl;
        cout << "Dolazna destinacija: " << dolaznaDestinacija << endl;
        cout << "Datum i vreme poletanja: " << datumVremePoletanja << endl;
        cout << "Broj mesta u redovnom avionu: " << brRedovanMestaAvion << endl;
        cout << "Broj mesta u vanrednom avionu: " << brVanredanMestaAvion << endl;
        cout << "Broj rezervisanih mesta: " << brRezervisanihMestaAvion << endl;
        cout << endl;
    }
};

template<class T, int max>
class AvioKompanija {
protected:
    T** letovi;
    int trenutno;
    int maxLetova;

public:
    AvioKompanija() {
        maxLetova = max;
        letovi = new T * [maxLetova];
        trenutno = 0;
    }

    void dodajLet(T* let) {
        if (trenutno < maxLetova) {
            letovi[trenutno++] = let;
        }
    }

    void obrisiLet(string pd, string dd, string dvp) {
        for (int i = 0; i < trenutno; i++) {
            if (letovi[i]->getPolazna() == pd && letovi[i]->getDolazna() == dd && letovi[i]->getVreme() == dvp) {
                trenutno--;
                letovi[i] = letovi[i + 1];
            }
        }
    }

    void rezervisiKartu(string pd, string dd, string dvp) {
        for (int i = 0; i < trenutno; i++) {
            if (letovi[i]->getPolazna() == pd && letovi[i]->getDolazna() == dd && letovi[i]->getVreme() == dvp) {
                letovi[i]->dodajRezervaciju();
                break;
            }
        }
    }

    void Sortiraj() {
    for (int i = 0; i < trenutno - 1; i++) {
        for (int j = 0; j < trenutno - i - 1; j++) {
            if (letovi[j]->getVreme() > letovi[j + 1]->getVreme()) {
                T* temp = letovi[j];
                letovi[j] = letovi[j + 1];
                letovi[j + 1] = temp;
            }
        }
    }
}


    void Ispis() {
        cout << "Podaci o svim letovima: " << endl;
        for (int i = 0; i < trenutno; i++)
            letovi[i]->Ispis();
    }
};

int main() {
    AvioKompanija<Let, 100> AirSerbia;
    Redovan r1("Beograd", "Minhen", "2023-12-06 17:15:00", 100, 120);
    Redovan r2("Beograd", "Keln", "2023-12-07 20:00:00", 100, 150);
    Carter c1("Beograd", "London", "2023-12-08 14:30:00", 100, 80, 60);
    Carter c2("Minhen", "Berlin", "2023-12-06 17:15:00",100,90,55);
    Redovan r3("Keln", "Barselona", "2023-12-07 20:00:00",100,110);


    AirSerbia.dodajLet(&r1);
    AirSerbia.dodajLet(&r2);
    AirSerbia.dodajLet(&c1);
    AirSerbia.dodajLet(&c2);
    AirSerbia.dodajLet(&r3);

    AirSerbia.obrisiLet("Minhen", "Berlin", "2023-12-06 17:15:00");
    AirSerbia.obrisiLet("Keln", "Barselona", "2023-12-07 20:00:00");

    AirSerbia.rezervisiKartu("Beograd", "Minhen", "2023-12-06 17:15:00");
    AirSerbia.rezervisiKartu("Beograd", "Keln", "2023-12-07 20:00:00");

    AirSerbia.Sortiraj();
    AirSerbia.Ispis();

    return 0;
}
