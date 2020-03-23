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

//Stack Initialization
void mem_init(Memory *sys_mem){

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