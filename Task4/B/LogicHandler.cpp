//Task 4B Multithreaded Programming 2014
//Johannes Hovland - 101028
#include "LogicHandler.hpp"

LogicHandler::LogicHandler(bool* running, SafeQueue* inputQueue, SafeQueue* outputQueue) {
	this->running = running;
	this->inputQueue = inputQueue;
	this->outputQueue = outputQueue;
}

LogicHandler::~LogicHandler() {

}

void LogicHandler::run() {
	int input;
	int output;

	while(*running) {
		if(!inputQueue->empty()) {
			input = inputQueue->pop();
			output = input;

			#pragma omp parallel for reduction(+:output)
			for (int i = 0; i < input; i++) {
				output++;
			}

			outputQueue->push(output);
		}
	}
}
