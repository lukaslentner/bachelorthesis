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
    double acE;
    double avC;
    double erC;
    double acC;
    double avS;
    double erS;
    double acS;

  public:
  
    AbstractAlgorithm(AbstractModel* model_parameter) {
    
      model = model_parameter;
      t = 0;
      
      avE = 0;
      erE = 0;
      acE = 0;
      
      avC = 0;
      erC = 0;
      acC = 0;
      
      avS = 0;
      erS = 0;
      acS = 0;
    
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
    
    double getAutoCOfEnergy() {
    
      return acE;
    
    };
    
    double getAverageCHeat() {
    
      return avC;
    
    };
    
    double getStdDvOfCHeat() {
    
      return erC;
    
    };
    
    double getAutoCOfCHeat() {
    
      return acC;
    
    };
    
    double getAverageSuscept() {
    
      return avS;
    
    };
    
    double getStdDvOfSuscept() {
    
      return erS;
    
    };
    
    double getAutoCOfSuscept() {
    
      return acS;
    
    };
    
};

#endif
