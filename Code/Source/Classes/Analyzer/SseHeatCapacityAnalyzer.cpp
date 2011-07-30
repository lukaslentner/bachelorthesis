#ifndef CLASS_SSEHEATCAPACITYANALYZER
#define CLASS_SSEHEATCAPACITYANALYZER

#include "AbstractAnalyzer.cpp"

class SseHeatCapacityAnalyzer : public AbstractAnalyzer {
  
  public:
  
    SseHeatCapacityAnalyzer(AbstractAlgorithm* algorithm_parameter, AbstractLattice* lattice_parameter) : AbstractAnalyzer(algorithm_parameter, lattice_parameter) {};

    ~SseHeatCapacityAnalyzer() {};
    
    const char* getQuantityName() {
    
      return "Heat Capacity";
    
    };
    
    double getQuantity(long time) {
    
      return (pow(algorithm->getEnergyMeasurement(time), 2) * lattice->getN() / pow(algorithm->getTemperature(), 2)) - (pow(algorithm->getAverageEnergy(), 2) * lattice->getN() / pow(algorithm->getTemperature(), 2)) + (algorithm->getAverageEnergy() / algorithm->getTemperature());
    
    };
  
};

#endif
