#ifndef CLASS_PERIODIC2DMODEL
#define CLASS_PERIODIC2DMODEL

#include <cmath>

#include "AbstractModel.cpp"

class Periodic2DModel : public AbstractModel {

  protected:
  
    int m;
    
  public:
    
    Periodic2DModel(int n_parameter) : AbstractModel(n_parameter) {
    
      m = sqrt((double) n_parameter);
      if(pow((int) m, 2) != n_parameter) throw "[Periodic2DModel] Error: You choose a 2D model, please input a square number as n";
    
    };
    
    int getNb() {
    
      return 2 * n;
    
    };
    
    int getI1(int b) {
    
      return (b - 1) / 2;
    
    };
    
    int getI2(int b) {
    
      if(b & 1) {
      
        return (((b - 1) / 2) + m) % n;
      
      } else {
      
        return ((((b - 1) / 2) + 1) % m) + ((((b - 1) / 2) / m) * m);
      
      }
    
    };

};

#endif
