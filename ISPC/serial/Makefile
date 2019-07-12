
blur: blur.cpp
	g++ -o blur blur.cpp -O2 -L/usr/X11R6/lib -lm -lpthread -lX11 -std=c++11

run: blur
	./blur

clean:
	rm blur
