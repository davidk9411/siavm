/*
Assignment 3 _ SIA VM
Made by David Kim
Last Modified: 04/10/2020

Includes: BRANCH INSTRUCTIONS
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

//OPCODE 7: BRANCH
//Note this is for decode process purpose
int decode_branch(){

    int type = current_instruction[0] % 16;
    switch (type)
    {
    // TYPE 0: BRANCHIFLESS
    case 0:
        if_less();
        return 0;
    // TYPE 1: BRANCHIFLESSEQUAL
    case 1:
        if_less_equal();
        return 0;
    // TYPE 2: BRANCHIFEQUAL
    case 2:
        if_equal();
        return 0;
    //Unsupported branch type
    default:
        return 1;
    }
}

//TYPE 0: BRANCHIFLESS
void if_less(){

    /*Internal registers
    0=op1, 1=op2
    note this is an array*/
    int *internal_reg[2];

    //Handles internal register issues using seperate function
    get_registers(internal_reg,2);

    //check if less
    if(*internal_reg[0]<*internal_reg[1]){

        int offset = ((int)current_instruction[2] << 8) + current_instruction[3]; 
        mem_counter += (2*offset);
    }
    //false case
    else
        mem_counter += 2;
}

//TYPE 1: BRANCHIFLESSEQUAL
void if_less_equal(){

    /*Internal registers
    0=op1, 1=op2
    note this is an array*/
    int *internal_reg[2];

    //Handles internal register issues using seperate function
    get_registers(internal_reg,2);

    //check if less equal
    if(*internal_reg[0]<=(*internal_reg[1])){

        int offset = ((int)current_instruction[2] << 8) + current_instruction[3]; 
        mem_counter += (2*offset);
    }
    //false case
    else
        mem_counter += 2;
}

//TYPE 2: BRANCHIFLESSEQUAL
void if_equal(){

    /*Internal registers
    0=op1, 1=op2
    note this is an array*/
    int *internal_reg[2];

    //Handles internal register issues using seperate function
    get_registers(internal_reg,2);

    //check if equal
    if(*internal_reg[0]==(*internal_reg[1])){

        int offset = ((int)current_instruction[2] << 8) + current_instruction[3]; 
        mem_counter += (2*offset);
    }
    //false case
    else
        mem_counter += 2;
}