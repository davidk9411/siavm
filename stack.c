/*
Assignment 3 _ SIA VM
Made by David Kim
Last Modified: 04/13/2020

Includes: LOAD, STORE, AND STACK INSTRUCTIONS
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
// OPCODE 8: LOAD OPERATION
void load_memory(){

    /*Internal registers 
    0: register to load
    1: address register*/
    int *internal_reg[2];

    //Values to load
    unsigned char values[4];

    //Assogm porper register to internal register
    get_registers(internal_reg,3);

    //Calculate address to load
    unsigned int address = *internal_reg[1]+2*(current_instruction[1]%16);

    //read from memory
    for(int i=0; i<sizeof(values)/sizeof(unsigned char); i++)
        values[i] = mem_search(&sys_memory,address+i);

    //Write to target register
    *internal_reg[0] = (values[0]<<24) + (values[1]<<16) + (values[2]<<8) + values[3];
}

// OPCODE 9: STORE OPERATION
void store_memory(){

    /*Internal registers 
    0: register to load
    1: address register*/
    int *internal_reg[2];
    //Values to store
    unsigned char values[4];

    //Assign proper register to internal register
    get_registers(internal_reg,3);

    //Calculate address to store
    unsigned int address = *internal_reg[1]+2*(current_instruction[1]%16);

    handle_val(*internal_reg[0], values);

    //Store to memory
    for(int i=0; i<sizeof(values)/sizeof(unsigned char); i++)
        mem_wirte(&sys_memory, values[i],address+i);
}

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
    // TYPE 1: PUSH
    case 1:
        push_R15();
        return 0;
    // TYPE 2: POP
    case 2:
        pop_R15();
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

// TYPE 1: PUSH
void push_R15(){

    //Obtain register's value
    int register_val = cpu_register[current_instruction[0]%16];

    //Values to store
    unsigned char values[4];

    //Divide values by bytes
    handle_val(register_val,values);

    //Write to memory (PUSH)
    for(int i=0; i<sizeof(values)/sizeof(unsigned char); i++)
        mem_wirte(&sys_memory,values[i],cpu_register[15]+i);

    //Move R15 to next location
    cpu_register[15]-=4;

    //Move memory counter for next instruction
    mem_counter+=2;

}

// TYPE 2: POP
void pop_R15(){

    //Link cpu_register to internal register
    int *reg_ptr = &cpu_register[current_instruction[0]%16];

    //Move R15
    cpu_register[15]+=4;

    //Pre processing before pop
    *reg_ptr=0;

    //pop process
    for(int i=0; i<sizeof(*reg_ptr); i++){
        *reg_ptr += mem_search(&sys_memory,cpu_register[15]+i) << (24-(8*i));
        mem_wirte(&sys_memory,0xff, cpu_register[15]+i);
    }

    //Move memory counter for next instruction
    mem_counter+=2;

}

//Value devider
void handle_val(int reg_val, unsigned char *arr){

    arr[0] = reg_val>>24;
    arr[1] = (reg_val>>16)%256;
    arr[2] = (reg_val>>8)%256;
    arr[3] = reg_val%256;
}