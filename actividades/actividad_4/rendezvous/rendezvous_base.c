main:
  shared a1_ready := semaphore(0)
  shared b1_ready := semaphore(0)
	create_thread(thread_a)
	create_thread(thread_b)

thread_a:
	statement a1
	signal(a1_ready)
	wait(b1_ready)
	statement a2

thread_b:
	statement b1
	signal(b1_ready)
	wait(a1_ready)
	statement b2
