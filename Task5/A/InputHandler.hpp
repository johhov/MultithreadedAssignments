//Task 5A Multithreaded Programming 2014
//Johannes Hovland - 101028
#pragma once

#include <string>
#include <stdio.h>
#include <iostream>
#include <thread>

#include "Barrier.hpp"
#include "Callbacks.hpp"

class InputHandler {
public:
	InputHandler(	bool* running,
					std::string* callbackString,
					Barrier* newInput,
					Barrier* finishedOutput);
	~InputHandler();

	void run();
	bool checkForInputError(char charInput);
	bool runCallback(int intInput);
private:
	//External
	bool* running;
	Barrier* newInput;
	Barrier* finishedOutput;

	std::string* callbackString;

	//Internal
	Callbacks callbacks;
};