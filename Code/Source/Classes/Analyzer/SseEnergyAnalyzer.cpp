#ifndef CLASS_SSEENERGYANALYZER
#define CLASS_SSEENERGYANALYZER

#include "AbstractAnalyzer.cpp"

class SseEnergyAnalyzer : public AbstractAnalyzer {
  
  public:
  
    SseEnergyAnalyzer(AbstractAlgorithm* algorithm_parameter, AbstractLattice* lattice_parameter) : AbstractAnalyzer(algorithm_parameter, lattice_parameter) {};

    ~SseEnergyAnalyzer() {};
    
    const char* getQuantityName() {

      return "Energy";
    
    };
    
    double getQuantity(long time) {
    
      return algorithm->getEnergyMeasurement(time);
    
    };
  
};

#endif
