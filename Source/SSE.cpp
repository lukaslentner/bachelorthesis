#include "Classes/Configuration.cpp"
#include "Classes/Configuration1DOpen.cpp"
#include "Classes/Configuration1DPeriodic.cpp"
#include "Classes/Configuration2DOpen.cpp"
#include "Classes/Configuration2DPeriodic.cpp"

#include <fstream>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
#include <stdio.h>

using namespace std;

int main(int argc, char *argv[]) {

  if(argc != 5) {
    cerr << "ERROR: Please specify 4 parameters (model[=0:1DO,1:1DP,2:2DO,3:2DP], size, temperatureStart, temperatureEnd)" << endl;
    return EXIT_FAILURE;
  }

  int model                    = atoi(argv[1]);
  int size                     = atoi(argv[2]);
  long double temperatureStart = atof(argv[3]);
  long double temperatureEnd   = atof(argv[4]);

  if(temperatureStart > temperatureEnd) swap(temperatureStart, temperatureEnd);

  printf("# SSE - Data\n");
  printf("# ----------------------------------------\n");
  printf("# Model [=0:1DO,1:1DP,2:2DO,3:2DP] = %.10i\n" , model);
  printf("# Size                             = %.10i\n" , size);
  printf("# TemperatureStart                 = %.10Le\n", temperatureStart);
  printf("# TemperatureEnd                   = %.10Le\n", temperatureEnd);
  
  const long double temperatureStep = 0.01;
  const long double expInv          = exp(-1);
  const long timeToTryThermalize    = pow(10, 4);
  const long countMeasurements      = pow(10, 4) * 3;

  long double energy;
  long double energyWhileTryToThermalize[timeToTryThermalize];
  int relaxationTime;

  long double sumOfEnergy        = 0.0;
  long double sumOfEnergySquared = 0.0;
  
  Configuration *config;

  if(model == 0) {
    config = new Configuration1DOpen(size, temperatureEnd);
  } else if(model == 1) {
    config = new Configuration1DPeriodic(size, temperatureEnd);
  }
  
  printf("#\n");
  printf("# %-17s | %-18s | %-18s | %-18s | %-18s | %-100s\n",
         "Model",
         "Size",
         "Temperature",
         "RelaxationTime",
         "Energy",
         "Configuration at last measurement");

  for(long double temperature = temperatureEnd; temperature > temperatureStart - (temperatureStep / 2); temperature -= temperatureStep) {

    printf("# ----------------------\n");
      
    config->setTemperature(temperature);
   
    /*sumOfEnergy        = 0.0;
    sumOfEnergySquared = 0.0;

    for(int i = 0; i < timeToTryThermalize; i++) {
    
      energyWhileTryToThermalizing[i] = config.getEnergy();
      config.doSweep();
      
      sumOfEnergy        += energyWhileTryToThermalizing[i];
      sumOfEnergySquared += pow(energyWhileTryToThermalizing[i], 2);
    
    }
    
    long double energyAutoC;
  
    for(relaxationTime = 0; relaxationTime < timeToTryThermalize; relaxationTime++) {
  
      energyAutoC = 0.0;
    
      for(int i = 0; i < timeToTryThermalize - relaxationTime; i++) {
        energyAutoC += energyWhileTryToThermalizing[i] * energyWhileTryToThermalizing[i + relaxationTime];
      }
    
      energyAutoC /= timeToTryThermalize - relaxationTime;
    
      energyAutoC = (energyAutoC - pow(sumOfEnergy / timeToTryThermalize, 2)) / ((sumOfEnergySquared / timeToTryThermalize) - pow(sumOfEnergy / timeToTryThermalize, 2));
      
      if(isnan(energyAutoC)) break;
      
      printf("# AutoCorrelation of Energy=%.10Le\n", energyAutoC);
      
      if(energyAutoC < expInv) break;
  
    }
    
    if(isnan(energyAutoC)) {
      printf("# T<=%.10Le was not measured, due to the unknown relaxation time\n", temperature);
      break;
    }
    
    if(10 * relaxationTime > timeToTryThermalize) {
      for(int i = timeToTryThermalize; i < 10 * relaxationTime; i++) {
        config.doSweep();
      }
    }
    
    printf("# Data:\n");
    
    sumOfEnergy        = 0.0;
    sumOfEnergySquared = 0.0;*/ relaxationTime = 2;
    
    long double sumOfNr = 0;
  
    for(int i = 10 * relaxationTime; i < 10 * relaxationTime + 2 * relaxationTime * countMeasurements; i += 2 * relaxationTime) {
    
      //long double tempSumOfEnergy        = 0.0;
      //long double tempSumOfEnergySquared = 0.0;
      
      long double tempSumOfNr = 0;
    
      for(int j = 0; j < 2 * relaxationTime; j++) {
      
        /*if(i + j < timeToTryThermalize) {
      
          tempSumOfEnergy        += energyWhileTryToThermalizing[i + j];
          tempSumOfEnergySquared += pow(energyWhileTryToThermalizing[i + j], 2);
      
        } else {

          energy = config.getEnergy();*/
          config->doSweep();
          
          tempSumOfNr += config->Nr;


          /*tempSumOfEnergy        += energy;
          tempSumOfEnergySquared += pow(energy, 2);
        
        }*/
      
      }
      
      sumOfNr += tempSumOfNr / (2 * relaxationTime);
      
      //sumOfEnergy        += tempSumOfEnergy        / (2 * relaxationTime);
      //sumOfEnergySquared += tempSumOfEnergySquared / (2 * relaxationTime);

    }
    
    cerr << "SSE: " << model << "%" << size << "%" << temperature << endl;

    printf("%20.20i|%20.20i|%+20.13Le|%20.20i|%+20.13Le|",
           model,
           size,
           temperature,
           relaxationTime,
           -sumOfNr / countMeasurements * temperature);
    cout << config->getSpinStatesAsString() << endl;

  }
  
  delete config;

  return EXIT_SUCCESS;

};
