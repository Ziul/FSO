#include <convert.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 80

int main(int argc, char const *argv[])
{
	char * coluna;
	FILE * dumb;

	dumb = fopen("dumb_file", "r");

	coluna = (char *)calloc(SIZE, sizeof(char));
	if (coluna == NULL)
	{
		printf("Tiranossauro aleijado! ABORTAR!\n");
		return 0;
	}

	for (int i = 0; i < SIZE; ++i)
	{
		fscanf(dumb, "%c", &coluna[i]);
	}

	tradicional(coluna, SIZE);

	return 0;
}
