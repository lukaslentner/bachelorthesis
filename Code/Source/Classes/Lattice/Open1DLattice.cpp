#ifndef CLASS_OPEN1DLATTICE
#define CLASS_OPEN1DLATTICE

#include "AbstractLattice.cpp"

class Open1DLattice : public AbstractLattice {
    
  public:
    
    Open1DLattice(int n_parameter) : AbstractLattice(n_parameter) {};
    
    int *getNeighbours(int i) {
    
      int *neighbours;
    
      if(i == 0) {
      
        neighbours = new int(2);
        neighbours[0] = 1;
        neighbours[1] = i + 1;
      
      } else if(i == n - 1) {
      
        neighbours = new int(2);
        neighbours[0] = 1;
        neighbours[1] = i - 1;
      
      } else {
      
        neighbours = new int(3);
        neighbours[0] = 2;
        neighbours[1] = i - 1;
        neighbours[2] = i + 1;
      
      }
    
      return neighbours;
    
    };
    
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
