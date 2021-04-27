

defualt:
	clang -c Engine/Darkness.c -o darkness.o
	clang darkness.o *.c -lm -lvulkan -lGL -lglfw -lGLEW -o binary
	
gcc:
	gcc -c Engine/Darkness.c -o darkness.o
	gcc darkness.o *.c -lm -lvulkan -lGL -lglfw -lGLEW -o binary


o3:
	clang -O3 -c Engine/Darkness.c -o darkness_o3.o
	clang -O3 darkness_o3.o *.c -lm -lvulkan -lGL -lglfw -lGLEW -o binary_o3

