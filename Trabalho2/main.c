#include <convert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	char * coluna;
	FILE * dumb;
	unsigned int SIZE, i;

	dumb = fopen("dumb_file", "r");

	fseek(dumb, 0, SEEK_END);
	SIZE = ftell(dumb)+1;
	fseek(dumb, 0, SEEK_SET);

	coluna = (char *)calloc(SIZE, sizeof(char));
	if (coluna == NULL)
	{
		printf("Tiranossauro aleijado! ABORTAR!\n");
		return 0;
	}

	for (i = 0; i < SIZE; ++i)
	{
		coluna[i] = fgetc(dumb);
	}

	printf("%s.[%d]\n",coluna,SIZE);

	coluna = tradicional(coluna, &SIZE);

	printf("%s.[%d]\n",coluna,SIZE);

	free(dumb);
	free(coluna);

	return 0;
}
