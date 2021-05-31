#include <iostream>
#include <ctime>
#include <cmath>
#include <windows.h>
using namespace std;
/**************************************************************/
template <typename T> class Kopiec_binarny;
/**************************************************************/
template <typename T>
class Kopiec_binarny
{
public:
    T *Kopiec;
    int pojemnosc;
    int liczba_obiektow;
    Kopiec_binarny(); // konstruktor
    ~Kopiec_binarny(); // destruktor
    void dodaj_element(T nowy, Kopiec_binarny<T> & KB);
    void czyszczenie_kopca(Kopiec_binarny<T> & KB);
    void wyswietl_kopiec(Kopiec_binarny<T> & KB, int ile);
    T usun_maksymalny(Kopiec_binarny<T> & KB);
    void przekopcowanie_w_dol(Kopiec_binarny<T> & KB);
    //void przekopcowanie_w_gore(Kopiec_binarny<T> & KB);
private:
    void przekopcowanie_d(Kopiec_binarny<T> & KB, int indeks);
    //void przekopcowanie_g(Kopiec_binarny<T> & KB, int indeks);
    void powieksz_rozmiar();

};
/**************************************************************/
template <typename T>
Kopiec_binarny<T>::Kopiec_binarny()
{
    liczba_obiektow = 0;
    pojemnosc = 1;
    Kopiec = new T[pojemnosc];
}
/**************************************************************/
template <typename T>
Kopiec_binarny<T>::~Kopiec_binarny()
{
    delete [] Kopiec;
}
/**************************************************************/
template <typename T>
T Kopiec_binarny<T>::usun_maksymalny(Kopiec_binarny<T> & KB)
{
    if(liczba_obiektow <= 0)
    {
        return 0;
    }
    int maks = KB.Kopiec[0];
    KB.Kopiec[0] = KB.Kopiec[liczba_obiektow - 1];
    KB.liczba_obiektow = KB.liczba_obiektow - 1;
    przekopcowanie_d(KB, 0);
    return maks;
}
/**************************************************************/
template <typename T>
void Kopiec_binarny<T>::powieksz_rozmiar()
{
    int wspolczynnik = 2;
    T *nowy_kopiec = new T[wspolczynnik * pojemnosc];

    // skopiowanie zawartosci
    for(int i = 0; i < liczba_obiektow; i++)
    {
        nowy_kopiec[i] = Kopiec[i];
    }
    pojemnosc *= wspolczynnik; // nowa pojemnosc
    delete [] Kopiec; // usuniecie starego kopca
    Kopiec = nowy_kopiec;
}
/***************************************************************/
template <typename T>
void Kopiec_binarny<T>::czyszczenie_kopca(Kopiec_binarny<T> & KB)
{
    delete [] KB.Kopiec;
    KB.Kopiec = nullptr;
}
/***************************************************************/
template <typename T>
void Kopiec_binarny<T>::przekopcowanie_w_dol(Kopiec_binarny<T> & KB)
{
    //pojemnosc = liczba_obiektow;
    for(int i = (liczba_obiektow - 1); i >= 0; i--)
    {
        przekopcowanie_d(KB, i);
    }
}
/***************************************************************/
//template <typename T>
//void Kopiec_binarny<T>::przekopcowanie_w_gore(Kopiec_binarny<T> & KB)
//{
//    //pojemnosc = liczba_obiektow;
//    for(int i = 0; i < liczba_obiektow; i++)
//    {
//        przekopcowanie_g(KB, i);
//    }
//}
/***************************************************************/
template <typename T>
void Kopiec_binarny<T>::przekopcowanie_d(Kopiec_binarny<T> & KB, int i)
{
    int wiekszy = 0;
    int lewe_dziecko = (2 * i) + 1;
    int prawe_dziecko = (2 * i) + 2;
    if((lewe_dziecko < liczba_obiektow) && ((KB.Kopiec[lewe_dziecko] > (KB.Kopiec[i]))))
    {
        wiekszy = lewe_dziecko;
    }
    else
    {
        wiekszy = i;
    }

    if((prawe_dziecko < liczba_obiektow) && ((KB.Kopiec[prawe_dziecko] > (KB.Kopiec[wiekszy]))))
    {
        wiekszy = prawe_dziecko;
    }

    if(wiekszy != i)
    {
        T tmp = 0;
        tmp = KB.Kopiec[i];
        KB.Kopiec[i] = KB.Kopiec[wiekszy];
        KB.Kopiec[wiekszy] = tmp;
        przekopcowanie_d(KB, wiekszy);
    }
}
/*****************************************************************/
//template <typename T>
//void Kopiec_binarny<T>::przekopcowanie_g(Kopiec_binarny<T> & KB, int i)
//{
//    int mniejszy = 0;
//    int lewe_dziecko = (2 * i) + 1;
//    int prawe_dziecko = (2 * i) + 2;
//    if((lewe_dziecko > liczba_obiektow) && ((KB.Kopiec[lewe_dziecko] > (KB.Kopiec[i]))))
//    {
//        mniejszy = lewe_dziecko;
//    }
//    else
//    {
//        mniejszy = i;
//    }
//
//    if((prawe_dziecko > liczba_obiektow) && ((KB.Kopiec[prawe_dziecko] > (KB.Kopiec[mniejszy]))))
//    {
//        mniejszy = prawe_dziecko;
//    }
//
//    if(mniejszy != i)
//    {
//        T tmp = 0;
//        tmp = KB.Kopiec[i];
//        KB.Kopiec[i] = KB.Kopiec[mniejszy];
//        KB.Kopiec[mniejszy] = tmp;
//        przekopcowanie_g(KB, mniejszy);
//    }
//}
/********************************************************************/
template <typename T>
void Kopiec_binarny<T>::dodaj_element(T nowy, Kopiec_binarny<T> & KB)
{
    if(liczba_obiektow == pojemnosc)
    {
        powieksz_rozmiar();
    }
    KB.Kopiec[liczba_obiektow++] = nowy;
}
/********************************************************************/
template <typename T>
void Kopiec_binarny<T>::wyswietl_kopiec(Kopiec_binarny<T> & KB, int ile)
{
    if(KB.liczba_obiektow == 0)
    {
        cout << "Kopiec jest pusty." << endl;
    }
    if(KB.liczba_obiektow < ile)
    {
        for(int i = 0; i < KB.liczba_obiektow; i++)
        {
            cout << KB.Kopiec[i] << " ";
        }
    }
    if(KB.liczba_obiektow >= ile)
    {
        for(int i = 0; i < ile; i++)
        {
            cout << KB.Kopiec[i] << " ";
        }
    }
}
int main()
{
    srand(time(NULL));
    for(int i = 0; i < 8; i++)
    {
        Kopiec_binarny<int> KB;
        const int n = pow(10, i);
        clock_t t1 = clock();
        for(int j = 0; j < n; j++)
        {
            KB.dodaj_element(((rand() << 15) + rand() + 1), KB);
        }
        KB.przekopcowanie_w_dol(KB);
        clock_t t2 = clock();
        double czas_dodawania = (t2 - t1) / double(CLOCKS_PER_SEC);
        cout << "\nDodanie 10^" << i << " elementow: " << czas_dodawania << "s. "
             << "Czas na jeden element: " << czas_dodawania / n << "s." << endl;

        clock_t t3 = clock();
        for(int k = 0; k < n; k++)
        {
            KB.usun_maksymalny(KB);
        }
        clock_t t4 = clock();
        double czas_usuniecia = (t4 - t3) / double(CLOCKS_PER_SEC);
        cout << "Usuniecie 10^" << i << " elementow: " << czas_usuniecia << "s. "
             << "Czas na jeden element: " << czas_usuniecia / n << "s." << endl;

        //KB.czyszczenie_kopca(KB);
    }
    //Sleep(5000);
//    Kopiec_binarny<int> KB;
//    for(int i = 0; i < 1000; i++)
//    {
//        KB.dodaj_element(i, KB);
//    }
//    KB.przekopcowanie_w_dol(KB);
//    for(int i = 0; i < 1000; i++)
//    {
//        Sleep(10);
//        cout << KB.usun_maksymalny(KB) << endl;
//    }
//    Kopiec_binarny<int> KB;
//    KB.dodaj_element(4, KB);
//    KB.dodaj_element(1, KB);
//    KB.dodaj_element(3, KB);
//    KB.dodaj_element(2, KB);
//    KB.dodaj_element(16, KB);
//    KB.dodaj_element(9, KB);
//    KB.dodaj_element(10, KB);
//    KB.dodaj_element(14, KB);
//    KB.dodaj_element(8, KB);
//    KB.dodaj_element(7, KB);
//    KB.przekopcowanie_w_dol(KB);
//    cout << "Liczba obiektow: " << KB.liczba_obiektow << endl;
//    cout << "Pojemnosc kopca: " << KB.pojemnosc << endl;
//    KB.wyswietl_kopiec(KB, 10);
//
//    cout << endl << "Usuniecie maksymalnego:";
//    cout << endl << "korzen: " << KB.usun_maksymalny(KB);
//    cout << endl;
//    cout << "Liczba obiektow: " << KB.liczba_obiektow << endl;
//    cout << "Pojemnosc kopca: " << KB.pojemnosc << endl;
//    KB.wyswietl_kopiec(KB, 9);

//    KB.czyszczenie_kopca(KB);
    return 0;
}
