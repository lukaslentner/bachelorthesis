#ifndef CLASS_ABSTRACTALGORITHM
#define CLASS_ABSTRACTALGORITHM

#include <sstream>
#include <string>

#include "../Lattice/AbstractLattice.cpp"

class AbstractAlgorithm {

  protected:
  
    AbstractLattice* lattice;
    long measureCount;
    long runCount;
    double *energyMeasurements;
    double *magMeasurements;
    double t;
    double avE;
    double erE;
    long rtE;
    double avH;
    double erH;
    long rtH;
    double avM;
    double erM;
    long rtM;
    double avS;
    double erS;
    long rtS;

  public:
  
    AbstractAlgorithm(AbstractLattice* lattice_parameter, int measureCount_parameter) {
    
      lattice = lattice_parameter;
      measureCount = measureCount_parameter;
      runCount = measureCount * 3 / 2;
      
      energyMeasurements = new double[measureCount];
      magMeasurements    = new double[measureCount];
      
      t = 0;
      
      avE = 0;
      erE = 0;
      rtE = 0;
      
      avH = 0;
      erH = 0;
      rtH = 0;
      
      avM = 0;
      erM = 0;
      rtM = 0;
      
      avS = 0;
      erS = 0;
      rtS = 0;
    
    };
    
    ~AbstractAlgorithm() {
    
      delete[] magMeasurements;
      delete[] energyMeasurements;
    
    };
    
    long getMeasureCount() {
    
      return measureCount;
    
    };
    
    long getRunCount() {
    
      return runCount;
    
    };

    virtual void runTemperatureRound() = 0;
    
    virtual void setTemperature(double t_parameter) {
    
      t = t_parameter;
      
      avE = 0;
      erE = 0;
      rtE = 0;
      
      avH = 0;
      erH = 0;
      rtH = 0;
      
      avM = 0;
      erM = 0;
      rtM = 0;
      
      avS = 0;
      erS = 0;
      rtS = 0;
    
    };
    
    double getTemperature() {
    
      return t;
    
    };
    
    double getEnergyMeasurement(long time) {
    
      return energyMeasurements[time];
    
    };
    
    double getMagMeasurement(long time) {
    
      return magMeasurements[time];
    
    };
    
    double getAverageEnergy() {
    
      return avE;
    
    };
    
    double getErrorOfEnergy() {
    
      return erE;
    
    };
    
    long getRelTiOfEnergy() {
    
      return rtE;
    
    };
    
    double getAverageHeat() {
    
      return avH;
    
    };
    
    double getErrorOfHeat() {
    
      return erH;
    
    };
    
    long getRelTiOfHeat() {
    
      return rtH;
    
    };
    
    double getAverageMag() {
    
      return avM;
    
    };
    
    double getErrorOfMag() {
    
      return erM;
    
    };
    
    long getRelTiOfMag() {
    
      return rtM;
    
    };
    
    double getAverageSuscept() {
    
      return avS;
    
    };
    
    double getErrorOfSuscept() {
    
      return erS;
    
    };
    
    long getRelTiOfSuscept() {
    
      return rtS;
    
    };
    
};

#endif
