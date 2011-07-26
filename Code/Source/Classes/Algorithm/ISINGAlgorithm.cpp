#ifndef CLASS_ISINGALGORITHM
#define CLASS_ISINGALGORITHM

#include <gsl/gsl_rng.h>

#include "AbstractAlgorithm.cpp"
#include "../Analyzer/EAnalyzer.cpp"
#include "../Analyzer/HAnalyzer.cpp"
#include "../Analyzer/MAnalyzer.cpp"
#include "../Analyzer/SAnalyzer.cpp"

class ISINGAlgorithm : public AbstractAlgorithm {

  protected:

    const gsl_rng_type *generatorType;
    gsl_rng *generator;
    
    bool *spins;
    double energy;
    int spinSum;
    bool start;
    
    void doSweep() {
    
      double energyDifference;
      double weight;
      double randomWeight;
      
      for(int i = 0; i < lattice->getN(); i++) {

        energyDifference = getEnergyDifferenceOfFlip(i);
        weight = exp(-energyDifference / t);
        randomWeight = gsl_rng_uniform(generator);

        if(weight >= randomWeight) {
          spinSum += getSpinSumDifferenceOfFlip(i);
          energy  += energyDifference;
          spins[i] = !spins[i];
        }

      }
    
    };

    double calculateEnergy() {

      int sumOfBonds = 0;

      for(int b = 1; b <= lattice->getNb(); b++) {
        sumOfBonds += spins[lattice->getI1(b)] == spins[lattice->getI2(b)] ? 1 : -1;
      }

      return -sumOfBonds;

    };
    
    int calculateSpinSum() {

      int spinSum = 0;

      for(int i = 0; i < lattice->getN(); i++) {
        spinSum += spins[i] ? 1 : -1;
      }

      return spinSum;

    };
    
    double getEnergyDifferenceOfFlip(int i) {

      int *neighbours = lattice->getNeighbours(i);
      double energyDiffernce = 0;
      
      for(int j = 1; j <= neighbours[0]; j++) {
        energyDiffernce += 2 * (spins[i] == spins[neighbours[j]] ? 1 : -1);
      }
      
      delete[] neighbours;
      
      return energyDiffernce;
      
    };

    int getSpinSumDifferenceOfFlip(int i) {

      return -2 * (spins[i] ? 1 : -1);

    };

  public:
    
    ISINGAlgorithm(AbstractLattice* lattice_parameter, int measureCount_parameter) : AbstractAlgorithm(lattice_parameter, measureCount_parameter) {
    
      gsl_rng_env_setup();
      generatorType = gsl_rng_default;
      generator = gsl_rng_alloc(generatorType);
      gsl_rng_set(generator, time(NULL));
      
      spins = new bool[lattice->getN()];
      start = true;
    
    };
    
    ~ISINGAlgorithm() {
    
      delete[] spins;

      gsl_rng_free(generator);
    
    };
    
    void setTemperature(double t_parameter) {
    
      AbstractAlgorithm::setTemperature(t_parameter);
      
      if(start) {
        for(int i = 0; i < lattice->getN(); i++) {
          spins[i] = bool(gsl_rng_uniform_int(generator, 2));
        }

        energy  = calculateEnergy();
        spinSum = calculateSpinSum();
        start = false;
      }
    
    };
    
    void runTemperatureRound() {
    
      for(long i = 0; i < runCount; i++) {
      
        if(i > runCount - measureCount) {
          energyMeasurements[i - runCount + measureCount] = energy;
          magMeasurements[i - runCount + measureCount]    = fabs(double(spinSum) / lattice->getN());
        }
        
        doSweep();
        
      }

      EAnalyzer *eAnalyzer = new EAnalyzer(this, lattice);
      eAnalyzer->analyze();
      avE = eAnalyzer->getAverage();
      erE = eAnalyzer->getError();
      rtE = eAnalyzer->getRelaxationTime();
      delete eAnalyzer;

      HAnalyzer *hAnalyzer = new HAnalyzer(this, lattice);
      hAnalyzer->analyze();
      avH = hAnalyzer->getAverage();
      erH = hAnalyzer->getError();
      rtH = hAnalyzer->getRelaxationTime();
      delete hAnalyzer;

      MAnalyzer *mAnalyzer = new MAnalyzer(this, lattice);
      mAnalyzer->analyze();
      avM = mAnalyzer->getAverage();
      erM = mAnalyzer->getError();
      rtM = mAnalyzer->getRelaxationTime();
      delete mAnalyzer;

      SAnalyzer *sAnalyzer = new SAnalyzer(this, lattice);
      sAnalyzer->analyze();
      avS = sAnalyzer->getAverage();
      erS = sAnalyzer->getError();
      rtS = sAnalyzer->getRelaxationTime();
      delete sAnalyzer;
      
    };
    
};

#endif
