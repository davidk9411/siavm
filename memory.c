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
//Memory load purpose!
int mem_push(Memory *sys_mem, unsigned char data){

	//Checks whether memroy is full or not
	if(sys_mem->point == mem_SIZE-1){
		return 1;
	}

	//Note that pointer increments first and then overwrites data
	sys_mem->address[++sys_mem->point] = data;
	return 0;
}

//Point check
//End of file check purpose
int check_point(Memory *sys_mem){

	return sys_mem->point;
}

unsigned char mem_search(Memory *sys_mem, int index){

	//Check whether memory is empty
	if(mem_is_empty(&sys_memory)==TRUE){
		return 0xff;
	}

	//Return memory value
	return sys_mem->address[index];
}

//WRITE operation
//Performs memory boundary check first
//Returns 0 when successfully pushes
int mem_wirte(Memory *sys_mem, unsigned char data, int index){

	//Checks whether memroy is full or not
	if(sys_mem->point == mem_SIZE-1){
		return 1;
	}

	//Note that pointer increments first and then overwrites data
	sys_mem->address[index] = data;
	return 0;
}