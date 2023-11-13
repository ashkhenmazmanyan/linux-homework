all: do-command

do-command: do-command.o
	g++ do-command.o-o do-command

do-command.o: hacker_rm.cpp
	g++ do-command.cpp -c

clean:
	rm*.o do-command