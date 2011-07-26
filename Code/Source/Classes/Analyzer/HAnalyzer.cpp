#ifndef CLASS_HANALYZER
#define CLASS_HANALYZER

#include "AbstractAnalyzer.cpp"

class HAnalyzer : public AbstractAnalyzer {
  
  public:
  
    HAnalyzer(AbstractAlgorithm* algorithm_parameter, AbstractLattice* lattice_parameter) : AbstractAnalyzer(algorithm_parameter, lattice_parameter) {};

    ~HAnalyzer() {};
    
    const char* getQuantityName() {
    
      return "Specific Heat";
    
    };
    
    double getQuantity(long time) {
    
      return (pow(algorithm->getEnergyMeasurement(time), 2) - pow(algorithm->getAverageEnergy(), 2)) / lattice->getN() / pow(algorithm->getTemperature(), 2);
    
    };
  
};

#endif
