//ESERCIZIO 2
#pragma once 

#include <iostream> //libreria per input/ouput

using namespace std;


//Importdatas legge i dati di input dal file per gli investimenti 
bool importDatas(const string& inputFilePath,
				 size_t& n,
				 double& S,
				 double*& w,
				 double*& r);
//RateofReturn calcola il rendimento atteso e il valore finale del portafoglio

double totPortfolio (const size_t& n,
					 const double& S,
					 const double* const& w, 
					 const double* const& r);

double rateOfReturn (const double& S,
					 const double& totPortfolio);

string ArrayToString(const size_t& n,
                     const double* const& v);

bool exportResult(const string& outputFilePath,
                  const size_t& n,
				  const double& S,
                  const double* const& w,
                  const double* const& r,
				  const double& totPortfolio,
                  const double& rateOfReturn);


