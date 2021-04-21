

defualt:
	-clear
	clang -c Engine/Darkness.c -o darkness.o
	clang darkness.o *.c -lvulkan -lGL -lglfw -lGLEW -o binary
