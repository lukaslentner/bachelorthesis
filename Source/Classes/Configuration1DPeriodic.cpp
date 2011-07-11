using namespace std;

class Configuration1DPeriodic : public Configuration {
    
  public:
    
    Configuration1DPeriodic(int N_Parameter, long double T_Parameter)
    : Configuration(N_Parameter, getNb(N_Parameter), T_Parameter) {};
    
    int getNb(int N) {
    
      return N;
    
    };
    
    int getI1(int b) {
    
      return b - 1;
    
    };
    
    int getI2(int b) {
    
      return b % N;
    
    };

};
