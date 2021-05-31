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
    void dodaj_tablice(T *tab, T rozmiar, char opcja, Kopiec_binarny<T> & KB);
    void czyszczenie_kopca(Kopiec_binarny<T> & KB);
    void wyswietl_kopiec(Kopiec_binarny<T> & KB, int ile);
    T usun_maksymalny(Kopiec_binarny<T> & KB);
    void przekopcowanie_w_dol(Kopiec_binarny<T> & KB);
    //void przekopcowanie_w_gore(Kopiec_binarny<T> & KB);
    void sortowanie_przez_kopcowanie(Kopiec_binarny<T> & KB, char opcja);
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
template <typename T>
void Kopiec_binarny<T>::sortowanie_przez_kopcowanie(Kopiec_binarny<T> & KB, char opcja)
{
    if(opcja == 'D')
    {
        przekopcowanie_w_dol(KB);
        int lo = liczba_obiektow;
        for(int i = liczba_obiektow - 1; i >= 0; i--)
        {
            T tmp = 0;
            tmp = KB.Kopiec[0];
            KB.Kopiec[0] = KB.Kopiec[i];
            KB.Kopiec[i] = tmp;
            liczba_obiektow = liczba_obiektow - 1;
            KB.przekopcowanie_d(KB, 0);
        }
        liczba_obiektow = lo;
    }
}
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
void Kopiec_binarny<T>::dodaj_tablice(T *tab, T rozmiar, char opcja, Kopiec_binarny<T> & KB)
{
    for(int i = 0; i < rozmiar; i++)
    {
        dodaj_element(tab[i], KB);
    }
    sortowanie_przez_kopcowanie(KB, opcja);
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
/*********************************************************************/
void sortowanie_przez_zliczanie(int *A, int rozmiar_A, int m)
{
    int tab_liczniki[m];

    int *B = new int[rozmiar_A];

    // inicjowanie tablicy licznikow
    for(int j = 0; j <= (m - 1); j++)
    {
        tab_liczniki[j] = 0;
    }

    // tab_liczniki[k] zawiera teraz liczbe elementow rownych k
    for(int k = 0; k < rozmiar_A; k++)
    {
        tab_liczniki[A[k]] = tab_liczniki[A[k]] + 1;
    }

    // tab_liczniki[x] zawiera teraz liczbe elementow mniejszych badz rownych x
    for(int x = 1; x <= (m - 1); x++)
    {
        tab_liczniki[x] = tab_liczniki[x] + tab_liczniki[x - 1];
    }

    // wszystkie elementy A[y] zostaja umieszczone na wlasciwych pozycjach w tablicy B
    for(int y = rozmiar_A - 1; y >= 0; y--)
    {
        B[tab_liczniki[A[y]] - 1] = A[y];
        tab_liczniki[A[y]] = tab_liczniki[A[y]] - 1;
    }

    // przepisanie elementow z tablicy B[] do tablicy A[]
    for(int i = 0; i < rozmiar_A; i++)
    {
        A[i] = B[i];
    }
}
/***********************************************************************/
void sortowanie_kubelkowe_int(int *A, int rozmiar_A, int m)
{
    int tab_kubelki[m]; // tablica kubelkow

    // zerowanie tablicy kubelkow
    for(int i = 0; i <= (m - 1); i++)
    {
        tab_kubelki[i] = 0;
    }

    // po tej petli kubelki beda zawieraly liczbe wystapien
    // kazdej z mozliwych wartosci
    for(int j = 0; j < rozmiar_A; j++)
    {
        tab_kubelki[A[j]] = tab_kubelki[A[j]] + 1;
    }

    // wpisanie do tablicy A numerow kubelkow roznych od zera
    // tyle samo razy, ile wynosi ich zawartosc; tablica A
    // bedzie posortowana
    int k = 0;
    for(int l = 0; l <= (m - 1); l++)
    {
        while(tab_kubelki[l] != 0)
        {
            tab_kubelki[l] = tab_kubelki[l] - 1;
            A[k] = l;
            k = k + 1;
        }
    }
}
/***********************************************************************/
void test_inty()
{
    cout << "POROWNANIE SORTOWAN DLA LICZB CALKOWITYCH: " << endl;
    cout << "===============================================================================" << endl;
    const int MAX_ORDER = 7;
    const int m = pow(10, 5);

    for(int o = 1; o <= MAX_ORDER; o++)
    {
        const int n = (int)pow(10, o);
        int *tab_Z = new int[n];
        int *tab_KI = new int[n];
        Kopiec_binarny<int> KB_I;
        for(int i = 0; i < n; i++)
        {
            tab_Z[i] = ((rand() << 15) + rand()) % m;
            tab_KI[i] = tab_Z[i];
        }
        KB_I.dodaj_tablice(tab_Z, n, 'D', KB_I);
        clock_t t5 = clock();
        sortowanie_kubelkowe_int(tab_KI, n, m);
        clock_t t6 = clock();

        double t_kubelkowe = (t6 - t5) / double(CLOCKS_PER_SEC);
        cout << "KUBELKOWE:  Rzad wielkosci: 10^" << o << ": " << t_kubelkowe << "s. ";
        cout << "Czas na 1 element: " << t_kubelkowe / n << "s.   ";

        clock_t t3 = clock();
        KB_I.sortowanie_przez_kopcowanie(KB_I, 'D');
        clock_t t4 = clock();

        double t_kopcowanie = (t4 - t3) / double(CLOCKS_PER_SEC);
        cout << "\nKOPCOWANIE: Rzad wielkosci: 10^" << o << ": " << t_kopcowanie << "s. ";
        cout << "Czas na 1 element: " << t_kopcowanie / n << "s.   ";


        clock_t t1 = clock();
        sortowanie_przez_zliczanie(tab_Z, n, m);
        clock_t t2 = clock();

        double t_zliczanie = (t2 - t1) / double(CLOCKS_PER_SEC);
        cout << "\nZLICZANIE:  Rzad wielkosci: 10^" << o << ": " << t_zliczanie << "s. ";
        cout << "Czas na 1 element: " << t_zliczanie / n << "s.   ";
        //<< " x = : " << rownosc_dwoch_tablic(tab_Z, KB_I, n) << "\n";
        cout << endl;
        for(int i = 0; i < 20; i++)
            cout << tab_KI[i] << " ";

        cout << endl;
        KB_I.wyswietl_kopiec(KB_I, 20);

        cout << endl;
        for(int i = 0; i < 20; i++)
            cout << tab_Z[i] << " ";

        cout << "\n==========================================================" << endl;

        delete [] tab_KI;
        delete [] tab_Z;
        KB_I.czyszczenie_kopca(KB_I);
    }
}
/**********************************************************************************************/
void test_rzeczywiste()
{
    cout << "SORTOWANIE PRZEZ KOPCOWANIE DLA LICZB RZECZYWISTYCH: " << endl;
    cout << "===============================================================================" << endl;
    const int MAX_ORDER = 7;
    const double m_double = (double)pow(2, 30);

    for(int o = 1; o <= MAX_ORDER; o++)
    {
        const int n = (int)pow(10, o);
        double *tab_KD = new double[n];
        Kopiec_binarny<double> KB_D;
        for(int i = 0; i < n; i++)
        {
            tab_KD[i] = ((rand() << 15) + rand()) / m_double;
            //KB_D.dodaj_element(tab_KD[i], KB_D);
        }
        KB_D.dodaj_tablice(tab_KD, n, 'D', KB_D);
//        clock_t t5 = clock();
//        sortowanie_kubelkowe_T(tab_KD, n, m_double);
//        clock_t t6 = clock();
//
//        double t_kubelkowe = (t6 - t5) / double(CLOCKS_PER_SEC);
//        cout << "KUBELKOWE:  Rzad wielkosci: 10^" << o << ": " << t_kubelkowe << "s. ";
//        cout << "Czas na 1 element: " << t_kubelkowe / n << "s.   ";

        clock_t t3 = clock();
        KB_D.sortowanie_przez_kopcowanie(KB_D, 'D');
        clock_t t4 = clock();

        double t_kopcowanie = (t4 - t3) / double(CLOCKS_PER_SEC);
        cout << "KOPCOWANIE: Rzad wielkosci: 10^" << o << ": " << t_kopcowanie << "s. ";
        //cout << "Czas na 1 element: " << t_kopcowanie / n << "s.   ";

//        cout << endl;
//        for(int i = 0; i < 10; i++)
//            cout << tab_KD[i] << " ";

        cout << endl;
        KB_D.wyswietl_kopiec(KB_D, 20);

        cout << "\n==========================================================" << endl;

        delete [] tab_KD;
        KB_D.czyszczenie_kopca(KB_D);
    }
}
/**********************************************************************************************/
int main()
{
    srand(time(NULL));
    test_inty();
    test_rzeczywiste();
    return 0;
}

