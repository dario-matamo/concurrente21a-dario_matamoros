all: golbach golbach_asan golbach_msan memcheck helgrind

golbach: golbach_serial.c
	cc -g -Wall -Wextra golbach_serial.c -o golbach -lm

golbach_asan:
	clang -g -Wall -Wextra -fsanitize=address golbach_serial.c -o golbach_asan -lm

golbach_msan:
	clang -g -Wall -Wextra -fsanitize=address golbach_serial.c -o golbach_msan -lm

.PHONY: rebuild
rebuild: clean golbach golbach_asan golbach_msan

.PHONY:memcheck
memcheck:
	valgrind --quiet --tool=memcheck ./golbach
	
.PHONY: helgrind
helgrind:
	valgrind --quiet --tool=helgrind ./golbach

.PHONY: lint
lint:
	cpplint --filter=-[readability/casting] golbach_serial.c

.PHONY: clean
clean:
	rm -rf golbach
