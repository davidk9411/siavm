/*
Assignment 3 _ SIA VM
Made by David Kim
Last Modified: 04/10/2020

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
    get_registers(internal_reg,1);
    //Performs ADDITION
    *internal_reg[2]=(*internal_reg[0])+(*internal_reg[1]);
}

//OPCODE 2: AND
void andr(){

    //Internal registers
    int *internal_reg[3];
    //Handles internal register issues using seperate function
    get_registers(internal_reg,1);
    //Performs BITWISE AND
    *internal_reg[2]=(*internal_reg[0])&(*internal_reg[1]);
}

//OPCODE 3: DIVIDE
void divider(){

    //Internal registers
    int *internal_reg[3];
    //Handles internal register issues using seperate function
    get_registers(internal_reg,1);
    //Performs DIVISION
    *internal_reg[2]=(*internal_reg[0])/(*internal_reg[1]);
}

//OPCODE 4: MULTIPLY
void multiplyr(){

    //Internal registers
    int *internal_reg[3];
    //Handles internal register issues using seperate function
    get_registers(internal_reg,1);
    //Performs MULTIPLICATION
    *internal_reg[2]=(*internal_reg[0])*(*internal_reg[1]);
}

//OPCODE 5: SUBTRACT
void subtractr(){
        
    //Internal registers
    int *internal_reg[3];
    //Handles internal register issues using seperate function
    get_registers(internal_reg,1);
    //Performs SUBTRACTION
    *internal_reg[2]=(*internal_reg[0])-(*internal_reg[1]);
}

//OPCODE 6: OR
void orr(){

    //Internal registers
    int *internal_reg[3];
    //Handles internal register issues using seperate function
    get_registers(internal_reg,1);
    //Performs BITWISE OR
    *internal_reg[2]=(*internal_reg[0])|(*internal_reg[1]);
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
        puts("REGISTER INFORMATION: DECIMAL(HEX)");
        for(int i=0; i<sizeof(cpu_register)/sizeof(int); i++){
            cpu_register[i] == DEFAULT_VAL ? printf("R%d:\t%s\n",i,"NULL") : printf("R%d:\t%010d(%04X)\n",i,cpu_register[i],cpu_register[i]);
        }
        print_reset();
    }
    else{
        print_blue();
        puts("MEMORY INFORMATION: DECIMAL(HEX)");
        for(int i=0; i<mem_SIZE; i++){
            unsigned char mem_val = mem_search(&sys_memory,i);
            mem_val == 0xff ? printf("M%d:\t%s\n",i,"NULL") : printf("M%d:\t%03d(%02X)\n",i,mem_val,mem_val);
        }
    }
}

