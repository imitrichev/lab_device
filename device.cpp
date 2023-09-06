#include <iostream>
#include <cassert>
#include <memory>
#include <vector>
#include <string>

using namespace std;
int streamcounter;

class Stream
{
private:
    double mass_flow;
    string name;

public:
    Stream(int s) { setName("s" + std::to_string(s)); }
    void setName(string s) { name = s; }
    string getName() { return name; }
    void setMassFlow(double m) { mass_flow = m; }
    double getMassFlow() { return mass_flow; }
    void print() { cout << "Stream " << getName() << " flow = " << getMassFlow() << endl; }
};

class Device
{
protected:
    vector<shared_ptr<Stream>> inputs;
    vector<shared_ptr<Stream>> outputs;

public:
    void addInput(shared_ptr<Stream> s) { inputs.push_back(s); }
    void addOutput(shared_ptr<Stream> s) { outputs.push_back(s); }
    virtual void updateOutputs() = 0;
};

class SimpleColumn : public Device
{
public:
    SimpleColumn() {}

    void updateOutputs() override {
        if (inputs.size() == 1 && outputs.size() == 2) {
            double inputMassFlow = inputs[0]->getMassFlow();
            double outputMassFlow = inputMassFlow / 2.0;
            outputs[0]->setMassFlow(outputMassFlow);
            outputs[1]->setMassFlow(outputMassFlow);
        }
    }
};

void testStream() {
    // Тест случая для класса Stream
    shared_ptr<Stream> s(new Stream(1));
    s->setMassFlow(15.0);
    
    // Проверяем, что массовый расход устанавливается и возвращается корректно
    assert(s->getMassFlow() == 15.0);
    
    // Проверяем, что имя объекта устанавливается корректно
    assert(s->getName() == "s1");
}

void testSimpleColumn() {
    // Тест случая для класса SimpleColumn
    shared_ptr<Stream> s1(new Stream(1));
    shared_ptr<Stream> s2(new Stream(2));
    shared_ptr<Stream> s3(new Stream(3));

    s1->setMassFlow(10.0);
    s2->setMassFlow(5.0);

    SimpleColumn column;
    column.addInput(s1);
    column.addOutput(s2);
    column.addOutput(s3);

    // Вызываем метод updateOutputs для SimpleColumn
    column.updateOutputs();

    // Проверяем, что массовый расход установлен корректно для выходных потоков s2 и s3
    assert(s2->getMassFlow() == 7.5);
    assert(s3->getMassFlow() == 7.5);
}

void runTests() {
    testStream();
    testSimpleColumn();
    cout << "All tests passed!" << endl;
}

int main() {
    runTests();
    return 0;
}
