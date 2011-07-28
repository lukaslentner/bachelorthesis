#ifndef CLASS_ISINGMAGNETISATIONANALYZER
#define CLASS_ISINGMAGNETISATIONANALYZER

#include "AbstractAnalyzer.cpp"

class IsingMagnetisationAnalyzer : public AbstractAnalyzer {
  
  public:
  
    IsingMagnetisationAnalyzer(AbstractAlgorithm* algorithm_parameter, AbstractLattice* lattice_parameter) : AbstractAnalyzer(algorithm_parameter, lattice_parameter) {};

    ~IsingMagnetisationAnalyzer() {};
    
    const char* getQuantityName() {
    
      return "Magnetization";
    
    };
    
    double getQuantity(long time) {
    
      return algorithm->getMagnetisationMeasurement(time);
    
    };
  
};

#endif
