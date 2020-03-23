/*
Assignment 3 _ SIA VM
Made by David Kim
Last Modified: 03/23/2020
WARNING: MEMORY STACK STRUCTURE INCLUDED
DO NOT MODIFIY!!!!
*/

//SIZE OF ARRAY = 1024 byte (1 char = 1 byte = 8bits)
#define mem_SIZE 1024

//Memroy structure constructed based on array
typedef struct memory_stack
{

	//Each char is equivalent to memory address 
	unsigned char address[mem_SIZE];
	//ADDRESS indicator
	int point;
}memory_stack;

typedef memory_stack Memory;