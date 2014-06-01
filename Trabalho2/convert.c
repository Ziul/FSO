 
#include <convert.h>
#include <stdlib.h>

char*
replace_char(char c1, char c2, char* data, unsigned int* size)
{
	unsigned int i;

	for (i=0;i<(*size); i++)
 	{
 		if(data[i] == c1)
 			data[i] = c2;
 	}

	return data;
}

char*
replace_string(char* c1, char c2, char* data, unsigned int *size)
{

	unsigned int new_size = (*size)*2;
	char* new_data = (char*) malloc(sizeof(char*)*new_size);
	unsigned int i=0;

	for (i=0;i<*size; i++)
	{
		if ( (data[i]== c1[0]) && (data[i+1]== c1[1]) )
		{
			new_data[i]=c2;
			i++;
		}
		else
			new_data[i] = data[i];
	}

	*size = i+1;
	data= new_data;
	return new_data;
}

char* 
reorder_lines(char* data, unsigned int *size)
{
	unsigned int new_size = (*size)*2;
	char* new_data = (char*) malloc(sizeof(char*)*new_size);
	unsigned int i=0;

	for (i=0;i<*size; i++)
	{
		if ((i%NEW_BREAK_LINE)==0)
		{
			new_data[i]='\n';
			i++;
		}
		new_data[i] = data[i];
	}
	new_data[++i] = ' ';
	new_data[++i] = '\0';

	*size = i+1;
	data= new_data;
	return new_data;
}


 char* 
 tradicional(char* data, unsigned int *size)
 {

 	replace_char('\n',' ',data,size);
 	replace_string("**",'#',data,size);
 	reorder_lines(data, size);

 	return data;
 }