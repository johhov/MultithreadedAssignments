//Task 3B Multithreaded Programming 2014
//Johannes Hovland - 101028
Bug
	segfault
Solution
	moved allocation of temporary variable outside of "#pragma omp critical"

Bug
	segfault
Solution
	check to see if stack is empty before looking at the top.
	Return -1 if empty

Bug
	Program would not proceed to pop after having filled the stack.
Solution
	There was a sem_post() placed after the return statement in SafeStack::empty().
	This took waaaaay too long to figure out.