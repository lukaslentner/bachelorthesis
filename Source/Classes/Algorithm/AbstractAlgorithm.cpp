#ifndef CLASS_ABSTRACTALGORITHM
#define CLASS_ABSTRACTALGORITHM

#include <sstream>
#include <string>

class AbstractAlgorithm {

  protected:
  
    AbstractModel* model;
    double t;
    double avE;
    double erE;
    double avC;
    double erC;

  public:
  
    AbstractAlgorithm(AbstractModel* model_parameter) {
    
      model = model_parameter;
      t = 0;
      avE = 0;
      erE = 0;
      avC = 0;
    
    };

    virtual void runTemperatureRound() = 0;
    
    void setTemperature(double t_parameter) {
    
      t = t_parameter;
    
    };
    
    double getAverageEnergy() {
    
      return avE;
    
    };
    
    double getStdDvOfEnergy() {
    
      return erE;
    
    };
    
    double getAverageCHeat() {
    
      return avC;
    
    };
    
};

#endif
