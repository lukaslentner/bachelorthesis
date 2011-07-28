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
    double *magnetisationMeasurements;
    double *absoluteMagnetisationMeasurements;
    
    double t;
    
    double averageEnergy;
    double errorOfEnergy;
    long autoCorrelationTimeOfEnergy;
    
    double averageHeatCapacity;
    double errorOfHeatCapacity;
    long autoCorrelationTimeOfHeatCapacity;
    
    double averageMagnetisation;
    double errorOfMagnetisation;
    long autoCorrelationTimeOfMagnetisation;
    
    double averageSusceptibility;
    double errorOfSusceptibility;
    long autoCorrelationTimeOfSusceptibility;
    
    double averageAbsoluteMagnetisation;
    double errorOfAbsoluteMagnetisation;
    long autoCorrelationTimeOfAbsoluteMagnetisation;
    
    double averageAbsoluteSusceptibility;
    double errorOfAbsoluteSusceptibility;
    long autoCorrelationTimeOfAbsoluteSusceptibility;

  public:
  
    AbstractAlgorithm(AbstractLattice* lattice_parameter, int measureCount_parameter) {
    
      lattice = lattice_parameter;
      measureCount = measureCount_parameter;
      runCount = measureCount * 3 / 2;
      
      energyMeasurements                   = new double[measureCount];
      magnetisationMeasurements            = new double[measureCount];
      absoluteMagnetisationMeasurements    = new double[measureCount];
    
    };
    
    ~AbstractAlgorithm() {
    
      delete[] absoluteMagnetisationMeasurements;
      delete[] magnetisationMeasurements;
      delete[] energyMeasurements;
      
    };
    
    long getMeasureCount() {
    
      return measureCount;
    
    };
    
    long getRunCount() {
    
      return runCount;
    
    };
    
    virtual void runTemperatureRound(double t_parameter) {
    
      t = t_parameter;
      
      averageEnergy = 0;
      errorOfEnergy = 0;
      autoCorrelationTimeOfEnergy = 0;
      
      averageHeatCapacity = 0;
      errorOfHeatCapacity = 0;
      autoCorrelationTimeOfHeatCapacity = 0;
      
      averageMagnetisation = 0;
      errorOfMagnetisation = 0;
      autoCorrelationTimeOfMagnetisation = 0;
      
      averageSusceptibility = 0;
      errorOfSusceptibility = 0;
      autoCorrelationTimeOfSusceptibility = 0;
      
      averageAbsoluteMagnetisation = 0;
      errorOfAbsoluteMagnetisation = 0;
      autoCorrelationTimeOfAbsoluteMagnetisation = 0;
      
      averageAbsoluteSusceptibility = 0;
      errorOfAbsoluteSusceptibility = 0;
      autoCorrelationTimeOfAbsoluteSusceptibility = 0;
    
    };
    
    double getTemperature() {
    
      return t;
    
    };
    
    double getEnergyMeasurement(long time) {
    
      return energyMeasurements[time];
    
    };
    
    double getMagnetisationMeasurement(long time) {
    
      return magnetisationMeasurements[time];
    
    };
    
    double getAbsoluteMagnetisationMeasurement(long time) {
    
      return absoluteMagnetisationMeasurements[time];
    
    };
    
    double getAverageEnergy() {
    
      return averageEnergy;
    
    };
    
    double getErrorOfEnergy() {
    
      return errorOfEnergy;
    
    };
    
    long getAutoCorrelationTimeOfEnergy() {
    
      return autoCorrelationTimeOfEnergy;
    
    };
    
    double getAverageHeatCapacity() {
    
      return averageHeatCapacity;
    
    };
    
    double getErrorOfHeatCapacity() {
    
      return errorOfHeatCapacity;
    
    };
    
    long getAutoCorrelationTimeOfHeatCapacity() {
    
      return autoCorrelationTimeOfHeatCapacity;
    
    };
    
    double getAverageMagnetisation() {
    
      return averageMagnetisation;
    
    };
    
    double getErrorOfMagnetisation() {
    
      return errorOfMagnetisation;
    
    };
    
    long getAutoCorrelationTimeOfMagnetisation() {
    
      return autoCorrelationTimeOfMagnetisation;
    
    };
    
    double getAverageSusceptibility() {
    
      return averageSusceptibility;
    
    };
    
    double getErrorOfSusceptibility() {
    
      return errorOfSusceptibility;
    
    };
    
    long getAutoCorrelationTimeOfSusceptibility() {
    
      return autoCorrelationTimeOfSusceptibility;
    
    };
    
    double getAverageAbsoluteMagnetisation() {
    
      return averageAbsoluteMagnetisation;
    
    };
    
    double getErrorOfAbsoluteMagnetisation() {
    
      return errorOfAbsoluteMagnetisation;
    
    };
    
    long getAutoCorrelationTimeOfAbsoluteMagnetisation() {
    
      return autoCorrelationTimeOfAbsoluteMagnetisation;
    
    };
    
    double getAverageAbsoluteSusceptibility() {
    
      return averageAbsoluteSusceptibility;
    
    };
    
    double getErrorOfAbsoluteSusceptibility() {
    
      return errorOfAbsoluteSusceptibility;
    
    };
    
    long getAutoCorrelationTimeOfAbsoluteSusceptibility() {
    
      return autoCorrelationTimeOfAbsoluteSusceptibility;
    
    };
    
};

#endif
