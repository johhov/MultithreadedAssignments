//Task 5B Multithreaded Programming 2014
//Johannes Hovland - 101028
#include "Callbacks.hpp"	

Callbacks::Callbacks() {
	mixed = false;

	callbacksSequensial[0] = &Callbacks::getKeyOne;
	callbacksSequensial[1] = &Callbacks::getKeyTwo;
	callbacksSequensial[2] = &Callbacks::getKeyThree;
	callbacksSequensial[3] = &Callbacks::getKeyFour;
	callbacksSequensial[4] = &Callbacks::getKeyFive;

	callbacksMixed[0] = &Callbacks::getKeyFive;
	callbacksMixed[1] = &Callbacks::getKeyFour;
	callbacksMixed[2] = &Callbacks::getKeyOne;
	callbacksMixed[3] = &Callbacks::getKeyTwo;
	callbacksMixed[4] = &Callbacks::getKeyThree;
}

Callbacks::~Callbacks() {

}


void Callbacks::changeOrder() {
	mixed = !mixed;
}

funcPtr_t Callbacks::getCallbacks(int input) {
	if (mixed) {
		return callbacksMixed[input-1];
	}

	return callbacksSequensial[input-1];
}

std::string Callbacks::getKeyOne() {
	return *(new std::string("One"));
}

std::string Callbacks::getKeyTwo() {
	return *(new std::string("Two"));	
}

std::string Callbacks::getKeyThree() {
	return *(new std::string("Three"));
}

std::string Callbacks::getKeyFour() {
	return *(new std::string("Four"));
}

std::string Callbacks::getKeyFive() {
	return *(new std::string("Five"));
}