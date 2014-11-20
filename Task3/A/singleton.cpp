//Task 3A Multithreaded Programming 2014
//Johannes Hovland - 101028

#include "singleton.hpp"

//PUBLIC
Singleton* Singleton::getInstance(){
	if(instance == NULL) {
		#pragma omp critical
		{
			if(instance == NULL) {
				instance = new Singleton();
			}
		}
	}

	return instance;
}

//PRIVATE
Singleton* Singleton::instance = NULL;

Singleton::Singleton() {
	doWork();
}

void Singleton::doWork() {
	usleep(50000);
}