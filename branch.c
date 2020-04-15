/*
Assignment 3 _ SIA VM
Made by David Kim
Last Modified: 04/13/2020

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
    // TYPE 3: BRANCHIFNOTEQUAL
    case 3:
        if_not_equal();
        return 0;
    // TYPE 4: BRAMCHIFGREATER
    case 4:
        if_greater();
        return 0;
    // TYPE 5: BRAMCHIFGREATEREQUAL
    case 5:
        if_greater_equal();
        return 0;
    // TYPE 6: CALL
    case 6:
        call_fn();
        return 0;
    // TYPE 7: JUMP
    case 7:
        jump();
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

    //Internal registers
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

//TYPE 2: BRANCHIFEQUAL
void if_equal(){

    //Internal registers
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
        mem_counter += 4;
}

//TYPE 3: BRANCHIFNOTEQUAL
void if_not_equal(){

    //Internal registers
    int *internal_reg[2];

    //Handles internal register issues using seperate function
    get_registers(internal_reg,2);

    //check if not equal
    if(*internal_reg[0]!=(*internal_reg[1])){

        int offset = ((int)current_instruction[2] << 8) + current_instruction[3]; 
        mem_counter += (2*offset);
    }
    //false case
    else
        mem_counter += 2;
}

//TYPE 4: BRANCHIFGREATER
void if_greater(){

    //Internal registers
    int *internal_reg[2];

    //Handles internal register issues using seperate function
    get_registers(internal_reg,2);

    //check if greater
    if(*internal_reg[0]>(*internal_reg[1])){

        int offset = ((int)current_instruction[2] << 8) + current_instruction[3]; 
        mem_counter += (2*offset);
    }
    //false case
    else
        mem_counter += 2;
}

//TYPE 5: BRANCHIFGREATEREQUAL
void if_greater_equal(){

    //Internal registers
    int *internal_reg[2];

    //Handles internal register issues using seperate function
    get_registers(internal_reg,2);

    //check if greater equal
    if(*internal_reg[0]>=(*internal_reg[1])){

        int offset = ((int)current_instruction[2] << 8) + current_instruction[3]; 
        mem_counter += (2*offset);
    }
    //false case
    else
        mem_counter += 2;
}

//TYPE 6: CALL
void call_fn(){

    unsigned int address = 0;

    //Addes up bits of address from current register (NEEDS TO BE FIXED)
    /*for (int i=1; i<sizeof(current_instruction)/sizeof(unsigned char); i++)
        address+=current_instruction[i];
    */

   address+=current_instruction[1]<<16;
   address+=current_instruction[2]<<8;
   address+=current_instruction[3];

    //Values to store
    unsigned char values[4];

    //Divide values by bytes
    handle_val(mem_counter+4,values);

    //Write to memory (PUSH)
    for(int i=0; i<sizeof(values)/sizeof(unsigned char); i++)
        mem_wirte(&sys_memory,values[i],cpu_register[15]+i);

    //Move R15 to next location
    cpu_register[15]-=4;

    //Multiplies 2 to jump specified location
    address*=2;
    
    //Indicates next instruction location address
    mem_counter = address;
}

//TYPE 7: JUMP
void jump(){

    unsigned int address;

    //Addes up bits of address from current register
    for (int i=1; i<sizeof(current_instruction)/sizeof(unsigned char); i++)
        address+=current_instruction[i];

    //Multiplies 2 to jump specified location
    address*=2;

    //Indicates next instruction location address
    mem_counter = address;
}