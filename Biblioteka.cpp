#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

enum ZANR { Modernizam, Realizam, Ekspresionizam };

class Knjiga {
private:
    string naslov;
    string autor;
    int godina;
    ZANR zanr;
    int brojStranica;
    
public:
    Knjiga() {
        naslov = "Na Drini Cuprija";
        autor = "Ivo Andric";
        godina = 1960;
        zanr = Modernizam;
        brojStranica = 289;
    }

    Knjiga(string n, string a, int god, ZANR z, int b) {
        naslov = n;
        autor = a;
        godina = god;
        zanr = z;
        brojStranica = b;
    }

    void Ispis() {
        cout << "Podaci o knjizi: " << endl;
        cout << "Naslov: " << naslov << endl;
        cout << "Autor: " << autor << endl;
        cout << "Godina izdanja: " << godina << endl;
        cout << "Zanr: " << nadjiZanr() << endl;
        cout << "Broj stranica: " << brojStranica << endl;
    }

    string getNaslov() { return naslov; }
    string getAutor() { return autor; }
    int getGodina() { return godina; }
    ZANR getZanr() { return zanr; }
    int getBrojStranica() { return brojStranica; }

    void setNaslov(string value) { naslov = value; }
    void setAutor(string value) { autor = value; }
    void setGodina(int value) { godina = value; }
    void setZanr(ZANR value) { zanr = value; }
    void setBrojStranica(int value) { brojStranica = value; }

    string nadjiZanr() {
        switch (zanr) {
        case Modernizam: return "Modernizam";
        case Realizam: return "Realizam";
        case Ekspresionizam: return "Ekspresionizam";
        default: return "Nepoznat zanr";
        }
    }
};
class Biblioteka{
    private:
    Knjiga *knjige;
    int max;
    int br;
    public:
    Biblioteka(Knjiga *k,int maxKnjiga){
        max=maxKnjiga;
        knjige=new Knjiga [max];
        for(int i=0;i<maxKnjiga;i++)
        knjige[i]=k[i];
        br=maxKnjiga;
    }
    void dodajKnjigu(Knjiga *k){
        if(br<max){
            knjige[br++]=*k;
        }
        else
        cout<<"Nema mesta u biblioteci."<<endl;
    }
    
    void ukloniKnjigu(){
        if(br>0){
            br--;
        }
        else
        cout<<"Nema knjiga u biblioteci."<<endl;
    }
    
    int brojKnjiga(){
        if(br>0 && br<max){
            return br;
        }
        else
        return 0;
    }
    
    Knjiga* pronadjipoNaslovu(string n){
        Knjiga *nadjiKnjigu;
        int brojac=0;
        for(int i=0;i<br;i++)
        if(knjige[i].getNaslov()==n){
           brojac++;
        }
        if(brojac>0){
            nadjiKnjigu=new Knjiga[brojac];
            int broj=0;
            for(int i=0;i<br;i++)
            if(knjige[i].getNaslov()==n){
                nadjiKnjigu[broj++]=knjige[i];
            }
        }
        if(nadjiKnjigu)
        return nadjiKnjigu;
        else
        return NULL;
    }
    
    Knjiga* pronadjipoAutoru(string n){
        Knjiga *nadjiKnjigu;
        int brojac=0;
        for(int i=0;i<br;i++)
        if(knjige[i].getAutor()==n){
           brojac++;
        }
        if(brojac>0){
            nadjiKnjigu=new Knjiga[brojac];
            int broj=0;
            for(int i=0;i<br;i++)
            if(knjige[i].getAutor()==n){
                nadjiKnjigu[broj++]=knjige[i];
            }
        }
        if(nadjiKnjigu)
        return nadjiKnjigu;
        else
        return NULL;
    }
    
    Knjiga* pronadjipoGodini(int n){
        Knjiga *nadjiKnjigu;
        int brojac=0;
        for(int i=0;i<br;i++)
        if(knjige[i].getGodina()==n){
           brojac++;
        }
        if(brojac>0){
            nadjiKnjigu=new Knjiga[brojac];
            int broj=0;
            for(int i=0;i<br;i++)
            if(knjige[i].getGodina()==n){
                nadjiKnjigu[broj++]=knjige[i];
            }
        }
        if(nadjiKnjigu)
        return nadjiKnjigu;
        else
        return NULL;
    }
    
    Knjiga* pronadjipoZanru(ZANR n){
        Knjiga *nadjiKnjigu;
        int brojac=0;
        for(int i=0;i<br;i++)
        if(knjige[i].getZanr()==n){
           brojac++;
        }
        if(brojac>0){
            nadjiKnjigu=new Knjiga[brojac];
            int broj=0;
            for(int i=0;i<br;i++)
            if(knjige[i].getZanr()==n){
                nadjiKnjigu[broj++]=knjige[i];
            }
        }
        if(nadjiKnjigu)
        return nadjiKnjigu;
        else
        return NULL;
    }
    void Ispis(){
        cout<<"Knjige u biblioteci:"<<endl;
        for(int i=0;i<br;i++){
        knjige[i].Ispis();
        cout<<endl;
        }
    }
    ~Biblioteka(){
        delete[]knjige;
    }
};
int main(){
    Knjiga k1("Sarajevo","Abdul Sidran",1992,Modernizam,160),k2("Hor Cvijetova","Rasim Omerovic",1995,Ekspresionizam,179),k4("x","sead",2006,Realizam,200);
    Knjiga knjige[3]={k1,k2,k4};
    Biblioteka B(knjige,3);
    //B.ukloniKnjigu();
    //cout<<"Ukupan broj knjiga u biblioteci je "<<B.brojKnjiga()<<endl;
    B.Ispis();
    Knjiga *nadjeno=B.pronadjipoZanru(Modernizam);
    return 0;
}
