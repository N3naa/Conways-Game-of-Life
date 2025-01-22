#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "cell.h"
#include "cells.c"
#include "user_input.c"
#include "game_logic.c"

#define SPEED 250

int main(int argc, char* argv[])
{
	struct Cell Head = { .x = 0, .y = 0, .next = NULL, .prev = NULL};
	
	InputCoordinates(&Head,argv[1]);
	InitilizeGrid(&Head);
   	usleep(SPEED*1000);
 	system("clear");

	while(PrintGrid(&Head))
	{
		
		usleep(SPEED*1000);
		NextGeneration(&Head);
		system("clear");

	}

	return 0;
}
