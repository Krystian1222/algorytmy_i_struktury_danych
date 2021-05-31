#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
using namespace std;
int licznik_find = 0; // licznik operacji find
class Krawedz_grafu;
class Union_Find;
class Wezel_grafu;
void sortowanie_przez_kopcowanie(Krawedz_grafu kraw[], int liczba_obiektow);
/*******************************************************************/
class Wezel_grafu
{
public:
    float wsp_x;
    float wsp_y;
    Wezel_grafu(float x = 0, float y = 0)
    {
        wsp_x = x;
        wsp_y = y;
    }
    void ustawianie_wezla(float x, float y);
};
/*******************************************************************/
void Wezel_grafu::ustawianie_wezla(float x, float y)
{
    wsp_x = x;
    wsp_y = y;
}
/*******************************************************************/
class Krawedz_grafu
{
public:
    int w_i;
    int w_j;
    float waga;
    Krawedz_grafu();
    Krawedz_grafu(int wezel_i, int wezel_j, float w);
    void ustawianie_krawedzi(int wezel_i, int wezel_j, float w);
    bool operator<(Krawedz_grafu a);
    float operator-(Krawedz_grafu a);
    bool operator>(Krawedz_grafu a);
    void operator=(float a);
};
/*******************************************************************/
Krawedz_grafu::Krawedz_grafu()
{
    w_i = 0;
    w_j = 0;
    waga = 1;
}
/*******************************************************************/
Krawedz_grafu::Krawedz_grafu(int wezel_i, int wezel_j, float w)
{
    w_i = wezel_i;
    w_j = wezel_j;
    waga = w;
}
/*******************************************************************/
void Krawedz_grafu::ustawianie_krawedzi(int wezel_i, int wezel_j, float w)
{
    w_i = wezel_i;
    w_j = wezel_j;
    waga = w;
}
/*******************************************************************/
bool Krawedz_grafu::operator<(Krawedz_grafu a)
{
    if(waga < a.waga)
        return true;
    return false;
}
/*******************************************************************/
float Krawedz_grafu::operator-(Krawedz_grafu a)
{
    return waga - a.waga;
}
/*******************************************************************/
bool Krawedz_grafu::operator>(Krawedz_grafu a)
{
    if(waga > a.waga)
        return true;
    return false;
}
/*******************************************************************/
void Krawedz_grafu::operator=(float a)
{
    waga = a;
}
/*******************************************************************/
class Union_Find
{
public:
    int liczba_wezlow;
    int *rodzic; // indeksy rodzicow
    int *ranga; // gorne ograniczenie na wysokosc drzewa
    Union_Find(int l_wezlow);
    int optymalny_find(int i); // z kompresja sciezki
    int nieoptymalny_find(int i);
    void polacz_po_rangach(int i_root, int j_root);
    void polacz_normalnie(int i_root, int j_root);
};
/*******************************************************************/
Union_Find::Union_Find(int l_wezlow)
{
    liczba_wezlow = l_wezlow;
    rodzic = new int[liczba_wezlow];
    ranga = new int[liczba_wezlow];

    for(int i = 0; i < liczba_wezlow; i++)
    {
        rodzic[i] = i;
        ranga[i] = 0;
    }
}
/*******************************************************************/
Union_Find::optymalny_find(int i)
{
    licznik_find++;
    if(i == rodzic[i])
    {
        return i;
    }
    rodzic[i] = optymalny_find(rodzic[i]);
    //int f = optymalny_find(rodzic[i]);
    //if (f != rodzic[i])
        //rodzic[i] = f;
    return rodzic[i];
}
/*******************************************************************/
Union_Find::nieoptymalny_find(int i)
{
    licznik_find++;
    if(i == rodzic[i])
    {
        return i;
    }
    return nieoptymalny_find(rodzic[i]);
}
/*******************************************************************/
void Union_Find::polacz_po_rangach(int i_root, int j_root)
{
    if(ranga[i_root] < ranga[j_root])
    {
        rodzic[i_root] = j_root;
    }
    else if(ranga[j_root] < ranga[i_root])
    {
        rodzic[j_root] = i_root;
    }
    else
    {
        rodzic[i_root] = j_root;
        ranga[j_root]++;
    }
}
/*******************************************************************/
void Union_Find::polacz_normalnie(int i_root, int j_root)
{
    rodzic[j_root] = i_root;
    ranga[i_root]++;
}
/*******************************************************************/
class Graf
{
public:
    Wezel_grafu *tab_wezly; // tablica na wezly
    Krawedz_grafu *tab_kraw; // tablica na krawedzie
    int liczba_wezlow = 0;
    int liczba_krawedzi = 0;

    Graf(int l_w, Wezel_grafu *tab_w);
    Graf(int i); // do odczytu pliku
    void sortowanie_krawedzi();
};
/***********************************************************************/
Graf::Graf(int l_w, Wezel_grafu *tab_w)
{
    liczba_wezlow = l_w;
    tab_wezly = tab_w;
}
/***********************************************************************/
Graf::Graf(int i)
{
    string linia; // pojedyncza linia
    fstream FPTR; // uchwyt do pliku File PoinTeR
    if(i == 1)
    {
        FPTR.open("g1.txt", ios::in); // otwarcie w trybie do odczytu
    }
    else if(i == 2)
    {
        FPTR.open("g2.txt", ios::in);
    }
    else if(i == 3)
    {
        FPTR.open("g3.txt", ios::in);
    }
    else
    {
        cout << "Blad otwarcia pliku." << endl;
    }

    if(FPTR.good() == true)
    {
            getline(FPTR, linia); // pierwsza linia - liczba wezlow w grafie
            liczba_wezlow = stoi(linia);
            tab_wezly = new Wezel_grafu[liczba_wezlow];

            for(int i = 0; i < liczba_wezlow; i++)
            {
                getline(FPTR, linia);

                float x_arg = 0;
                float y_arg = 0;
                string slowo = "";

                for(auto z : linia)
                {
                    if(z == ' ')
                    {
                        x_arg = stof(slowo);
                        slowo = "";
                    }
                    else
                    {
                        slowo = slowo + z;
                    }
                }
                y_arg = stof(slowo);
                tab_wezly[i].ustawianie_wezla(x_arg, y_arg);
            }

            getline(FPTR, linia); // wczytanie z pliku liczby krawedzi
            liczba_krawedzi = stoi(linia);
            tab_kraw = new Krawedz_grafu[liczba_krawedzi];

            for(int i = 0; i < liczba_krawedzi; i++)
            {
                int tab[] = {0, 0};
                getline(FPTR, linia);
                string slowo = "";
                float waga = 1;
                int tymczasowy = 0;


                for(auto z : linia) // podzial linii
                {
                    if(z == ' ')
                    {
                        int b = stoi(slowo);
                        tab[tymczasowy] = b;
                        slowo = "";
                        tymczasowy++;
                    }
                    else
                    {
                        slowo = slowo + z;
                    }
                }
                waga = stof(slowo);
                tab_kraw[i].ustawianie_krawedzi(tab[0], tab[1], waga);
            }
            FPTR.close();
    }
    else
    {
        liczba_wezlow = 0;
        liczba_krawedzi = 0;
        cout << "Blad otwarcia pliku." << endl;
    }
}
/***********************************************************************/
void Graf::sortowanie_krawedzi()
{
    sortowanie_przez_kopcowanie(tab_kraw, liczba_krawedzi);
}
/***********************************************************************/
float suma_krawedzi(Graf G)
{
    float suma_k = 0;
    for(int i = 0; i < G.liczba_krawedzi; i++)
    {
        suma_k = suma_k + G.tab_kraw[i].waga;
    }
    return suma_k;
}
/***********************************************************************/
void kopcowanie(Krawedz_grafu kraw[], int liczba_obiektow, int indeks)
{
    int najwiekszy = indeks;
    int lewy = 2 * indeks + 1;
    int prawy = 2 * indeks + 2;

    if(lewy < liczba_obiektow && kraw[lewy].waga > kraw[najwiekszy].waga)
    {
        najwiekszy = lewy;
    }
    if((prawy < liczba_obiektow) && (kraw[prawy] > kraw[najwiekszy]))
    {
        najwiekszy = prawy;
    }
    if(najwiekszy != indeks)
    {
        swap(kraw[indeks], kraw[najwiekszy]);
        kopcowanie(kraw, liczba_obiektow, najwiekszy);
    }
}
/***********************************************************************/
void sortowanie_przez_kopcowanie(Krawedz_grafu kraw[], int liczba_obiektow)
{
    for(int i = liczba_obiektow / 2 - 1; i >= 0; i--)
    {
        kopcowanie(kraw, liczba_obiektow, i);
    }
    for(int i = liczba_obiektow - 1; i >= 0; i--)
    {
        swap(kraw[0], kraw[i]);
        kopcowanie(kraw, i, 0);
    }
}
/***************************************************************/
Graf Kruskal_UF_MST(Graf G, int szukanie = 0, int laczenie = 0)
{
    licznik_find = 0;
    Union_Find junion(G.liczba_wezlow);
    Graf MST(G.liczba_wezlow, G.tab_wezly);

    MST.liczba_krawedzi = MST.liczba_wezlow - 1;
    MST.tab_kraw = new Krawedz_grafu[MST.liczba_krawedzi];

    int indeks = 0;

    clock_t t1 = clock();
    G.sortowanie_krawedzi();
    clock_t t2 = clock();

    double czas_sortowania = (t2 - t1) / (double)CLOCKS_PER_SEC;
    cout <<"Czas sortowania krawedzi: "<< czas_sortowania << "s. " << endl;

    if(szukanie == 0 && laczenie == 0)
    {
        t1 = clock();
        for(int i = 0; i < G.liczba_krawedzi - 1; i++)
        {
            int junion_i = junion.nieoptymalny_find(G.tab_kraw[i].w_i);
            int junion_j = junion.nieoptymalny_find(G.tab_kraw[i].w_j);

            if(junion_i != junion_j)
            {
                MST.tab_kraw[indeks] = G.tab_kraw[i];
                junion.polacz_normalnie(junion_i, junion_j);
                indeks += 1;
            }
        }
        t2 = clock();
        double czas_glownej_petli = (t2 - t1) / (double)CLOCKS_PER_SEC;
        cout << "Czas obliczen glownej petli: " << czas_glownej_petli << "s." << endl;
        cout << "Liczba krawedzi wynikowego MST: " << MST.liczba_krawedzi << endl;
        cout << "Laczna waga wynikowego MST: " << suma_krawedzi(MST) << endl;
        cout << "Liczba operacji find: " << licznik_find << endl;
    }

    if(szukanie == 0 && laczenie == 1)
    {
        t1 = clock();
        for(int i = 0; i < G.liczba_krawedzi - 1; i++)
        {
            int junion_i = junion.nieoptymalny_find(G.tab_kraw[i].w_i);
            int junion_j = junion.nieoptymalny_find(G.tab_kraw[i].w_j);

            if(junion_i != junion_j)
            {
                MST.tab_kraw[indeks++] = G.tab_kraw[i];
                junion.polacz_po_rangach(junion_i, junion_j);
            }
        }
        t2 = clock();
        double czas_glownej_petli = (t2 - t1) / (double)CLOCKS_PER_SEC;
        cout << "Czas obliczen glownej petli: " << czas_glownej_petli << "s." << endl;
        cout << "Liczba krawedzi wynikowego MST: " << MST.liczba_krawedzi << endl;
        cout << "Laczna waga wynikowego MST: " << suma_krawedzi(MST) << endl;
        cout << "Liczba operacji find: " << licznik_find << endl;
    }
    if(szukanie == 1 && laczenie == 0)
    {
        t1 = clock();
        for(int i = 0; i < G.liczba_krawedzi - 1; i++)
        {
            int junion_i = junion.optymalny_find(G.tab_kraw[i].w_i);
            int junion_j = junion.optymalny_find(G.tab_kraw[i].w_j);

            if(junion_i != junion_j)
            {
                MST.tab_kraw[indeks++] = G.tab_kraw[i];
                junion.polacz_normalnie(junion_i, junion_j);
            }
        }
        t2 = clock();
        double czas_glownej_petli = (t2 - t1) / (double)CLOCKS_PER_SEC;
        cout << "Czas obliczen glownej petli: " << czas_glownej_petli << "s." << endl;
        cout << "Liczba krawedzi wynikowego MST: " << MST.liczba_krawedzi << endl;
        cout << "Laczna waga wynikowego MST: " << suma_krawedzi(MST) << endl;
        cout << "Liczba operacji find: " << licznik_find << endl;
    }
    if(szukanie == 1 && laczenie == 1)
    {
        t1 = clock();
        for(int i = 0; i < G.liczba_krawedzi - 1; i++)
        {
            int junion_i = junion.optymalny_find(G.tab_kraw[i].w_i);
            int junion_j = junion.optymalny_find(G.tab_kraw[i].w_j);

            if(junion_i != junion_j)
            {
                MST.tab_kraw[indeks++] = G.tab_kraw[i];
                junion.polacz_po_rangach(junion_i, junion_j);
            }
        }
        t2 = clock();
        double czas_glownej_petli = (t2 - t1) / (double)CLOCKS_PER_SEC;
        cout << "Czas obliczen glownej petli: " << czas_glownej_petli << "s." << endl;
        cout << "Liczba krawedzi wynikowego MST: " << MST.liczba_krawedzi << endl;
        cout << "Laczna waga wynikowego MST: " << suma_krawedzi(MST) << endl;
        cout << "Liczba operacji find: " << licznik_find << endl;
    }

    return MST;
}
int main()
{
    cout << "Znajdowanie zwykle i laczenie zwykle: " << endl;
    for(int i = 1; i < 4; i++)
    {
        Graf G(i);
        Graf mst = Kruskal_UF_MST(G, 0, 0);
        cout << endl;
    }
    cout << "=====================================================" << endl;
    cout << "Znajdowanie zwykle i laczenie po rangach: " << endl;
    for(int i = 1; i < 4; i++)
    {
        Graf G(i);
        Graf mst = Kruskal_UF_MST(G, 0, 1);
        cout << endl;
    }
    cout << "=====================================================" << endl;
    cout << "Znajdowanie z kompresja sciezki i laczenie zwykle: " << endl;
    for(int i = 1; i < 4; i++)
    {
        Graf G(i);
        Graf mst = Kruskal_UF_MST(G, 1, 0);
        cout << endl;
    }
    cout << "=====================================================" << endl;
    cout << "Znajdowanie z kompresja sciezki i laczenie po rangach: " << endl;
    for(int i = 1; i < 4; i++)
    {
        Graf G(i);
        Graf mst = Kruskal_UF_MST(G, 1, 1);
        cout << endl;
    }
    return 0;
}
