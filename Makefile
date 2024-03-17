build: compile link
compile:
	g++ -c main.cpp view.cpp -IC:\first_sfml_project\libraries\SFML-2.5.1-mingw-64-bit\SFML-2.5.1\include -DSFML_STATIC

link:
	g++ main.o view.o -o main.exe -LC:\first_sfml_project\libraries\SFML-2.5.1-mingw-64-bit\SFML-2.5.1\lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main


