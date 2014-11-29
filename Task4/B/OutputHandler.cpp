//Task 4B Multithreaded Programming 2014
//Johannes Hovland - 101028
#include "OutputHandler.hpp"

OutputHandler::OutputHandler(bool* running, SafeQueue* outputQueue) {
	this->running = running;
	this->outputQueue = outputQueue;
}

OutputHandler::~OutputHandler() {

}

void OutputHandler::run() {
	while(*running) {
		if(!outputQueue->empty()) {
			printf("%d\n", outputQueue->pop());
		}
	}	
}
