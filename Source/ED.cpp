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

//#include <atlas_enum.h>
//#include "clapack.h"

#include <tnt/tnt_array2d.h>
#include <jama_eig.h>

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

  int N = 3;
  int TwoPowN = pow(2, N);
  /*double **H;
  
  H = (double**) malloc(TwoPowN * sizeof(*H));
  if(H == NULL) throw "Problems allocating memory";
  for(int bs1 = 0; bs1 < TwoPowN; bs1++) {
    H[bs1] = (double*) malloc(TwoPowN * sizeof(**H));
    if(H[bs1] == NULL) throw "Problems allocating memory";
    for(int bs2 = 0; bs2 < TwoPowN; bs2++) {
      H[bs1][bs2] = 0;
    }
  }*/
  
  TNT::Array2D<double> H(TwoPowN, TwoPowN, 0.0);
  TNT::Array2D<double> D(TwoPowN, TwoPowN, 0.0);
  
  ED ed;

  for(int bs = 0; bs < TwoPowN; bs++) {
    ed.H2bs(H, bs, N, TwoPowN);
  }
  
  for(int bs1 = 0; bs1 < TwoPowN; bs1++) {
    cout << "[";
    for(int bs2 = 0; bs2 < TwoPowN; bs2++) {
      printf("% .3f ", H[bs1][bs2]);
    }
    cout << "]" << endl;
  }
  
  JAMA::Eigenvalue<double> Ev(H);
  
  Ev.getD(D);
  
  for(int bs1 = 0; bs1 < TwoPowN; bs1++) {
    cout << "[";
    for(int bs2 = 0; bs2 < TwoPowN; bs2++) {
      printf("% .3f ", D[bs1][bs2]);
    }
    cout << "]" << endl;
  }

};
