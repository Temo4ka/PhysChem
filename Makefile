all:
	g++ -IC:\SFML-2.5.1\include -LC:\SFML-2.5.1\lib main.cpp ./raycasting/source/rayCast.cpp ./raycasting/source/vect.cpp ./source/graphics.cpp ./source/scene.cpp ./source/vect.cpp ./source/molecule.cpp ./source/piston.cpp ./source/button.cpp -lm -o react.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-main -mwindows

linux:
	g++ main.cpp ./RayCasting/Source/rayCast.cpp ./RayCasting/Source/vect.cpp ./Source/graphics.cpp ./Source/scene.cpp ./Source/vect.cpp ./Source/molecule.cpp ./Source/piston.cpp ./Source/button.cpp -lm -o react -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio