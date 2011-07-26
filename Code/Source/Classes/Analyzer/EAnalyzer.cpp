#ifndef CLASS_EANALYZER
#define CLASS_EANALYZER

#include "AbstractAnalyzer.cpp"

class EAnalyzer : public AbstractAnalyzer {
  
  public:
  
    EAnalyzer(AbstractAlgorithm* algorithm_parameter, AbstractLattice* lattice_parameter) : AbstractAnalyzer(algorithm_parameter, lattice_parameter) {};

    ~EAnalyzer() {};
    
    const char* getQuantityName() {
    
      return "Energy";
    
    };
    
    double getQuantity(long time) {
    
      return algorithm->getEnergyMeasurement(time);
    
    };
  
};

#endif
