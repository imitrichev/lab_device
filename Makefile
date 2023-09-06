all:
	g++ -std=c++17 device.cpp -o prog.out

clean:
	rm prog.out