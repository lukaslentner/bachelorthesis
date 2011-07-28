#ifndef CLASS_ISINGSPECIFICHEATANALYZER
#define CLASS_ISINGSPECIFICHEATANALYZER

#include "AbstractAnalyzer.cpp"

class IsingSpecificHeatAnalyzer : public AbstractAnalyzer {
  
  public:
  
    IsingSpecificHeatAnalyzer(AbstractAlgorithm* algorithm_parameter, AbstractLattice* lattice_parameter) : AbstractAnalyzer(algorithm_parameter, lattice_parameter) {};

    ~IsingSpecificHeatAnalyzer() {};
    
    const char* getQuantityName() {
    
      return "Heat Capacity";
    
    };
    
    double getQuantity(long time) {
    
      return (pow(algorithm->getEnergyMeasurement(time), 2) - pow(algorithm->getAverageEnergy(), 2)) * lattice->getN() / pow(algorithm->getTemperature(), 2);
    
    };
  
};

#endif
