//Task 5A Multithreaded Programming 2014
//Johannes Hovland - 101028
#include <stdlib.h>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "InputHandler.hpp"
#include "LogicHandler.hpp"
#include "OutputHandler.hpp"

int main (int argc, char* argv[]) {
	bool running = true;
	std::mutex lock;
	std::condition_variable newInput;
	std::condition_variable newLength;

	std::string callbackString = "";
	int callbackStringLength = 0;

	InputHandler inputHandler(&running, &callbackString, &newInput);
	LogicHandler logicHandler(&running, &callbackString, &callbackStringLength, &lock, &newInput, &newLength);
	OutputHandler outputHandler(&running, &callbackString, &callbackStringLength, &lock, &newLength);

	std::thread inputThread(&InputHandler::run, &inputHandler);
	std::thread logicThread(&LogicHandler::run, &logicHandler);
	std::thread outputThread(&OutputHandler::run, &outputHandler);

	inputThread.join();
	logicThread.join();
	outputThread.join();
	return 0;
}