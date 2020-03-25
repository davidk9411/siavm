/*
Assignment 3 _ SIA VM
Made by David Kim
Last Modified: 03/23/2020
WARNING: MEMORY STACK FUNCTIONS INCLUDED
DO NOT MODIFIY!!!!
*/

#include <stdio.h>
#include <stdlib.h>

#include "define.h"

extern Memory sys_memory;

//Stack Initialization
void mem_init(Memory *sys_mem){

    //default value for memory is 255(max value) instead of 0
    //since there are lots of 0 in instruction let's avoid confusion
    for(int index=0; index<mem_SIZE; index++){
        sys_mem->address[index] = 0xff;
    }

	//Empties stack for initialization
	//by indicating pointer to -1;
	sys_mem->point = -1;
}


//Checks whether memory is empty or not.
int mem_is_empty(Memory *sys_mem){

	if(sys_mem->point == -1)
		return TRUE;
	else
		return FALSE;
}

//PUSH operation
//Performs memory boundary check first
//Returns 0 when successfully pushes
int mem_push(Memory *sys_mem, unsigned char data){

	//Checks whether memroy is full or not
	if(sys_mem->point == mem_SIZE-1){
		return 1;
	}

	//Note that pointer increments first and then overwrites data
	sys_mem->address[++sys_mem->point] = data;
	return 0;
}

//POP operation
//Returns 0 when successfully pops or 1 if fails
int mem_pop(Memory *sys_mem){

	//Check whether memory is empty
	if(mem_is_empty(&sys_memory)==TRUE){
		return 1;
	}

	//Memory erase
	sys_mem->address[sys_mem->point--] = 0xff;

	return 0; 
}