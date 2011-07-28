#ifndef CLASS_ISINGABSOLUTESUSCEPTIBILITYANALYZER
#define CLASS_ISINGABSOLUTESUSCEPTIBILITYANALYZER

#include "AbstractAnalyzer.cpp"

class IsingAbsoluteSusceptibilityAnalyzer : public AbstractAnalyzer {
  
  public:
  
    IsingAbsoluteSusceptibilityAnalyzer(AbstractAlgorithm* algorithm_parameter, AbstractLattice* lattice_parameter) : AbstractAnalyzer(algorithm_parameter, lattice_parameter) {};

    ~IsingAbsoluteSusceptibilityAnalyzer() {};
    
    const char* getQuantityName() {
    
      return "Absolute Susceptibility";
    
    };
    
    double getQuantity(long time) {
    
      return (pow(algorithm->getAbsoluteMagnetisationMeasurement(time), 2) - pow(algorithm->getAverageAbsoluteMagnetisation(), 2)) * lattice->getN() / algorithm->getTemperature();
    
    };
  
};

#endif
