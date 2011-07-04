using namespace std;

class Configuration2DPeriodic : public Configuration {
    
  public:
  
    int m;
    
    Configuration2DPeriodic(int N_Parameter, long double T_Parameter)
    : Configuration(N_Parameter, getNb(N_Parameter), T_Parameter) {
    
      m = sqrt((float) N_Parameter);
      if(pow((int) m, 2) != N_Parameter) throw "[SSE] Error: You choose a 2D model, please input a square number as size";
    
    };
    
    int getNb(int N) {
    
      return 2 * N;
    
    };
    
    int getI1(int b) {
    
      return (b - 1) / 2;
    
    };
    
    int getI2(int b) {
    
      if(b & 1) {
      
        return (((b - 1) / 2) + m) % N;
      
      } else {
      
        return ((((b - 1) / 2) + 1) % m) + ((((b - 1) / 2) / m) * m);
      
      }
    
    };

};
