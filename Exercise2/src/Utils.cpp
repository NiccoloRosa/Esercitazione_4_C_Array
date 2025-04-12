//ESERCIZIO 2
#include "Utils.hpp"
#include "iostream"
#include "fstream" //libreria per file
#include "sstream" //libreria per manipolare le stringhe
#include "iomanip" //libreria per manipolare la precisione dei dati

using namespace std;

bool importDatas(const string& inputFilePath,
				 size_t& n,
				 double& S,
				 double*& w,
				 double*& r)
{
	//Apro il file
	ifstream file;
	file.open(inputFilePath);

	if(file.fail())
	{
		cerr << "Errore nell'aperutra del file di input"<< endl; //gestisco l'errore di apertura file
		return false;
	}
	
	//Ottengo n ed S

	string useless_line;
	string usefull_line;	

	//Ottengo la somma totale da investire S		
	getline(file, useless_line, ';');
	getline(file, usefull_line);
	istringstream convertS; //definisco un oggetto di tipo stringstream, che mi permette di convertire una stringa in un numero
	convertS.str(usefull_line); //associo il contenuto (stringa) della riga letta all'oggetto convertS
	convertS >> S; //l'operatore >> converte automaticamente la stringa nel tipo S (unsigned int)

	//Ottengo il numero il numero di asset n		
	getline(file, useless_line, ';');
	getline(file, usefull_line);
	istringstream convertN;
	convertN.str(usefull_line);
	convertN >> n;

	//Definisco w ed r
	w = new double[n]; //alloco la memoria per il vettore w
	r = new double[n]; //alloco la memoria per il vettore r

	//Leggo la riga 'w;r' che non mi dà info
	getline(file, useless_line);

	//Ottengo w ed r

	string line_wi;
	string line_ri;

	int i = 0;
	while(getline(file, usefull_line))
	{
		istringstream data_w_and_r(usefull_line); //definisco un oggetto di tipo istringstream, che mi permette di manipolare più comodamennte la stringa e di convertirla in un numero
		getline(data_w_and_r, line_wi, ';'); //leggo la prima parte della riga, che contiene il valore di wi
		getline(data_w_and_r, line_ri); //leggo la seconda parte della riga, che contiene il valore di ri
		istringstream convertWi;
		istringstream convertRi;
		convertWi.str(line_wi);
		convertRi.str(line_ri);
		convertWi >> w[i]; //l'operatore >> converte automaticamente la stringa nel tipo w[i] (double)
		convertRi >> r[i];
		i ++;
	}

	//Chiudo il file
	file.close();
	return true;
}

double totPortfolio (const size_t& n,	
					 const double& S,
					 const double* const& w, 
					 const double* const& r)
{
	double totPortfolio = 0;
	for (unsigned int i = 0; i<n; i++)
	{
		totPortfolio += (1 + r[i])*(w[i]*S);
	}
	return totPortfolio; //restituisco il valore finale del portafoglio	
}

double rateOfReturn (const double& S,
					 const double& totPortfolio)
{
	double RateofReturn = 0;
	RateofReturn = (totPortfolio/S) - 1; //calcolo il rendimento atteso
	return RateofReturn; //restituisco il rendimento atteso
}

string ArrayToString(const size_t& n,const double* const& v)
{
	ostringstream toString; //definisco un oggetto di tipo ostringstream, che mi permette di convertire un numero in una stringa e di scriverci sopra
	toString << "[ ";
	for (unsigned int i = 0; i < n; i++) 
		toString << v[i] << " ";
    toString << "]";

	return toString.str(); //restituisco la stringa
}

bool exportResult (const string& outputFilePath,
                  const size_t& n,
				  const double& S,
                  const double* const& w,
                  const double* const& r,
				  const double& TotPortfolio,
                  const double& RateofReturn)
{	
	ofstream file;
	file.open(outputFilePath);
	
	//Gestisco L'errore di apertura file
	if (file.fail())
	{
		cerr << "Errore nell'apertura del file di output" << endl;
		return false;
	}
	
	file << "S = " << fixed << setprecision(2) << S << ", n = " << n << endl;
	file << "w = " << ArrayToString(n, w) << endl;
	file << "r = " << ArrayToString(n, r) << endl;
	file << "Rate of return of the portfolio: " << fixed << setprecision(4) << RateofReturn << endl;
	file << "V: " << fixed << setprecision(2) << TotPortfolio << endl;

	//Chiudo il file
	file.close();

	return true;
}