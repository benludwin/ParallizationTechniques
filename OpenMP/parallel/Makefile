
heat: heat.o
	g++ -m64 -std=c++11 -O2 -Wall -fopenmp -o heat heat.o

heat.o: heat.cpp
	g++ -m64 -std=c++11 -O2 -Wall -fopenmp -c -o $@ $<

run: heat
	./heat

clean:
	rm heat

