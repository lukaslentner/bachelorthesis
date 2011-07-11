#ifndef CLASS_PERIODIC1DMODEL
#define CLASS_PERIODIC1DMODEL

#include "AbstractModel.cpp"

class Periodic1DModel : public AbstractModel {
    
  public:
    
    Periodic1DModel(int n_parameter) : AbstractModel(n_parameter) {};
    
    int getNb() {
    
      return n;
    
    };
    
    int getI1(int b) {
    
      return b - 1;
    
    };
    
    int getI2(int b) {
    
      return b % n;
    
    };

};

#endif
