//Task 5A Multithreaded Programming 2014
//Johannes Hovland - 101028
#include "LogicHandler.hpp"

LogicHandler::LogicHandler(	bool* running,
							std::string* callbackString,
							int* callbackStringLength,
							std::mutex* lock,
							std::condition_variable* newInput,
							std::condition_variable* newLength) {
	this->running = running;
	this->callbackString = callbackString;
	this->callbackStringLength = callbackStringLength;
	this->lock = lock;
	this->newInput = newInput;
	this->newLength = newLength;
}

LogicHandler::~LogicHandler() {

}

void LogicHandler::run() {
	while(*running) {
		std::unique_lock<std::mutex> lock((*this->lock));
		newInput->wait(lock);

		if(!(*running)) {
			break;
		}

		*callbackStringLength = callbackString->length();
		newLength->notify_all();
	}

	newLength->notify_all();
}
