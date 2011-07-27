#ifndef CLASS_SANALYZER
#define CLASS_SANALYZER

#include "AbstractAnalyzer.cpp"

class SAnalyzer : public AbstractAnalyzer {
  
  public:
  
    SAnalyzer(AbstractAlgorithm* algorithm_parameter, AbstractLattice* lattice_parameter) : AbstractAnalyzer(algorithm_parameter, lattice_parameter) {};

    ~SAnalyzer() {};
    
    const char* getQuantityName() {
    
      return "Susceptibility";
    
    };
    
    double getQuantity(long time) {
    
      return (pow(algorithm->getMagMeasurement(time), 2) - pow(algorithm->getAverageMagnetization(), 2)) * lattice->getN() / algorithm->getTemperature();
    
    };
  
};

#endif
