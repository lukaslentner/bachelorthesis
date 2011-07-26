#ifndef CLASS_PERIODIC1DLATTICE
#define CLASS_PERIODIC1DLATTICE

#include "AbstractLattice.cpp"

class Periodic1DLattice : public AbstractLattice {
    
  public:
    
    Periodic1DLattice(int n_parameter) : AbstractLattice(n_parameter) {};
    
    int getNb() {
    
      return n;
    
    };
    
    int *getNeighbours(int i) {
    
      int *neighbours = new int(3);
      neighbours[0] = 2;
      neighbours[1] = (i - 1 + n) % n;
      neighbours[2] = (i + 1) % n;
    
      return neighbours;
    
    };
    
    int getI1(int b) {
    
      return b - 1;
    
    };
    
    int getI2(int b) {
    
      return b % n;
    
    };

};

#endif
