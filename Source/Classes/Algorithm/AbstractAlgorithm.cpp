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
    double rtE;
    double avH;
    double erH;
    double rtH;
    double avS;
    double erS;
    double rtS;

  public:
  
    AbstractAlgorithm(AbstractModel* model_parameter) {
    
      model = model_parameter;
      t = 0;
      
      avE = 0;
      erE = 0;
      rtE = 0;
      
      avH = 0;
      erH = 0;
      rtH = 0;
      
      avS = 0;
      erS = 0;
      rtS = 0;
    
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
    
    double getRelTiOfEnergy() {
    
      return rtE;
    
    };
    
    double getAverageHeat() {
    
      return avH;
    
    };
    
    double getStdDvOfHeat() {
    
      return erH;
    
    };
    
    double getRelTiOfHeat() {
    
      return rtH;
    
    };
    
    double getAverageSuscept() {
    
      return avS;
    
    };
    
    double getStdDvOfSuscept() {
    
      return erS;
    
    };
    
    double getRelTiOfSuscept() {
    
      return rtS;
    
    };
    
};

#endif
