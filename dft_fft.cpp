#include <iostream>
#include <math.h>
#include <complex>
#include <cmath>
#include <ctime>
#include <stdio.h>
#define _USE_MATH_DEFINES
#define M_PI 3.14159265358979323846
using namespace std;
complex<double> jednostka_urojona(0, 1);
/*********************************************************/
// definicyjne DFT
complex<double> *DFT(double *tablica, int rozmiar_tablicy)
{
    complex<double> *tablica_wspolczynnikow = new complex<double>[rozmiar_tablicy];
    for(int n = 0; n < rozmiar_tablicy; n++)
    {
        for(int k = 0; k < rozmiar_tablicy; k++)
        {
            tablica_wspolczynnikow[k] += polar(tablica[n], -2*M_PI*k*n/(rozmiar_tablicy));
        }
    }
    return tablica_wspolczynnikow;
}
/*********************************************************/
// szybkie FFT
complex<double> *FFT(double *tablica, int rozmiar_tablicy)
{
    if(rozmiar_tablicy <= 1)
    {
        complex<double> *c0 = new complex<double>(tablica[0], 0);
        return c0;
    }
    complex<double> *wspolczynniki = new complex<double>[rozmiar_tablicy];
    double *parzyste = new double[rozmiar_tablicy / 2];
    double *nieparzyste = new double[rozmiar_tablicy / 2];
    int j = 0;
    for(int i = 0; i < rozmiar_tablicy; i = i + 2)
    {
        parzyste[j] = tablica[i];
        j++;
    }
    j = 0;
    for(int i = 1; i < rozmiar_tablicy; i = i + 2)
    {
        nieparzyste[j] = tablica[i];
        j++;
    }
    complex<double> *E = new complex<double>[rozmiar_tablicy / 2];
    complex<double> *O = new complex<double>[rozmiar_tablicy / 2];
    E = FFT(parzyste, rozmiar_tablicy / 2);
    O = FFT(nieparzyste, rozmiar_tablicy / 2);

    for(int k = 0; k < (rozmiar_tablicy / 2); k++)
    {
        wspolczynniki[k] = E[k] + polar(1.0, -2 * M_PI * k / rozmiar_tablicy) * O[k];
        wspolczynniki[k + rozmiar_tablicy / 2] = E[k] - polar(1.0, -2 * M_PI * k / rozmiar_tablicy) * O[k];
    }
    return wspolczynniki;
}
/*********************************************************************/
double blad(complex<double> *DFT, complex<double> *FFT, int rozmiar)
{
    complex<double> suma(0, 0);
    for(int k = 0; k < rozmiar; k++)
    {
        suma = suma + abs(DFT[k] - FFT[k]);
    }
    complex<double> jeden(1, 0);
    complex<double> rozmiar_zespolony(rozmiar, 0);
    complex<double> blad_ostateczny = (jeden / rozmiar_zespolony) * suma;
    return blad_ostateczny.real();
}
/*********************************************************************/
int main(void)
{
    const int MAX_ORDER = 3; // maksymalny rzad wielkosci danych (w ramach bazy 2)
    const bool PRINT_COEFS = true; // przelacznik do ewentualnego wypisu na ekran rezultatow DFT, FFT

    for(int o = 1; o <= MAX_ORDER; o++)
    {
        const int N = 1 << o; // rozmiar problemu (potega dwojki - przesuniecie bitowe w lewo)
        printf("N: %i\n", N);

        double *f = new double[N];
        for(int n = 0; n < N; n++)
        {
            f[n] = double(n) / double(N); // przykladowe dane (tu akurat: probki funkcji liniowej)
        }

        clock_t t1 = clock();
        complex<double> *cDFT = DFT(f, N);
        clock_t t2 = clock();
        double dft_time = (t2 - t1) / (double)CLOCKS_PER_SEC * 1000.0;
        printf("DFT time [ms]: %f\n", dft_time);

        t1 = clock();
        complex<double> *cFFT = FFT(f, N);
        t2 = clock();
        double fft_time = (t2 - t1) / (double)CLOCKS_PER_SEC * 1000.0;
        printf("FFT time [ms]: %f\n", fft_time);

        printf("mean error: %f\n", blad(cDFT, cFFT, N));

        if(PRINT_COEFS)
        {
            cout << "Od lewej: Wspolczynniki DFT, wspolczynniki FFT:\n";
            for(int k = 0; k < N; k++)
            {
                cout << cDFT[k] << "\t" << cFFT[k] << endl;
            }
        }
        printf("----------\n");
        delete [] f, cDFT, cFFT;
    }

    return 0;
//    int N = 1;
//    double tablica_probek[N];
//    tablica_probek[0] = 1.0;
////    tablica_probek[1] = 1.0;
////    tablica_probek[2] = 1.0;
////    tablica_probek[3] = 1.0;
////    tablica_probek[4] = 0.0;
////    tablica_probek[5] = 0.0;
////    tablica_probek[6] = 0.0;
////    tablica_probek[7] = 0.0;
//    for(int n = 0; n < N; n++)
//    {
//        //cout << sin(double(n) / double(N)) << endl;
//        tablica_probek[n] = (double(n + 5) / double(N));
//    }
//    cout << tablica_probek[0] << endl;
//
//    complex<double> *tab_wsp_DFT = DFT(tablica_probek, N);
//    cout << "DFT" << endl;
//    for(int i = 0; i < N; i++)
//    {
//        cout << tab_wsp_DFT[i] << endl;
//    }
//
//    complex<double> *tab_wsp_FFT = FFT(tablica_probek, N);
//    cout << "FFT" << endl;
//    for(int i = 0; i < N; i++)
//    {
//        cout << tab_wsp_FFT[i] << endl;
//    }
//
//    cout << "Blad: " << blad(tab_wsp_DFT, tab_wsp_FFT, N);


//    return 0;
}
