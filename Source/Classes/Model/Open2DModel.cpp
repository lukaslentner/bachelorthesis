#ifndef CLASS_OPEN2DMODEL
#define CLASS_OPEN2DMODEL

#include <cmath>

#include "AbstractModel.cpp"

class Open2DModel : public AbstractModel {

  protected:
  
    int m;
    
  public:
    
    Open2DModel(int n_parameter) : AbstractModel(n_parameter) {
    
      m = sqrt((float) n_parameter);
      if(pow((int) m, 2) != n_parameter) throw "[Open2DModel] Error: You choose a 2D model, please input a square number as n";
    
    };
    
    int getNb() {
    
      return 2 * (n - m);
    
    };
    
    int getI1(int b) {
    
      if(b <= n - m) {
      
        return (((b - 1) / (m - 1)) * m) + ((b - 1) % (m - 1));
      
      } else {
      
        return (((b - 1 - (n - m)) / m) * m) + ((b - 1 - (n - m)) % m);
      
      }
    
    };
    
    int getI2(int b) {
    
      if(b <= n - m) {
      
        return (((b - 1) / (m - 1)) * m) + ((b - 1) % (m - 1)) + 1;
      
      } else {
      
        return (((b - 1 - (n - m)) / m) * m) + ((b - 1 - (n - m)) % m) + m;
      
      }
    
    };

};

#endif
