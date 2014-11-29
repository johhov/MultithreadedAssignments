//Task 4B Multithreaded Programming 2014
//Johannes Hovland - 101028
#include "InputHandler.hpp"

InputHandler::InputHandler(bool* running, SafeQueue* inputQueue) {
	this->running = running;
	this->inputQueue = inputQueue;
}

InputHandler::~InputHandler() {

}

void InputHandler::run() {
	char charInput[100];
	int intInput;

	while (*running) {
		scanf(" %100s", charInput);
		intInput = atoi(charInput);

		if (charInput[0] == 'q') {
			*running = false;
			return;
		}

		if(intInput != 0) {
			inputQueue->push(intInput);
		}
	}
}
