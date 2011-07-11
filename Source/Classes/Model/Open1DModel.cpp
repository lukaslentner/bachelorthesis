#ifndef CLASS_OPEN1DMODEL
#define CLASS_OPEN1DMODEL

#include "AbstractModel.cpp"

class Open1DModel : public AbstractModel {
    
  public:
    
    Open1DModel(int n_parameter) : AbstractModel(n_parameter) {};
    
    int getNb() {
    
      return n - 1;
    
    };
    
    int getI1(int b) {
    
      return b - 1;
    
    };
    
    int getI2(int b) {
    
      return b;
    
    };

};

#endif
