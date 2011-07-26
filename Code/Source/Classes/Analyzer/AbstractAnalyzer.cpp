#ifndef CLASS_ABSTRACTANALYZER
#define CLASS_ABSTRACTANALYZER

class AbstractAnalyzer {

  protected:
  
    AbstractAlgorithm* algorithm;
    AbstractLattice* lattice;
    
    double average;
    double error;
    long relaxationTime;
  
  public:
  
    AbstractAnalyzer(AbstractAlgorithm* algorithm_parameter, AbstractLattice* lattice_parameter) {

      algorithm = algorithm_parameter;
      lattice = lattice_parameter;
      
      average = 0;
      error = 0;
      relaxationTime = 0;
      
    };

    ~AbstractAnalyzer() {};
    
    virtual const char* getQuantityName() = 0;
    virtual double getQuantity(long time) = 0;
    
    void analyze() {
      
      double *sum        = new double[algorithm->getMeasureCount()];
      double *sumSquared = new double[algorithm->getMeasureCount()];
        
      for(long time = 0; time < algorithm->getMeasureCount(); time++) {
        sum[time]        = (time == 0 ? 0 : sum[time - 1]) + getQuantity(time);
        sumSquared[time] = (time == 0 ? 0 : sumSquared[time - 1]) + pow(getQuantity(time), 2);
      }
      
      for(relaxationTime = 0; relaxationTime < algorithm->getMeasureCount(); relaxationTime++) {
      
        double sumP = 0;
        
        for(long time = 0; time < algorithm->getMeasureCount() - relaxationTime; time++) {
          sumP += getQuantity(time) * getQuantity(time + relaxationTime);
        }
        
        long timeToAverage = algorithm->getMeasureCount() - relaxationTime;
        double autoCorrelation = ((sumP / timeToAverage) - pow(sum[algorithm->getMeasureCount() - 1] / timeToAverage, 2)) / ((sumSquared[algorithm->getMeasureCount() - 1] / timeToAverage) - pow(sum[algorithm->getMeasureCount() - 1] / timeToAverage, 2));
      
        if(isnan(autoCorrelation)) {
          printf("# %s at temperature=%+20.13e was not measured, due to the unknown relaxation time\n", getQuantityName(), algorithm->getTemperature());
          relaxationTime = -1;
          break;
        }
        
        printf("# Auto-Correlation of %s=%+20.13e\n", getQuantityName(), autoCorrelation);
        
        if(autoCorrelation < exp(-1)) break;
    
      }
      
      relaxationTime++;
      
      if(relaxationTime != 0) {
      
        long binsCount = algorithm->getMeasureCount() / 3 / relaxationTime;
        double *binAverage = new double[binsCount];

        for(long bin = 0; bin < binsCount; bin++) {
          binAverage[bin] = (sum[(bin + 1) * 3 * relaxationTime] - sum[bin * 3 * relaxationTime]) / 3 / relaxationTime;
          average += binAverage[bin] / binsCount;
        }
        
        double deviationSum = 0;
        for(long bin = 0; bin < binsCount; bin++) {
          deviationSum += pow(binAverage[bin] - average, 2);
        }
        error = sqrt(deviationSum / binsCount / (binsCount - 1));
        
        delete[] binAverage;
        
      }
      
      delete[] sum;
      delete[] sumSquared;

    };
    
    double getAverage() {
    
      return average;
    
    };
    
    double getError() {
    
      return error;
    
    };

    long getRelaxationTime() {
    
      return relaxationTime;
    
    };
  
};

#endif
