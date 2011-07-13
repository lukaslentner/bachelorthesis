#ifndef CLASS_ABSTRACTALGORITHM
#define CLASS_ABSTRACTALGORITHM

#include <sstream>
#include <string>

class AbstractAlgorithm {

  protected:
  
    AbstractModel* model;
    long double t;
    long double avE;
    long double erE;
    long double avC;
    long double erC;

  public:
  
    AbstractAlgorithm(AbstractModel* model_parameter) {
    
      model = model_parameter;
      t = 0;
      avE = 0;
      erE = 0;
      avC = 0;
      erC = 0;
    
    };

    virtual void runTemperatureRound() = 0;
    
    void setTemperature(long double t_parameter) {
    
      t = t_parameter;
    
    };
    
    long double getAverageEnergy() {
    
      return avE;
    
    };
    
    long double getStdDvOfEnergy() {
    
      return erE;
    
    };
    
    long double getAverageCHeat() {
    
      return avC;
    
    };
    
    long double getStdDvOfCHeat() {
    
      return erC;
    
    };
    
    std::string intArrayToString(int *a_parameter, int c_parameter) {
    
      std::stringstream out;
    
      for(int i = 0; i < c_parameter; i++) {
        if(i != 0) out << ",";
        out << a_parameter[i];
      }
      
      return out.str();
    
    };
    
};

#endif
