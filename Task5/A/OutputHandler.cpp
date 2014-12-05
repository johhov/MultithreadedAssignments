//Task 5A Multithreaded Programming 2014
//Johannes Hovland - 101028
#include "OutputHandler.hpp"

OutputHandler::OutputHandler(	bool* running,
								std::string* callbackString,
								int* callbackStringLength,
								Barrier* newLength,
								Barrier* finishedOutput) {
	this->running = running;
	this->callbackString = callbackString;
	this->callbackStringLength = callbackStringLength;
	this->newLength = newLength;
	this->finishedOutput= finishedOutput;
}

OutputHandler::~OutputHandler() {

}

void OutputHandler::run() {
	while(*running) {
		newLength->wait();
		
		if(!(*running)) {
			break;
		}
		
		std::cout << *callbackString << ", " << *callbackStringLength << std::endl;
		finishedOutput->signal();
	}

	finishedOutput->signal();
}
