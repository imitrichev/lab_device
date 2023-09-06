all:
	g++ -std=c++17 -I/usr/include/gtest -L/usr/lib/x86_64-linux-gnu -lgtest -lgtest_main device.cpp -o main
clean:
	rm main