#include <stdio.h>
#pragma warning (disable: 4996 6001 6387 6308 28182)

#include <string.h>
#include <stdlib.h>
/////////////////////////////////////////////////////////////////////////////////////////////
//StringContainer is a dynamic array list for C strings									   //
//Written by Szymon Kozio³ (Critteros) for C labs exercises								   //
//More info https://github.com/Critteros/StringContainer								   //
//Version 1.0 modified: 03.01.2021 16:30												   //
//Requires headers: (string.h, stdlib.h, stdio.h)										   //
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
void DeleteContainer(strings* obj); //Deletes struct ALWAYS use to prevent memory leaks
void strings_put(strings* obj, char* string); //Puts a C string to an array
char* strings_get(strings* obj, size_t index); //Returns an element from an array of specific index
void strings_remove(strings* obj, size_t index); //Removes element of specific index from an array
void strings_printAll(strings* obj); //Prints all array strings to stdout
void strings_clear(strings* obj); //Clears the array
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
strings NewConatiner(void)
{
	strings context;
	const size_t initialCapacity = 1;

	context.capacity = initialCapacity;
	context.m_Data = (char**)malloc(initialCapacity * sizeof(char*));
	for (int i = 0; i < (int)initialCapacity; i++)
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
		for (size_t i = obj->size; i < obj->capacity; i++)
		{
			obj->m_Data[i] = NULL;
		}
	}

	size_t putIndex = obj->size;
	size_t neededSize = strlen(string) + 1;
	char* space = (char*)malloc(neededSize * sizeof(char));
	strcpy(space, string);
	obj->m_Data[putIndex] = space;
	obj->size++;

}

char* strings_get(strings* obj, size_t index)
{
	if (!obj->m_Data[index])
	{
		printf("ERROR: Null pointer exception");
		exit(-100);
	}
	else
	{
		return (obj->m_Data[index]);
	}
}

void strings_remove(strings* obj, size_t index)
{
	if (index >= obj->capacity)
	{
		printf("ERROR: Null pointer exception");
		exit(-200);
	}
	
	size_t newCapacity = obj->capacity - 1;
	char** newData = (char**)malloc(newCapacity * sizeof(char*));
	char** oldData = obj->m_Data;
	size_t oldCapacity = obj->capacity;
	

	size_t j = 0;
	for (size_t i = 0; i < oldCapacity; i++)
	{
		if (i == index)
		{
			continue;
		}
		else
		{
			newData[j] = oldData[i];
			j++;
		}
	}
	obj->m_Data = newData;
	obj->capacity = newCapacity;
	obj->size--;

	//Cleanup
	free(oldData[index]);
	free(oldData);



}

void strings_printAll(strings* obj)
{
	if (obj->size == 0)
	{
		printf("Nothing to print\n");
	}
	else
	{
		printf("[");
		for (size_t i = 0; i < (obj->size - 1); i++)
		{
			printf("%s, ", strings_get(obj, i));
		}
		printf("%s]\n", strings_get(obj, (obj->size - 1)));
	}
	
}

void strings_clear(strings* obj)
{
	size_t cap = obj->capacity;

	for (size_t i = 0; i < cap; i++)
	{
		if (obj->m_Data[i])
		{
			free(obj->m_Data[i]);
		}
		obj->m_Data[i] = NULL;
	}
	obj->size = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////


//For testing only
int main(void)
{
	strings test = NewConatiner();
	
	static char buffer[200];

	const int max = 30;

	for (int i = 0; i <= max; i++)
	{
		sprintf(buffer, "Example string:[%d]", i);
		strings_put(&test, buffer);
	}
	strings_remove(&test, 10);
	strings_remove(&test, 9);

	strings_printAll(&test);
	//system("pause");
	DeleteContainer(&test);
	//system("pause");
	return 0;
}