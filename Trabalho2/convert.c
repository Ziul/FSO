 
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
	unsigned int i=0,j=0;

	/*
	i = old data
	j = new data
	*/
	for (i=0,j=0;i<*size; i++,j++)
	{
		if ( (data[i]== c1[0]) && (data[i+1]== c1[1]) )
		{
			new_data[j]=c2;
			i++;
		}
		else
			new_data[j] = data[i];
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
	unsigned int i=0,j=0;

	for (i=0,j=0;i<*size; i++,j++)
	{
		if ( ((i%NEW_BREAK_LINE)==0) && i>2 )
		{
			new_data[j]='\n';
			j++;
		}
		if (data[i] == '\0')
		{
			new_data[j++] = ' ';
		}
		new_data[j] = data[i];
	}

	*size = i+1;
	data= new_data;
	return new_data;
}


 char* 
 tradicional(char* data, unsigned int *size)
 {

 	replace_char('\n',' ',data,size);
 	data = replace_string("**",'#',data,size);
 	data = reorder_lines(data, size);

 	return data;
 }