#include <iostream>
#include <string>
#include <vector>
#include <memory>

int streamcounter = 0;

class Stream
{
    private:
    	double mass_flow = 0;
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
      	std::vector<std::shared_ptr<Stream>> inputs;
      	std::vector<std::shared_ptr<Stream>> outputs;
    public:
      	void addInput(std::shared_ptr<Stream> s) { inputs.push_back(s); }
      	void addOutput(std::shared_ptr<Stream> s) { outputs.push_back(s); }
      	
		virtual void updateOutputs() = 0;
};

//class Mixer.......

int main()
{
	streamcounter=0;
    //Mixer d1;
    
    std::shared_ptr<Stream> s1(new Stream(++streamcounter));
    std::shared_ptr<Stream> s2(new Stream(++streamcounter));
    std::shared_ptr<Stream> s3(new Stream(++streamcounter));
    s1->setMassFlow(10.0);
    s2->setMassFlow(5.0);
    
    //d1.addInput......
}
