

defualt:
	clang -std=gnu11 -c Engine/Darkness.c -o darkness.o
	clang -std=gnu11 darkness.o *.c -lm -lvulkan -lGL -lglfw -lGLEW -o Game/binary
	
gcc:
	gcc -std=gnu11 -c Engine/Darkness.c -o darkness.o
	gcc -std=gnu11 darkness.o *.c -lm -lvulkan -lGL -lglfw -lGLEW -o Game/binary


o3:
	clang -std=gnu11 -O3 -c Engine/Darkness.c -o darkness_o3.o
	clang -std=gnu11 -O3 darkness_o3.o *.c -lm -lvulkan -lGL -lglfw -lGLEW -o Game/binary_o3o3:
ofast:
	clang -std=gnu11 -Ofast -c Engine/Darkness.c -o darkness_ofast.o
	clang -std=gnu11 -Ofast	darkness_ofast.o *.c -lm -lvulkan -lGL -lglfw -lGLEW -o Game/binary_ofast


