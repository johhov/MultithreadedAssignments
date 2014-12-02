//Task 5A Multithreaded Programming 2014
//Johannes Hovland - 101028
#pragma once

#include <string>
#include <vector>

class Callbacks;

typedef std::string(Callbacks::*funcPtr_t)();

class Callbacks {
public:
	Callbacks();
	~Callbacks();

	void changeOrder();

	funcPtr_t getCallbacks(int input);

private:
	std::string getKeyOne();
	std::string getKeyTwo();
	std::string getKeyThree();
	std::string getKeyFour();
	std::string getKeyFive();

	bool mixed;

	funcPtr_t callbacksSequensial[5];
	funcPtr_t callbacksMixed[5];	
};