//Task 5A Multithreaded Programming 2014
//Johannes Hovland - 101028
#pragma once

#include <string>
#include <stdio.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "Callbacks.hpp"

class InputHandler {
public:
	InputHandler(	bool* running,
					std::string* callbackString,
					std::condition_variable* newInput);
	~InputHandler();

	void run();
private:
	//External
	bool* running;
	std::condition_variable* newInput;

	std::string* callbackString;

	//Internal
	Callbacks callbacks;
};