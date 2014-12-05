//Task 5A Multithreaded Programming 2014
//Johannes Hovland - 101028
#include <stdlib.h>
#include <string>
#include <thread>

#include "InputHandler.hpp"
#include "LogicHandler.hpp"
#include "OutputHandler.hpp"
#include "Barrier.hpp"

int main (int argc, char* argv[]) {
	//Shared data
	bool running = true;
	std::string callbackString = "";
	int callbackStringLength = 0;

	Barrier newInput;
	Barrier newLength;
	Barrier finishedOutput;

	//Thread handler initialization
	InputHandler inputHandler(&running, &callbackString, &newInput, &finishedOutput);
	LogicHandler logicHandler(&running, &callbackString, &callbackStringLength, &newInput, &newLength);
	OutputHandler outputHandler(&running, &callbackString, &callbackStringLength, &newLength, &finishedOutput);

	//Threads
	std::thread inputThread(&InputHandler::run, &inputHandler);
	std::thread logicThread(&LogicHandler::run, &logicHandler);
	std::thread outputThread(&OutputHandler::run, &outputHandler);

	//Close program
	inputThread.join();
	logicThread.join();
	outputThread.join();
	return 0;
}