all: golbach golbach_asan golbach_msan golbach_tsan memcheck helgrind

golbach: golbach_concurrente.c
	cc -g -Wall -Wextra golbach_concurrente.c -o golbach -lm -pthread

golbach_asan:
	clang -g -Wall -Wextra -fsanitize=address golbach_concurrente.c -o golbach_asan -lm

golbach_msan:
	clang -g -Wall -Wextra -fsanitize=memory golbach_concurrente.c -o golbach_msan -lm

golbach_tsan:
	clang -g -Wall -Wextra -fsanitize=thread golbach_concurrente.c -o golbach_tsan -lm

.PHONY: rebuild
rebuild: clean golbach golbach_asan golbach_msan

.PHONY:memcheck
memcheck:
	valgrind --tool=memcheck ./golbach
	
.PHONY: helgrind
helgrind:
	valgrind --quiet --tool=helgrind ./golbach

.PHONY: lint
lint:
	cpplint --filter=-[readability/casting] golbach_concurrente.c

.PHONY: gitignore
gitignore:
	echo golbach golbach_asan golbach_msan memcheck helgrind | tr " " "\n" > .gitignore

.PHONY: clean
clean:
	rm -rf golbach golbach_asan golbach_msan golbach_tsan
