#include <iostream>
#include <ctime>
#include <cmath>
#include <string.h>
#include <windows.h>
using namespace std;

template <typename T> class lista_dwukierunkowa;
template <typename T> ostream & operator<<(ostream & stru, lista_dwukierunkowa<T> & spis);

/*****************************************************/
template <typename T>
class lista_dwukierunkowa
{
public:
    class wezel_listy
    {
        public:
        T *wsk_dane;  // wskaznik do danych przechowywanych w wezle;
        wezel_listy *poprzedni;
        wezel_listy *nastepny;


        // deklaracja konstruktora wezla
        wezel_listy(T & ukryty);

        // deklaracja destruktora wezla
        ~wezel_listy();
    };

    // odpowiednie wskazniki
    wezel_listy *pierwszy_wsk;      // na pierwszy wezel
    wezel_listy *ostatni_wsk;       // na ostatni wezel
    wezel_listy *wybrany_wsk;       // na wybrany wezel

    // konstruktor listy
    lista_dwukierunkowa();

    // destruktor listy
    ~lista_dwukierunkowa();

    // dodawanie elementu do listy (punkty: a, b)
    void dodaj_element(T obiekt);

    // void dodaj_z_porzadkiem(T obiekt, lista_dwukierunkowa & lista);

    // usuwanie elementu z listy (punkty: c, d)
    void usun_element();

    void usun_liste(); // punkt j

    //T & wyszukaj(T wzor, lista_dwukierunkowa<T> & lista);

    //T & wyszukaj_i_usun(T wzor, lista_dwukierunkowa<T> & lista);



    // zwraca zawartosc wezla wskazywanego przez wybrany_wsk
    T & co_na_wybranym_wsk();

    // ustawia wybrany_wsk na pierwszy wezel
    void na_pierwszy();

    // ustawia wybrany_wsk na nullptr
    void na_nullptr();

    // ustawia "wybrany" wezel na nastepny
    wezel_listy *przejdz_na_nastepny()
    {
        if(wybrany_wsk)     // jesli rozny od nullptr
        {
            return (wybrany_wsk = wybrany_wsk->nastepny);
        }
        else
        {
            return nullptr;
        }
    }

    // ustawia "wybrany" wezel na poprzedni
    wezel_listy *przejdz_na_poprzedni()
    {
        if(wybrany_wsk != pierwszy_wsk)
        {
            return (wybrany_wsk = wybrany_wsk->poprzedni);
        }
        else
        {
            return pierwszy_wsk;
        }
    }

    // wyswietla zawartosc jakiegos wezla (punkt: e)
    void i_ty_wezel_listy(int i);

    // zaprzyjazniona funkcja realizujaca przeladowanie operatora<<
    friend ostream & operator<<
    <T> (ostream & strumien, lista_dwukierunkowa<T> & lista);   // punkt: k

    //wezel_listy *poprzedni_wezel_listy(wezel_listy *odnosnik_wsk);

private:
    // wstawia element na koniec listy (punkt: a)
    void wstaw_na_koniec(wezel_listy *nowy_wsk);

    // wstawia element na poczatek listy (punkt: b)
    void wstaw_na_poczatek(wezel_listy *nowy_wsk);

    // usuwa ostatni element na liscie (punkt: c)
    void usun_ostatni_element();

    // usuwa pierwszy element z listy (punkt: d)
    void usun_pierwszy_element();
};
/********************************************************/
// definicja konstruktora wezla
template <typename T>
lista_dwukierunkowa<T>::wezel_listy::wezel_listy(T & ukryty) : poprzedni(nullptr), nastepny(nullptr), wsk_dane(nullptr)
{
    wsk_dane = new T;
    *wsk_dane = ukryty;
}
/**********************************************************/
// definicja destruktora wezla
template <typename T>
lista_dwukierunkowa<T>::wezel_listy::~wezel_listy()
{
    delete wsk_dane;
}
/*****************************************************************/
// definicja konstruktora listy
template <typename T>
lista_dwukierunkowa<T>::lista_dwukierunkowa()
{
    pierwszy_wsk = wybrany_wsk = ostatni_wsk = nullptr;
}
/*****************************************************************/
// definicja destruktora listy
template <typename T>
lista_dwukierunkowa<T>::~lista_dwukierunkowa()
{
    for(wybrany_wsk = pierwszy_wsk ; wybrany_wsk ; )
    {
        wezel_listy *pamietaj_nastepce;
        // odczytanie i zapamietanie nastepcy
        pamietaj_nastepce = wybrany_wsk->nastepny;
        delete wybrany_wsk;
        wybrany_wsk = pamietaj_nastepce;
    }
}
/*****************************************************************/
// funkcja dodajaca elementy do listy
template <typename T>
void lista_dwukierunkowa<T>::dodaj_element(T obiekt)
{
    // umieszczenie w wezle informacji o elemencie
    wezel_listy * nowy_wsk = new wezel_listy(obiekt);

    // dodanie elementu do listy
    if(wybrany_wsk == nullptr) // jesli dodaje na koncu listy
    {
        wstaw_na_koniec(nowy_wsk);      // punkt: a
    }
    else
    {
        if(wybrany_wsk = pierwszy_wsk) // jesli dodaje na poczatek
        {
            wstaw_na_poczatek(nowy_wsk);  // punkt: b
        }
    }
}
/*****************************************************************/
//template <typename T>
//void lista_dwukierunkowa<T>::dodaj_z_porzadkiem(T obiekt, lista_dwukierunkowa & lista)
//{
//    lista.dodaj_element(); // dodanie elementu
//    // kod sortujacy
//    na_pierwszy();
//
//}

/*****************************************************************/
// zwraca zawartosc wezla wskazywanego przez wybrany_wsk
template <typename T>
T & lista_dwukierunkowa<T>::co_na_wybranym_wsk()
{
    return *(wybrany_wsk->wsk_dane);
}
/****************************************************************/
template <typename T>
void lista_dwukierunkowa<T>::na_pierwszy()
{
    wybrany_wsk = pierwszy_wsk;
}
/****************************************************************/
template <typename T>
void lista_dwukierunkowa<T>::na_nullptr()
{
    wybrany_wsk = nullptr;
}
/***************************************************************/
template <typename T>
void lista_dwukierunkowa<T>::wstaw_na_koniec(wezel_listy *nowy_wsk)
{
    if(!pierwszy_wsk)   // lista jest pusta
    {
        pierwszy_wsk = nowy_wsk;
    }
    else                // lista nie jest pusta
    {
        ostatni_wsk->nastepny = nowy_wsk;
        nowy_wsk->poprzedni = ostatni_wsk;
    }
    ostatni_wsk = nowy_wsk;
}
/***************************************************************/
template <typename T>
void lista_dwukierunkowa<T>::wstaw_na_poczatek(wezel_listy *nowy_wsk)
{
    pierwszy_wsk = nowy_wsk;
    nowy_wsk->nastepny = wybrany_wsk;
    wybrany_wsk->poprzedni = nowy_wsk;
    nowy_wsk->poprzedni = nullptr;
    wybrany_wsk = nowy_wsk;
}
/***************************************************************/
template <typename T>
void lista_dwukierunkowa<T>::usun_element()
{
    if(wybrany_wsk == nullptr)
    {
        return;     // nie usuwam nullptr
    }
    else if(wybrany_wsk == ostatni_wsk)
    {
        usun_ostatni_element();         // punkt: c
    }
    else
    {
        usun_pierwszy_element();        // punkt: d
    }
}
/***************************************************************/
template <typename T>
void lista_dwukierunkowa<T>::usun_ostatni_element()
{
    // znajduje poprzedni wezel
    wezel_listy *pomocniczy = wybrany_wsk->poprzedni;
    pomocniczy->nastepny = nullptr;
    ostatni_wsk = pomocniczy;
    delete wybrany_wsk;
    wybrany_wsk = nullptr;
}
/***************************************************************/
template <typename T>
void lista_dwukierunkowa<T>::usun_pierwszy_element()
{
    pierwszy_wsk = pierwszy_wsk->nastepny;
    delete wybrany_wsk;
    wybrany_wsk = pierwszy_wsk;
    if(pierwszy_wsk)
    {
        pierwszy_wsk->poprzedni = nullptr;
    }
    else
    {
        ostatni_wsk = nullptr;
    }
}
/********************************************************************/
template <typename T>
void lista_dwukierunkowa<T>::i_ty_wezel_listy(int i)
{
    na_pierwszy();
    for(int n = 0; n < i; n++)
    {
        przejdz_na_nastepny();
    }
}
/********************************************************************/
template <typename T>
ostream & operator<<(ostream & strumien, lista_dwukierunkowa<T> & lista)
{
    typename lista_dwukierunkowa<T>::wezel_listy *iteruj = lista.pierwszy_wsk;
    int rozmiar = 0;
    cout << "Od lewej: Numer elementu, element listy, adres\n";
    int i = 0;
    for(i = 0 ; iteruj ; i++, iteruj = iteruj->nastepny)
    {
        rozmiar = sizeof(lista) * (i + 1);
        //rozmiar = rozmiar + sizeof(iteruj->wsk_dane);
        strumien << i << ") " << *(iteruj->wsk_dane) << " " << (int)iteruj->wsk_dane << endl;
    }
    //rozmiar = sizeof(lista) * i;
    //cout << rozmiar;
    return strumien;
}
/********************************************************************/
template <typename T>
void lista_dwukierunkowa<T>::usun_liste()
{
    na_pierwszy();
    while(wybrany_wsk != nullptr)
    {
        if(wybrany_wsk == nullptr)
        {
            return;     // nie usuwam nullptr
        }
        else if(wybrany_wsk == ostatni_wsk)
        {
            usun_ostatni_element();         // punkt: c
            na_pierwszy();
        }
        else if(wybrany_wsk == pierwszy_wsk)
        {
            usun_pierwszy_element();        // punkt: d
            na_pierwszy();
        }
        przejdz_na_nastepny();
    }
    usun_pierwszy_element();
    wybrany_wsk = nullptr;
    //cout << "Usuwam liste" << endl;
}
/****************************************************************/
//template <typename T>
//T & lista_dwukierunkowa<T>::wyszukaj(T wzor, lista_dwukierunkowa<T> & lista)
//{
//    typename lista_dwukierunkowa<T>::wezel_listy *iteruj = lista.pierwszy_wsk;
//    for(int i = 0 ; iteruj ; i++, iteruj = iteruj->nastepny)
//    {
//        if(wzor == *(iteruj->wsk_dane))
//        {
//            return *(iteruj->wsk_dane);
//            //cout << iteruj;
//        }
//        if(wzor =! *(iteruj->wsk_dane))
//        {
//            break;
//            //cout << 0;
//        }
//    }
//}
/*****************************************************************/
//template <typename T>
//T & lista_dwukierunkowa<T>::wyszukaj_i_usun(T wzor, lista_dwukierunkowa<T> & lista)
//{
//    typename lista_dwukierunkowa<T>::wezel_listy *iteruj = lista.pierwszy_wsk;
//    for(int i = 0 ; iteruj ; i++, iteruj = iteruj->nastepny)
//    {
//        if(wzor == *(iteruj->wsk_dane))
//        {
//            wezel_listy *wl = wybrany_wsk->poprzedni;
//            wl->nastepny = wybrany_wsk->nastepny;
//            (wybrany_wsk->nastepny)->poprzedni = wl;
//            delete wybrany_wsk;
//            wybrany_wsk = wl;
//            //cout << iteruj;
//        }
//        else
//        {
//            //return 0;
//            //cout << 0;
//        }
//    }
//}
/*****************************************************************/
int main()
{
    /*lista_dwukierunkowa<int> lista3;
    lista3.dodaj_element(0);
    lista3.dodaj_element(1);
    lista3.dodaj_element(2);
    lista3.i_ty_wezel_listy(1);
    cout << lista3.co_na_wybranym_wsk();*/

    /*lista_dwukierunkowa<int> lista100;
    clock_t e = clock();
    for(int i = 0; i < 100; i++)
    {
        lista100.dodaj_element(i);
    }
    clock_t f = clock();
    double cz = (f - e) / (double)CLOCKS_PER_SEC;
    clock_t t5 = clock();
    lista100.usun_liste();
    clock_t t6 = clock();
    double czas4 = (t6 - t5) / (double)CLOCKS_PER_SEC;
    cout << "Tworzenie listy 100-elementowej: " << cz << " s. Czas na jedna operacje: " << cz / 100 << " s." << endl;
    cout << "Usuwanie listy 100-elementowej: " << czas4 << " s. Czas na jedna operacje: " << czas4 / 100 << " s." << endl;

    lista_dwukierunkowa<int> lista1000;
    clock_t ppp = clock();
    for(int i = 0; i < 1000; i++)
    {
        lista1000.dodaj_element(i);
    }
    clock_t ooo = clock();
    double czcz = (ooo - ppp) / (double)CLOCKS_PER_SEC;
    clock_t t55 = clock();
    lista1000.usun_liste();
    clock_t t66 = clock();
    double czas44 = (t66 - t55) / (double)CLOCKS_PER_SEC;
    cout << "Tworzenie listy 1000-elementowej: " << czcz << " s. Czas na jedna operacje: " << czcz / 1000 << " s." << endl;
    cout << "Usuwanie listy 1000-elementowej: " << czas44 << " s. Czas na jedna operacje: " << czas44 / 1000 << " s." << endl;

    lista_dwukierunkowa<int> lista10000;
    clock_t zzz = clock();
    for(int i = 0; i < 10000; i++)
    {
        lista10000.dodaj_element(i);
    }
    clock_t qqq = clock();
    double aaa = (qqq - zzz) / (double)CLOCKS_PER_SEC;
    clock_t t505 = clock();
    lista10000.usun_liste();
    clock_t t606 = clock();
    double czas42 = (t606 - t505) / (double)CLOCKS_PER_SEC;
    cout << "Tworzenie listy 10000-elementowej: " << aaa << " s. Czas na jedna operacje: " << aaa / 10000 << " s." << endl;
    cout << "Usuwanie listy 10000-elementowej: " << czas42 << " s. Czas na jedna operacje: " << czas42 / 10000 << " s." << endl;

    lista_dwukierunkowa<int> lista100000;
    clock_t rrr = clock();
    for(int i = 0; i < 100000; i++)
    {
        lista100000.dodaj_element(i);
    }
    clock_t yyy = clock();
    double www = (yyy - rrr) / (double)CLOCKS_PER_SEC;
    clock_t l = clock();
    lista100000.usun_liste();
    clock_t m = clock();
    double x = (m - l) / (double)CLOCKS_PER_SEC;
    cout << "Tworzenie listy 100000-elementowej: " << www << " s. Czas na jedna operacje: " << www / 10000 << " s." << endl;
    cout << "Usuwanie listy 100000-elementowej: " << x << " s. Czas na jedna operacje: " << x / 100000 << " s." << endl;

    lista_dwukierunkowa<int> lista1000000;
    clock_t nnn = clock();
    for(int i = 0; i < 1000000; i++)
    {
        lista1000000.dodaj_element(i);
    }
    clock_t ddd = clock();
    double xxx = (ddd - nnn) / (double)CLOCKS_PER_SEC;
    clock_t o = clock();
    lista1000000.usun_liste();
    clock_t p = clock();
    double q = (p - o) / (double)CLOCKS_PER_SEC;
    cout << "Tworzenie listy 1000000-elementowej: " << xxx << " s. Czas na jedna operacje: " << xxx / 1000000 << " s." << endl;
    cout << "Usuwanie listy 1000000-elementowej: " << q << " s. Czas na jedna operacje: " << q / 1000000 << " s." << endl;

    lista_dwukierunkowa<int> lista;
    for(int i = 0; i < 10; i++)
    {
        lista.na_nullptr();
        lista.dodaj_element(i);
    }
    cout << lista;
    for(int i = 9; i > 0; i--)
    {
        lista.i_ty_wezel_listy(i);
        lista.usun_element();
    }
    cout << lista;

    /*lista_dwukierunkowa<int> lista2;
    for(int i = 1; i < 8; i++)
    {
        int n = pow(10, i);

        clock_t t1 = clock();
        for(int j = 1; j < n; j++)
            lista2.dodaj_element(j);

        clock_t t2 = clock();
        double czas = (t2 - t1) / (double)CLOCKS_PER_SEC;
        cout << "Dodanie " << n << " elementow: " << czas << " s. Czas na dodanie jednego elementu: " << czas / n << endl;
    }*/

    //lista2.usun_liste();

    //cout << lista2;
    lista_dwukierunkowa<char> znaki;
    //znaki.na_nullptr();
    znaki.dodaj_element('a');
    znaki.dodaj_element('b');
    znaki.dodaj_element('c');
    znaki.dodaj_element('d');
    cout << znaki;

    znaki.i_ty_wezel_listy(0);
    znaki.usun_element();
    cout << znaki;

    znaki.i_ty_wezel_listy(2);
    znaki.usun_element();
    cout << znaki;


    return 0;
}













