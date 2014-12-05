//Task 5A Multithreaded Programming 2014
//Johannes Hovland - 101028
#include "InputHandler.hpp"

InputHandler::InputHandler(	bool* running,
							std::string* callbackString,
							Barrier* newInput,
							Barrier* finishedOutput) {
	this->running = running;
	this->callbackString = callbackString;
	this->newInput = newInput;
	this->finishedOutput = finishedOutput;
}

InputHandler::~InputHandler() {

}

void InputHandler::run() {
	char charInput;
	int intInput;

	while (*running) {
		charInput = getchar();

		//Consumes remainig chars and \n
		while (getchar() != '\n') {
		}

		if(checkForInputError(charInput)) {
			break;
		}

		if (charInput == 'q') {
			break;
		}

		if (charInput == ' ') {
			for(int i = 1; i <= 5; i ++) {	//Run for all valid numeric input, 1->5
				if(!runCallback(i)){
					break;
				}
				finishedOutput->wait();
			}
		}

		if(charInput !=  ' ') {
			intInput = charInput - '0';
			if(!runCallback(intInput)){
				break;
			}		
			callbacks.changeOrder();
		}
	}

	*running = false;
	newInput->signal();
}

bool InputHandler::checkForInputError(char charInput) {
	if(charInput != ' ' && charInput != 'q' && (charInput < '0' || charInput > '5')) {
		printf("ERROR! Invalid input.\n");
		printf("ERROR! Exiting program.\n");
		printf("ERROR! Only the numbers 1->5  the letter 'q' and <space> is valid.\n");
		return true;
	}

	return false;
}

bool InputHandler::runCallback(int intInput) {
	auto getString = callbacks.getCallbacks(intInput);

	if(getString == nullptr) {
		printf("ERROR! getCallbacks returned nullptr.\n");
		printf("ERROR! Exiting program.\n");
		return false;
	}

	*callbackString = (callbacks.*getString)();
	newInput->signal();
	return true;
}