#include <iostream>
#include <string>
#include <vector>
#include <memory>

int streamcounter = 0;

class Device;

class Stream
{
    private:
    	double mass_flow;
      	std::string name;
		std::shared_ptr<Device> came_from;	// Поток вытекает из
		std::shared_ptr<Device> came_to;	// Поток течёт в 
    public:
      	Stream(int s) { setName("s" + std::to_string(s)); }

      	void setName(std::string s) { name = s; }
      	void print() { std::cout << "Stream " << getName() << " flow = " << getMassFlow() << std::endl;}
      	void setMassFlow(double m) { mass_flow = m; }

      	std::string getName() { return name; }

      	double getMassFlow() { return mass_flow; }

		void setStreamCameFrom(std::shared_ptr<Device> came_from) { this->came_from = came_from; }
		void setStreamCameTo(std::shared_ptr<Device> came_to) { this->came_to = came_to; }
		std::shared_ptr<Device> getStreamCameFrom() { return came_from; }
		std::shared_ptr<Device> getStreamCameTo()	{ return came_to; }
};

class Device
{
    protected:
      	std::vector<std::shared_ptr<Stream> > inputs;
      	std::vector<std::shared_ptr<Stream> > outputs;
		std::string name;
    public:

		Device() {};
		Device(std::string name) { this->name = name; }

      	void addInput(std::shared_ptr<Stream> s) { inputs.push_back(s); }
      	void addOutput(std::shared_ptr<Stream> s) { outputs.push_back(s); }

		void printInputs()
		{
			std::cout << "Inputs for " << name << "\n";
			for (auto input : inputs)
				input.get()->print();
			
			std::cout << "\n";
		}

		void printOutpus()
		{
			std::cout << "Outputs for " << name << "\n";
			for (auto output : outputs)
				output.get()->print();

			std::cout << "\n";
		}

		virtual void updateOutputs()
		{

		};
};

//class Mixer.......

int main()
{
    //Mixer d1;
    
    std::shared_ptr<Stream> s1(new Stream(++streamcounter));
    std::shared_ptr<Stream> s2(new Stream(++streamcounter));
    std::shared_ptr<Stream> s3(new Stream(++streamcounter));
    std::shared_ptr<Stream> s4(new Stream(++streamcounter));
    std::shared_ptr<Stream> s5(new Stream(++streamcounter));

    s1->setMassFlow(10.0);
    s2->setMassFlow(5.0);
	s3->setMassFlow(7.5);
	s4->setMassFlow(3.0);
	s5->setMassFlow(1.3);
    
	std::shared_ptr<Device> d1(new Device("First Device"));
	std::shared_ptr<Device> d2(new Device("Second Device"));
	std::shared_ptr<Device> d3(new Device("Third Device"));

	d1->addInput(s1);
	d1->addInput(s2);
	d1->addOutput(s3);

	d1->printInputs();
	d1->printOutpus();

	d2->addInput(s3);
	d2->addOutput(s4);

	d2->printInputs();
	d2->printOutpus();

	d3->addInput(s1);
	d3->addOutput(s5);

	d3->printInputs();
	d3->printOutpus();

    //d1.addInput......
}
