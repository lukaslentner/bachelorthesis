#ifndef CLASS_ISINGENERGYANALYZER
#define CLASS_ISINGENERGYANALYZER

#include "AbstractAnalyzer.cpp"

class IsingEnergyAnalyzer : public AbstractAnalyzer {
  
  public:
  
    IsingEnergyAnalyzer(AbstractAlgorithm* algorithm_parameter, AbstractLattice* lattice_parameter) : AbstractAnalyzer(algorithm_parameter, lattice_parameter) {};

    ~IsingEnergyAnalyzer() {};
    
    const char* getQuantityName() {

      return "Energy";
    
    };
    
    double getQuantity(long time) {
    
      return algorithm->getEnergyMeasurement(time);
    
    };
  
};

#endif
