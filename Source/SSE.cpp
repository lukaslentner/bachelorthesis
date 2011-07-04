//TODO: Pseudo thermalization should become self tested
//TODO: Errorbars
//TODO: Other models

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
    cerr << "[SSE] Error: Please specify 4 parameters (Model, Size, Temperature at the start, Temperature at the end)" << endl;
    return EXIT_FAILURE;
  }

  int model                    = atoi(argv[1]);
  int size                     = atoi(argv[2]);
  long double temperatureStart = atof(argv[3]);
  long double temperatureEnd   = atof(argv[4]);

  if(temperatureStart > temperatureEnd) swap(temperatureStart, temperatureEnd);
  
  const long double temperatureStep = 0.01;
  const int countMeasurements = 100;
  const int binSize = 1000;
  
  Configuration *config;
  string modelLabel = "";
  
  switch(model) {
  
    case 0:
      config = new Configuration1DOpen(size, temperatureEnd);
      modelLabel = "1D-Open";
      break;
  
    case 1:
      config = new Configuration1DPeriodic(size, temperatureEnd);
      modelLabel = "1D-Periodic";
      break;
  
    case 2:
      config = new Configuration2DOpen(size, temperatureEnd);
      modelLabel = "2D-Open";
      break;
  
    case 3:
      config = new Configuration2DPeriodic(size, temperatureEnd);
      modelLabel = "2D-Periodic";
      break;
  
    default:
      cerr << "[SSE] Error: The parameter model has to be within [0;3]" << endl;
      return EXIT_FAILURE;
  
  }

  cout << "#\n";
  cout << "# SSE - DATA\n";
  cout << "#\n";
  cout << "# ----------------------------------------\n";
  cout << "#\n";
  cout << "# Model            = " << modelLabel << "\n";
  
  printf("# Size             = %.10i\n" , size);
  printf("# TemperatureStart = %.10Le\n", temperatureStart);
  printf("# TemperatureEnd   = %.10Le\n", temperatureEnd);
  
  printf("#\n#\n");
  printf("# %-17s | %-18s | %-18s | %-18s | %-18s\n",
         "Model",
         "Size",
         "Temperature",
         "Energy",
         "Specific Heat");
  printf("# ------------------------------------------------------------------------------------------------------\n");
   
  long double sumOfCountOfRealOperators = 0; 
  long double sumOfCountOfRealOperatorsSquared = 0;
  long double tempSumOfCountOfRealOperators = 0;
  long double tempSumOfCountOfRealOperatorsSquared = 0;

  for(long double temperature = temperatureEnd; temperature > temperatureStart + (temperatureStep / 2); temperature -= temperatureStep) {
    
    for(int j = 0; j < 10000; j++) {
      config->doSweep();
    }

    config->setTemperature(temperature);
   
    sumOfCountOfRealOperators        = 0;
    sumOfCountOfRealOperatorsSquared = 0;
  
    for(int i = 0; i < binSize * countMeasurements; i += binSize) {
    
      tempSumOfCountOfRealOperators        = 0;
      tempSumOfCountOfRealOperatorsSquared = 0;
    
      for(int j = 0; j < binSize; j++) {
      
        config->doSweep();
          
        tempSumOfCountOfRealOperators        +=     config->getCountOfRealOperators();
        tempSumOfCountOfRealOperatorsSquared += pow(config->getCountOfRealOperators(), 2);

      }
      
      sumOfCountOfRealOperators        += tempSumOfCountOfRealOperators        / binSize;
      sumOfCountOfRealOperatorsSquared += tempSumOfCountOfRealOperatorsSquared / binSize;
      
    }
    
    cerr << "[SSE] Info: Model=" << modelLabel << ", Size=" << size << ", Temperature=" << temperature << endl;

    printf("%20.20i|%20.20i|%+20.13Le|%+20.13Le|%+20.13Le\n",
           model,
           size,
           temperature,
           (-sumOfCountOfRealOperators * temperature / countMeasurements) + ((long double) config->getCountOfBonds() / 4),
           (sumOfCountOfRealOperatorsSquared / countMeasurements) - pow(sumOfCountOfRealOperators / countMeasurements, 2) - (sumOfCountOfRealOperators / countMeasurements));

  }
  
  delete config;

  return EXIT_SUCCESS;

};
