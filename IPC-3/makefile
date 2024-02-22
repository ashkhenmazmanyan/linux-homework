shared_array.o: shared_array.cpp
	g++ shared_array.cpp -c -oshared_array.oshared_array

first:	first.o shared_array.o
	g++	 first.o shared_array.o -o first

first.o: first.cpp
	g++ first.cpp -c -o first.cpp

second:	second.o shared_array.o
	g++	 second.o shared_array.o -o second
	
second.o: second.cpp
	g++ second.cpp -c -o second.cpp

clean:
	rm*.first second