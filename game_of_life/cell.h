
//#pragma once

#ifndef CELL_H
#define CELL_H


/*typedef enum
{
       	DEAD,
       	ALIVE
} State;*/

struct Cell;
typedef struct Cell* Position;

struct Cell
{
	//State state;
	int x;
	int y;
	Position next;
	Position prev;	
};

int InputCoordinates(Position head_cell, char* file_name);

Position CreateCell(int x, int y);

int InsertCell(Position cell, int x, int y);

int LexicalOrder(Position cell, int x, int y);

bool IsCellAlive(Position cell, int x, int y);

int InitilizeGrid(Position cell);

int PrintGrid(Position cell);

int NextGeneration(Position cell);

int CountLiveNeighbors(Position cell, int x, int y);

int DeleteCells(Position cell);

#endif
