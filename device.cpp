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
          if(inputs.size() < inputAmount) inputs.push_back(s);
          else throw"INPUT STREAM LIMIT!";
      }
      void addOutput(shared_ptr<Stream> s){
          if(outputs.size() < outputAmount) outputs.push_back(s);
          else throw "OUTPUT STREAM LIMIT!";
      }
      virtual void updateOutputs() = 0;
};

class Reactor : Device{
    Reactor(bool isDoubleReactor) {
        inputAmount = 1;
        if (isDoubleReactor) outputAmount = 2;
        else inputAmount = 1;
    }
    
    void updateOutputs() override{
        double inputMass = inputs.at(0) -> getMassFlow();
            for(int i = 0; i < outputAmount; i++){
            double outputLocal = inputMass * (1/(outputAmount - i));
            outputs.at(i) -> setMassFlow(outputLocal);
            inputMass -= outputLocal;
        }
    }
};

void testTooManyOutputStreams(){
    streamcounter=0;
    
    Reactor dl = new Reactor(false);
    
    shared_ptr<Stream> s1(new Stream(++streamcounter));
    shared_ptr<Stream> s2(new Stream(++streamcounter));
    shared_ptr<Stream> s3(new Stream(++streamcounter));
    s1->setMassFlow(10.0);
    s2->setMassFlow(5.0);
    dl.addInput(s1);
    dl.addOutput(s2);
    try{
        dl.addOutput(s3);
    } catch(const string ex){
         if (ex == "OUTPUT STREAM LIMIT!") {
        cout << "Test 1 passed" << endl;

        return;
    }
    
     cout << "Test 1 failed" << endl;
}

void testTooManyInputStreams(){
    streamcounter=0;
    
    Reactor dl = new Reactor(false);
    
    shared_ptr<Stream> s1(new Stream(++streamcounter));
    shared_ptr<Stream> s3(new Stream(++streamcounter));
    s1->setMassFlow(10.0);
    s2->setMassFlow(5.0);
    dl.addInput(s1);
    try{
        dl.addInput(s3);
    } catch(const string ex){
         if (ex == "INPUT STREAM LIMIT!") {
        cout << "Test 2 passed" << endl;

        return;
    }
    
     cout << "Test 2 failed"s << endl;
}

void testInputEqualOutput(){
        streamcounter=0;
    
    Reactor dl = new Reactor(true);
    
    shared_ptr<Stream> s1(new Stream(++streamcounter));
    shared_ptr<Stream> s2(new Stream(++streamcounter));
    shared_ptr<Stream> s3(new Stream(++streamcounter));
    s1->setMassFlow(10.0);
    s2->setMassFlow(5.0);
    dl.addInput(s1);
    dl.addOutput(s2);
    dl.addOutput(s3);
    
    dl.updateOutputs();
    
    if(dl.outputs.at(0).getMassFlow + dl.outputs.at(1).getMassFlow == dl.inputs.at(0).getMassFlow){
        cout << "Test 3 passed" << endl;
    } else cout << "Test 3 failed" << endl;
}

void tests(){
    testInputEqualOutput();
    testTooManyOutputStreams();
    testTooManyInputStreams();
}

int main()
{
    tests;
}

