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

class ComplexSeparator : public Device
{
private:
  int _outputs_count = 0;

public:
  ComplexSeparator(int outputs_count) : Device()
  {
    _outputs_count = outputs_count;
  }

  void addInput(shared_ptr<Stream> s)
  {
    if (inputs.size() > 1)
    {
      throw "Only one input allowed for ComplexSeparator.";
    }
    inputs.push_back(s);
  }

  void addOutput(shared_ptr<Stream> s)
  {
    if (outputs.size() == _outputs_count)
    {
      throw "Too many outputs for ComplexSeparator.";
    }
    outputs.push_back(s);
  }

  void updateOutputs() override
  {
    if (inputs.empty())
    {
      throw "No input provided for ComplexSeparator.";
    }

    double input_mass_flow = inputs[0]->getMassFlow();
    double output_mass = input_mass_flow / _outputs_count;

    for (auto &output_stream : outputs)
    {
      output_stream->setMassFlow(output_mass);
    }
  }
};

int main()
{
  streamcounter = 0;

  // create new complex separator with 3 output streams
  ComplexSeparator separator(3);

  shared_ptr<Stream> s1(new Stream(++streamcounter));
  s1->setMassFlow(10.0);
  s1->print();
  separator.addInput(s1);

  shared_ptr<Stream> s2(new Stream(++streamcounter));
  shared_ptr<Stream> s3(new Stream(++streamcounter));
  shared_ptr<Stream> s4(new Stream(++streamcounter));

  separator.addOutput(s2);
  separator.addOutput(s3);
  separator.addOutput(s4);

  separator.updateOutputs();
  s2->print();
  s3->print();
  s4->print();

  return 0;
}
