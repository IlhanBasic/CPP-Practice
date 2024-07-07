#include <iostream>
#include <string>
using namespace std;
enum VrstaPovrsine { TRAVNATA, BETONSKA, ASFALTIRANA };
class Park {
private:
    string naziv;
    string adresa;
    float povrsina;
    int brojKlupa;
    bool igraliste;
    VrstaPovrsine povrsinaParka;
public:
    Park(string naziv, string adresa, float povrsina, int brojKlupa, bool igraliste, VrstaPovrsine povrsinaParka) :
        naziv(naziv), adresa(adresa), povrsina(povrsina), brojKlupa(brojKlupa), igraliste(igraliste), povrsinaParka(povrsinaParka) {}
    
    friend ostream& operator<<(ostream& os, const Park& park) {
        os << "Naziv parka: " << park.naziv << endl;
        os << "Adresa parka: " << park.adresa << endl;
        os << "Povrsina parka: " << park.povrsina << " m^2" << endl;
        os << "Broj klupa u parku: " << park.brojKlupa << endl;
        os << "Postoji li igraliste u parku: " << (park.igraliste ? "Da" : "Ne") << endl;
        os << "Vrsta povrsine parka: ";
        switch (park.povrsinaParka) {
            case TRAVNATA:
                os << "Travnata";
                break;
            case BETONSKA:
                os << "Betonska";
                break;
            case ASFALTIRANA:
                os << "Asfaltirana";
                break;
        }
        os << endl;
        return os;
    }
    
    float getPovrsina() const {
        return povrsina;
    }
    
    int getBrojKlupa() const {
        return brojKlupa;
    }
};
float prosjecnaPovrsina(Park parkovi[], int brojParkova) {
    float ukupnaPovrsina = 0;
    for (int i = 0; i < brojParkova; i++) {
        ukupnaPovrsina += parkovi[i].getPovrsina();
    }
    return ukupnaPovrsina / brojParkova;
}
int ukupanBrojKlupa(Park parkovi[], int brojParkova) {
    int ukupnoKlupa = 0;
    for (int i = 0; i < brojParkova; i++) {
        ukupnoKlupa += parkovi[i].getBrojKlupa();
    }
    return ukupnoKlupa;
}
int main() {
    const int BROJ_PARKOVA = 3;
    Park parkovi[BROJ_PARKOVA] = {
        Park("Park Mladen Stojanovic", "Ulica Brace Jerkovic 55", 1500, 25, true, TRAVNATA),
        Park("Park Josip Broz Tito", "Bulevar Oslobodjenja 13", 2500, 40, false, ASFALTIRANA),
        Park("Park Petar II Petrovic Njegos", "Bulevar Kralja Aleksandara 55",3400,30,true,BETONSKA)
    };
    cout<<"Prosecana povrsina parkova u Beogradu iznosi: "<<prosjecnaPovrsina(parkovi,BROJ_PARKOVA)<<endl;
    cout<<"Ukupan broj klupa u parkovima grada Beograda iznosi: "<<ukupanBrojKlupa(parkovi,BROJ_PARKOVA)<<endl<<endl;
    for(int i=0;i<BROJ_PARKOVA;i++){
    cout<<parkovi[i]<<endl;
    }
    return 0;
}
