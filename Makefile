all:
	g++ -std=c++17 -pthread -I/usr/include/gtest -L/usr/lib/x86_64-linux-gnu -lgtest -lpthread device.cpp -o main
clean:
	rm main