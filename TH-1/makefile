all: array-summary

array-summary: array-summary.o
	g++ array-summary.o-o array-summary

array-summary.o: array-summary.cpp
	g++ array-summary.cpp -c

clean:
	rm*.o array-summary