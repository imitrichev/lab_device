#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <gtest/gtest.h>

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
      	void setMassFlow(double m) { mass_flow = m; }

		void setStreamCameFrom(std::shared_ptr<Device> came_from) { this->came_from = came_from; }
		void setStreamCameTo(std::shared_ptr<Device> came_to) { this->came_to = came_to; }

      	void print() { std::cout << "Stream " << getName() << " flow = " << getMassFlow() << std::endl;}

      	double getMassFlow() { return mass_flow; }

      	std::string getName() { return name; }
		
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
				input->print();
			
			std::cout << "\n";
		}

		void printOutpus()
		{
			std::cout << "Outputs for " << name << "\n";
			for (auto output : outputs)
				output->print();

			std::cout << "\n";
		}

		std::string getName() { return name; }

		virtual void updateOutputs() { };
};

TEST(StreamTests, TestStreamSettrGettr)
{
    std::shared_ptr<Stream> s1(new Stream(++streamcounter));
    std::shared_ptr<Stream> s2(new Stream(++streamcounter));
    std::shared_ptr<Stream> s3(new Stream(++streamcounter));

	std::shared_ptr<Device> d1(new Device("First Device"));
	std::shared_ptr<Device> d2(new Device("Second Device"));

	d1->addInput(s1);
	d1->addInput(s2);
	d1->addOutput(s3);

	d2->addInput(s3);
	d2->addOutput(s1);

	s1->setStreamCameTo(d1);
	s1->setStreamCameFrom(d2);
	s2->setStreamCameTo(d1);

	s3->setStreamCameFrom(d1);
	s3->setStreamCameTo(d2);

	ASSERT_EQ(s1->getStreamCameTo(), d1);
	ASSERT_EQ(s2->getStreamCameTo(), d1);
	ASSERT_EQ(s3->getStreamCameTo(), d2);

	ASSERT_EQ(s1->getStreamCameFrom(), d2);
	ASSERT_EQ(s3->getStreamCameFrom(), d1);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}