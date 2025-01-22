#include <stdlib.h>
#include <stdbool.h>
#include "cell.h"
#define HEIGHT 50
#define WIDHT 30
#define CELL '0'
#define BACKROUND '.'

static int generation = 0;

bool IsCellAlive(Position cell, int x, int y)
{
	while(cell->next != NULL)
	{
		if(cell->next->x == x && cell->next->y == y)
		{
			return true;
		}

		cell = cell->next;
	}


	return false;
}

int CountLiveNeighbors(Position cell, int x, int y)
{
	int live_neighbor_cells = 0;


	for(int dy = -1; dy <= 1; dy++)
	{
		for(int dx = -1; dx <= 1; dx++)
		{
			if(dx == 0 && dy == 0)
			{
				continue;
			}

			if(IsCellAlive(cell,(x + dx + WIDHT) % WIDHT, (y + dy + HEIGHT) % HEIGHT))
			{
				live_neighbor_cells++;
			}
		}
	}


	return live_neighbor_cells;
}

int InitilizeGrid(Position cell)
{
	
	for(int y = 0; y < HEIGHT; y++)
	{
		for(int x = 0; x < WIDHT; x++)
		{
			if(IsCellAlive(cell, x, y))
			{
				printf(" %c ", CELL);
			}

			else
			{
				printf(" %c ", BACKROUND);
			}
			
		}

		printf("\n");
	}


	return EXIT_SUCCESS;
}

int PrintGrid(Position cell)
{
	int live_cells = 0;

	for(int y = 0; y < HEIGHT; y++)
	{
		for(int x = 0; x < WIDHT; x++)
		{
			if(IsCellAlive(cell, x, y))
			{
				printf(" %c ", CELL);
				live_cells++;
			}

			else
			{
				printf(" %c ", BACKROUND);
			}
		}

		printf("\n");
	}

	printf("\n\n");
	printf("_____________________________________________________________________________________________\n");
	printf("Population: %d\n", live_cells);
	printf("Generation: %d\n", generation);
	printf("_____________________________________________________________________________________________\n");


	return live_cells;
}

int NextGeneration(Position cell)
{
	
	Position new_cells = (Position )malloc(sizeof(struct Cell));
	Position temp_cell = (Position )malloc(sizeof(struct Cell));

    
	 if(new_cells == NULL || temp_cell == NULL)
   	 {
       		 puts("The next generation cannot be generated!");
       		 exit(-1);
   	 }
    
   	 new_cells->next = NULL;
   	 new_cells->prev = NULL;
	 new_cells->x = 0;
	 new_cells->y = 0;

	temp_cell->next = NULL;
	temp_cell->prev = NULL;
	temp_cell->x = 0;
	temp_cell->y = 0;
    
	Position current = cell->next;

	while(current != NULL)
	{
		int live_neighbor_cells = CountLiveNeighbors(cell,(current->x + WIDHT) % WIDHT, (current->y + HEIGHT) % HEIGHT);

		if((live_neighbor_cells == 2 || live_neighbor_cells == 3))
		{
			LexicalOrder(new_cells,(current->x + WIDHT) % WIDHT, (current->y + HEIGHT) % HEIGHT);
		}

		for(int dy = -1; dy <= 1; dy++)
		{
			for(int dx = -1; dx <= 1; dx++)
			{
				if(dx == 0 && dy == 0)
				{
					continue;
				}

				if(!IsCellAlive(cell, (current->x + dx + WIDHT) % WIDHT, (current->y + dy + HEIGHT) % HEIGHT) && CountLiveNeighbors(cell, (current->x + dx + WIDHT) % WIDHT, (current->y + dy + HEIGHT) % HEIGHT) == 3)
				{
					LexicalOrder(temp_cell, (current->x + dx + WIDHT) % WIDHT, (current->y + dy + HEIGHT) % HEIGHT);
				}
			}
		}

		current = current->next;
	}

	Position temp;
	
	while(temp_cell->next != NULL)
	{
		LexicalOrder(new_cells, temp_cell->next->x, temp_cell->next->y);
		temp = temp_cell->next;
		temp_cell->next = temp_cell->next->next;
		free(temp);
	}

	DeleteCells(cell);
	cell->next = new_cells->next;
	if(cell->next != NULL) cell->next->prev = cell;
	free(new_cells);
	free(temp_cell);

	generation++;


	return EXIT_SUCCESS;
}

int DeleteCells(Position cell)
{
	Position temp;

	while(cell->next != NULL)
	{
		temp = cell->next;
		cell->next = cell->next->next;
		if(cell->next != NULL) cell->next->prev = cell;
		free(temp);
	}


	return EXIT_SUCCESS;
}
