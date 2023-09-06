all:
	g++ -std=c++17 -pthread -I/usr/include/gtest -L/usr/lib/x86_64-linux-gnu device.cpp -o main -lgtest -lpthread
clean:
	rm main
