#ifndef CLASS_PERIODIC2DLATTICE
#define CLASS_PERIODIC2DLATTICE

#include <cmath>

#include "AbstractLattice.cpp"

class Periodic2DLattice : public AbstractLattice {

  protected:
  
    int m;
    
  public:
    
    Periodic2DLattice(int n_parameter) : AbstractLattice(n_parameter) {
    
      m = sqrt((double) n_parameter);
      if(pow((int) m, 2) != n_parameter) throw "[Periodic2DLattice] Error: You choose a 2D lattice, please input a square number as n";
    
    };
    
    int *getNeighbours(int i) {
    
      int *neighbours = new int[5];
      neighbours[0] = 4;
      neighbours[1] = i - m <  0     ? i - m + n : i - m;
      neighbours[2] = i + m >= n     ? i + m - n : i + m;
      neighbours[3] = i % m == 0     ? i + m - 1 : i - 1;
      neighbours[4] = i % m == m - 1 ? i - m + 1 : i + 1;
    
      return neighbours;
    
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
