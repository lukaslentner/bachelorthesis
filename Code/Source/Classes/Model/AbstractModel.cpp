#ifndef CLASS_ABSTRACTMODEL
#define CLASS_ABSTRACTMODEL

class AbstractModel {

  protected:
  
    int n;

  public:

    AbstractModel(int n_parameter) {

      n = n_parameter;
        
    };

    int getN() {
    
      return n;
    
    };

    virtual int getNb() = 0;
    virtual int getI1(int b) = 0;
    virtual int getI2(int b) = 0;
    
};

#endif
