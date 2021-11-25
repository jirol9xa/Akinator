all:
	g++ Akin.cpp textLib.cpp Akin_main.cpp Tree.cpp logsLib.cpp -o -I/include akin -fsanitize=address,leak,undefined -g