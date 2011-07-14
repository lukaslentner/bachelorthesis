#ifndef CLASS_SSEALGORITHM
#define CLASS_SSEALGORITHM

#include <gsl/gsl_rng.h>
#include <iostream>

#include "AbstractAlgorithm.cpp"

class SSEAlgorithm : public AbstractAlgorithm {

  protected:

    const gsl_rng_type *generatorType;
    gsl_rng *generator;

    bool *spins;
    int nr;
    int countMeasurements;
    int lMax;
    int l;
    int *s;
    int *x;
    
    void doSweep() {
      
      doDiagonalUpdate();
      
      doOperatorLoopUpdate();
      
      if(l < 4 * nr / 3) l = 4 * nr / 3;
    
    };
    
    void doDiagonalUpdate() {
    
      int b;
    
      for(int p = 0; p < l; p++) {
      
        if(s[p] == 0) { // No operator -> try to insert

          b = gsl_rng_uniform_int(generator, model->getNb()) + 1;

          if(spins[model->getI1(b)] == spins[model->getI2(b)]) continue; // if bond-neighbour spins are parallel -> go to next p
          
          if(gsl_rng_uniform(generator) < ((double) model->getNb()) / 2 / (l - nr) / t) {
            s[p] = 2 * b;
            nr++;
          }

        } else if(s[p] % 2 == 0) { // Diagonal operator -> try to remove
        
          if(gsl_rng_uniform(generator) < (double) 2 * (l - nr + 1) * t / model->getNb()) {
            s[p] = 0;
            nr--;
          }
        
        } else { // Off-Diagonal operator -> just flip the bond-neighbour spins
        
          b = s[p] / 2;
          
          spins[model->getI1(b)] = !spins[model->getI1(b)];
          spins[model->getI2(b)] = !spins[model->getI2(b)];
        
        }
      
      }
    
    };
    
    void doOperatorLoopUpdate() {
    
      // Construct link list x
      int v0;
      int b;
      int i1;
      int i2;

      int *vFirst = new int[model->getN()];
      for(int i = 0; i < model->getN(); i++) vFirst[i] = -1;
      int *vLast = new int[model->getN()];
      for(int i = 0; i < model->getN(); i++) vLast[i]  = -1;
      
      for(int v = 0; v < 4 * l; v++) x[v] = -1;
      
      for(int p = 0; p < l; p++) {
      
        if(s[p] == 0) continue; // No operator -> go to next p
        
        v0 = 4 * p;
        b = s[p] / 2;
        i1 = model->getI1(b);
        i2 = model->getI2(b);
        
        // Link the last 2-vertex on this spin to new 0-vertex
        if(vLast[i1] == -1) {
          vFirst[i1] = v0;
        } else {
          x[vLast[i1]] = v0;
          x[v0] = vLast[i1];
        }
        
        // Link the last 3-vertex on this spin to new 1-vertex
        if(vLast[i2] == -1) {
          vFirst[i2] = v0 + 1;
        } else {
          x[vLast[i2]] = v0 + 1;
          x[v0 + 1] = vLast[i2];
        }
        
        // Set the 2 and 3-vertex as last vertex on this spin
        vLast[i1] = v0 + 2;
        vLast[i2] = v0 + 3;
      
      }
      
      // Link vertexes periodicly if they interacted with operators
      for(int i = 0; i < model->getN(); i++) {
      
        if(vFirst[i] != -1) {
          x[vFirst[i]] = vLast[i];
          x[vLast[i]] = vFirst[i];
        }
        
      }
    
      // Do the actual update
      int vT;
      bool flipping;
      int p;
        
      for(int v = 0; v < 4 * l; v += 2) {
      
        if(x[v] < 0) continue;
        
        vT = v;
        flipping = gsl_rng_uniform(generator) < 0.5;
        
        while(x[vT] >= 0) {
        
          // Flip
          if(flipping) {
            p = vT / 4;
            s[p] = s[p] ^ 1;
          }
          
          // Walk to other operator
          vT = x[vT];
          
          // Delete the way I went and the way back
          x[vT] = x[x[vT]] = flipping ? -2 : -1;
          
          // Walk to neighbour on operator
          vT = vT ^ 1;
        
        }
      
      }
      
      // Adjust spins
      for(int i = 0; i < model->getN(); i++) {
      
        if(vFirst[i] == -1) {
          if(gsl_rng_uniform(generator) < 0.5) spins[i] = !spins[i];
        } else {
          if(x[vFirst[i]] == -2) spins[i] = !spins[i];
        }
      
      }
      
      delete[] vLast;
      delete[] vFirst;
    
    };
    
    int getRelaxationTime() {
    
      const int relaxationTimeTryTime = 50;
      int relaxationTime;
      
      double sumOfNr = 0;
      double sumOfNrSquared = 0;
      double *nrWhileTrying = new double[relaxationTimeTryTime];
    
      for(int time = 0; time < relaxationTimeTryTime; time++) {
      
        nrWhileTrying[time] = nr;
        doSweep();
        
        sumOfNr += nrWhileTrying[time];
        sumOfNrSquared += pow(nrWhileTrying[time], 2);
      
      }
      
      double autoCorrelation;
    
      for(relaxationTime = 0; relaxationTime < relaxationTimeTryTime; relaxationTime++) {
    
        autoCorrelation = 0;
      
        for(int i = 0; i < relaxationTimeTryTime - relaxationTime; i++) {
          autoCorrelation += nrWhileTrying[i] * nrWhileTrying[i + relaxationTime];
        }
      
        autoCorrelation *= pow(t, 2);
        autoCorrelation /= relaxationTimeTryTime - relaxationTime;
        autoCorrelation = (autoCorrelation - pow(sumOfNr * t / relaxationTimeTryTime, 2)) / ((sumOfNrSquared * pow(t, 2) / relaxationTimeTryTime) - pow(sumOfNr * t / relaxationTimeTryTime, 2));
        
        if(isnan(autoCorrelation)) {
          printf("# Temperatures underneeth %+20.13e were not measured, due to the unknown relaxation time\n", t);
          throw "Stop execution due to problems to determine the relaxation time";
        };
        
        if(autoCorrelation < exp((double) -1)) {
          //delete nrWhileTrying;
          return relaxationTime;
        }
    
      }
      
      printf("# Temperatures underneeth %+20.13e were not measured, due to the unknown relaxation time\n", t);
      throw "Stop execution due to problems to determine the relaxation time";
    
    };
    
  public:
    
    SSEAlgorithm(AbstractModel* model_parameter) : AbstractAlgorithm(model_parameter) {
    
      gsl_rng_env_setup();
      generatorType = gsl_rng_default;
      generator = gsl_rng_alloc(generatorType);
      gsl_rng_set(generator, time(NULL));

      spins = new bool[model->getN()];
      for(int i = 0; i < model->getN(); i++) spins[i] = gsl_rng_uniform_int(generator, 2);
      nr = 0;
      countMeasurements = 10000;
      lMax = 10000;
      l = 10;
      s = new int[lMax];
      for(int p = 0; p < lMax; p++) s[p] = 0;
      x = new int[4 * lMax];
    
    };
    
    ~SSEAlgorithm() {

      delete x;
      delete s;
      delete spins;

      gsl_rng_free(generator);

    };
    
    void runTemperatureRound() {
      
      double sumOfNr = 0; 
      double sumOfNrSquared = 0;
      double tempSumOfNr = 0; 
      double tempSumOfNrSquared = 0;
      
      int relaxationTime = getRelaxationTime();
      int binSize = 10 * relaxationTime;

      for(int j = 0; j < 1000; j++) {
        doSweep();
      }
      
      for(long i = 0; i < (long) binSize * countMeasurements; i += binSize) {
      
        tempSumOfNr = 0; 
        tempSumOfNrSquared = 0;
      
        for(int j = 0; j < binSize; j++) {
        
          doSweep();
            
          tempSumOfNr        += nr;
          tempSumOfNrSquared += pow(nr, 2);

        }
        
        sumOfNr        += tempSumOfNr        / binSize;
        sumOfNrSquared += tempSumOfNrSquared / binSize;
        
      }
      
      avE = (-sumOfNr * t / countMeasurements) + ((double) model->getNb() / 4);
      erE = sqrt(((sumOfNrSquared * pow(t, 2) / countMeasurements) - pow(sumOfNr * t / countMeasurements, 2)) / (countMeasurements - 1));
      avC = (sumOfNrSquared / countMeasurements) - pow(sumOfNr / countMeasurements, 2) - (sumOfNr / countMeasurements);
    
    };

};

#endif
