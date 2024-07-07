#include <iostream>
#include <string.h>

using namespace std;
class Vreme
{
	int hours;
	int minutes;
	int seconds;

public:
	int ukupnoVreme;
	Vreme()
	{
		hours = 0;
		minutes = 0;
		seconds = 0;
		ukupnoVreme = 0;
	}
	Vreme(int Hours, int Minutes)
	{

		hours = Hours;
		minutes = Minutes;
		seconds = 0;
		ukupnoVreme = hours * 3600 + minutes * 60;
	}
	Vreme(int Hours, int Minutes, int Seconds)
	{
		hours = Hours;
		minutes = Minutes;
		seconds = Seconds;
		ukupnoVreme = ukupnoVreme = hours * 3600 + minutes * 60 + seconds;
	}
	void info(bool check)
	{
		if (check)
		{
			cout << hours << ":" << minutes << ":" << seconds;
		}
		else
		{
			cout << hours << ":" << minutes;
		}
	}
	Vreme add(Vreme v2)
	{
		int vremeUkupno = ukupnoVreme + v2.ukupnoVreme;

		int h = (vremeUkupno / 3600);
		vremeUkupno -= h * 3600;
		int m = (vremeUkupno / 60);
		vremeUkupno -= m * 60;
		int s = vremeUkupno;
		cout << "Time by another time " << h % 24 << ":" << m % 60 << ":" << s % 60 << endl;

		Vreme newV(h % 24, m % 60, s % 60);
		return newV;
	}
	Vreme addByMin(int mins)
	{

		cout << mins << endl;
		int m = mins + minutes;
		int h = hours + m / 60;
		int s = seconds;

		cout << "time by min " << h % 24 << ":" << m % 60 << ":" << s % 60 << endl;
		Vreme newV(h % 24, m % 60, s % 60);
		return newV;
	}
	int compareTo(Vreme v)
	{
		if (ukupnoVreme == v.ukupnoVreme)
		{
			return 0;
		}
		else if (ukupnoVreme > v.ukupnoVreme)
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}
	void ispis()
	{
		cout << hours << ":" << minutes << ":" << seconds << endl;
	}
};
class Datum
{
	int dan;
	int mesec;
	int godina;

public:
	Datum()
	{
		dan = 0;
		mesec = 0;
		godina = 0;
	}
	Datum(int Dan, int Mesec, int Godina)
	{
		dan = Dan;
		mesec = Mesec;
		godina = Godina;
	}

	void ispis()
	{
		cout << dan << "/" << mesec << "/" << godina << endl;
	}

	~Datum()
	{
	}
};

enum TIP
{
	ADMIN,
	GOST
};

class Korisnik
{
	char punoIme[30];
	char ime[20];
	string lozinka;
	TIP tip;

public:
	Korisnik(char *PI = "", char *I = "", string L = "", TIP tip = GOST)
	{
		strcpy(punoIme, PI);
		strcpy(ime, I, 19);
		lozinka = L;
		this->tip = tip;
	}
	void ispis()
	{
		cout << "IME " << ime << "Puno ime " << punoIme << endl;
	}
	void promeniLozinku(string oldP, string newP)
	{
		if (oldP == lozinka)
		{
			lozinka = newP;
		}
		else
		{
			cout << "Error" << endl;
		}
	}
	char *getAutor()
	{
		return ime;
	}
	TIP getTip()
	{
		return tip;
	}
};

class Komentar
{
	string tekst;
	Datum datum;
	Vreme vreme;
	double popularnost;
	Korisnik korisnik;

public:
	Komentar(string T = "", Datum D = Datum(), Vreme V = Vreme(), double P = 0, Korisnik K = Korisnik())
	{
		tekst = T;
		datum = D;
		vreme = V;
		popularnost = P;
		korisnik = K;
	}

	void ispis()
	{
		cout << tekst << endl;
	}

	void povecajPopluarnost()
	{
		popularnost += 1;
	}
};

class Clanak
{
	char naslov[50];
	string sadrzaj;
	Datum datum;
	Vreme vreme;
	int brojPregleda;
	string tagovi[100];
	int brojTagova;
	Korisnik autor;
	Komentar *komentari;
	int brojKomentara;

public:
	Clanak(Korisnik korisnik = Korisnik(), char *N = "", string S = "", Datum D = Datum(1, 1, 2022), Vreme V = Vreme(0, 0, 0), int BP = 0)
	{
		strcpy(naslov, N);
		sadrzaj = S;
		datum = D;
		vreme = V;
		brojPregleda = BP;
		brojKomentara = 0;
		brojTagova = 0;
		komentari = new Komentar[brojKomentara];
		autor = korisnik;
	}
	void dodajTag(string t)
	{
		tagovi[brojTagova] = t;
		brojTagova++;
	}

	void dodajKomentar(Komentar k)
	{
		if (autor.getTip() == GOST)
		{
			Komentar *newList = new Komentar[brojKomentara + 1];

			for (int i = 0; i < brojKomentara; i++)
			{
				cout << "koment added";

				newList[i] = komentari[i];
			}
			newList[brojKomentara] = k;
			delete[] komentari;
			komentari = newList;
			brojKomentara++;
		}
		else
		{
			cout << "Moderator ne moze ostaviti komenatar" << endl;
		}
	}

	void promeniSadrzaj(string ime, string Sadrzaj, Datum d)
	{
		cout << ime << "=" << autor.getAutor() << endl;
		if (ime == autor.getAutor())
		{
			datum = d;
			sadrzaj = Sadrzaj;
		}
		else
		{
			cout << "Ne mozete menjati sadrzaj" << endl;
		}
	}
	friend ostream &operator<<(ostream &COUT, Clanak &cla)
	{
		COUT << "Naslov:" << endl
			 << cla.naslov << endl
			 << "Sadrzaj:" << endl
			 << cla.sadrzaj << endl
			 << "KOMENTARI:" << endl;

		for (int i = 0; i < cla.brojKomentara; i++)
		{
			cla.komentari[i].ispis();
		}
		COUT << "Objavljeno:";
		cla.datum.ispis();
		cla.vreme.ispis();
		return COUT;
	}
};
using namespace std;
int main()
{
	system("cls");
	Vreme v1(4, 56, 20);
	Vreme v2(23, 4, 20);
	Vreme v3 = v1.add(v2);
	Vreme v4 = v1.addByMin(25);
	cout << "Poredjenje vremena " << v1.compareTo(v2) << endl;

	Datum d1(1, 8, 2023);
	Datum d2(2, 4, 2020);
	Korisnik kor1("Hamza Gorcevic", "hamza", "hamza123", GOST);
	Komentar kom1("Ovo je divno", d1, v1, 976, kor1);

	Komentar kom2("Ne svidja mi se", d1, v2);
	Clanak c1(kor1, "Twiter", "Elon musk", d1, v1, 20);

	c1.dodajKomentar(kom1);
	c1.dodajKomentar(kom2);

	c1.promeniSadrzaj("hamza", "Andrew Tate", d2);

	cout << c1;
	return 0;
}
