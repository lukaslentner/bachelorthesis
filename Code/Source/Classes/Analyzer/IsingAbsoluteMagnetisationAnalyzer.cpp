#ifndef CLASS_ISINGABSOLUTEMAGNETISATION
#define CLASS_ISINGABSOLUTEMAGNETISATION

#include "AbstractAnalyzer.cpp"

class IsingAbsoluteMagnetisationAnalyzer : public AbstractAnalyzer {
  
  public:
  
    IsingAbsoluteMagnetisationAnalyzer(AbstractAlgorithm* algorithm_parameter, AbstractLattice* lattice_parameter) : AbstractAnalyzer(algorithm_parameter, lattice_parameter) {};

    ~IsingAbsoluteMagnetisationAnalyzer() {};
    
    const char* getQuantityName() {
    
      return "Absolute Magnetization";
    
    };
    
    double getQuantity(long time) {
    
      return algorithm->getAbsoluteMagnetisationMeasurement(time);
    
    };
  
};

#endif
