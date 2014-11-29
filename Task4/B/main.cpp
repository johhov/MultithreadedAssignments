//Task 4B Multithreaded Programming 2014
//Johannes Hovland - 101028
#include <thread>

#include "InputHandler.hpp"
#include "LogicHandler.hpp"
#include "OutputHandler.hpp"
#include "SafeQueue.hpp"

int main (int argc, char* argv[]) {
	bool running = true;

	SafeQueue inputQueue;
	SafeQueue outputQueue;

	InputHandler inputHandler(&running, &inputQueue);
	LogicHandler logicHandler(&running, &inputQueue, &outputQueue);
	OutputHandler outputHandler(&running, &outputQueue);

	std::thread inputThread(&InputHandler::run, &inputHandler);
	std::thread logicThread(&LogicHandler::run, &logicHandler);
	std::thread outputThread(&OutputHandler::run, &outputHandler);

	inputThread.join();
	logicThread.join();
	outputThread.join();
	return 0;
}