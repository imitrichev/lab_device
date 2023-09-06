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
// Обновление выходных потоков и проверка условия одного входа и выхода
    void updateOutputs() override {
        if (inputs.size() == 1 && outputs.size() == 1) {
            // Получение массового расхода входного потока
            double inputMassFlow = inputs[0]->getMassFlow();
            // Получение выходного потока согласно массовому расходу
            double outputMassFlow = inputMassFlow * 0.3;
            // Устанавление массового расхода для выходного потока
            outputs[0]->setMassFlow(outputMassFlow);
        }
    }
};
void testTooManyOutputStreams(){
    streamcounter=0;
    
    Drobilka dl = new Drobilka (false);
    
    shared_ptr<Stream> s1(new Stream(++streamcounter));
    shared_ptr<Stream> s2(new Stream(++streamcounter));
    shared_ptr<Stream> s3(new Stream(++streamcounter));
    s1->setMassFlow(10.0);
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
    
     Drobilka dl = new  Drobilka(false);
    
    shared_ptr<Stream> s1(new Stream(++streamcounter));
    shared_ptr<Stream> s3(new Stream(++streamcounter));
    s1->setMassFlow(10.0);
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
    
     Drobilka dl = new  Drobilka(true);
    
    shared_ptr<Stream> s1(new Stream(++streamcounter));
    shared_ptr<Stream> s2(new Stream(++streamcounter));
    shared_ptr<Stream> s3(new Stream(++streamcounter));
    s1->setMassFlow(10.0);
    dl.addInput(s1);
    dl.addOutput(s2);
    dl.addOutput(s3);
    
    dl.updateOutputs();
    
    if(dl.outputs.getMassFlow == dl.inputs.getMassFlow){
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
    streamcounter=0;
    //Mixer d1;
    // Создание экземпляра класса
    Drobilka drobilka;
    shared_ptr<Stream> s1(new Stream(++streamcounter));
    shared_ptr<Stream> s2(new Stream(++streamcounter));

    s1->setMassFlow(10.0);
    // Добавление потоков в дробилку
    drobilka.addInput(s1);
    drobilka.addOutput(s2);
    // Обновление выходного потока
    drobilka.updateOutputs();
    // Вывод входного и выходного потока
    s1->print();
    s2->print();
    tests;
    //d1.addInput......
}
