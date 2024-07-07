#include <iostream>
#include <string>
#include <stdbool.h>
using namespace std;

class Vest {
private:
string naslov;
string tekstVesti;
string autor;
int dan;
int mesec;
int godina;
public:
Vest(){
    naslov="Nogonja";
    tekstVesti="Kako je dobro biti nogonja.";
    autor="Edvard";
    dan=15;
    mesec=11;
    godina=2002;
}
Vest(string n, string t, string a, int d, int m, int g) {
naslov = n;
tekstVesti = t;
autor = a;
dan = d;
mesec = m;
godina = g;
}
int getDan() { return dan; }
int getMesec() { return mesec; }
int getGodina() { return godina; }
void Ispis() {
cout << "\n'" << naslov << "'\n" << tekstVesti << endl << "Autor: " << autor << endl << "Datum objave: " << dan << "." << mesec << "." << godina << endl;
}
};

class NovinarskaAgencija {
private:
string naziv;
Vest* lista;
int br;
int max;
public:
NovinarskaAgencija(string n, int m) {
naziv = n;
max = m;
lista = new Vest[max];
br = 0;
}
void dodajVest(Vest* v1) {
if (br < max)
lista[br++] = *v1;
else
cout << "\nTrenutno nema posla.\n" << endl;
}
void obrisiVest() {
if (br > 0)
br--;
else
cout << "\nNema vesti za brisanje.\n" << endl;
}
void IspisSvih() {
for (int i = 0; i < br; i++) {
lista[i].Ispis();
}
}
void IspisNajnovijih() {
for (int i = 0; i < br; i++)
if (lista[i].getDan() == 22 && lista[i].getMesec() == 4 && lista[i].getGodina() == 2023)
lista[i].Ispis();
}
void IspisNajstarijih() {
for (int i = 0; i < br; i++)
if (lista[i].getGodina() < 2023)
lista[i].Ispis();
}
~NovinarskaAgencija(){
    delete[]lista;
}
};

int main() {
Vest v1("Koncert Dina Merlina", "Dolazak Dina Merlina u nas grad obradovace nase sugradjane koji su ljubitelji njegove muzike...", "Ilhan", 12, 4, 2023);
Vest v2("Sanirana Deponija", "Deponija na brdu Lug je posle duzeg vremena obecavanja konacno sanirana...", "Aldin", 22, 4, 2023);
Vest v3("Otvaranje klinickog centra", "Velike reci ce biti uskoro ispunjene. Dugo su nasi sugradjani cekali na klinicki centar u svom gradu...", "Idris", 30, 4, 2022);
Vest v4("Dobrodusni sugradjanin", "Sead Hrustic iz naselja Kult pronasao je novcanik...", "Kenan", 12, 3, 2023);
Vest v5("Humanitarna utakmica za Elvira Husejinagica", "Na dan 15.07. bice odigrana humanitarna utakmica...", "Kemal", 1, 7, 2007);
NovinarskaAgencija n("PrijepoljeInfo", 5);
n.dodajVest(&v1);
n.dodajVest(&v2);
n.obrisiVest();
n.dodajVest(&v3);
n.dodajVest(&v4);
cout<<"Najstarije vesti: "<<endl;
n.IspisNajstarijih();
cout<<"Najnovije vesti: "<<endl;
//n.IspisNajnovijih();
cout<<"Sve vesti: "<<endl;
n.IspisSvih();
return 0;
}
