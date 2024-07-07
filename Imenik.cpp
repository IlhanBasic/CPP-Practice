#include <iostream>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

using namespace std;

class JMBG {
  char jmbg[14];
public:
  JMBG() {
    strcpy(jmbg, "");
  }
  JMBG(char* j) {
    strcpy(jmbg, j);
  }
  void setJmbg(char* value) {
    strcpy(jmbg, value);
  }
  char* getJmbg() {
    return jmbg;
  }
  friend bool jesteVeci(JMBG j1, JMBG j2) {
    return strcmp(j1.jmbg, j2.jmbg) > 0;
  }
};

class Osoba {
  string ime;
  JMBG Jmbg;
public:
  JMBG getJMBG() {
    return Jmbg;
  }
  Osoba() {}
  Osoba(string i, JMBG j) {
    ime = i;
    Jmbg = j;
  }
  void Ispis() {
    cout << ime << "(" << Jmbg.getJmbg() << ")" << endl;
  }
};

class Imenik {
  int brOsoba;
  Osoba *osobe;
public:
  Imenik() {
    brOsoba = 0;
    osobe = NULL;
  }
  void dodajOsobu(Osoba *o) {
    if (osobe == NULL) {
      osobe = new Osoba[1];
      osobe[0] = *o;
      brOsoba++;
    } else {
      Osoba *temp = new Osoba[brOsoba + 1];
      for (int i = 0; i < brOsoba; i++) {
        temp[i] = osobe[i];
      }
      temp[brOsoba] = *o;
      brOsoba++;
      delete[] osobe;
      osobe = temp;
    }
  }
  void Ispis() {
    Osoba pomocna;
    for (int i = 0; i < brOsoba - 1; i++) {
      for (int j = i + 1; j < brOsoba; j++) {
        if (jesteVeci(osobe[i].getJMBG(), osobe[j].getJMBG())) {
          pomocna = osobe[i];
          osobe[i] = osobe[j];
          osobe[j] = pomocna;
        }
      }
    }
    for (int i = 0; i < brOsoba; i++)
      osobe[i].Ispis();
  }
  ~Imenik(){
  	delete[]osobe;
  }
};

int main() {
  JMBG j1("0306003793925"), j2("0304002783629"), j3("0312990561245"), j4("0310990261247"), j5("0392990531245");
  Osoba o1("Kenan Omerovic", j1), o2("Suad Huskic", j2), o3("Zela Sarajlija", j3), o4("Aldina Music", j4), o5("Amar Hrustemovic", j5);
  Imenik i;
  i.dodajOsobu(&o1);
  i.dodajOsobu(&o2);
  i.dodajOsobu(&o3);
  i.dodajOsobu(&o4);
  i.dodajOsobu(&o5);
  i.Ispis();
  return 0;
