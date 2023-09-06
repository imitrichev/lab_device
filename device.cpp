#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;
int streamcounter;

class Stream
{
    private:
      double mass_flow;
      string name;
    public:
      Stream(int s){setName("s"+std::to_string(s));}
      void setName(string s){name=s;}
      string getName(){return name;}
      void setMassFlow(double m){mass_flow=m;}
      double getMassFlow(){return mass_flow;}
      void print(){cout<<"Stream "<<getName()<<" flow = "<<getMassFlow()<<endl;}
};

class Device
{
    protected:
      vector<shared_ptr<Stream>> inputs;
      vector<shared_ptr<Stream>> outputs;
      int inputAmount;
      int outputAmount;
    public:
      void addInput(shared_ptr<Stream> s){
          if(inputs.size < inputAmount) inputs.push_back(s);
          else cout << "INPUT STREAM LIMIT!" << endl;
      }
      void addOutput(shared_ptr<Stream> s){
          if(outputs.size < outputAmount) outputs.push_back(s);
          else cout << "OUTPUT STREAM LIMIT!" << endl;
      }
      virtual void updateOutputs() = 0;
};

class Reactor : Device{
    Reactor(bool isDoubleReactor) {
        inputAmount = 1;
        if (isDoubleReactor) outputAmount = 2;
        else inputAmount = 1;
    }
    void updateOutputs override(){
    double inputMass = inputs.at(0) -> getMassFlow() 
        for(int i = 0; i < outputAmount; i++){
            outputs.at(i) -> setMassFlow(inputMass * 0.83)
        }
    }
}

//class Mixer.......

int main()
{
    streamcounter=0;
    //Mixer d1;
    
    shared_ptr<Stream> s1(new Stream(++streamcounter));
    shared_ptr<Stream> s2(new Stream(++streamcounter));
    shared_ptr<Stream> s3(new Stream(++streamcounter));
    s1->setMassFlow(10.0);
    s2->setMassFlow(5.0);
    
    //d1.addInput......
}
