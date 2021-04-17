globach: golbach_serial.c
	cc -g -Wall -Wextra golbach_serial.c -o golbach -lm

all: golbach memcheck helgrind
.PHONY: rebuild
rebuild: clean golbach

.PHONY:memcheck
memcheck:
	valgrind --quiet --tool=memcheck ./golbach
	
.PHONY: helgrind
helgrind:
	valgrind --quiet --tool=helgrind ./golbach
	
.PHONY: clean
clean:
	rm -rf golbach
