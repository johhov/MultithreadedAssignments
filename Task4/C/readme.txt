Bug:
	Program will not run.
Problem:
	Bad makefile.
Solution:
	Removed unused libraries.

Bug:
	Program never stopped popping.
Problem:
	Race condition.
Solution:
	Added a mutex so that no threads can skip over and miss the end of data flag.