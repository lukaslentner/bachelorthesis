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

    if(argc != 7) throw "[QHS] Error: Please specify 6 parameters (Size, Model-Index, Algorithm-Index, Start-Temperature, End-Temperature, Temperature-Step)";

    int size                     = atoi(argv[1]);
    int modelIndex               = atoi(argv[2]);
    int algorithmIndex           = atoi(argv[3]);
    long double startTemperature = atof(argv[4]);
    long double endTemperature   = atof(argv[5]);
    long double temperatureStep  = atof(argv[6]);
    
    AbstractModel* model;
    const char* modelLabel;
    AbstractAlgorithm* algorithm;
    const char* algorithmLabel;
    
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

    if(startTemperature > endTemperature) std::swap(startTemperature, endTemperature);
    
    printf("#\n");
    printf("# QHS - DATA\n");
    printf("#\n");
    printf("# ----------------------------------------\n");
    printf("#\n");
    printf("# Size                 = %+19.19i\n", size);
    printf("# Model                = %s\n", modelLabel);
    printf("# Algorithm            = %s\n", algorithmLabel);
    printf("# Start-Temperature    = %+20.13Le\n", startTemperature);
    printf("# End-Temperature      = %+20.13Le\n", endTemperature);
    printf("# Temperature-Step     = %+20.13Le\n", temperatureStep);
    printf("#\n");
    printf("# %-17s | %-18s | %-18s | %-18s | %-18s | %-18s | %-18s | %-18s\n",
           "Size",
           "Model-Index",
           "Algorithm-Index",
           "Temperature",
           "AverageEnergy",
           "StdDvOfEnergy",
           "AverageCHeat",
           "StdDvOfCHeat");
    printf("# ------------------------------------------------------------------------------------------------------\n");

    for(long double temperature = endTemperature; temperature > startTemperature + (temperatureStep / 2); temperature -= temperatureStep) {
    
      algorithm->setTemperature(temperature);
      algorithm->runTemperatureRound();
      
      std::cerr << "[QHS] Info: Size=" << size << ", Model=" << modelLabel << ", Algorithm=" << algorithmLabel << ", Temperature=" << temperature << std::endl;
      
      printf("%+19.19i|%+19.19i|%+19.19i|%+20.13Le|%+20.13Le|%+20.13Le|%+20.13Le|%+20.13Le\n",
             size,
             modelIndex,
             algorithmIndex,
             temperature,
             algorithm->getAverageEnergy(),
             algorithm->getStdDvOfEnergy(),
             algorithm->getAverageCHeat(),
             algorithm->getStdDvOfCHeat());

    }
    
    delete algorithm;
    delete model;

    return EXIT_SUCCESS;
  
  } catch(const char *message) {
  
    std::cerr << message << std::endl;
    return EXIT_FAILURE;
  
  }

};
