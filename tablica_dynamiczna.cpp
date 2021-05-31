#include <iostream>
#include <ctime>
#include <cmath>
//#include <cstdlib>
//#include <iomanip>
using namespace std;
/***********************************************************/
template <typename T> class tablica_dynamiczna;
template <typename T> ostream & operator<<(ostream & stru, tablica_dynamiczna<T> & spis);
/***********************************************************/
template <typename T>
class tablica_dynamiczna
{
public:
    T *tablica;
    int pojemnosc;
    int liczba_obiektow;
    // konstruktor
    tablica_dynamiczna()
    {
        liczba_obiektow = 0;
        pojemnosc = 1;
        tablica = new T[pojemnosc];
    }
    // destruktor
    ~tablica_dynamiczna()
    {
        delete [] tablica;
    }

    void dodaj_na_koncu(T nowy);

    T usun_obiekt();

    void usun_tablice(tablica_dynamiczna<T> & spis);

    void wyswietl_ity_element(int indeks, tablica_dynamiczna<T> & spis);

    void podmiana_elementu(int indeks, T nowe_dane, tablica_dynamiczna<T> & spis);

    friend ostream & operator<< <T>
    (ostream & stru, tablica_dynamiczna<T> & x);

private:
    int powieksz_rozmiar();
};

///////////////////////////////////////////////////////////////////

// definicje funkcji skladowych
/*************************************************************/
template <typename T>
void podmiana_elementu(int indeks, T nowe_dane, tablica_dynamiczna<T> & spis)
{
    spis.tablica[indeks] = nowe_dane;
}
/*************************************************************/
template <typename T>
void tablica_dynamiczna<T>::dodaj_na_koncu(T nowy)
{
    if(liczba_obiektow == pojemnosc)
    {
        clock_t t1 = clock();
        powieksz_rozmiar();
        clock_t t2 = clock();
        double czas = (t2 - t1) / (double)CLOCKS_PER_SEC;
        if(czas > 0.000001) cout << "Powiekszono rozmiar: Czas operacji: " << czas << "s.; Pojemnosc: " << pojemnosc << " bajtow." << endl;
    }
    tablica[liczba_obiektow++] = nowy;
}
/*************************************************************/
template <typename T>
T tablica_dynamiczna<T>::usun_obiekt()
{
    if(liczba_obiektow <= 0)
    {
        //cout << "Tablica jest pusta" << endl;
    }
    return (tablica[--liczba_obiektow]);
}
/*************************************************************/
template <typename T>
void tablica_dynamiczna<T>::usun_tablice(tablica_dynamiczna<T> & spis)
{
    while(liczba_obiektow >= 0)
    {
        usun_obiekt();
    }
}
/*************************************************************/
template <typename T>
int tablica_dynamiczna<T>::powieksz_rozmiar()
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
void tablica_dynamiczna<T>::wyswietl_ity_element(int indeks, tablica_dynamiczna<T> & spis)
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
ostream & operator<<(ostream & stru, tablica_dynamiczna<T> & spis)
{
    for(int i = 0; i < spis.liczba_obiektow; i++)
    {
        stru << i << ") " << spis.tablica[i] << "; adres: " << (int)&spis.tablica[i] << endl;
    }
    stru << endl;
    return stru;
}
/**************************************************************/
int main()
{
    srand(time(NULL));
    //cout << setprecision(10000);
    for(int i = 0; i < 9; i++)
    {
        tablica_dynamiczna<int> tab;
        clock_t t1 = clock();
        const int n = pow(10, i);
        for(int i = 0; i < n; i++)
        {
            tab.dodaj_na_koncu((rand() << 15) + rand());
        }

        clock_t t2 = clock();
        double czas_dodawania = (t2 - t1) / (double)CLOCKS_PER_SEC;
        cout << "\nDodanie " << n << " elementow: " << czas_dodawania << "s. "
             << "Sredni czas na dodanie jednego elementu: " << czas_dodawania / n << "s." << endl;

        cout << "Odwolanie sie do losowego indeksu tablicy majacej " << tab.liczba_obiektow << " elementow: ";
        clock_t t3 = clock();
        tab.wyswietl_ity_element(rand() % tab.liczba_obiektow, tab);
        clock_t t4 = clock();
        double czas_odwolania = (t4 - t3) / (double)CLOCKS_PER_SEC;
        cout << "; Czas odwolania = " << czas_odwolania << "s." << endl;

        cout << "Podmiana elementu losowymi danymi: ";
        clock_t t5 = clock();
        podmiana_elementu(n, (rand() << 15) + rand(), tab);
        tab.wyswietl_ity_element(n, tab);
        clock_t t6 = clock();
        double czas_podmiany = (t6 - t5) / (double)CLOCKS_PER_SEC;
        cout << "; Czas podmiany = " << czas_podmiany << "s." << endl;

        clock_t t7 = clock();
        tab.usun_tablice(tab);
        clock_t t8 = clock();
        double czas_usuwania = (t8 - t7) / (double)CLOCKS_PER_SEC;
        cout << "Usuniecie " << n << " elementow: " << czas_usuwania << "s. "
             << "Sredni czas na usuniecie jednego elementu: " << czas_usuwania / n << "s." << endl;
    }

    /*tablica_dynamiczna<char> tab_wys;
    for(char i = 70; i < 100; i++)
    {
        tab_wys.dodaj_na_koncu(i);
    }
    cout << "Zawartosc tablicy tab_wys:" << endl;
    cout << tab_wys << endl;
    cout << "Liczba elementow: " << tab_wys.liczba_obiektow << endl;
    cout << "Pojemnosc: " << tab_wys.pojemnosc << endl;

    podmiana_elementu(2, 'e', tab_wys);
    cout << tab_wys;*/

    return 0;
}
