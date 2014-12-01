all:	bin

bin:	markov.h test.cpp
	@g++ -Wall -g test.cpp -o bin
	@./bin
#	@valgrind ./bin

clean:
	rm bin
	rm *~
