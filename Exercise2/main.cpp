//ESERCIZIO 2
#include <iostream>
#include <fstream> //libreria per file
#include <sstream> //libreria per manipolare le stringhe
#include <iomanip> //libreria per manipolare la precisione dei dati
#include "Utils.hpp"

using namespace std;

int main()
{
    string inputFileName = "data.txt"; //nome del file di input
    size_t n = 0; //inizializzo a zero il numero di asset
    double S = 0; //inizializzo a zero la somma totale da investire
    double* w = nullptr; //inizializzo a null il puntatore al vettore w
    double* r = nullptr; //inizializzo a null il puntatore al vettore r

    if (!importDatas(inputFileName, n, S, w, r))
    {
        cerr << "Qualcosa è andato storto nella fase di importazione dati" << endl;
        return -1;
    }
    else
        cout << "Importazione avvenuta con successo:" << "\nS = " << fixed << setprecision(2) << S << ", n = " << n << "\nw = " << ArrayToString(n, w) << "\nr = " << ArrayToString(n, r) << endl;

    double TotPortfolio = totPortfolio(n, S, w, r);
    cout << "Valore finale del portafoglio: " << fixed << setprecision(2) << TotPortfolio << endl;

    double RateofReturn = rateOfReturn(S, TotPortfolio);
    cout << "Rendimento atteso: " << fixed << setprecision(4) << RateofReturn << endl;

    string outputFileName = "result.txt"; //nome del file di output

    if (!exportResult(outputFileName, n, S, w, r, TotPortfolio, RateofReturn))
    {
        cout << "Qualcosa è andato storto nella fase di esportazione dati" << endl;
        return -1;
    }
    else
            cout << "Esportazione in 'result.txt' avvenuta con successo!" << endl;
    delete[] w; //dealloco la memoria per il vettore w
    delete[] r; //dealloco la memoria per il vettore r

    return 0;
}

