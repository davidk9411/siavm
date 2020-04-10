/*
Assignment 3 _ SIA VM
Made by David Kim
Last Modified: 04/09/2020

Includes: 3R type instructions and MOVE type instructions 
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

/*Opcode 1: ADD
to avoid "implicit declaration of function 'add' is invalid in C99"
using function name as addr which means add between registers
*/
void addr(){

    /*Internal registers
    0=op1, 1=op2, 2=result(target)
    note this is an array*/
    int *internal_reg[3];
    //Handles internal register issues using seperate function
    get_registers(internal_reg);
    //Performs ADD
    *internal_reg[2]=(*internal_reg[0])+(*internal_reg[1]);
}

//OPCODE 2: AND
void andr(){

    //Internal registers
    int *internal_reg[3];
    //Handles internal register issues using seperate function
    get_registers(internal_reg);
    //Performs AND
    *internal_reg[2]=(*internal_reg[0])&(*internal_reg[1]);
}

//OPCODE 3: DIVIDE
void divider(){

    //Internal registers
    int *internal_reg[3];
    //Handles internal register issues using seperate function
    get_registers(internal_reg);
    //Performs DIVISION
    *internal_reg[2]=(*internal_reg[0])/(*internal_reg[1]);
}

//Opcode 11: Move
void move(){

    //Isolates register number from first byte of instruction
    int reg_indicator = current_instruction[0] % 16;
    /*
    Obtains immediate value,
    note that type of register is unsigned char
    in order to use signed value, typecast to char is required
    */
    int immediate_value = (char)current_instruction[1];
    //Assign immediate value to register
    cpu_register[reg_indicator] = immediate_value;
}

//Opcode 12: Interrupt
//Based on immediate value prints registers or memory
void interrupt(){
    
    //Condition check
    if(current_instruction[1]==0){
        //Prints registers
        print_green();
        for(int i=0; i<sizeof(cpu_register)/sizeof(int); i++){
            printf("R%d:\t%d\n",i,cpu_register[i]);
        }
        print_reset();
    }
    else
        printf("Memory\n");
}

//Internal register handler
void get_registers(int **reg){

    int index[3];

    //Obtains cpu_register number for OP1
    index[0] = current_instruction[0] % 16;
    //Obtains cpu_register number for OP2
    index[1] = current_instruction[1] >> 4;
    //Obtains cpu_register number for result(target)
    index[2] = current_instruction[1] % 16;

    //Assigns proper cpu_registers to internal registers
    reg[0]=&cpu_register[index[0]];
    reg[1]=&cpu_register[index[1]];
    reg[2]=&cpu_register[index[2]];
}