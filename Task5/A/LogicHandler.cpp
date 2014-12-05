//Task 5A Multithreaded Programming 2014
//Johannes Hovland - 101028
#include "LogicHandler.hpp"

LogicHandler::LogicHandler(	bool* running,
							std::string* callbackString,
							int* callbackStringLength,
							Barrier* newInput,
							Barrier* newLength) {
	this->running = running;
	this->callbackString = callbackString;
	this->callbackStringLength = callbackStringLength;
	this->newInput = newInput;
	this->newLength = newLength;
}

LogicHandler::~LogicHandler() {

}

void LogicHandler::run() {
	while(*running) {
		newInput->wait();

		if(!(*running)) {
			break;
		}

		*callbackStringLength = callbackString->length();
		newLength->signal();
	}

	newLength->signal();
}
