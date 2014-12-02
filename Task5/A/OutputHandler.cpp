//Task 5A Multithreaded Programming 2014
//Johannes Hovland - 101028
#include "OutputHandler.hpp"

OutputHandler::OutputHandler(	bool* running,
								std::string* callbackString,
								int* callbackStringLength,
								std::mutex* lock,
								std::condition_variable* newLength) {
	this->running = running;
	this->callbackString = callbackString;
	this->callbackStringLength = callbackStringLength;
	this->lock = lock;
	this->newLength = newLength;
}

OutputHandler::~OutputHandler() {

}

void OutputHandler::run() {
	while(*running) {
		std::unique_lock<std::mutex> lLock((*this->lock));
		newLength->wait(lLock);
		
		if(!(*running)) {
			break;
		}
		
		std::cout << *callbackString << ", " << *callbackStringLength << std::endl;
	}	
}
