slm: src/main.cpp src/Reader.cpp src/Generator.cpp src/Reader.h src/Generator.h
	g++ src/main.cpp src/Reader.cpp src/Generator.cpp -o slm

clean:
	rm -f slm