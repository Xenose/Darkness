

defualt:
	clang -c Engine/Darkness.c -o darkness.o
	clang darkness.o *.c -lvulkan -lglfw -lGLEW -o binary
