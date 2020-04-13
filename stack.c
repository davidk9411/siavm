/*
Assignment 3 _ SIA VM
Made by David Kim
Last Modified: 04/13/2020

Includes: STACK INSTRUCTIONS
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

// OPCODE 10: STACK DECODER
int decode_stack(){

    //Get type of stack operation from current instruction register
    int ops = (int)current_instruction[1]>>6;

    switch (ops)
    {
    // TYPE 0: RETURN
    case 0:
        return_R15();
        return 0;
    // ERROR: UNSUPPORTED OPERATION
    default:
        return 1;
    }

}

// Type 0: RETURN
void return_R15(){

    //Get next instruction location from R15
    mem_counter = cpu_register[15];

    //Stack check
    int index=1020;

    //Check whether stack is occupied
    while(mem_search(&sys_memory,index+3)!=0xff){
        index-=4;
    }

    //Overwrites R15 with top of the stack
    cpu_register[15] = index;
}