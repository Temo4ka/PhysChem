all:
	g++ main.cpp ./RayCasting/Source/rayCast.cpp ./RayCasting/Source/vect.cpp ./Source/graphics.cpp ./Source/scene.cpp ./Source/vect.cpp ./Source/molecule.cpp ./Source/piston.cpp ./Source/button.cpp -lm -o react -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
