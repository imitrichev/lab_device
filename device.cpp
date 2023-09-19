#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cassert>


using namespace std;
int streamcounter;
int inp_counts = 1;
const float POSSIBLE_ERROR = 0.01;
const int DROBILKA_OUTPUTS = 1;


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
    public:
      void addInput(shared_ptr<Stream> s){inputs.push_back(s);}
      void addOutput(shared_ptr<Stream> s){outputs.push_back(s);}
      virtual void updateOutputs() = 0;
};

//class Mixer.......
class Drobilka : public Device
{
    
public:
    Drobilka() {}  // Конструктор
    
    void addInput(shared_ptr<Stream> s) {
        if (inputs.size() == inp_counts) {
          throw "Too much inputs";
        }
        inputs.push_back(s);
     }
    void addOutput(shared_ptr<Stream> s) {
        if (outputs.size() == DROBILKA_OUTPUTS) {
          throw "Too much outputs";
        }
        outputs.push_back(s);
    }
// Обновление выходных потоков и проверка условия одного входа и выхода
    void updateOutputs() override {
        if (inputs.size() == 1 && outputs.size() == 1) {
            // Получение массового расхода входного потока
            double inputMassFlow = inputs[0]->getMassFlow();
            // Получение выходного потока согласно массовому расходу
            double outputMassFlow = inputMassFlow ;
            // Устанавление массового расхода для выходного потока
            outputs[0]->setMassFlow(outputMassFlow);
        }
        else {
            throw("invalid streams");
        }
    }
};
void correctGetMassFlow() {
    streamcounter=0;
    Drobilka drobilka;
    
    shared_ptr<Stream> s1(new Stream(++streamcounter));
    shared_ptr<Stream> s2(new Stream(++streamcounter));
    shared_ptr<Stream> s3(new Stream(++streamcounter));
    
    s1->setMassFlow(10.0);

    drobilka.addInput(s1);
    drobilka.addOutput(s2);

    drobilka.updateOutputs();

    if (abs(s2->getMassFlow()) - 10 < POSSIBLE_ERROR) {
      cout << "Test 1 passed" << endl;
    } else {
      cout << "Test 1 failed" << endl;
    }
}
void correctOutputs() {
    streamcounter=0;
    Drobilka drobilka;
    
    shared_ptr<Stream> s1(new Stream(++streamcounter));
    shared_ptr<Stream> s2(new Stream(++streamcounter));
    shared_ptr<Stream> s3(new Stream(++streamcounter));
    
    s1->setMassFlow(10.0);
    
    drobilka.addInput(s1);
    drobilka.addOutput(s2);

    try {
      drobilka.addOutput(s3);
    } catch (const char* ex) {
      if (ex == "Too much outputs") {
        cout << "Test 2 passed" << endl;

        return;
      }
    }

    cout << "Test 2 failed" << endl;
}
void correctInputs() {
    streamcounter=0;
    Drobilka drobilka;
    
    shared_ptr<Stream> s1(new Stream(++streamcounter));
    shared_ptr<Stream> s2(new Stream(++streamcounter));
    shared_ptr<Stream> s3(new Stream(++streamcounter));

    s1->setMassFlow(10.0);

    drobilka.addInput(s1);
    drobilka.addOutput(s2);

    try {
      drobilka.addInput(s3);
    } catch (const char* ex) {
      if (ex == "Too much inputs") {
        cout << "Test 3 passed" << endl;

        return;
      }
    }

    cout << "Test 3 failed" << endl;
}

void tests() {
  correctGetMassFlow();
  correctOutputs();
  correctInputs();
}

int main()
{
    tests();
   
}
