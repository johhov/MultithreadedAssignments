//Task 5A Multithreaded Programming 2014
//Johannes Hovland - 101028
#pragma once

#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

class LogicHandler {
public:
	LogicHandler(	bool* running,
					std::string* callbackString,
					int* callbackStringLength,
					std::mutex* lock,
					std::condition_variable* newInput,
					std::condition_variable* newLength);
	~LogicHandler();

	void run();
private:
	//External
	bool* running;
	std::mutex* lock;
	std::condition_variable* newInput;
	std::condition_variable* newLength;

	std::string* callbackString;
	int* callbackStringLength;

	//Internal
};