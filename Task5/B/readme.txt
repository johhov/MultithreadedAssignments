Bug:
	Giving space as input produced the wrong output
Problem:
	Had forgotten to count down the samaphore on numerical input
Solution:
	Added a sem_wait on line 82