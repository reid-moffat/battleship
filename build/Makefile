main.out: main.o screenManager.o state.o screenTemplate.o homepage.o instructions.o gameModeSelection.o difficultySelection.o fleetPlacement.o intermediary.o gameplay.o gameOver.o button.o coordinate.o grid.o target.o
	g++ -std=c++11 main.o screenManager.o state.o screenTemplate.o homepage.o instructions.o gameModeSelection.o difficultySelection.o fleetPlacement.o intermediary.o gameplay.o gameOver.o button.o coordinate.o grid.o target.o -o main.out -L/usr/local/Cellar/sfml/2.5.1_1/lib -lsfml-window -lsfml-system -lsfml-graphics 

main.o: ../src/main.cpp
	g++ -c -std=c++11 ../src/main.cpp -I/usr/local/Cellar/sfml/2.5.1_1/include

screenManager.o: ../src/screen/screenManager.cpp
	g++ -c -std=c++11 ../src/screen/screenManager.cpp -I/usr/local/Cellar/sfml/2.5.1_1/include

state.o: ../src/state.cpp
	g++ -c -std=c++11 ../src/state.cpp -I/usr/local/Cellar/sfml/2.5.1_1/include

screenTemplate.o: ../src/screen/screenTemplate.cpp
	g++ -c -std=c++11 ../src/screen/screenTemplate.cpp -I/usr/local/Cellar/sfml/2.5.1_1/include

homepage.o: ../src/screen/homepage.cpp
	g++ -c -std=c++11 ../src/screen/homepage.cpp -I/usr/local/Cellar/sfml/2.5.1_1/include

instructions.o: ../src/screen/instructions.cpp
	g++ -c -std=c++11 ../src/screen/instructions.cpp -I/usr/local/Cellar/sfml/2.5.1_1/include

gameModeSelection.o: ../src/screen/gameModeSelection.cpp
	g++ -c -std=c++11 ../src/screen/gameModeSelection.cpp -I/usr/local/Cellar/sfml/2.5.1_1/include

difficultySelection.o: ../src/screen/difficultySelection.cpp
	g++ -c -std=c++11 ../src/screen/difficultySelection.cpp -I/usr/local/Cellar/sfml/2.5.1_1/include

fleetPlacement.o: ../src/screen/fleetPlacement.cpp
	g++ -c -std=c++11 ../src/screen/fleetPlacement.cpp -I/usr/local/Cellar/sfml/2.5.1_1/include

intermediary.o: ../src/screen/intermediary.cpp
	g++ -c -std=c++11 ../src/screen/intermediary.cpp -I/usr/local/Cellar/sfml/2.5.1_1/include
	
gameplay.o: ../src/screen/gameplay.cpp
	g++ -c -std=c++11 ../src/screen/gameplay.cpp -I/usr/local/Cellar/sfml/2.5.1_1/include

gameOver.o: ../src/screen/gameOver.cpp
	g++ -c -std=c++11 ../src/screen/gameOver.cpp -I/usr/local/Cellar/sfml/2.5.1_1/include

button.o: ../src/entity/button.cpp
	g++ -c -std=c++11 ../src/entity/button.cpp -I/usr/local/Cellar/sfml/2.5.1_1/include

coordinate.o: ../src/entity/coordinate.cpp
	g++ -c -std=c++11 ../src/entity/coordinate.cpp -I/usr/local/Cellar/sfml/2.5.1_1/include

grid.o: ../src/entity/grid.cpp
	g++ -c -std=c++11 ../src/entity/grid.cpp -I/usr/local/Cellar/sfml/2.5.1_1/include

target.o: ../src/entity/target.cpp
	g++ -c -std=c++11 ../src/entity/target.cpp -I/usr/local/Cellar/sfml/2.5.1_1/include

clean:
	rm *.o main.out