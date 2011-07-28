#ifndef CLASS_ISINGSUSCEPTIBILITYANALYZER
#define CLASS_ISINGSUSCEPTIBILITYANALYZER

#include "AbstractAnalyzer.cpp"

class IsingSusceptibilityAnalyzer : public AbstractAnalyzer {
  
  public:
  
    IsingSusceptibilityAnalyzer(AbstractAlgorithm* algorithm_parameter, AbstractLattice* lattice_parameter) : AbstractAnalyzer(algorithm_parameter, lattice_parameter) {};

    ~IsingSusceptibilityAnalyzer() {};
    
    const char* getQuantityName() {
    
      return "Susceptibility";
    
    };
    
    double getQuantity(long time) {
    
      return (pow(algorithm->getMagnetisationMeasurement(time), 2) - pow(algorithm->getAverageMagnetisation(), 2)) * lattice->getN() / algorithm->getTemperature();
    
    };
  
};

#endif
