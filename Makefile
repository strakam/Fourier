fourier-app: main.o machine.o circle.o
	g++ main.o circle.o machine.o -o fourier-app -lsfml-graphics \
	-lsfml-window -lsfml-system

main.o: src/main.cpp
	g++ -c src/main.cpp

circle.o: src/circle.cpp
	g++ -c src/circle.cpp

machine.o: src/machine.cpp
	g++ -c src/machine.cpp

clean:
	rm *.o
