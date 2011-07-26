#ifndef CLASS_MANALYZER
#define CLASS_MANALYZER

#include "AbstractAnalyzer.cpp"

class MAnalyzer : public AbstractAnalyzer {
  
  public:
  
    MAnalyzer(AbstractAlgorithm* algorithm_parameter, AbstractLattice* lattice_parameter) : AbstractAnalyzer(algorithm_parameter, lattice_parameter) {};

    ~MAnalyzer() {};
    
    const char* getQuantityName() {
    
      return "Magnetization";
    
    };
    
    double getQuantity(long time) {
    
      return algorithm->getMagMeasurement(time);
    
    };
  
};

#endif
