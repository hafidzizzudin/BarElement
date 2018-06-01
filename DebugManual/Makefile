all: BAR

BAR: main.o Node.o Coordinates.o System.o Mtx.o Element.o 
	g++ main.o Node.o Coordinates.o System.o Mtx.o Element.o -o BAR

main.o: ../src/main.cpp
	g++ -c ../src/main.cpp

Node.o: ../src/Node.cpp
	g++ -c ../src/Node.cpp

Coordinates.o: ../src/Coordinates.cpp
	g++ -c ../src/Coordinates.cpp

System.o: ../src/System.cpp
	g++ -c ../src/System.cpp

Mtx.o: ../src/Mtx.cpp
	g++ -c ../src/Mtx.cpp

Element.o: ../src/Element.cpp
	g++ -c ../src/Element.cpp

clean:
	rm -rf *.o BAR