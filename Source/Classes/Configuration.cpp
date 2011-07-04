#include <iostream>
#include <string>
#include <cmath>
#include <gsl/gsl_rng.h>
#include <sstream>

using namespace std;

class Configuration {

  public:

    const gsl_rng_type *generatorType;
    gsl_rng *generator;

    long double T;
    int Nb;
    int N;
    bool *spins;
    int Nr;
    int LMax;
    int L;
    int *s;
    int *X;
    
    Configuration(int N_Parameter, int Nb_Parameter, long double T_Parameter) {

      gsl_rng_env_setup();
      generatorType = gsl_rng_default;
      generator = gsl_rng_alloc(generatorType);
      gsl_rng_set(generator, time(NULL));

      T = T_Parameter;
      Nb = Nb_Parameter;
      N = N_Parameter;
      spins = new bool[N];
      for(int i = 0; i < N; i++) spins[i] = gsl_rng_uniform_int(generator, 2);
      Nr = 0;
      LMax = 10000;
      L = 10;
      s = new int[LMax];
      for(int p = 0; p < LMax; p++) s[p] = 0;
      X = new int[4 * LMax];
        
    };

    ~Configuration() {

      delete spins;
      delete s;
      delete X;

      gsl_rng_free(generator);

    };
    
    virtual int getI1(int b) = 0;
    virtual int getI2(int b) = 0;
    
    void doSweep() {
      
      doDiagonalUpdate();
      
      doOperatorLoopUpdate();
      
      if(L < 4 * Nr / 3) L = 4 * Nr / 3;
    
    };
    
    void doDiagonalUpdate() {
    
      for(int p = 0; p < L; p++) {
      
        if(s[p] == 0) { // No operator -> try to insert

          int b = gsl_rng_uniform_int(generator, Nb) + 1;

          if(spins[getI1(b)] == spins[getI2(b)]) continue; // if bond-neighbour spins are parallel -> go to next p
          
          if(gsl_rng_uniform(generator) < ((long double) Nb) / (long double) 2 / (L - Nr) / T) {
            s[p] = 2 * b;
            Nr++;
          }

        } else if(s[p] % 2 == 0) { // Diagonal operator -> try to remove
        
          if(gsl_rng_uniform(generator) < (long double) 2 * (L - Nr + 1) * T / Nb) {
            s[p] = 0;
            Nr--;
          }
        
        } else { // Off-Diagonal operator -> just flip the bond-neighbour spins
        
          int b = s[p] / 2;
          
          spins[getI1(b)] = !spins[getI1(b)];
          spins[getI2(b)] = !spins[getI2(b)];
        
        }
      
      }
    
    };
    
    void doOperatorLoopUpdate() {
    
      int *vFirst = new int[N];
      for(int i = 0; i < N; i++) vFirst[i] = -1;
      int *vLast = new int[N];
      for(int i = 0; i < N; i++) vLast[i]  = -1;
      
      for(int v = 0; v < 4 * L; v++) X[v] = -1;
    
      // Construct link list X
      for(int p = 0; p < L; p++) {
      
        if(s[p] == 0) continue; // No operator -> go to next p
        
        int v0 = 4 * p;
        int b = s[p] / 2;
        int i1 = getI1(b);
        int i2 = getI2(b);
        
        // Link the last 2-vertex on this spin to new 0-vertex
        if(vLast[i1] == -1) {
          vFirst[i1] = v0;
        } else {
          X[vLast[i1]] = v0;
          X[v0] = vLast[i1];
        }
        
        // Link the last 3-vertex on this spin to new 1-vertex
        if(vLast[i2] == -1) {
          vFirst[i2] = v0 + 1;
        } else {
          X[vLast[i2]] = v0 + 1;
          X[v0 + 1] = vLast[i2];
        }
        
        // Set the 2 and 3-vertex as last vertex on this spin
        vLast[i1] = v0 + 2;
        vLast[i2] = v0 + 3;
      
      }
      
      // Link vertexes periodicly if they interacted with operators
      for(int i = 0; i < N; i++) {
      
        if(vFirst[i] != -1) {
          X[vFirst[i]] = vLast[i];
          X[vLast[i]] = vFirst[i];
        }
        
      }
    
      // Do the actual update
      for(int v = 0; v < 4 * L; v += 2) {
      
        if(X[v] < 0) continue;
        
        int vT = v;
        bool flipping = gsl_rng_uniform(generator) < 0.5;
        
        while(X[vT] >= 0) {
        
          // Flip
          if(flipping) {
            int p = vT / 4;
            s[p] = s[p] ^ 1;
          }
          
          // Walk to other operator
          vT = X[vT];
          
          // Delete the way I went and the way back
          X[vT] = X[X[vT]] = flipping ? -2 : -1;
          
          // Walk to neighbour on operator
          vT = vT ^ 1;
        
        }
      
      }
      
      // Adjust spins
      for(int i = 0; i < N; i++) {
      
        if(vFirst[i] == -1) {
          if(gsl_rng_uniform(generator) < 0.5) spins[i] = !spins[i];
        } else {
          if(X[vFirst[i]] == -2) spins[i] = !spins[i];
        }
      
      }
    
    };
    
    void setTemperature(long double T_Parameter) {
    
      T = T_Parameter;
    
    };
    
    int getCountOfRealOperators() {
    
      return Nr;
    
    };
    
    int getCountOfBonds() {
    
      return Nb;
    
    };
    
    string getSpinStatesAsString() {
      
      string str = "";
    
      for(int i = 0; i < N; i++) {
        str += spins[i] ? "+" : "-";
      }
      
      return str;
      
    };
    
    string intArrayToString(int *a, int c) {
    
      stringstream out;
    
      for(int i = 0; i < c; i++) {
        if(i != 0) out << ",";
        out << a[i];
      }
      
      return out.str();
    
    };

};
