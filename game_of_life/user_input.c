
#define FILE_LINE 1024

int InputCoordinates(Position head_cell, char* file_name)
{
	char buffer[FILE_LINE];

	memset(buffer,'\0',FILE_LINE);

	FILE* fp = fopen(file_name, "r");

	if(fp == NULL)
	{
		perror("Could not open the file!");
           	exit(-1);
	}

	int x;
	int y;
	int check = 0;

	while(!feof(fp))
	{
		fgets(buffer,FILE_LINE, fp);
		sscanf(buffer,"%d,%d %n", &x, &y, &check);

		if(check < 4 && check > 6)
		{
			puts("Invalid coordinates!");
			return EXIT_FAILURE;
		}

		LexicalOrder(head_cell,x,y);
	}

	fclose(fp);


	return EXIT_SUCCESS;
}
