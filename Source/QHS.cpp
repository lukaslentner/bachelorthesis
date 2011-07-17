#include "Classes/Model/Open1DModel.cpp"
#include "Classes/Model/Periodic1DModel.cpp"
#include "Classes/Model/Open2DModel.cpp"
#include "Classes/Model/Periodic2DModel.cpp"

#include "Classes/Algorithm/SSEAlgorithm.cpp"
#include "Classes/Algorithm/EDAlgorithm.cpp"

#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {

  try {

    if(argc != 7) throw "[QHS] Error: Please specify 6 parameters (Size, Model-Index, Algorithm-Index, Start-Temperature, End-Temperature, Temperature-Step)\n              - Size can be any positive integer\n              - Model-Index:\n                 0: Open-1D\n                 1: Periodic-1D\n                 2: Open-2D\n                 3: Periodic-2D\n              - Algorithm-Index:\n                 0: SSE - Stochastic Series Expansion\n                 1: ED  - Exact Diagonalization\n              - Temperatures should be positive floats (use the dot as delimiter)";

    int size                = atoi(argv[1]);
    int modelIndex          = atoi(argv[2]);
    int algorithmIndex      = atoi(argv[3]);
    double startTemperature = atof(argv[4]);
    double endTemperature   = atof(argv[5]);
    double temperatureStep  = atof(argv[6]);

    if(size <= 0) throw "[QHS] Error: The Size has to be positive";
    
    AbstractModel* model;
    const char* modelLabel;
    
    switch(modelIndex) {
    
      case 0:
        model = new Open1DModel(size);
        modelLabel = "Open-1D";
        break;
    
      case 1:
        model = new Periodic1DModel(size);
        modelLabel = "Periodic-1D";
        break;
    
      case 2:
        model = new Open2DModel(size);
        modelLabel = "Open-2D";
        break;
    
      case 3:
        model = new Periodic2DModel(size);
        modelLabel = "Periodic-2D";
        break;
    
      default:
        throw "[QHS] Error: The Model-Index has to be within [0;3]";
    
    }
    
    AbstractAlgorithm* algorithm;
    const char* algorithmLabel;

    switch(algorithmIndex) {
    
      case 0:
        algorithm = new SSEAlgorithm(model);
        algorithmLabel = "SSE";
        break;
    
      case 1:
        algorithm = new EDAlgorithm(model);
        algorithmLabel = "ED";
        break;
    
      default:
        throw "[QHS] Error: The Algorithm-Index has to be within [0;1]";
    
    }
    
    if(startTemperature < 0) throw "[QHS] Error: The Start-Temperature has to be positive or zero";
    if(endTemperature   <= 0) throw "[QHS] Error: The End-Temperature has to be positive";
    if(temperatureStep  <= 0) throw "[QHS] Error: The Temperature-Step has to be positive";
    if(startTemperature > endTemperature) std::swap(startTemperature, endTemperature);
    
    printf("#\n");
    printf("# QHS - DATA\n");
    printf("#\n");
    printf("# ----------------------------------------\n");
    printf("#\n");
    printf("# Size                 = %+19.19i\n", size);
    printf("# Model                = %s\n", modelLabel);
    printf("# Algorithm            = %s\n", algorithmLabel);
    printf("# Start-Temperature    = %+20.13e\n", startTemperature);
    printf("# End-Temperature      = %+20.13e\n", endTemperature);
    printf("# Temperature-Step     = %+20.13e\n", temperatureStep);
    printf("#\n");
    printf("# %-17s | %-18s | %-18s | %-18s | %-18s | %-18s | %-18s\n",
           "Size",
           "Model-Index",
           "Algorithm-Index",
           "Temperature",
           "AverageEnergy",
           "StdDvOfEnergy",
           "AverageCHeat");
    printf("# ------------------------------------------------------------------------------------------------------\n");

    for(double temperature = endTemperature; temperature > startTemperature + (temperatureStep / 2); temperature -= temperatureStep) {
    
      algorithm->setTemperature(temperature);
      algorithm->runTemperatureRound();
      
      std::cerr << "[QHS] Info: Size=" << size << ", Model=" << modelLabel << ", Algorithm=" << algorithmLabel << ", Temperature=" << temperature << std::endl;
      
      printf("%+19.19i|%+19.19i|%+19.19i|%+20.13e|%+20.13e|%+20.13e|%+20.13e\n",
             size,
             modelIndex,
             algorithmIndex,
             temperature,
             algorithm->getAverageEnergy(),
             algorithm->getStdDvOfEnergy(),
             algorithm->getAverageCHeat());

    }
    
    delete algorithm;
    delete model;

    return EXIT_SUCCESS;
  
  } catch(const char *message) {
  
    std::cerr << message << std::endl;
    return EXIT_FAILURE;
  
  }

};
