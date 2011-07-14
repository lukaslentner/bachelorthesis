#ifndef CLASS_EDALGORITHM
#define CLASS_EDALGORITHM

#include <tnt/tnt_array2d.h>
#include <jama/jama_eig.h>

#include "AbstractAlgorithm.cpp"

class EDAlgorithm : public AbstractAlgorithm {

  protected:
  
    int twoPowN;

    void hAction(TNT::Array2D<double> h, int s, TNT::Array1D<int> mapS) {

      int tempS;
      double value;

      for(int b = 1; b <= model->getNb(); b++) {
      
        tempS = s;
        value = 1;
        szAction(model->getI2(b), &tempS, &value);
        szAction(model->getI1(b), &tempS, &value);
        if(tempS >= 0) h[mapS[s]][mapS[tempS]] += value;
        
        tempS = s;
        value = 0.5;
        smAction(model->getI2(b), &tempS, &value);
        spAction(model->getI1(b), &tempS, &value);
        if(tempS >= 0) h[mapS[s]][mapS[tempS]] += value;
        
        tempS = s;
        value = 0.5;
        spAction(model->getI2(b), &tempS, &value);
        smAction(model->getI1(b), &tempS, &value);
        if(tempS >= 0) h[mapS[s]][mapS[tempS]] += value;
      
      }
      
    };

    void szAction(int i, int* s_pointer, double* value_pointer) {
    
      if(*s_pointer == -1) return;
      
      *value_pointer *= 0.5;

      if(~*s_pointer & (int(1) << i)) *value_pointer *= -1;

    };

    void spAction(int i, int* s_pointer, double* value_pointer) {
    
      if(*s_pointer == -1) return;
      
      if(*s_pointer & (int(1) << i)) {
      
        *s_pointer = -1;
      
      } else {
      
        *s_pointer ^= int(1) << i;
      
      }

    };

    void smAction(int i, int* s_pointer, double* value_pointer) {
    
      if(*s_pointer == -1) return;
      
      if(*s_pointer & (int(1) << i)) {
      
        *s_pointer ^= int(1) << i;
      
      } else {
      
        *s_pointer = -1;
      
      }

    };
    
    int getNumOf1Bits(int value) {
    
      value = ((value & 0xaaaaaaaa) >> 1)  + (value & 0x55555555);
      value = ((value & 0xcccccccc) >> 2)  + (value & 0x33333333);
      value = ((value & 0xf0f0f0f0) >> 4)  + (value & 0x0f0f0f0f);
      value = ((value & 0xff00ff00) >> 8)  + (value & 0x00ff00ff);
      value = ((value & 0xffff0000) >> 16) + (value & 0x0000ffff);
      
      return value;
    
    };

  public:
    
    EDAlgorithm(AbstractModel* model_parameter) : AbstractAlgorithm(model_parameter) {
    
      twoPowN = int(1) << model->getN();
    
    };
    
    ~EDAlgorithm() {};
    
    void runTemperatureRound() {

      double sumOfE        = 0;
      double sumOfESquared = 0;
      double z             = 0;
      
      TNT::Array2D<int> mapSIndex(model->getN() + 1, twoPowN, -1); // 2nd dimension needs to be minimum "choose n/2 from n", but I was lazy ...
      TNT::Array1D<int> mapS(twoPowN, -1);
      TNT::Array1D<int> sIndexLength(model->getN() + 1, 0);
      
      int g;
      for(int s = 0; s < twoPowN; s++) {

        g = getNumOf1Bits(s);
        mapSIndex[g][sIndexLength[g]] = s;
        mapS[s] = sIndexLength[g];
        sIndexLength[g]++;

      }
      
      for(int g = 0; g <= model->getN(); g++) {
      
        TNT::Array2D<double> h(sIndexLength[g], sIndexLength[g], 0.0);
        TNT::Array1D<double> e(sIndexLength[g], 0.0);
        
        for(int sIndex = 0; sIndex < sIndexLength[g]; sIndex++) {
          hAction(h, mapSIndex[g][sIndex], mapS);
        }
        
        JAMA::Eigenvalue<double> eFactory(h);
        eFactory.getRealEigenvalues(e);
        
        for(int sIndex = 0; sIndex < sIndexLength[g]; sIndex++) {
          sumOfE        += exp(-e[sIndex] / t) * e[sIndex];
          sumOfESquared += exp(-e[sIndex] / t) * pow(e[sIndex], 2);
          z             += exp(-e[sIndex] / t);
        }
      
      }

      avE = sumOfE / z;
      erE = 0;
      avC = ((sumOfESquared / z) - pow(sumOfE / z, 2)) / pow(t, 2);
      
    };
    
};

#endif
