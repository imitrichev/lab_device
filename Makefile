all: g++ -std=c++17 -lgtest -lgtest_main device.cpp -o main
clean: rm main