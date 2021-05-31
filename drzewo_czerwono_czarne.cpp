#include <iostream>
#include <ctime>
#include <cmath>
//#include <iomanip>
using namespace std;
/***********************************************************/
template <typename T>
class DCC // klasa opisujaca DCC
{
    /**********************************************/
    class Wezel_DCC // klasa wezla DCC
    {
    public:
        Wezel_DCC *rodzic;
        Wezel_DCC *lewy_potomek;
        Wezel_DCC *prawy_potomek;
        char kolor;
        T klucz;
        int indeks = 0; // po to aby uniknac wyswietlania adresow z pamieci
        int wysokosc_wezla = 1;
    };
    /***********************************************/
    Wezel_DCC straznik; // wezel straznika
    void rotacja_w_lewo(Wezel_DCC *A); // rotacja DCC w lewo wzgledem wybranego wezla
    void rotacja_w_prawo(Wezel_DCC *A); // rotacja DCC w prawo wzgledem wybranego wezla
    /***********************************************/
public:
    /***********************************************/
    Wezel_DCC *korzen; // korzen DCC
    int liczba_trafien = 0; // trafienia przy wyszukiwaniu
    int liczba_pudel = 0; // pudla przy wyszukiwaniu
    int wysokosc_DCC = 0;
    int liczba_wezlow_DCC = 0;
    /***********************************************/
    DCC(); // konstruktor klasy
    void wypisz_IO_DCC(Wezel_DCC *wsk, int ile); // porzadek inorder, ile okresla liczbe wypisywanych poczatkowych wezlow
    void wypisz_PO_DCC(Wezel_DCC *wsk, int ile); // porzadek preorder
    void wyczysc_DCC(Wezel_DCC *wsk); // czysci drzewo
    int wypisz_wysokosc_DCC(Wezel_DCC *wsk); // wysokosc drzewa
    void wypisz_DCC(Wezel_DCC *wsk, int ile); // tekstowa reprezentacja drzewa
    void dodaj_wezel(T k, int i); // dodaje nowy wezel o kluczu k i indeksie i do drzewa
    Wezel_DCC *wyszukaj_wezel(T k) // wyszukuje wezel o kluczu k
    // zwraca wskaznik na odnaleziony element lub nullptr w przypadku nietrafienia
    {
        Wezel_DCC *wsk;

        wsk = korzen; // rozpoczecie przeszukiwania od korzenia
        while((wsk != &straznik) && (wsk->klucz != k))
        {
            if(k < wsk->klucz) // jezeli podany klucz jest mniejszy niz wskazywany
            {
                wsk = wsk->lewy_potomek; // przeszukuj lewe poddrzewo
            }
            else // jezeli jest wiekszy lub rowny
            {
                wsk = wsk->prawy_potomek; // przeszukuj prawe poddrzewo
            }
        }
        if(wsk == &straznik) // jezeli elementu nie znaleziono
        {
            liczba_pudel++;
            return nullptr;
        }
        else
        {
            liczba_trafien++;
            return wsk;
        }
    }
};
/****************************************************************/
template <typename T>
void DCC<T>::rotacja_w_lewo(Wezel_DCC *A)
{
    // wezel A moze byc dowolnym wezlem w drzewie, ktorego
    // prawy potomek rozni sie od straznika
    Wezel_DCC *B;
    Wezel_DCC *wsk;

    B = A->prawy_potomek; // inicjalizacja wezla B
    if(B != &straznik)
    {
        wsk = A->rodzic; // wsk jest ustawiany na rodzica wezla A
        // zamiana lewego poddrzewa wezla B na prawe poddrzewo wezla A
        A->prawy_potomek = B->lewy_potomek;
        if(A->prawy_potomek != &straznik) // jezeli prawy potomek jest rozny od straznika
        {
            A->prawy_potomek->rodzic = A; // A staje sie nowym korzeniem poddrzewa
        }

        B->lewy_potomek = A; // A staje sie lewym potomkiem wezla B
        B->rodzic = wsk; // ustawienie rodzica wezla B na wsk
        A->rodzic = B; // wezel B jest rodzicem wezla A

        if(wsk != &straznik) // jezeli wsk jest rozne od straznika
        {
            if(wsk->lewy_potomek == A) // jezeli lewy potomek wsk to jest A
            {
                wsk->lewy_potomek = B; // to B staje sie lewym potomkiem wsk
            }
            else // w przeciwnym przypadku
            {
                wsk->prawy_potomek = B; // B staje sie prawym potomkiem wsk
            }
        }
        else // jezeli rodzic wezla B jest straznikiem
        {
            korzen = B; // to wezel B staje sie korzeniem
        }
    }
}
/***************************************************************/
template <typename T>
void DCC<T>::rotacja_w_prawo(Wezel_DCC *A)
{
    // dzialanie "lustrzane" w porownaniu do rotacji w lewo
    Wezel_DCC *B;
    Wezel_DCC *wsk;

    B = A->lewy_potomek;
    if(B != &straznik)
    {
        wsk = A->rodzic;
        A->lewy_potomek = B->prawy_potomek;
        if(A->lewy_potomek != &straznik)
        {
            A->lewy_potomek->rodzic = A;
        }

        B->prawy_potomek = A;
        B->rodzic = wsk;
        A->rodzic = B;

        if(wsk != &straznik)
        {
            if(wsk->lewy_potomek == A)
            {
                wsk->lewy_potomek = B;
            }
            else
            {
                wsk->prawy_potomek = B;
            }
        }
        else
        {
            korzen = B;
        }
    }
}
/***************************************************************/
template <typename T>
DCC<T>::DCC()
{
    korzen = &straznik;
    straznik.rodzic = &straznik;
    straznik.prawy_potomek = &straznik;
    straznik.lewy_potomek = &straznik;
    straznik.kolor = 'B'; // inicjowanie straznika
}
/*************************************************************/
template <typename T>
void DCC<T>::wypisz_IO_DCC(Wezel_DCC *wsk, int ile)
{
    if(wsk != &straznik)
    {
        wypisz_IO_DCC(wsk->lewy_potomek, ile);
        static int tmp = 0;
        if(tmp < ile)
        {
            cout << wsk->indeks << " ";
            tmp++;
        }
        wypisz_IO_DCC(wsk->prawy_potomek, ile);
    }
}
/****************************************************************/
template <typename T>
void DCC<T>::wypisz_PO_DCC(Wezel_DCC *wsk, int ile)
{
    if(wsk != &straznik)
    {
        static int tmp = 0;
        if(tmp < ile)
        {
            cout << wsk->indeks << " ";
            tmp++;
        }
        wypisz_PO_DCC(wsk->lewy_potomek, ile);
        wypisz_PO_DCC(wsk->prawy_potomek, ile);
    }
}
/*************************************************************/
template <typename T>
void DCC<T>::wyczysc_DCC(Wezel_DCC *wsk)
{
    if(wsk != &straznik)
    {
        wyczysc_DCC(wsk->lewy_potomek); // usuniecie lewego poddrzewa
        wyczysc_DCC(wsk->prawy_potomek); // usuniecie prawego poddrzewa
        delete wsk; // usuniecie samego wezla
    }
}
/*************************************************************/
template <typename T>
int DCC<T>::wypisz_wysokosc_DCC(Wezel_DCC *wsk)
{
    if(wsk != &straznik)
    {
        // jezeli przetwarzany wezel ma lewe poddrzewo
        if(wsk->lewy_potomek)
        {
            // zwiekszenie o 1 wysokosci lewego poddrzewa
            wsk->lewy_potomek->wysokosc_wezla = wsk->wysokosc_wezla + 1;
        }
        // ma prawe poddrzewo
        if(wsk->prawy_potomek)
        {
            wsk->prawy_potomek->wysokosc_wezla = wsk->wysokosc_wezla + 1;
        }
        // jezeli wysokosc wezla jest wieksza niz wysokosc drzewa
        if(wsk->wysokosc_wezla > wysokosc_DCC)
        {
            // do wysokosci drzewa zostaje wpisana wysokosc wezla
            wysokosc_DCC = wsk->wysokosc_wezla;
        }
        wypisz_wysokosc_DCC(wsk->lewy_potomek); // przetworzenie lewego poddrzewa
        wypisz_wysokosc_DCC(wsk->prawy_potomek); // przetworzenie prawego poddrzewa
        return wysokosc_DCC;
    }
}
/***************************************************************/
template <typename T>
void DCC<T>::wypisz_DCC(Wezel_DCC *wsk, int ile)
{
    static int tmp = 0;
    if(tmp < 1)
    {
        cout << "Liczba wezlow: " << liczba_wezlow_DCC << endl;
        cout << "Rozmiar DCC: " << (sizeof(Wezel_DCC) * liczba_wezlow_DCC) + (sizeof(DCC) - sizeof(Wezel_DCC)) << " bajtow. " << endl;
        tmp++;
    }
    if(wsk != &straznik)
    {
        static int tmp = 0;
        if(tmp < ile)
        {
            cout << "kolor: " << wsk->kolor << " indeks: " << wsk->indeks << " indeks rodzica: " << wsk->rodzic->indeks;
            cout << " indeks lp: " << wsk->lewy_potomek->indeks << " indeks pp: " << wsk->prawy_potomek->indeks << endl;
            tmp++;
        }
        wypisz_DCC(wsk->lewy_potomek, ile);
        wypisz_DCC(wsk->prawy_potomek, ile);
    }
}
/*******************************************************************/
template <typename T>
void DCC<T>::dodaj_wezel(T k, int i)
{
    Wezel_DCC *N; // nowy wezel
    Wezel_DCC *wujek_N; // wujek nowego wezla
    N = new Wezel_DCC;  // tworzenie nowego wezla
    liczba_wezlow_DCC++; // inkrementacja liczby wezlow
    // inicjalizowanie danych nowego wezla
    N->prawy_potomek = &straznik;
    N->lewy_potomek = &straznik;
    N->rodzic = korzen;
    N->klucz = k;
    N->indeks = i;

    // jezeli nowy wezel nie ma rodzica
    if(N->rodzic == &straznik)
    {
        korzen = N; // to nowy wezel staje sie korzeniem
    }
    while(true)
    {
        if(k < N->rodzic->klucz) // jezeli klucz nowego jest mniejszy niz klucz rodzica
        {
            if(N->rodzic->lewy_potomek == &straznik) // jezeli rodzic nowego nie ma lewego potomka
            {
                N->rodzic->lewy_potomek = N; //  nowy zastepuje lewego potomka
                break;
            }
            N->rodzic = N->rodzic->lewy_potomek;
        }
        else // jezeli klucz nowego jest wiekszy lub rowny kluczowi rodzica
        {
            if(N->rodzic->prawy_potomek == &straznik) // -------------------------- prawego ------
            {
                N->rodzic->prawy_potomek = N; // nowy zastepuje prawego potomka
                break;
            }
            N->rodzic = N->rodzic->prawy_potomek;
        }
    }
    N->kolor = 'R'; // wezel kolorujemy na czerwono
    while((N != korzen) && (N->rodzic->kolor == 'R'))
    {
        if(N->rodzic == N->rodzic->rodzic->lewy_potomek)
        {
            wujek_N = N->rodzic->rodzic->prawy_potomek; // inicjalizacja wujka nowego wezla

            // Przypadek 1: Wujek nowego wezla jest czerwony
            if(wujek_N->kolor == 'R')
            {
                N->rodzic->kolor = 'B'; // ojciec nowego wezla jest kolorowany na czarno
                wujek_N->kolor = 'B'; // wujek nowego wezla jest kolorowany na czarno
                N->rodzic->rodzic->kolor = 'R'; // dziadek nowego wezla jest kolorowany na czerwono
                N = N->rodzic->rodzic; // za nowe N zostaje przyjety dziadek
                continue; // kontynuowanie petli
            }

            // Przypadek 2: Wujek nowego wezla jest czarny,
            // a nowy wezel jest prawym potomkiem rodzica
            if(N == N->rodzic->prawy_potomek)
            {
                N = N->rodzic; // za nowy wezel przyjmuje sie jego rodzica
                rotacja_w_lewo(N); // rotacja w lewo wzgledem nowego wezla
            }

            // Przypadek 3: Wujek nowego wezla jest czarny,
            // a nowy wezel jest lewym potomkiem rodzica

            // zmiana kolorow
            N->rodzic->kolor = 'B'; // zmiana koloru ojca
            N->rodzic->rodzic->kolor = 'R'; // zmiana koloru dziadka
            rotacja_w_prawo(N->rodzic->rodzic); // rotacja w prawo wzgledem dziadka
            break; // wyjscie z petli
        }
        else // Przypadki lustrzane
        {
            wujek_N = N->rodzic->rodzic->lewy_potomek;

            // Przypadek 1
            if(wujek_N->kolor == 'R')
            {
                N->rodzic->kolor = 'B';
                wujek_N->kolor = 'B';
                N->rodzic->rodzic->kolor = 'R';
                N = N->rodzic->rodzic;
                continue;
            }

            // Przypadek 2
            if(N == N->rodzic->lewy_potomek)
            {
                N = N->rodzic;
                rotacja_w_prawo(N);
            }

            // Przypadek 3
            N->rodzic->kolor = 'B';
            N->rodzic->rodzic->kolor = 'R';
            rotacja_w_lewo(N->rodzic->rodzic);
            break;
        }
    }
    korzen->kolor = 'B'; // kolorowanie korzenia na czarno
}
/****************************************************************/
int main()
{
    //cout << setprecision(10);

    srand(time(NULL));
    for(int i = 0; i < 8; i++)
    {
        DCC<int> RBT_I;
        const int n = pow(10, i);
        clock_t t1 = clock();
        for(int i = 0; i < n; i++)
        {
            RBT_I.dodaj_wezel(((rand() << 15) + rand() + 1), (rand() << 15) + rand() + 1);
        }
        clock_t t2 = clock();
        cout << "\nWysokosc drzewa o 10^" << i << " elementach: "  << RBT_I.wypisz_wysokosc_DCC(RBT_I.korzen);
        double czas_dodawania = (t2 - t1) / double(CLOCKS_PER_SEC);
        cout << "\nDodanie 10^" << i << " elementow: " << czas_dodawania << "s. "
             << "Sredni czas na dodanie jednego elementu: " << czas_dodawania / n << "s." << endl;

        clock_t t3 = clock();
        for(int i = 0; i < 10000; i++)
        {
            RBT_I.wyszukaj_wezel(((rand() << 15) + rand() + 1));
        }
        clock_t t4 = clock();
        double czas_wyszukiwania = (t4 - t3) / double(CLOCKS_PER_SEC);
        cout << "Wyszukiwanie 10^" << i << " elementow: " << czas_wyszukiwania << "s. "
             << "Sredni czas na wyszukanie jednego elementu: " << czas_wyszukiwania / n << "s." << endl;
        cout << "Liczba trafien: " << RBT_I.liczba_trafien << endl;
        cout << "Liczba pudel: " << RBT_I.liczba_pudel << endl;

        /*
        clock_t t5 = clock();
        RBT_I.wypisz_PO_DCC(RBT_I.korzen, 0);
        clock_t t6 = clock();
        double czas_preorder = (t6 - t5) / double(CLOCKS_PER_SEC);
        cout << "Przejscie pre-order drzewa o 10^" << i << " elementow: " << czas_preorder << "s. "
             << "Sredni czas na przejscie jednego elementu: " << czas_preorder / n << "s." << endl;

        clock_t t7 = clock();
        RBT_I.wypisz_IO_DCC(RBT_I.korzen, 0);
        clock_t t8 = clock();
        double czas_inorder = (t8 - t7) / double(CLOCKS_PER_SEC);
        cout << "Przejscie in-order drzewa o 10^" << i << " elementow: " << czas_inorder << "s. "
             << "Sredni czas na przejscie jednego elementu: " << czas_inorder / n << "s." << endl;

        clock_t t9 = clock();
        RBT_I.wyczysc_DCC(RBT_I.korzen);
        clock_t t10 = clock();
        double czas_usuniecia = (t10 - t9) / double(CLOCKS_PER_SEC);
        cout << "Usuniecie drzewa o 10^" << i << " elementow: " << czas_usuniecia << "s. "
             << "Sredni czas na usuniecie jednego elementu: " << czas_usuniecia / n << "s." << endl;
        */
    }

    DCC<int> RBT;
    RBT.dodaj_wezel(55,55);
    RBT.dodaj_wezel(69,69);
    RBT.dodaj_wezel(62,62);
    RBT.dodaj_wezel(57,57);
    RBT.dodaj_wezel(35,35);
    RBT.dodaj_wezel(83,83);
    RBT.dodaj_wezel(72,72);
    RBT.dodaj_wezel(74,74);
//    RBT.dodaj_wezel(16,16);
//    RBT.dodaj_wezel(19,19);
//    RBT.dodaj_wezel(23,23);
//    RBT.dodaj_wezel(28,28);
//    RBT.dodaj_wezel(38,38);
//    RBT.dodaj_wezel(7,7);
//    RBT.dodaj_wezel(12,12);
//    RBT.dodaj_wezel(15,15);
//    RBT.dodaj_wezel(20,20);
//    RBT.dodaj_wezel(35,35);
//    RBT.dodaj_wezel(39,39);
//    RBT.dodaj_wezel(3,3);
    RBT.wypisz_DCC(RBT.korzen, 20);
    cout << "\nWysokosc DCC: " << RBT.wypisz_wysokosc_DCC(RBT.korzen);
    cout << "\nPorzadek inorder:" << endl;
    RBT.wypisz_IO_DCC(RBT.korzen, 20);
    cout << "\nPorzadek preorder:" << endl;
    RBT.wypisz_PO_DCC(RBT.korzen, 20);
    cout << "\nWyszukanie wezla o kluczu 7: " << endl;
    RBT.wyszukaj_wezel(7);
    cout << "Liczba trafien: " << RBT.liczba_trafien << endl;
    cout << "Liczba pudel: " << RBT.liczba_pudel << endl;
    RBT.wyczysc_DCC(RBT.korzen);

    // drzewo powstale z dodania elementow o kluczach z przedzialu 1 - 1000
    // 1 2 3 4 5 ...

//    DCC<int> RBT;
//    for(int i = 1; i < 1001; i++)
//    {
//        RBT.dodaj_wezel(i, i);
//    }
//    RBT.wypisz_DCC(RBT.korzen, 0);
//    cout << "\nPorzadek preorder: " << endl;
//    RBT.wypisz_PO_DCC(RBT.korzen, 0);
//    cout << "\nPorzadek inorder: " << endl;
//    RBT.wypisz_IO_DCC(RBT.korzen, 100);
//    cout << "\nWysokosc DCC: " << RBT.wypisz_wysokosc_DCC(RBT.korzen);

    return 0;
}
