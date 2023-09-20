all:
	g++ -std=c++20 device.cpp -o a.out -lgtest -pthread
clean:
	rm a.out
