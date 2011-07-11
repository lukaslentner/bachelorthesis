#ifndef CLASS_EDALGORITHM
#define CLASS_EDALGORITHM

#include <tnt/tnt_array2d.h>
#include <jama/jama_eig.h>

#include "AbstractAlgorithm.cpp"

class EDAlgorithm : public AbstractAlgorithm {

  protected:
  
    int twoPowN;
    
    void hAction(TNT::Array2D<double> h, int bs) {
    
      int tempBs;
      double value;

      for(int b = 1; b <= model->getNb(); b++) {
      
        tempBs = bs;
        value = 2;
        szAction(model->getI2(b), &tempBs, &value);
        szAction(model->getI1(b), &tempBs, &value);
        if(tempBs >= 0) h[bs][tempBs] += value;
        
        tempBs = bs;
        value = 1;
        smAction(model->getI2(b), &tempBs, &value);
        spAction(model->getI1(b), &tempBs, &value);
        if(tempBs >= 0) h[bs][tempBs] += value;
        
        tempBs = bs;
        value = 1;
        spAction(model->getI2(b), &tempBs, &value);
        smAction(model->getI1(b), &tempBs, &value);
        if(tempBs >= 0) h[bs][tempBs] += value;
      
      }
      
    };

    void szAction(int i, int* state_pointer, double* value_pointer) {
    
      if(*state_pointer == -1) return;
      
      *value_pointer *= 0.5;

      if(~*state_pointer & (int) pow(2, i)) *value_pointer *= -1;

    };

    void spAction(int i, int* state_pointer, double* value_pointer) {
    
      if(*state_pointer == -1) return;
      
      if(*state_pointer & (int) pow(2, i)) {
      
        *state_pointer = -1;
      
      } else {
      
        *state_pointer ^= (int) pow(2, i);
      
      }

    };

    void smAction(int i, int* state_pointer, double* value_pointer) {
    
      if(*state_pointer == -1) return;
      
      if(*state_pointer & (int) pow(2, i)) {
      
        *state_pointer ^= (int) pow(2, i);
      
      } else {
      
        *state_pointer = -1;
      
      }

    };

  public:
    
    EDAlgorithm(AbstractModel* model_parameter) : AbstractAlgorithm(model_parameter) {
    
      twoPowN = pow(2, model->getN());
    
    };
    
    ~EDAlgorithm() {};
    
    void runTemperatureRound() {

      TNT::Array2D<double> h(twoPowN, twoPowN, 0.0);
      TNT::Array2D<double> d(twoPowN, twoPowN, 0.0);

      for(int bs = 0; bs < twoPowN; bs++) {
        hAction(h, bs);
      }

      JAMA::Eigenvalue<double> e(h);
  
      e.getD(d);

      double sumOfE        = 0;
      double sumOfESquared = 0;
      double z             = 0;

      for(int bs = 0; bs < twoPowN; bs++) {
        sumOfE        += exp(-h[bs][bs] / t) * h[bs][bs];
        sumOfESquared += exp(-h[bs][bs] / t) * pow(h[bs][bs], 2);
        z             += exp(-h[bs][bs] / t);
      }
      
      avE = sumOfE / z;
      erE = 0;
      avC = ((sumOfESquared / z) - pow(sumOfE / z, 2)) / pow(t, 2);
      erC = 0;
      
    };
    
};

#endif
