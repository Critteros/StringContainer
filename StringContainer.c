#include <stdio.h>
#pragma warning (disable: 4996 6001 6387 )

#include <string.h>
#include <stdlib.h>
/////////////////////////////////////////////////////////////////////////////////////////////
//StringContainer is a dynamic array list for C strings									   //
//Written by Szymon Kozio³ (Critteros) for C labs exercises								   //
//More info https://github.com/Critteros/StringContainer								   //
/////////////////////////////////////////////////////////////////////////////////////////////
struct StringContainer
{
//Public space
	size_t size; //Size of the array READONLY
	size_t capacity; //Current capacity of the array READONLY

//For internal use only 
	char** m_Data;
};
typedef struct StringContainer strings;
//Functions
strings NewConatiner(void); //Return new initialized struct for use 
void DeleteContainer(strings* obj); //Deletes struct
void strings_put(strings* obj, char* string); //Puts a C string to an array
//char* strings_get(strings* obj, size_t index); //Returns an element from an array of specific index
//char* strings_remove(strings* obj, size_t index); //Removes element of specific index from an array
//void strings_clear(strings* obj); //Clears the array
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
strings NewConatiner(void)
{
	strings context;
	const size_t initialCapacity = 1;

	context.capacity = initialCapacity;
	context.m_Data = (char**)malloc(initialCapacity * sizeof(char*));
	for (int i = 0; i < initialCapacity; i++)
	{
		context.m_Data[i] = NULL;
	}
	context.size = 0;

	return context;
}

void DeleteContainer(strings* obj)
{
	for (size_t i = 0; i < obj->capacity; i++)
	{
		if (obj->m_Data[i])
		{
			free(obj->m_Data[i]);
		}
	}
	free(obj->m_Data);
}

void strings_put(strings* obj, char* string)
{
	if (obj->capacity == obj->size)
	{
		//Time to resize
		size_t newSize = obj->capacity * 2;
		obj->m_Data = (char**)realloc(obj->m_Data, newSize * sizeof(char*));
		obj->capacity = newSize;
	}

	size_t putIndex = obj->size;
	size_t neededSize = strlen(string) + 1;
	char* space = (char*)malloc(neededSize * sizeof(char));
	strcpy(space, string);
	obj->m_Data[putIndex] = space;
	obj->size++;

}

/////////////////////////////////////////////////////////////////////////////////////////////


//For testing only
int main(void)
{
	strings test = NewConatiner();
	strings_put(&test, "Aba");
	strings_put(&test, "skakdkasmdkasdm");
	strings_put(&test, "skasadasdasdas");
	strings_put(&test, "skakdkasdasdasdkasdm");


	
	printf("%s\n", test.m_Data[0]);
	printf("%s\n", test.m_Data[1]);

	DeleteContainer(&test);
	return 0;
}