CC = g++
OUTPUT = solution
    
all: pugixml.o
	$(CC) pugixml.o main.cpp -o $(OUTPUT)

pugixml.o: pugixml.hpp pugiconfig.hpp pugixml.cpp
	$(CC) -c pugixml.cpp

clean:
	rm -f $(OUTPUT) *.o
