#include <iostream>
#include <string.h>

using namespace std;
enum ZNAK
{
    PIK,
    TREF,
    KARO,
    HERC
};
enum BROJ
{
    K1 = 1,
    K2,
    K3,
    K4,
    K5,
    K6,
    K7,
    K8,
    K9,
    K10,
    ZANDAR,
    DAMA,
    KRALJ
};

class Karta
{
    ZNAK znak;
    BROJ broj;

public:
    Karta()
    {
        znak = PIK;
        broj = K1;
    }
    Karta(ZNAK z, BROJ b)
    {
        znak = z;
        broj = b;
    }
    int getBroj()
    {
        return broj;
    }
    int vrednost()
    {
        if (broj == KRALJ || broj == K10 || broj == DAMA || broj == ZANDAR || broj == K1)
        {
            return 1;
        }
        else if (broj == K10 && znak == KARO || (broj == K2 && znak == TREF))
        {
            return 2;
        }
        else
        {
            return 0;
        }
    }
    string getZnak()
    {
        switch (znak)
        {
        case PIK:
            return "pik";
            break;
        case HERC:
            return "herc";
            break;
        case KARO:
            return "karo";
            break;
        case TREF:
            return "tref";
            break;
        default:
            return "Netacna karta";
            break;
        }
    }

    bool operator>(const Karta &k)
    {
        return broj > k.broj;
    }
    bool operator>>(Karta &k)
    {
        return vrednost() > k.vrednost();
    }

    friend ostream &operator<<(ostream &COUT, Karta &k)
    {
        COUT << "Karta:"
             << "(" << k.getZnak() << "," << k.broj << ")" << endl;

        return COUT;
    }
};

class Spil
{
    int brKarata;
    Karta *karte;

public:
    Spil()
    {
        brKarata = 0;
        karte = new Karta[brKarata + 1];
    }
    void operator+=(Karta k)
    {
        karte[brKarata] = k;

        brKarata++;
    }

    void operator--(int)
    {
        brKarata--;
    }

    Karta getNajvecu()
    {
        int max = karte[0].getBroj();
        for (int i = 0; i < brKarata; i++)
        {
            if (max < karte[i].getBroj())
            {
                max = karte[i].getBroj();
                return karte[i];
            }
        }
    }
    int operator()()
    {
        return brKarata;
    }

    bool operator>(Spil &s1)
    {
        return brKarata > s1.brKarata;
    }
    bool operator>>(Spil &s1)
    {
        return getNajvecu().vrednost() > s1.getNajvecu().vrednost();
    }

    friend ostream &operator<<(ostream &COUT, Spil s)
    {
        COUT << "Spil"
             << "(" << s.brKarata << ")" << endl;

        for (int i = 0; i < s.brKarata; i++)
        {
            cout << s.karte[i];
        }
        return COUT;
    }
};
int main()
{
    BROJ b1 = K2;
    Karta prva(HERC, K1);
    Karta druga(PIK, K10);
    Karta treca(TREF, K5);
    Karta cetvrta(KARO, K7);

    Karta prva1(HERC, K2);
    Karta druga1(PIK, K1);
    Karta treca1(TREF, K5);
    Karta cetvrta1(KARO, K8);
    Spil s;
    Spil s1;

    s1 += prva1;
    s1 += druga1;
    s1 += treca1;
    s1 += cetvrta1;

    cout << s1;

    // bool check = prva > druga;
    // cout << check;
    // cout << s;

    s += prva;
    s += druga;
    s += treca;
    s += cetvrta;
    s--;
    cout<< s;

    bool check = s1 > s;
    bool dcheck = s1 >> s;
    cout << "Da li je veca s1 od s    " << check << endl
         << "da li je najveca veca s1 od s  " << dcheck << endl;
    // cout << "Broj karti:" << s() << endl;

    // cout << "Najveca karta u spilu :" << endl
    //      << s.getNajvecu() << endl;
    return 0;
}
