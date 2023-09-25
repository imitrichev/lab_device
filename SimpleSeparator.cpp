#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cassert>

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

class SimpleSeparator : public Device {
    private:
        double splittingRatio;

    public:
        SimpleSeparator(double ratio) : splittingRatio(ratio) {}

        void setSplittingRatio(double ratio) {
            splittingRatio = ratio;
        }

        double getSplittingRatio() {
            return splittingRatio;
        }

        void updateOutputs() override {
            if (inputs.size() < 1 || outputs.size() < 2) {
                cerr << "Not enough input or output streams are set for SimpleSeparator!" << endl;
                return;
            }

            double inputMassFlow = inputs[0]->getMassFlow();
            outputs[0]->setMassFlow(inputMassFlow * splittingRatio);
            outputs[1]->setMassFlow(inputMassFlow * (1 - splittingRatio));
        }
};

// Тестовая функция для класса Stream
void testStream() {
    shared_ptr<Stream> s(new Stream(streamcounter));
    s->setName("s0");
    assert(s->getName() == "s0"); // проверка установки имени потока
    s->setMassFlow(20.0);
    assert(s->getMassFlow() == 20.0); // проверка установки и извлечения массы потока
}

// Тестовая функция для класса SimpleSeparator
void testSimpleSeparator() {
    shared_ptr<Stream> s1(new Stream(++streamcounter));
    s1->setMassFlow(10.0);

    shared_ptr<Stream> s2(new Stream(++streamcounter));
    shared_ptr<Stream> s3(new Stream(++streamcounter));

    SimpleSeparator separator(0.5);
    assert(separator.getSplittingRatio() == 0.5); // проверка установки и извлечения коэффициента разделения

    separator.addInput(s1);
    separator.addOutput(s2);
    separator.addOutput(s3);

    separator.updateOutputs();

    assert(s2->getMassFlow() == 5.0); // проверка корректного обновления выходных потоков
    assert(s3->getMassFlow() == 5.0);
}

// Тестовая функция для класса Device (на примере класса SimpleSeparator)
void testDevice() {
    shared_ptr<Stream> s1(new Stream(++streamcounter));
    s1->setMassFlow(20.0);

    shared_ptr<Stream> s2(new Stream(++streamcounter));
    shared_ptr<Stream> s3(new Stream(++streamcounter));

    SimpleSeparator separator(0.4);

    separator.addInput(s1);
    separator.addOutput(s2);
    separator.addOutput(s3);

    separator.updateOutputs();

    assert(s2->getMassFlow() == 8.0); // проверка корректного обновления выходных потоков
    assert(s3->getMassFlow() == 12.0);
}


int main() {
    streamcounter = 0;

    shared_ptr<Stream> s1(new Stream(++streamcounter));
    shared_ptr<Stream> s2(new Stream(++streamcounter));
    shared_ptr<Stream> s3(new Stream(++streamcounter));

    s1->setMassFlow(15.0);

    SimpleSeparator separator(0.6);
    separator.addInput(s1);
    separator.addOutput(s2);
    separator.addOutput(s3);

    separator.updateOutputs();

    s1->print();
    s2->print();
    s3->print();

    // Прогон тестовых функций
    testStream();
    testSimpleSeparator();
    testDevice();

    cout << "All tests passed successfully!" << endl;

    return 0;
}