#include "Classes/Configuration2D.cpp"

#include <fstream>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
#include <stdio.h>

using namespace std;

int main(int argc, char *argv[]) {

  if(argc != 4) {
    cerr << "ERROR: Please specify 3 parameters (modul, temperatureStart, temperatureEnd)" << endl;
    return EXIT_FAILURE;
  }

  int modul                    = atoi(argv[1]);
  long double temperatureStart = atof(argv[2]);
  long double temperatureEnd   = atof(argv[3]);

  if(temperatureStart > temperatureEnd) swap(temperatureStart, temperatureEnd);

  printf("# CMCS - Data\n");
  printf("# ----------------------------------------\n");
  printf("# Modul            = %.10i\n", modul);
  printf("# TemperatureStart = %.10Le\n", temperatureStart);
  printf("# TemperatureEnd   = %.10Le\n", temperatureEnd);
  
  /////////////////////////////////////////////////////////////////////////////////////////////

  const long double expInv    = exp(-1);
  const long timeToThermalize = pow(10, 4);
  long timeBetween            = pow(10, 1);
  long countMeasurements      = pow(10, 4) * 3;

  long double energy;
  long double magnetization;
  long double energyWhileThermalizing[timeToThermalize];
  long double magnetizationWhileThermalizing[timeToThermalize];
  int relaxationTime;

  long double sumOfEnergy               = 0.0;
  long double sumOfEnergySquared        = 0.0;
  long double sumOfMagnetization        = 0.0;
  long double sumOfMagnetizationSquared = 0.0;

  Configuration2D config(modul, temperatureEnd);
  config.randomizeSpins();
  
  printf("#\n");
  printf("# %-17s | %-18s | %-18s | %-18s | %-18s | %-18s | %-18s | %-18s | %-100s\n",
         "Modul",
         "Temperature",
         "RelaxationTime",
         "Energy",
         "Energy StD",
         "Specific Heat",
         "Magnetization",
         "Magnetization StD",
         "Suszeptibility",
         "Configuration at last measurement");

  for(long double temperature = temperatureEnd; temperature > temperatureStart - (0.015 / 2); temperature -= 0.015) {

    printf("# ----------------------\n");
      
    config.setTemperature(temperature);
   
    sumOfMagnetization        = 0.0;
    sumOfMagnetizationSquared = 0.0;

    for(int i = 0; i < timeToThermalize; i++) {
    
      magnetizationWhileThermalizing[i] = config.getMagnetization();
      energyWhileThermalizing[i] = config.getEnergy();
      config.tryFlipEvery();
      
      sumOfMagnetization += magnetizationWhileThermalizing[i];
      sumOfMagnetizationSquared += pow(magnetizationWhileThermalizing[i], 2);
    
    }
    
    long double magnetizationAutoC;
  
    for(relaxationTime = 0; relaxationTime < timeToThermalize; relaxationTime++) {
  
      magnetizationAutoC = 0.0;
    
      for(int i = 0; i < timeToThermalize - relaxationTime; i++) {
        magnetizationAutoC += magnetizationWhileThermalizing[i] * magnetizationWhileThermalizing[i + relaxationTime];
      }
    
      magnetizationAutoC /= timeToThermalize - relaxationTime;
    
      magnetizationAutoC = (magnetizationAutoC - pow(sumOfMagnetization / timeToThermalize, 2)) / ((sumOfMagnetizationSquared / timeToThermalize) - pow(sumOfMagnetization / timeToThermalize, 2));
      
      if(isnan(magnetizationAutoC)) break;
      
      printf("# AutoCorrelation of Magnization=%.10Le\n", magnetizationAutoC);
      
      if(magnetizationAutoC < expInv) break;
  
    }
    
    if(isnan(magnetizationAutoC)) {
      printf("# T<=%.10Le was not measured, due to the unknown relaxation time\n", temperature);
      break;
    }
    
    if(10 * relaxationTime > timeToThermalize) {
      for(int i = timeToThermalize; i < 10 * relaxationTime; i++) {
        config.tryFlipEvery();
      }
    }
    
    printf("# Data:\n");
    
    sumOfEnergy               = 0.0;
    sumOfEnergySquared        = 0.0;
    sumOfMagnetization        = 0.0;
    sumOfMagnetizationSquared = 0.0;
  
    for(int i = 10 * relaxationTime; i < 10 * relaxationTime + 2 * relaxationTime * countMeasurements; i += 2 * relaxationTime) {
    
      long double tempSumOfEnergy               = 0.0;
      long double tempSumOfEnergySquared        = 0.0;
      long double tempSumOfMagnetization        = 0.0;
      long double tempSumOfMagnetizationSquared = 0.0;
    
      for(int j = 0; j < 2 * relaxationTime; j++) {
      
        if(i + j < timeToThermalize) {
      
          tempSumOfEnergy               += energyWhileThermalizing[i + j];
          tempSumOfEnergySquared        += pow(energyWhileThermalizing[i + j], 2);
          tempSumOfMagnetization        += magnetizationWhileThermalizing[i + j];
          tempSumOfMagnetizationSquared += pow(magnetizationWhileThermalizing[i + j], 2);
      
        } else {

          energy = config.getEnergy();
          magnetization = config.getMagnetization();
          config.tryFlipEvery();

          tempSumOfEnergy               += energy;
          tempSumOfEnergySquared        += pow(energy, 2);
          tempSumOfMagnetization        += magnetization;
          tempSumOfMagnetizationSquared += pow(magnetization, 2);
        
        }
      
      }
      
      sumOfEnergy               += tempSumOfEnergy               / (2 * relaxationTime);
      sumOfEnergySquared        += tempSumOfEnergySquared        / (2 * relaxationTime);
      sumOfMagnetization        += tempSumOfMagnetization        / (2 * relaxationTime);
      sumOfMagnetizationSquared += tempSumOfMagnetizationSquared / (2 * relaxationTime);

    }
    
    cerr << "CMCS: " << modul << "%" << temperature << "%" << config.getSpinSum() << "%" << config.getMagnetization() << endl;

    printf("%20.20i|%+20.13Le|%20.20i|%+20.13Le|%+20.13Le|%+20.13Le|%+20.13Le|%+20.13Le|%+20.13Le|",
           modul,
           temperature,
           relaxationTime,
           sumOfEnergy / countMeasurements,
           sqrt(((sumOfEnergySquared / countMeasurements) - pow(sumOfEnergy / countMeasurements, 2)) / (countMeasurements - 1)),
           ((sumOfEnergySquared / countMeasurements) - pow(sumOfEnergy / countMeasurements, 2)) / config.getSpinLength() / pow(temperature, 2),
           sumOfMagnetization / countMeasurements,
           sqrt(((sumOfMagnetizationSquared / countMeasurements) - pow(sumOfMagnetization / countMeasurements, 2)) / (countMeasurements - 1)),
           ((sumOfMagnetizationSquared / countMeasurements) - pow(sumOfMagnetization / countMeasurements, 2)) * config.getSpinLength() / temperature);
    cout << config.getSpinStatesAsString() << endl;

  }

  return EXIT_SUCCESS;

};
