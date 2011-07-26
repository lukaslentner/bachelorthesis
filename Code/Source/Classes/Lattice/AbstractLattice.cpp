#ifndef CLASS_ABSTRACTLATTICE
#define CLASS_ABSTRACTLATTICE

class AbstractLattice {

  protected:
  
    int n;

  public:

    AbstractLattice(int n_parameter) {

      n = n_parameter;
        
    };

    int getN() {
    
      return n;
    
    };
    
    virtual int *getNeighbours(int i) = 0;

    virtual int getNb() = 0;
    virtual int getI1(int b) = 0;
    virtual int getI2(int b) = 0;
    
};

#endif
