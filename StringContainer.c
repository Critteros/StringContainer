#include <stdio.h>


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
char* strings_get(strings* obj, size_t index); //Returns an element from an array of specific index
char* strings_remove(strings* obj, size_t index); //Removes element of specific index from an array
void strings_clear(strings* obj); //Clears the array




int main(void)
{
	printf("Hello World\n");
}