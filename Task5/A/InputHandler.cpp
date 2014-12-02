//Task 5A Multithreaded Programming 2014
//Johannes Hovland - 101028
#include "InputHandler.hpp"

InputHandler::InputHandler(	bool* running,
							std::string* callbackString,
							std::condition_variable* newInput) {
	this->running = running;
	this->callbackString = callbackString;
	this->newInput = newInput;
}

InputHandler::~InputHandler() {

}

void InputHandler::run() {
	char charInput;
	int intInput;

	while (*running) {
		charInput = getchar(); //Get input
		intInput = -1; 
		
		if(charInput != ' ' && charInput != 'q' && (charInput < '0' || charInput > '5')) {
			printf("ERROR! Invalid input.\n");
			printf("ERROR! Exiting program.\n");
			printf("ERROR! Only the numbers 1->5  the letter 'q' and <space> is valid.\n");
			break;
		}

		if (charInput == 'q') {
			break;
		}

		//Consumes remainig chars and \n
		while (getchar() != '\n') {
		}

		intInput = charInput - '0';

		if (charInput == ' ') {
			callbacks.changeOrder();
		}

		if(charInput !=  ' ') {
			auto getString = callbacks.getCallbacks(intInput);
	
			if(getString == nullptr) {
				printf("ERROR! getCallbacks returned nullptr.\n");
				printf("ERROR! Exiting program.\n");
				break;
			}

			*callbackString = (callbacks.*getString)();
			newInput->notify_all();
		}
	}

	*running = false;
	newInput->notify_all();
}
