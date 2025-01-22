#include <stdlib.h>
#include <errno.h>
#include "cell.h"

Position CreateCell(int x, int y)
{
	Position new_cell = (Position )malloc(sizeof(struct Cell));

	if(new_cell == NULL)
	{
		perror("Could not allocate!");
		return NULL;
	}

	new_cell->x = x;
	new_cell->y = y;


	return new_cell;
}

int InsertCell(Position cell, int x, int y)
{
	Position new_cell = CreateCell(x, y);

	if(new_cell == NULL)
	{
		return EXIT_FAILURE;
	}

	new_cell->next = cell->next;
	cell->next = new_cell;
	new_cell->prev = cell;
	if(new_cell->next != NULL) new_cell->next->prev = new_cell;


	return EXIT_SUCCESS;
}

int LexicalOrder(Position cell, int x, int y)
{
	if(cell->next == NULL || (cell->next != NULL && cell->next->x > x))
	{
		InsertCell(cell,x,y);
		return EXIT_SUCCESS;
	}


	else
	{
		while(cell->next != NULL && cell->next->x < x)
		{
			cell = cell->next;
		}

		if((cell->next != NULL && cell->next->x > x) || cell->next == NULL)
		{
			InsertCell(cell,x,y);
			return EXIT_SUCCESS;
		}

		else
		{
			if(cell->next->y > y)
			{
				InsertCell(cell,x,y);
				return EXIT_SUCCESS;
			}

			else
			{
				while(cell->next != NULL && cell->next->y < y && cell->next->x == x)
				{
					cell = cell->next;
				}

				if(cell->next == NULL || (cell->next != NULL && (cell->next->y != y || cell->next->x != x)))
				{
					InsertCell(cell,x,y);
				}

			}	
		}
	}


	return EXIT_SUCCESS;
}
