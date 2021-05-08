shared count := 0
shared upper_limit := 0

main:
	// Read integer from standard input
	thread_count := read_integer()
	upper_limit := read_integer()
	shared mutex := semaphore(upper_limit)
	create_thread(thread_count, secondary)
	
secondary:
	// Critical section
	wait(mutex)
	count := count + 1
	signal(mutex)
