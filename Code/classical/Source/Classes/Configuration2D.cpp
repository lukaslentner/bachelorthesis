#include <iostream>
#include <string>
#include <cmath>
#include <gsl/gsl_rng.h>

using namespace std;

class Configuration2D {

  private:

    long double magneticMoment;
    long double magneticFlux;
    long double bonding;
    
    long double temperature;
    int edgeLength;
    int spinLength;
    bool *spins;
    int spinSum;
    long double energy;

    const gsl_rng_type *generatorType;
    gsl_rng *generator;

    int calculateSpinSum() {

      int spinSum = 0;

      for(int i = 0; i < spinLength; i++) {
        spinSum += getSpinValue(i);
      }

      return spinSum;

    };

    long double calculateEnergy() {

      long double sumOfSpins = 0.0;
      long double sumOfBonds = 0.0;

      for(int i = 0; i < spinLength; i++) {
        sumOfSpins += getSpinValue(i);
        sumOfBonds += (getSpinValue(i) * getSpinValue(i - edgeLength <  0 ? i - edgeLength + spinLength : i - edgeLength /* Top  neighbour */)) +
                      (getSpinValue(i) * getSpinValue(i % edgeLength == 0 ? i + edgeLength - 1          : i - 1          /* Left neighbour */));
      }

      return (-bonding * sumOfBonds) + (-magneticMoment * magneticFlux * sumOfSpins);

    };
    
  public:
    
    Configuration2D(int l, long double t) {

      magneticMoment = 1.0;
      magneticFlux   = 0.0;
      bonding        = 1.0;

      temperature = t;      
      edgeLength  = l;
      spinLength  = pow(l, 2);
      spins = new bool[spinLength];
      for(int i = 0; i < spinLength; i++) {
        spins[i]  = false;
      }
      spinSum     = 0;
      energy      = 0.0;

      gsl_rng_env_setup();
      generatorType = gsl_rng_default;
      generator = gsl_rng_alloc(generatorType);
      gsl_rng_set(generator, time(NULL));
        
    };

    ~Configuration2D() {

      delete spins;

      gsl_rng_free(generator);

    };

    int getSpinLength() {

      return spinLength;

    };

    int getSpinValue(int index) {

      return spins[index] ? 1 : -1;

    };
    
    void setTemperature(long double t) {
    
      temperature = t;
    
    };
    
    void randomizeSpins() {
      
      for(int i = 0; i < spinLength; i++) {
        spins[i] = gsl_rng_uniform_int(generator, 2);
      }

      energy  = calculateEnergy();
      spinSum = calculateSpinSum();
      
    };

    void tryFlipEvery() {

      for(int i = 0; i < spinLength; i++) {
        tryFlip(i);
      }

    };
    
    void tryFlip(int candidateIndex) {
      
      long double randomPropabillity = gsl_rng_uniform_pos(generator);

      long double energyDifference = getEnergyDifferenceOfFlip(candidateIndex);

      long double weightRatio = exp(-energyDifference / temperature);
      
      if(weightRatio >= randomPropabillity) {

        spinSum += getSpinSumDifferenceOfFlip(candidateIndex);
        energy  += energyDifference;

        spins[candidateIndex] = !spins[candidateIndex];

      }
      
    };

    long double getMagnetization() {

      return fabs(double(spinSum) / spinLength);

    };

    int getSpinSum() {

      return spinSum;

    };

    int getSpinSumDifferenceOfFlip(int candidateIndex) {

      return -2 * getSpinValue(candidateIndex);

    };

    long double getEnergy() {

      return energy;

    };
    
    long double getEnergyDifferenceOfFlip(int candidateIndex) {

      int neighbourIndices[4] = {
        candidateIndex - edgeLength <  0              ? candidateIndex - edgeLength + spinLength : candidateIndex - edgeLength, // Top neighbour
        candidateIndex + edgeLength >= spinLength     ? candidateIndex + edgeLength - spinLength : candidateIndex + edgeLength, // Bottom neighbour
        candidateIndex % edgeLength == 0              ? candidateIndex + edgeLength - 1 : candidateIndex - 1, // Left neighbour
        candidateIndex % edgeLength == edgeLength - 1 ? candidateIndex - edgeLength + 1 : candidateIndex + 1, // Right neighbour
      };

      long double energyDiffernce = 2 * magneticMoment * magneticFlux * getSpinValue(candidateIndex);

      for(int i = 0; i < 4; i++) {
        energyDiffernce += 2 * bonding * getSpinValue(candidateIndex) * getSpinValue(neighbourIndices[i]);
      }
      
      return energyDiffernce;
      
    };
    
    string getSpinStatesAsString() {
      
      string str = "";
    
      for(int i = 0; i < spinLength; i++) {
        str += spins[i] ? "+" : "-";
      }
      
      return str;
      
    };

};
