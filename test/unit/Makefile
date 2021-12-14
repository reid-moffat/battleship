output: main.o button.o background.o
	g++ -std=c++11 main.o buttonTest.o background.o -o main.out -L/usr/local/Cellar/sfml/2.5.1_1/lib -lsfml-system -lsfml-graphics -lsfml-window

main.o: main.cpp
	g++ -c -std=c++11 main.cpp -I/usr/local/Cellar/sfml/2.5.1_1/include

button.o: buttonTest.cpp buttonTest.h
	g++ -c -std=c++11 buttonTest.cpp -I/usr/local/Cellar/sfml/2.5.1_1/include

background.o: background.cpp background.h
	g++ -c -std=c++11 background.cpp -I/usr/local/Cellar/sfml/2.5.1_1/include

clean:
	rm *.o main.out