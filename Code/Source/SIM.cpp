#include "Classes/Lattice/Open1DLattice.cpp"
#include "Classes/Lattice/Periodic1DLattice.cpp"
#include "Classes/Lattice/Periodic2DLattice.cpp"

#include "Classes/Algorithm/SSEAlgorithm.cpp"
#include "Classes/Algorithm/EDAlgorithm.cpp"
#include "Classes/Algorithm/ISINGAlgorithm.cpp"

#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {

  try {

    if(argc != 8) throw "[SIM] Error: Please specify 7 parameters (Size, Lattice-Index, Measure-Count, Algorithm-Index, Start-Temperature, End-Temperature, Temperature-Step)\n              - Size can be any positive integer\n              - Lattice-Index:\n                 0: Open-1D\n                 1: Periodic-1D\n                 2: Periodic-2D\n              - Measure-Count should be a positive long integer - ED of course needs no Measure-Count (=0)\n              - Algorithm-Index:\n                 0: ED  - Exact Diagonalization\n                 1: ISING  - Classical Ising simulation\n                 2: SSE - Stochastic Series Expansion\n              - Temperatures should be positive floats (use the dot as delimiter)";

    int size                = atoi(argv[1]);
    int latticeIndex        = atoi(argv[2]);
    long measureCount       = atoi(argv[3]);
    int algorithmIndex      = atoi(argv[4]);
    double startTemperature = atof(argv[5]);
    double endTemperature   = atof(argv[6]);
    double temperatureStep  = atof(argv[7]);

    if(size <= 0) throw "[SIM] Error: The Size has to be positive";
    
    AbstractLattice* lattice;
    const char* latticeLabel;
    
    switch(latticeIndex) {
    
      case 0:
        lattice = new Open1DLattice(size);
        latticeLabel = "Open-1D";
        break;
    
      case 1:
        lattice = new Periodic1DLattice(size);
        latticeLabel = "Periodic-1D";
        break;
    
      case 2:
        lattice = new Periodic2DLattice(size);
        latticeLabel = "Periodic-2D";
        break;
    
      default:
        throw "[SIM] Error: The Lattice-Index has to be within [0;2]";
    
    }
    
    if(measureCount <= 0) throw "[SIM] Error: The Measure-Count has to be positive";
    
    AbstractAlgorithm* algorithm;
    const char* algorithmLabel;

    switch(algorithmIndex) {
    
      case 0:
        algorithm = new EDAlgorithm(lattice, measureCount);
        algorithmLabel = "ED";
        break;
    
      case 1:
        algorithm = new ISINGAlgorithm(lattice, measureCount);
        algorithmLabel = "ISING";
        break;
    
      case 2:
        algorithm = new SSEAlgorithm(lattice, measureCount);
        algorithmLabel = "SSE";
        break;
    
      default:
        throw "[SIM] Error: The Algorithm-Index has to be within [0;2]";
    
    }
    
    if(startTemperature <  0) throw "[SIM] Error: The Start-Temperature has to be positive or zero";
    if(endTemperature   <= 0) throw "[SIM] Error: The End-Temperature has to be positive";
    if(temperatureStep  <= 0) throw "[SIM] Error: The Temperature-Step has to be positive";
    if(startTemperature > endTemperature) std::swap(startTemperature, endTemperature);
    
    printf("#\n");
    printf("# SIM - DATA\n");
    printf("#\n");
    printf("# ----------------------------------------\n");
    printf("#\n");
    printf("# Size                 = %+19.19i\n", size);
    printf("# Lattice              = %s\n", latticeLabel);
    printf("# Measure-Count        = %+19.19li\n", measureCount);
    printf("# Algorithm            = %s\n", algorithmLabel);
    printf("# Start-Temperature    = %+20.13e\n", startTemperature);
    printf("# End-Temperature      = %+20.13e\n", endTemperature);
    printf("# Temperature-Step     = %+20.13e\n", temperatureStep);
    printf("#\n");
    printf("# %-17s | %-18s | %-18s | %-18s | %-18s | %-18s | %-18s | %-18s | %-18s | %-18s | %-18s | %-18s | %-18s | %-18s | %-18s | %-18s | %-18s\n",
           "Size",
           "Lattice-Index",
           "Measure-Count",
           "Algorithm-Index",
           "Temperature",
           "Average Energy",
           "Error Of Energy",
           "ACorTime Of Energy",
           "Average Heat",
           "Error Of Heat",
           "ACorTime Of Heat",
           "Average Mag",
           "Error Of Mag",
           "ACorTime Of Mag",
           "Average Suscept",
           "Error Of Suscept",
           "ACorTime Of Suscept");

    for(double temperature = endTemperature; temperature > startTemperature + (temperatureStep / 2); temperature -= temperatureStep) {
    
      algorithm->setTemperature(temperature);
      algorithm->runTemperatureRound();
      
      printf("%+19.19i|%+19.19i|%+19.19li|%+19.19i|%+20.13e|%+20.13e|%+20.13e|%+19.19li|%+20.13e|%+20.13e|%+19.19li|%+20.13e|%+20.13e|%+19.19li|%+20.13e|%+20.13e|%+19.19li\n",
             size,
             latticeIndex,
             measureCount,
             algorithmIndex,
             temperature,
             algorithm->getAverageEnergy(),
             algorithm->getErrorOfEnergy(),
             algorithm->getAutoCorrelationTimeOfEnergy(),
             algorithm->getAverageHeatCapacity(),
             algorithm->getErrorOfHeatCapacity(),
             algorithm->getAutoCorrelationTimeOfHeatCapacity(),
             algorithm->getAverageMagnetization(),
             algorithm->getErrorOfMagnetization(),
             algorithm->getAutoCorrelationTimeOfMagnetization(),
             algorithm->getAverageSusceptibility(),
             algorithm->getErrorOfSusceptibility(),
             algorithm->getAutoCorrelationTimeOfSusceptibility());
      
      std::cerr << "[SIM] Info: Finished, Size=" << size << ", Lattice=" << latticeLabel << ", Measure-Count=" << measureCount << ", Algorithm=" << algorithmLabel << ", Temperature=" << temperature << std::endl;

    }
    
    delete algorithm;
    delete lattice;

    return EXIT_SUCCESS;
  
  } catch(const char *message) {
  
    std::cerr << message << std::endl;
    return EXIT_FAILURE;
  
  }

};
