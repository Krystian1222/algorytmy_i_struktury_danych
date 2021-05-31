#include <iostream>
#include <random>
#include <cmath>
#include <cstring>
#include <random>
#include <algorithm>
#include <chrono>
using namespace std;
//    T *wyszukaj(T element)
//    {
//        int wynik = 0;
//        wynik = funkcja_mieszajaca(element.klucz);
//        //cout << "Wynik funkcji mieszajacej: " << wynik << endl;
//        for(int i = 0; i < TH[wynik].liczba_obiektow; i++)
//        {
//            if((TH[wynik].tablica[i].klucz == element.klucz) && (TH[wynik].tablica[i].wartosc == element.wartosc))
//            {
//                return &TH[wynik].tablica[i];
//            }
//            else
//            {
//                return nullptr;
//            }
//        }
//    }
/***************************************************************/
//template <typename T>
//int Tablica_Haszujaca<T>::usun_element(T element)
//{
//    int wynik = 0;
//    wynik = funkcja_mieszajaca(element.klucz);
//    //cout << "element.klucz: " << element.klucz << endl;
//    //cout << "element.wartosc: " << element.wartosc << endl;
//    //cout << "Wynik funkcji mieszajacej: " << wynik << endl;
//    if(TH[wynik].liczba_obiektow == 0)
//    {
//        return 0;
//    }
//    int i = 0;
//    //cout << "Liczba obiektow podtablicy: " << TH[wynik].liczba_obiektow << endl;
//    for(i = 0; i < TH[wynik].liczba_obiektow; i++)
//    {
//        //if(TH[wynik].tablica[i] == element)
//        if((TH[wynik].tablica[i].klucz == element.klucz) && (TH[wynik].tablica[i].wartosc == element.wartosc))
//        {
//            //cout << "TH[wynik].tablica[i].klucz: " << TH[wynik].tablica[i].klucz << endl;
//            //cout << "TH[wynik].tablica[i].wartosc: " << TH[wynik].tablica[i].wartosc << endl;
//            break;
//        }
//        //return 0;
//    }
//    //cout << "TH[wynik].tablica[i]: " << TH[wynik].tablica[i].klucz << ", " << TH[wynik].tablica[i].wartosc << endl;
//    //cout << "TH[wynik].liczba_obiektow--: " << TH[wynik].liczba_obiektow-- << endl;
//    //TH[wynik].tablica[i + 1];
//    TH[wynik].tablica[i] = TH[wynik].tablica[i + 1];
//    TH[wynik].liczba_obiektow--;
//    return 1;
//}
/***********************************************************/
template <typename T>
class ETH
{
public:
    string klucz;
    T wartosc;

    ETH()
    {

    }

    std::string to_string()
    {
        return klucz + " " + std::to_string(wartosc);
    }
    ETH(string k, T w);
};
/***********************************************************/
template <typename T>
ETH<T>::ETH(string k, T w)
{
    klucz = k;
    wartosc = w;
}
/***********************************************************/
/***********************************************************/
/***********************************************************/
template <typename T>
class Tablica_Dynamiczna
{
public:
    T *tablica;
    int pojemnosc;
    int liczba_obiektow;
    // konstruktor
    Tablica_Dynamiczna()
    {
        liczba_obiektow = 0;
        pojemnosc = 2;
        tablica = new T[pojemnosc];
    }
    // destruktor
    ~Tablica_Dynamiczna()
    {
        delete [] tablica;
    }

    void dodaj_na_koncu(T klucz);

    T usun_obiekt();
    void usun_tablice(Tablica_Dynamiczna<T> & spis);
    void wyswietl_ity_element(int indeks, Tablica_Dynamiczna<T> & spis);
    void podmiana_elementu(int indeks, T nowe_dane, Tablica_Dynamiczna<T> & spis);
    std::string to_string();
    void wyswietl_tablice(Tablica_Dynamiczna<T> & TD, int ile);

private:
    int powieksz_rozmiar();
};

///////////////////////////////////////////////////////////////////

// definicje funkcji skladowych
/*************************************************************/
template <typename T>
string Tablica_Dynamiczna<T>::to_string()
{
    string tekst;
    if(liczba_obiektow == 0)
        return "pusty";

    for(int i = 0; i < liczba_obiektow; i++)
    {
        tekst = tekst + tablica[i].to_string() + " -> ";
    }
    return tekst;
}
/*************************************************************/
template <typename T>
void podmiana_elementu(int indeks, T nowe_dane, Tablica_Dynamiczna<T> & spis)
{
    spis.tablica[indeks] = nowe_dane;
}
/*************************************************************/
template <typename T>
void Tablica_Dynamiczna<T>::dodaj_na_koncu(T dane)
{
    if(liczba_obiektow == pojemnosc)
    {
        powieksz_rozmiar();
    }
    tablica[liczba_obiektow++] = dane;
}
/*************************************************************/
template <typename T>
T Tablica_Dynamiczna<T>::usun_obiekt()
{
    if(liczba_obiektow <= 0)
    {
        //cout << "Tablica jest pusta" << endl;
    }
    return (tablica[--liczba_obiektow]);
}
/*************************************************************/
template <typename T>
void Tablica_Dynamiczna<T>::usun_tablice(Tablica_Dynamiczna<T> & spis)
{
    while(liczba_obiektow >= 0)
    {
        usun_obiekt();
    }
}
/*************************************************************/
template <typename T>
int Tablica_Dynamiczna<T>::powieksz_rozmiar()
{
    int wspolczynnik = 2;
    T *nowa_tablica = new T[wspolczynnik * pojemnosc];

    if(nowa_tablica == nullptr)
    {
        return 0;
    }

    // skopiowanie zawartosci
    for(int i = 0; i < liczba_obiektow; i++)
    {
        nowa_tablica[i] = tablica[i];
    }
    pojemnosc *= wspolczynnik;  // nowa pojemnosc
    delete tablica;     // usuniecie starej tablicy
    tablica = nowa_tablica;     // wskaznik tablica pokazuje teraz
    // na nowa tablice
    return 1;
}
/**************************************************************/
template <typename T>
void Tablica_Dynamiczna<T>::wyswietl_ity_element(int indeks, Tablica_Dynamiczna<T> & spis)
{
    if((indeks <= pojemnosc) && (indeks >= 0))
    {
        cout << "tab[" << indeks << "] = " << spis.tablica[indeks];
    }
    else
    {
        cout << "Nieprawidlowy indeks.";
    }
}
/*************************************************************/
// zaprzyjazniona funkcja
/*************************************************************/
template <typename T>
void Tablica_Dynamiczna<T>::wyswietl_tablice(Tablica_Dynamiczna & TD, int ile)
{
    if(TD.liczba_obiektow == 0)
    {
    }
    if(TD.liczba_obiektow < ile)
    {
        for(int i = 0; i < TD.liczba_obiektow; i++)
        {
            cout << TD.tablica[i] << " ";
        }
    }
    if(TD.liczba_obiektow >= ile)
    {
        for(int i = 0; i < ile; i++)
        {
            cout << TD.tablica[i] << " ";
        }
    }
}
/**************************************************************/
/**************************************************************/
/**************************************************************/
template <typename T>
class Tablica_Haszujaca
{
public:
    int aktualny_rozmiar;
    int maksymalny_rozmiar;

    Tablica_Dynamiczna<T> *TH;
    Tablica_Haszujaca();

    void dodaj_element(T element);
    std::string to_string();
    int funkcja_mieszajaca(string klucz);
    //int usun_element(T element);
    int usun_element(string klucz);
    void wyczysc_tablice();
    void statystyki();

    T *wyszukaj(string klucz)
    {
        int wynik = 0;
        wynik = funkcja_mieszajaca(klucz);
        for(int i = 0; i < TH[wynik].liczba_obiektow; i++)
        {
            if((TH[wynik].tablica[i].klucz == klucz))
            {
                return &TH[wynik].tablica[i];
            }
            else
            {
                return nullptr;
            }
        }
    }

private:
    void przemieszanie();

};

/***************************************************************/
template <typename T>
int Tablica_Haszujaca<T>::usun_element(string klucz)
{
    int wynik = 0;
    wynik = funkcja_mieszajaca(klucz);
    if(TH[wynik].liczba_obiektow == 0)
    {
        return 0;
    }
    int i = 0;
    for(i = 0; i < TH[wynik].liczba_obiektow; i++)
    {
        if(TH[wynik].tablica[i].klucz == klucz)
        {
            break;
        }
    }
    TH[wynik].tablica[i] = TH[wynik].tablica[i + 1];
    TH[wynik].liczba_obiektow--;
    return 1;
}
/***************************************************************/
template <typename T>
Tablica_Haszujaca<T>::funkcja_mieszajaca(string klucz)
{
    int dlugosc_napisu = klucz.length();
    int suma = 0;
    for (int i = 0; i < dlugosc_napisu; i++)
    {
        int x = dlugosc_napisu - i - 1;
        suma = suma + klucz[i] * pow(31, x);
    }
    suma = abs((suma % maksymalny_rozmiar));
    return suma;
}
/***************************************************************/
template <typename T>
Tablica_Haszujaca<T>::Tablica_Haszujaca()
{
    aktualny_rozmiar = 0;
    maksymalny_rozmiar = 1;
    TH = new Tablica_Dynamiczna<T>[maksymalny_rozmiar];
}
/***************************************************************/
template <typename T>
void Tablica_Haszujaca<T>::przemieszanie()
{
    int nowy_maks_rozmiar = 2 * maksymalny_rozmiar;
    Tablica_Dynamiczna<T> *Nowa_TH = new Tablica_Dynamiczna<T>[nowy_maks_rozmiar];

    int suma = 0;
    for(int i = 0; i < aktualny_rozmiar; i++)
    {
        for(int j = 0; j < TH[i].liczba_obiektow; j++)
        {
            T tymczasowy = TH[i].tablica[j];
            string klucz = tymczasowy.klucz;
            suma = funkcja_mieszajaca(klucz);
            Nowa_TH[suma].dodaj_na_koncu(tymczasowy);
        }
    }
    delete [] TH;
    maksymalny_rozmiar = nowy_maks_rozmiar;
    TH = Nowa_TH;
}
/***************************************************************/
template <typename T>
void Tablica_Haszujaca<T>::dodaj_element(T wartosc)
{
    if(aktualny_rozmiar >= (double) 0.75 * maksymalny_rozmiar)
    {
        przemieszanie();
    }

    string klucz = wartosc.klucz;
    int suma = funkcja_mieszajaca(klucz);
    TH[suma].dodaj_na_koncu(wartosc);
    aktualny_rozmiar = aktualny_rozmiar + 1;
}
/***************************************************************/
template <typename T>
std::string Tablica_Haszujaca<T>::to_string()
{
    string tekst;
    for(int i = 0; i < maksymalny_rozmiar; i++)
    {
        tekst = tekst + TH[i].to_string() + "\n";
    }
    return tekst;
}
/***************************************************************/
template <typename T>
void Tablica_Haszujaca<T>::statystyki()
{
    unsigned int minimum = 0;
    unsigned int maksimum = 0;
    unsigned int puste = 0;
    unsigned int suma = 0;
    unsigned int mianownik = 0;
    for(int i = 0; i < maksymalny_rozmiar; i++)
    {

        if(TH[i].liczba_obiektow == 0)
        {
            puste++;
        }
        else
        {
            if(minimum > TH[i].liczba_obiektow)
            {
                minimum = TH[i].liczba_obiektow;
            }
            suma = suma + TH[i].liczba_obiektow;
            mianownik = maksymalny_rozmiar * TH[i].liczba_obiektow;
        }
        if(maksimum < TH[i].liczba_obiektow)
        {
            maksimum = TH[i].liczba_obiektow;
        }

    }

    cout << "Statystyki:" << endl;
    cout << "Aktualny rozmiar: " << aktualny_rozmiar << endl;
    cout << "Maksymalny rozmiar: " << maksymalny_rozmiar << endl;
    cout << "Minimalna liczba elementow podtablicy: " << minimum << endl;
    cout << "Maksymalna liczba elementow podtablicy: " << maksimum << endl;
    cout << "Liczba pustych podtablic: " << puste << endl;
    cout << "Liczba niepustych podtablic: " << maksymalny_rozmiar - puste << endl;
    cout << "Srednia liczba elementow podtablicy: " << (float)suma / mianownik << endl;
}

/***************************************************************/
int main()
{
    srand(time(NULL));
    Tablica_Haszujaca<ETH<int>> TH;

	string tekst("abcdefghijklmnopqrstuvwxyz");
	random_device rd;
	mt19937 tworca(rd());

    const int MAX_ORDER = 6;
    for(int o = 1; o <= MAX_ORDER; o++)
    {
        const int n = pow(10, o);

        clock_t t1 = clock();
        for(int i = 0; i < n; i++)
        {
            std::shuffle(tekst.begin(), tekst.end(), tworca);
            string x = tekst.substr(0, 6);
            ETH<int> dane(x, i);
            TH.dodaj_element(dane);
        }
        clock_t t2 = clock();

        double czas_dodawania = (t2 - t1) / (double)CLOCKS_PER_SEC;
        cout << "\nDodanie 10^" << o << " elementow: " << czas_dodawania << "s. "
             << "Czas na jeden element: " << czas_dodawania / n << "s." << endl;


        const int m = pow(10, 4);
        int hits = 0;
        clock_t t3 = clock();
        for(int j = 0; j < m; j++)
        {
            std::shuffle(tekst.begin(), tekst.end(), tworca);
            string x = tekst.substr(0, 6);
            if(TH.wyszukaj(x) != nullptr)
            {
                hits++;
            }
            else
            {

            }
        }
        clock_t t4 = clock();
        double czas_wyszukiwania = (t4 - t3) / (double)CLOCKS_PER_SEC;
        cout << "Wyszukanie 10^" << o << " elementow: " << czas_wyszukiwania << "s. "
             << "Czas na jeden element: " << czas_wyszukiwania / n << "s." << endl;
        cout << "Liczba trafien: " << hits << endl;


    }
    //cout << TH.to_string() << endl;
    cout << "\n\n";
    TH.statystyki();

//    Tablica_Haszujaca<ETH<int>> TH_pokazowa;
//    ETH<int> dane1("jeden", 1);
//    ETH<int> dane2("dwa", 2);
//    ETH<int> dane3("trzy", 3);
//    ETH<int> dane4("cztery", 4);
//
//    TH_pokazowa.dodaj_element(dane1);
//    TH_pokazowa.dodaj_element(dane2);
//    TH_pokazowa.dodaj_element(dane3);
//    TH_pokazowa.dodaj_element(dane4);
//
//    cout << TH_pokazowa.to_string() << endl;
//    cout << TH_pokazowa.wyszukaj("jeden") << endl;
//    cout << TH_pokazowa.wyszukaj("dwa") << endl;
//
//    cout << TH_pokazowa.usun_element("cztery") << endl << endl;
//
//    cout << TH_pokazowa.to_string() << endl;
    return 0;
}
