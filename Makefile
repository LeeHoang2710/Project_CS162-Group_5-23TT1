build: compile link
compile:
	g++ -c main.cpp view_support.cpp page.cpp content/function_login.cpp content/function_student.cpp content/function_semester.cpp  content/function_year.cpp -I.\libraries\SFML-2.5.1-mingw-64-bit\SFML-2.5.1\include -DSFML_STATIC

link:
	g++ Other/main.o Other/view_support.o Other/page.o Other/function_login.o Other/function_student.o Other/function_year.o Other/function_semester.o -o main.exe -L.\libraries\SFML-2.5.1-mingw-64-bit\SFML-2.5.1\lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main