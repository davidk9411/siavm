/*
Assignment 3 _ SIA VM
Made by David Kim
Last Modified: 04/01/2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

//Personally defined header
//refer to the define.h file for further details
#include "define.h"

//Global Variable goes here
extern Memory sys_memory;
extern int cpu_register[NUM_REG];
extern unsigned char current_instruction[4];
extern int halt;
extern int mem_counter;

//resets all elements of current instruction register to xff
void ci_reset(){

    for(int i=0; i<sizeof(current_instruction)/sizeof(unsigned char); i++)
        current_instruction[i] = INT_MAX;

}

//fetches instruction from memory to current instruction
void fetch(){

    current_instruction[0] = mem_search(&sys_memory,mem_counter);
    current_instruction[1] = mem_search(&sys_memory,mem_counter+1);
}

int decode(){

    int opcode = current_instruction[0] >> 4;
    switch (opcode)
    {
    case 0:
        halt = TRUE;
        return 0;
    case 12:
        printf("Interrupt!\n");
        mem_counter+=2;
        return 0;
    default:
        return 1;
        break;
    }
}