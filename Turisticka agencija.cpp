#include <iostream>
#include <stdbool.h>
#include <string>
using namespace std;
enum Destinacija {Pariz,Rim,Barselona};
string nadjiDestinaciju(Destinacija d){
    switch(d){
        case 0:return "Pariz";
        case 1:return "Rim";
        case 2:return "Barselona";
        return "Greska";
    }
}
class TuristickaAgencija{
  private:
  string nazivAgencije;
  int brojDostupnihAranzmana;
  public:
  TuristickaAgencija(){
      nazivAgencije="BEJZIK TRAVEL";
      brojDostupnihAranzmana=14;
  }
  TuristickaAgencija(string n,int br){
      nazivAgencije=n;
      brojDostupnihAranzmana=br;
  }
  ~TuristickaAgencija(){
      
  }
  void rezervisiAranzman(int broj){
      brojDostupnihAranzmana-=broj;
  }
  void otkaziAranzman(int broj){
      brojDostupnihAranzmana+=broj;
  }
  friend ostream &operator << (ostream &out, TuristickaAgencija &t){
      out<<"Naziv: "<<t.nazivAgencije<<endl;
      out<<"Broj dostupnih aranzmana: "<<t.brojDostupnihAranzmana<<endl;
      return out;
  }
  void setNaziv(string value){nazivAgencije=value;}
  void setBrojDostupnihAranzmana(int value){brojDostupnihAranzmana=value;}
  string getNaziv(){return nazivAgencije;}
  int getBrojDostupnihAranzmana(){return brojDostupnihAranzmana;}
  friend void pretraziAranzmane(const TuristickaAgencija &t, Destinacija destinacija){
      int dostupnih=0;
      switch(destinacija){
          case 0:
          dostupnih+=t.brojDostupnihAranzmana/3;break;
          case 1:
          dostupnih+=t.brojDostupnihAranzmana/2;break;
          case 2:
          dostupnih=t.brojDostupnihAranzmana/4;break;
    }
    cout<<"Broj dostupnih aranzmana je "<<dostupnih<<" za destinaciju "<<nadjiDestinaciju(destinacija)<<endl;
  }
};
int main(){
    TuristickaAgencija agencija("Omladinac",200);
    cout<<agencija<<endl;
    agencija.rezervisiAranzman(20);
    cout<<agencija<<endl;
    agencija.otkaziAranzman(5);
    cout<<agencija<<endl;
    pretraziAranzmane(agencija,Pariz);
    pretraziAranzmane(agencija,Rim);
    pretraziAranzmane(agencija,Barselona);
    return 0;
}
