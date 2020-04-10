/*
Assignment 3 _ SIA VM
Made by David Kim
Last Modified: 04/09/2020
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

    //Let's avoid confliction when dealing with instruction
    //So I'm using UCHAR_MAX for initial value instead of 0;
    for(int i=0; i<sizeof(current_instruction)/sizeof(unsigned char); i++)
        current_instruction[i] = UCHAR_MAX;

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
        // OPCODE 0: HALT
        case 0:
            halt = TRUE;
            return 0;
        // OPCODE 1: ADD
        case 1:
            addr();
            mem_counter+=2;
            return 0;
        // OPCODE 2: AND
        case 2:
            andr();
            mem_counter+=2;
            return 0;
        // OPCODE 3: DIVIDE
        case 3:
            divider();
            mem_counter+=2;
            return 0;
        // OPCODE 11: MOVE
        case 11:
            move();
            mem_counter+=2;
            return 0;
        // OPCODE 12: INTERRUPT
        case 12:
            interrupt();
            mem_counter+=2;
            return 0;
        // ERROR
        default:
            return 1;
    }
}