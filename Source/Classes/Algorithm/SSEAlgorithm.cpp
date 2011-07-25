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
    long nr;
    int energy_countBins;
    int heat_countBins;
    int suscept_countBins;
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
      long v0;
      int b;
      int i1;
      int i2;

      long *vFirst = new long[model->getN()];
      for(int i = 0; i < model->getN(); i++) vFirst[i] = -1;
      long *vLast = new long[model->getN()];
      for(int i = 0; i < model->getN(); i++) vLast[i]  = -1;
      
      for(long v = 0; v < 4 * l; v++) x[v] = -1;
      
      for(long p = 0; p < l; p++) {
      
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
    
    int getSpinSum() {
    
      int spinSum = 0;
    
      for(int i = 0; i < model->getN(); i++) {
        spinSum += spins[i] ? 0.5 : -0.5;
      }
      
      return spinSum;
    
    };
    
    int getEnergyRelaxationTime() {
    
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
          autoCorrelation += nrWhileTrying[i] * nrWhileTrying[i + relaxationTime] * pow(t, 2);
        }
        autoCorrelation /= relaxationTimeTryTime - relaxationTime;
        autoCorrelation = (autoCorrelation - pow(sumOfNr * t / relaxationTimeTryTime, 2)) / ((sumOfNrSquared * pow(t, 2) / relaxationTimeTryTime) - pow(sumOfNr * t / relaxationTimeTryTime, 2));
        
        if(isnan(autoCorrelation)) {
          printf("# Temperatures underneeth %+20.13e were not measured, due to the unknown energy relaxation time\n", t);
          throw "Unknown energy relaxation time";
        };
        
        if(autoCorrelation < exp((double) -1)) {
          delete nrWhileTrying;
          return relaxationTime;
        }
    
      }
      
      printf("# Temperatures underneeth %+20.13e were not measured, because the maximal energy relaxation time was exceeded\n", t);
      throw "The maximal energy relaxation time was exceeded";
    
    };
    
    int getHeatRelaxationTime() {
    
      const int relaxationTimeTryTime = 50;
      int relaxationTime;
      
      double *sumOfNrWhileTrying        = new double[relaxationTimeTryTime];
      double *sumOfNrSquaredWhileTrying = new double[relaxationTimeTryTime];
    
      for(int time = 0; time < relaxationTimeTryTime; time++) {
      
        sumOfNrWhileTrying[time]        = (time == 0 ? 0 : sumOfNrWhileTrying[time - 1]) + nr;
        sumOfNrSquaredWhileTrying[time] = (time == 0 ? 0 : sumOfNrSquaredWhileTrying[time - 1]) + pow(nr, 2);
      
        doSweep();
      
      }
    
      for(relaxationTime = 0; relaxationTime < relaxationTimeTryTime - 1; relaxationTime++) {
        
        double sumOfAAa = 0;
        double sumOfA = 0;
        double sumOfASquared = 0;
        for(int i = 1; i < relaxationTimeTryTime - relaxationTime; i++) {
          sumOfAAa      +=    ((sumOfNrSquaredWhileTrying[i] / i) - pow(sumOfNrWhileTrying[i] / i, 2) - (sumOfNrWhileTrying[i] / i)) * ((sumOfNrSquaredWhileTrying[i + relaxationTime] / (i + relaxationTime)) - pow(sumOfNrWhileTrying[i + relaxationTime] / (i + relaxationTime), 2) - (sumOfNrWhileTrying[i + relaxationTime] / (i + relaxationTime)));
          sumOfA        +=     (sumOfNrSquaredWhileTrying[i] / i) - pow(sumOfNrWhileTrying[i] / i, 2) - (sumOfNrWhileTrying[i] / i);
          sumOfASquared += pow((sumOfNrSquaredWhileTrying[i] / i) - pow(sumOfNrWhileTrying[i] / i, 2) - (sumOfNrWhileTrying[i] / i), 2);
        }
        double autoCorrelation = ((sumOfAAa / (relaxationTimeTryTime - relaxationTime - 1)) - pow(sumOfA / (relaxationTimeTryTime - relaxationTime - 1), 2)) / ((sumOfASquared / (relaxationTimeTryTime - relaxationTime - 1)) - pow(sumOfA / (relaxationTimeTryTime - relaxationTime - 1), 2));
        
        std::cerr << sumOfAAa << "$" << sumOfA << "$" << sumOfASquared << " = " << autoCorrelation << std::endl;
        std::cerr << relaxationTimeTryTime - relaxationTime << std::endl;
        
        if(isnan(autoCorrelation)) {
          printf("# Temperatures underneeth %+20.13e were not measured, due to the unknown heat relaxation time\n", t);
          throw "Unknown heat relaxation time";
        };
        
        if(autoCorrelation < exp((double) -1)) {
          delete sumOfNrSquaredWhileTrying;
          delete sumOfNrWhileTrying;
          return relaxationTime;
        }
    
      }
      
      printf("# Temperatures underneeth %+20.13e were not measured, because the maximal heat relaxation time was exceeded\n", t);
      throw "The maximal heat relaxation time was exceeded";
    
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
      energy_countBins  = 3000;
      heat_countBins    = 10;
      suscept_countBins = 3000;
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
    
    void runTemperatureRound() {
      
      int energy_relaxationTime  = 3;//getEnergyRelaxationTime();
      int heat_relaxationTime    = 3;//getHeatRelaxationTime();
      int suscept_relaxationTime = 3;//getEnergyRelaxationTime();
      
      long energy_measurementsPerBin  = 40 * energy_relaxationTime;
      long heat_measurementsPerBin    = 4000 * heat_relaxationTime;
      long suscept_measurementsPerBin = 40 * suscept_relaxationTime;
      
      bool energy_finished  = false;
      bool heat_finished    = false;
      bool suscept_finished = false;
      
      double *energy_perBin  = new double[energy_countBins];
      double *heat_perBin    = new double[heat_countBins];
      double *suscept_perBin = new double[suscept_countBins];
      
      double energy_sumOfBin  = 0;
      double heat_sumOfBin    = 0;
      double suscept_sumOfBin = 0;

      for(int j = 0; j < 10000; j++) {
        doSweep();
      }
      
      double energy_sumOfNr              = 0;
      double heat_sumOfNr                = 0;
      double heat_sumOfNrSquared         = 0;
      double suscept_sumOfSpinSumSquared = 0;
      
      for(unsigned long j = 0; j < long(1) << (sizeof(long) * 8 - 1); j++) {
      
        if(j % energy_measurementsPerBin == 0 && j != 0 && !energy_finished) {
          int bin = j / energy_measurementsPerBin;
          energy_perBin[bin] = -energy_sumOfNr / energy_measurementsPerBin * t;
          energy_sumOfBin += energy_perBin[bin];
          energy_sumOfNr = 0;
          if(bin >= energy_countBins) energy_finished = true;
        }
      
        if(j % heat_measurementsPerBin == 0 && j != 0 && !heat_finished) {
          int bin = j / heat_measurementsPerBin;
          heat_perBin[bin] = (heat_sumOfNrSquared / heat_measurementsPerBin) - pow(heat_sumOfNr / heat_measurementsPerBin, 2) - (heat_sumOfNr / heat_measurementsPerBin);
          heat_sumOfBin += heat_perBin[bin];
          heat_sumOfNr = 0;
          heat_sumOfNrSquared = 0;
          if(bin >= heat_countBins) heat_finished = true;
        }
      
        if(j % suscept_measurementsPerBin == 0 && j != 0 && !suscept_finished) {
          int bin = j / suscept_measurementsPerBin;
          suscept_perBin[bin] = suscept_sumOfSpinSumSquared / suscept_measurementsPerBin / t / model->getN();
          suscept_sumOfBin += suscept_perBin[bin];
          suscept_sumOfSpinSumSquared = 0;
          if(bin >= suscept_countBins) suscept_finished = true;
        }
      
        energy_sumOfNr              += nr;
        heat_sumOfNr                += nr;
        heat_sumOfNrSquared         += pow(nr, 2);
        suscept_sumOfSpinSumSquared += pow(getSpinSum(), 2);
        
        doSweep();
        
        if(energy_finished && heat_finished && suscept_finished) break;
        
      }
      
      avE = (energy_sumOfBin / energy_countBins) + ((double) model->getNb() / 4);
      erE = 0;
      for(long bin = 0; bin < energy_countBins; bin++) {
        erE += pow(energy_perBin[bin] - avE, 2);
      }
      erE = sqrt(erE / energy_countBins / (energy_countBins - 1));
      rtE = energy_relaxationTime;
      
      avH = (heat_sumOfBin / heat_countBins);
      erH = 0;
      for(long bin = 0; bin < heat_countBins; bin++) {
        erH += pow(heat_perBin[bin]  - avH, 2);
      }
      erH = sqrt(erH / heat_countBins / (heat_countBins - 1));
      rtH = heat_relaxationTime;
      
      avS = (suscept_sumOfBin / suscept_countBins);
      erS = 0;
      for(long bin = 0; bin < suscept_countBins; bin++) {
        erS += pow(suscept_perBin[bin]  - avS, 2);
      }
      erS = sqrt(erS / suscept_countBins / (suscept_countBins - 1));
      rtS = suscept_relaxationTime;
      
      delete suscept_perBin;
      delete heat_perBin;
      delete energy_perBin;
    
    };

};

#endif
