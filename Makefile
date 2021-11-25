all:
	g++ Akin.cpp textLib.cpp Akin_main.cpp Tree/Tree.cpp logsLib.cpp -I include/ -o akin -fsanitize=address,leak,undefined -g