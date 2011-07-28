#ifndef CLASS_SSEALGORITHM
#define CLASS_SSEALGORITHM

#include <gsl/gsl_rng.h>

#include "AbstractAlgorithm.cpp"
/*#include "../Analyzer/EAnalyzer.cpp"
#include "../Analyzer/HAnalyzer.cpp"
#include "../Analyzer/MAnalyzer.cpp"
#include "../Analyzer/SAnalyzer.cpp"*/

class SSEAlgorithm : public AbstractAlgorithm {

  protected:

    const gsl_rng_type *generatorType;
    gsl_rng *generator;

    bool *spins;
    long nr;
    long lMax;
    long l;
    int *s;
    long *x;
    
    void doSweep() {
      
      doDiagonalUpdate();
      
      doOperatorLoopUpdate();
      
      if(l < 4 * nr / 3) l = 4 * nr / 3;
      if(l > lMax) throw "Reached lMax";
    
    };
    
    void doDiagonalUpdate() {
    
      int b;
    
      for(long p = 0; p < l; p++) {
      
        if(s[p] == 0) { // No operator -> try to insert

          b = gsl_rng_uniform_int(generator, lattice->getNb()) + 1;

          if(spins[lattice->getI1(b)] == spins[lattice->getI2(b)]) continue; // if bond-neighbour spins are parallel -> go to next p
          
          if(gsl_rng_uniform(generator) < ((double) lattice->getNb()) / 2 / (l - nr) / t) {
            s[p] = 2 * b;
            nr++;
          }

        } else if(s[p] % 2 == 0) { // Diagonal operator -> try to remove
        
          if(gsl_rng_uniform(generator) < (double) 2 * (l - nr + 1) * t / lattice->getNb()) {
            s[p] = 0;
            nr--;
          }
        
        } else { // Off-Diagonal operator -> just flip the bond-neighbour spins
        
          b = s[p] / 2;
          
          spins[lattice->getI1(b)] = !spins[lattice->getI1(b)];
          spins[lattice->getI2(b)] = !spins[lattice->getI2(b)];
        
        }
      
      }
    
    };
    
    void doOperatorLoopUpdate() {
    
      // Construct link list x
      long v0;
      int b;
      int i1;
      int i2;

      long *vFirst = new long[lattice->getN()];
      for(int i = 0; i < lattice->getN(); i++) vFirst[i] = -1;
      long *vLast = new long[lattice->getN()];
      for(int i = 0; i < lattice->getN(); i++) vLast[i]  = -1;
      
      for(long v = 0; v < 4 * l; v++) x[v] = -1;
      
      for(long p = 0; p < l; p++) {
      
        if(s[p] == 0) continue; // No operator -> go to next p
        
        v0 = 4 * p;
        b = s[p] / 2;
        i1 = lattice->getI1(b);
        i2 = lattice->getI2(b);
        
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
      for(int i = 0; i < lattice->getN(); i++) {
      
        if(vFirst[i] != -1) {
          x[vFirst[i]] = vLast[i];
          x[vLast[i]] = vFirst[i];
        }
        
      }
    
      // Do the actual update
      for(long v = 0; v < 4 * l; v += 2) {
      
        if(x[v] < 0) continue;
        
        long vT = v;
        bool flipping = gsl_rng_uniform(generator) < 0.5;
        
        while(x[vT] >= 0) {
        
          // Flip
          if(flipping) {
            long p = vT / 4;
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
      for(int i = 0; i < lattice->getN(); i++) {
      
        if(vFirst[i] == -1) {
          if(gsl_rng_uniform(generator) < 0.5) spins[i] = !spins[i];
        } else {
          if(x[vFirst[i]] == -2) spins[i] = !spins[i];
        }
      
      }
      
      delete[] vLast;
      delete[] vFirst;
    
    };
    
    int getSpinSum() {
    
      int spinSum = 0;
    
      for(int i = 0; i < lattice->getN(); i++) {
        spinSum += spins[i] ? 0.5 : -0.5;
      }
      
      return spinSum;
    
    };
    
  public:
    
    SSEAlgorithm(AbstractLattice* lattice_parameter, int measureCount_parameter) : AbstractAlgorithm(lattice_parameter, measureCount_parameter) {
    
      gsl_rng_env_setup();
      generatorType = gsl_rng_default;
      generator = gsl_rng_alloc(generatorType);
      gsl_rng_set(generator, time(NULL));

      spins = new bool[lattice->getN()];
      for(int i = 0; i < lattice->getN(); i++) spins[i] = gsl_rng_uniform_int(generator, 2);
      nr = 0;
      lMax = 10000000;
      l = 10;
      s = new int[lMax];
      for(long p = 0; p < lMax; p++) s[p] = 0;
      x = new long[4 * lMax];
    
    };
    
    ~SSEAlgorithm() {

      delete x;
      delete s;
      delete spins;

      gsl_rng_free(generator);

    };
    
    void runTemperatureRound(double t_parameter) {
    
      AbstractAlgorithm::runTemperatureRound(t_parameter);
    
      for(long i = 0; i < runCount; i++) {
      
        if(i > runCount - measureCount) {
          //energyMeasurements[i - runCount + measureCount] = -nr * t;
          //magMeasurements[i - runCount + measureCount]    = fabs(double(getSpinSum()) / lattice->getN());
        }
        
        doSweep();
        
      }

/*      EAnalyzer *eAnalyzer = new EAnalyzer(this, lattice);
      eAnalyzer->analyze();
      avE = eAnalyzer->getAverage();
      erE = eAnalyzer->getError();
      atE = eAnalyzer->getAutoCorrelationTime();
      delete eAnalyzer;

      HAnalyzer *hAnalyzer = new HAnalyzer(this, lattice);
      hAnalyzer->analyze();
      avH = hAnalyzer->getAverage();
      erH = hAnalyzer->getError();
      atH = hAnalyzer->getAutoCorrelationTime();
      delete hAnalyzer;

      MAnalyzer *mAnalyzer = new MAnalyzer(this, lattice);
      mAnalyzer->analyze();
      avM = mAnalyzer->getAverage();
      erM = mAnalyzer->getError();
      atM = mAnalyzer->getAutoCorrelationTime();
      delete mAnalyzer;

      SAnalyzer *sAnalyzer = new SAnalyzer(this, lattice);
      sAnalyzer->analyze();
      avS = sAnalyzer->getAverage();
      erS = sAnalyzer->getError();
      atS = sAnalyzer->getAutoCorrelationTime();
      delete sAnalyzer;*/
    
    };

};

#endif
