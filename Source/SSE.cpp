#include "Classes/Configuration.cpp"
#include "Classes/Configuration1DPeriodic.cpp"

#include <fstream>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
#include <stdio.h>

using namespace std;

int main(int argc, char *argv[]) {

  if(argc != 5) {
    cerr << "ERROR: Please specify 4 parameters (model[=0:1DO,1:1DP,2:2DO,3:2DP], N, temperatureStart, temperatureEnd)" << endl;
    return EXIT_FAILURE;
  }

  int model                    = atoi(argv[1]);
  int N                        = atoi(argv[2]);
  long double temperatureStart = atof(argv[3]);
  long double temperatureEnd   = atof(argv[4]);

  if(temperatureStart > temperatureEnd) swap(temperatureStart, temperatureEnd);

  printf("# SSE - Data\n");
  printf("# ----------------------------------------\n");
  printf("# Model [=0:1DO,1:1DP,2:2DO,3:2DP] = %.10i\n" , model);
  printf("# N                                = %.10i\n" , N);
  printf("# TemperatureStart                 = %.10Le\n", temperatureStart);
  printf("# TemperatureEnd                   = %.10Le\n", temperatureEnd);
  
  const long double temperatureStep = 0.01;
  const int countMeasurements = 100;
  const int binSize = 1000;
  
  Configuration *config = new Configuration1DPeriodic(N, temperatureEnd);
  
  printf("#\n");
  printf("# %-17s | %-18s | %-18s | %-18s | %-100s\n",
         "Model",
         "N",
         "Temperature",
         "Energy",
         "Configuration at last measurement");
   
  long double sumOfNr = 0;
  long double tempSumOfNr = 0;

  for(long double temperature = temperatureEnd; temperature > temperatureStart + (temperatureStep / 2); temperature -= temperatureStep) {
    
    for(int j = 0; j < 10000; j++) {
    
      config->doSweep();

    }

    config->setTemperature(temperature);
   
    sumOfNr = 0;
  
    for(int i = 0; i < binSize * countMeasurements; i += binSize) {
    
      tempSumOfNr = 0;
    
      for(int j = 0; j < binSize; j++) {
      
        config->doSweep();
          
        tempSumOfNr += config->Nr;

      }
      
      sumOfNr += tempSumOfNr / binSize;
      
    }
    
    cerr << "# SSE: " << model << "%" << N << "%" << temperature << endl;

    printf("%20.20i|%20.20i|%+20.13Le|%+20.13Le|",
           model,
           N,
           temperature,
           -sumOfNr * temperature / countMeasurements);
    cout << config->getSpinStatesAsString() << endl;

  }
  
  delete config;

  return EXIT_SUCCESS;

};
