#ifndef CLASS_EDALGORITHM
#define CLASS_EDALGORITHM

#include <tnt/tnt_array2d.h>
#include <jama/jama_eig.h>

#include "AbstractAlgorithm.cpp"

class EDAlgorithm : public AbstractAlgorithm {

  protected:
  
    int twoPowN;
    TNT::Array1D<double> *e;

    void hAction(TNT::Array2D<double> hg, int s, TNT::Array1D<int> mapS) {

      for(int b = 1; b <= model->getNb(); b++) {

        bool i1Up = s & (int(1) << model->getI1(b));
        bool i2Up = s & (int(1) << model->getI2(b));
        
        hg[mapS[s]][mapS[s]] += i1Up == i2Up ? 0.25 : -0.25;
        
        if(i1Up != i2Up) hg[mapS[s]][mapS[s ^ (int(1) << model->getI1(b)) ^ (int(1) << model->getI2(b))]] += 0.5;
      
      }
      
    };
    
    int getNumOf1Bits(int value) {
    
      value = ((value & 0xaaaaaaaa) >> 1 ) + (value & 0x55555555);
      value = ((value & 0xcccccccc) >> 2 ) + (value & 0x33333333);
      value = ((value & 0xf0f0f0f0) >> 4 ) + (value & 0x0f0f0f0f);
      value = ((value & 0xff00ff00) >> 8 ) + (value & 0x00ff00ff);
      value = ((value & 0xffff0000) >> 16) + (value & 0x0000ffff);
      
      return value;
    
    };

  public:
    
    EDAlgorithm(AbstractModel* model_parameter) : AbstractAlgorithm(model_parameter) {
    
      twoPowN = int(1) << model->getN();
      
      TNT::Array2D<int> mapSIndex(model->getN() + 1, twoPowN, 0); // 2nd dimension needs to be minimum "choose n/2 from n", but I was lazy ...
      TNT::Array1D<int> mapS(twoPowN, 0);
      TNT::Array1D<int> sIndexLength(model->getN() + 1, 0);
      
      e = new TNT::Array1D<double>(twoPowN, 0.0);
      int eIndex = 0;
      
      for(int s = 0; s < twoPowN; s++) {
        int g = getNumOf1Bits(s);
        mapSIndex[g][sIndexLength[g]] = s;
        mapS[s] = sIndexLength[g];
        sIndexLength[g]++;
      }
      
      for(int g = 0; g <= model->getN() / 2; g++) {
      
        TNT::Array2D<double> hg(sIndexLength[g], sIndexLength[g], 0.0);
        TNT::Array1D<double> eg(sIndexLength[g], 0.0);
        
        for(int sIndex = 0; sIndex < sIndexLength[g]; sIndex++) {
          hAction(hg, mapSIndex[g][sIndex], mapS);
        }
        
        std::cerr << "Diagonalize matrix " << (g + 1) << " von " << ((model->getN() / 2) + 1) << " [" << sIndexLength[g] << "²]" << std::endl;
        
        JAMA::Eigenvalue<double> eFactory(hg);
        eFactory.getRealEigenvalues(eg);
        
        for(int sIndex = 0; sIndex < sIndexLength[g]; sIndex++) {
        
          (*e)[eIndex] = eg[sIndex];
          eIndex++;
          if(model->getN() % 2 != 0 || g != model->getN() / 2) {
            (*e)[eIndex] = eg[sIndex];
            eIndex++;
          }
        }
      
      }
    
    };
    
    ~EDAlgorithm() {
    
      delete e;
    
    };
    
    void runTemperatureRound() {

      double sumOfE = 0;
      double sumOfESquared = 0;
      double z = 0;
      
      for(int s = 0; s < twoPowN; s++) {
        double weight = exp(-(*e)[s] / t);
        sumOfE += weight * (*e)[s];
        sumOfESquared += weight * pow((*e)[s], 2);
        z += weight;
      }

      avE = sumOfE / z;
      erE = 0;
      avC = ((sumOfESquared / z) - pow(sumOfE / z, 2)) / pow(t, 2);
      
    };
    
};

#endif
