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

/*Opcode 1: ADD
to avoid "implicit declaration of function 'add' is invalid in C99"
using function name as addr which means add between registers
*/
void addr(){

    //Internal registers
    int *op1, *op2, *target;
    //Register indicators
    int reg_indicator[3];

    //Obtains op1 indicator
    reg_indicator[0] = current_instruction[0] % 16;
    //Obtains op2 indicator
    reg_indicator[1] = current_instruction[1] >> 4;
    //Obtains target indicator
    reg_indicator[2] = current_instruction[1] % 16;

    op1=&cpu_register[reg_indicator[0]];
    op2=&cpu_register[reg_indicator[1]];
    target=&cpu_register[reg_indicator[2]];

    //printf("OP1:\t%d\nOP2:\t%d\nTARGET:\t%d\n",*op1,*op2,*target);
    *target=(*op1)+(*op2);
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