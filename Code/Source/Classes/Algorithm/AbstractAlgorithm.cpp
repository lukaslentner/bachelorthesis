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
    long atE;
    double avH;
    double erH;
    long atH;
    double avM;
    double erM;
    long atM;
    double avS;
    double erS;
    long atS;

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
      atE = 0;
      
      avH = 0;
      erH = 0;
      atH = 0;
      
      avM = 0;
      erM = 0;
      atM = 0;
      
      avS = 0;
      erS = 0;
      atS = 0;
    
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
      atE = 0;
      
      avH = 0;
      erH = 0;
      atH = 0;
      
      avM = 0;
      erM = 0;
      atM = 0;
      
      avS = 0;
      erS = 0;
      atS = 0;
    
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
    
    long getAutoCorrelationTimeOfEnergy() {
    
      return atE;
    
    };
    
    double getAverageHeatCapacity() {
    
      return avH;
    
    };
    
    double getErrorOfHeatCapacity() {
    
      return erH;
    
    };
    
    long getAutoCorrelationTimeOfHeatCapacity() {
    
      return atH;
    
    };
    
    double getAverageMagnetization() {
    
      return avM;
    
    };
    
    double getErrorOfMagnetization() {
    
      return erM;
    
    };
    
    long getAutoCorrelationTimeOfMagnetization() {
    
      return atM;
    
    };
    
    double getAverageSusceptibility() {
    
      return avS;
    
    };
    
    double getErrorOfSusceptibility() {
    
      return erS;
    
    };
    
    long getAutoCorrelationTimeOfSusceptibility() {
    
      return atS;
    
    };
    
};

#endif
