//TODO: Pseudo thermalization should become self tested
//TODO: Errorbars

/*#include "Classes/Configuration.cpp"
#include "Classes/Configuration1DOpen.cpp"
#include "Classes/Configuration1DPeriodic.cpp"
#include "Classes/Configuration2DPeriodic.cpp"
*/
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>

#include <tnt/tnt_array2d.h>
#include <jama/jama_eig.h>

using namespace std;

class ED {

  public:

    int getI1(int b) {

      return b - 1;

    };

    int getI2(int b) {

      return b;

    };

    void H2bs(TNT::Array2D<double> H, int bs, int N, int TwoPowN) {

      int Nb = N - 1;
      
      for(int b = 1; b <= Nb; b++) {
      
        int tempbs = bs;
        double value = 2;
        Sz(getI2(b), &tempbs, &value);
        Sz(getI1(b), &tempbs, &value);
        if(tempbs >= 0) H[bs][tempbs] += value;
        
        tempbs = bs;
        value = 1;
        Sm(getI2(b), &tempbs, &value);
        Sp(getI1(b), &tempbs, &value);
        if(tempbs >= 0) H[bs][tempbs] += value;
        
        tempbs = bs;
        value = 1;
        Sp(getI2(b), &tempbs, &value);
        Sm(getI1(b), &tempbs, &value);
        if(tempbs >= 0) H[bs][tempbs] += value;
      
      }
      
    };

    void Sz(int i, int* state_p, double* value_p) {
    
      if(*state_p == -1) return;
      
      *value_p *= 0.5;

      if(~*state_p & (int) pow(2, i)) *value_p *= -1;

    };

    void Sp(int i, int* state_p, double* value_p) {
    
      if(*state_p == -1) return;
      
      if(*state_p & (int) pow(2, i)) {
      
        *state_p = -1;
      
      } else {
      
        *state_p = *state_p ^ (int) pow(2, i);
      
      }

    };

    void Sm(int i, int* state_p, double* value_p) {
    
      if(*state_p == -1) return;
      
      if(*state_p & (int) pow(2, i)) {
      
        *state_p = *state_p ^ (int) pow(2, i);
      
      } else {
      
        *state_p = -1;
      
      }

    };

};

int main(int argc, char *argv[]) {

  try {

    if(argc != 5) throw "[SSE] Error: Please specify 4 parameters (Model, Size, Temperature at the start, Temperature at the end)";

    int model                    = atoi(argv[1]);
    int size                     = atoi(argv[2]);
    long double temperatureStart = atof(argv[3]);
    long double temperatureEnd   = atof(argv[4]);

    if(temperatureStart > temperatureEnd) swap(temperatureStart, temperatureEnd);
    
    int N = 3;
    int TwoPowN = pow(2, size);
    double temperatureStep = 0.01;
  
 
    ED ed;
    
    cout << "#\n";
    cout << "# ED - DATA\n";
    cout << "#\n";
    cout << "# ----------------------------------------\n";
    cout << "#\n";
    
    printf("# Size             = %.10i\n" , size);
    printf("# TemperatureStart = %.10Le\n", temperatureStart);
    printf("# TemperatureEnd   = %.10Le\n", temperatureEnd);
    
    printf("#\n#\n");
    printf("# %-17s | %-18s | %-18s | %-18s | %-18s\n",
           "Model",
           "Size",
           "Temperature",
           "Energy",
           "Specific Heat");
    printf("# ------------------------------------------------------------------------------------------------------\n");
     
    for(long double temperature = temperatureEnd; temperature > temperatureStart + (temperatureStep / 2); temperature -= temperatureStep) {

      TNT::Array2D<double> H(TwoPowN, TwoPowN, 0.0);
      TNT::Array2D<double> D(TwoPowN, TwoPowN, 0.0);

      for(int bs = 0; bs < TwoPowN; bs++) {
        ed.H2bs(H, bs, size, TwoPowN);
      }

      JAMA::Eigenvalue<double> Ev(H);
  
      Ev.getD(D);

      double avH = 0;
      double Z = 0;

      for(int bs = 0; bs < TwoPowN; bs++) {
        avH += exp(-H[bs][bs]/temperature)*H[bs][bs];
        Z   += exp(-H[bs][bs]/temperature);
      }
      
      cerr << "[ED] Info: Size=" << size << ", Temperature=" << temperature << endl;

      printf("%20.20i|%20.20i|%+20.13Le|%+20.13e|%+20.13e\n",
             model,
             size,
             temperature,
             avH/Z,
             0.0);

    }

    return EXIT_SUCCESS;
  
  } catch(const char *message) {
  
    cerr << message << endl;
    return EXIT_FAILURE;
  
  }

};
