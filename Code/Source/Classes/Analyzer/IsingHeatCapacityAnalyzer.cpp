#ifndef CLASS_ISINGHEATCAPACITYANALYZER
#define CLASS_ISINGHEATCAPACITYANALYZER

#include "AbstractAnalyzer.cpp"

class IsingHeatCapacityAnalyzer : public AbstractAnalyzer {
  
  public:
  
    IsingHeatCapacityAnalyzer(AbstractAlgorithm* algorithm_parameter, AbstractLattice* lattice_parameter) : AbstractAnalyzer(algorithm_parameter, lattice_parameter) {};

    ~IsingHeatCapacityAnalyzer() {};
    
    const char* getQuantityName() {
    
      return "Heat Capacity";
    
    };
    
    double getQuantity(long time) {
    
      return (pow(algorithm->getEnergyMeasurement(time), 2) - pow(algorithm->getAverageEnergy(), 2)) * lattice->getN() / pow(algorithm->getTemperature(), 2);
    
    };
  
};

#endif
