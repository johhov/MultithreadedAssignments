Bug:
	Crash on exit command
Problem:
	Class destructor deleting shared variables
Solution:
	Since all objects are used untill the program closes let the program free all memory on close.