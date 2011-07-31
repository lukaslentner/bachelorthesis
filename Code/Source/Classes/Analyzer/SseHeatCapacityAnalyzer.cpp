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
    
      double averageNr = ((algorithm->getAverageEnergy() - (double(lattice->getNb()) / lattice->getN() / 4)) * -lattice->getN() / algorithm->getTemperature());
      
      return (pow(-algorithm->getEnergyMeasurement(time) * lattice->getN() / algorithm->getTemperature(), 2) - pow(averageNr, 2) - averageNr)/lattice->getN();

    };
  
};

#endif
