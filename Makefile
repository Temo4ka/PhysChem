all:
	g++ -IC:\SFML-2.5.1\include -LC:\SFML-2.5.1\lib main.cpp ./raycasting/source/rayCast.cpp ./raycasting/source/vect.cpp ./source/graphics.cpp ./source/scene.cpp ./source/vect.cpp ./source/molecule.cpp ./source/button.cpp ./source/physics.cpp -lm -o react.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-main -mwindows

mac:
	clang++ -std=c++23 -I/opt/homebrew/Cellar/sfml/2.6.1/include -L/opt/homebrew/Cellar/sfml/2.6.1/lib main.cpp ./RayCasting/Source/rayCast.cpp ./RayCasting/Source/vect.cpp ./Source/graphics.cpp ./Source/scene.cpp ./Source/vect.cpp ./Source/molecule.cpp ./Source/button.cpp ./Source/Physics.cpp -lm -o react -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

linux:
	g++ main.cpp ./RayCasting/Source/rayCast.cpp ./RayCasting/Source/vect.cpp ./Source/graphics.cpp ./Source/scene.cpp ./Source/vect.cpp ./Source/molecule.cpp ./Source/button.cpp ./Source/Physics.cpp -lm -o react -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

linux_debug:
	g++ main.cpp ./RayCasting/Source/rayCast.cpp ./RayCasting/Source/vect.cpp ./Source/graphics.cpp ./Source/scene.cpp ./Source/vect.cpp ./Source/molecule.cpp ./Source/button.cpp ./Source/Physics.cpp -lm -o react -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -D _DEBUG -ggdb3 -Wall -O0 -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -fno-omit-frame-pointer -pie -Wstack-usage=8192 -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
