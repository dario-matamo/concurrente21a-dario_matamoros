shared count := 0
shared mutex := semaphore(1)

main:
	// Read integer from standard input
	thread_count := read_integer()
	create_thread(thread_count, secondary)

secondary:
	// Critical section
	wait(mutex)
	count := count + 1
	signal(mutex)
