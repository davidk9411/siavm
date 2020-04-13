/*
Assignment 3 _ SIA VM
Made by David Kim
Last Modified: 04/10/2020
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
    //decides whther instruction is 4 byte or 2 byte
    if(current_instruction[0] >> 4 == 7){
        current_instruction[2] = mem_search(&sys_memory,mem_counter+2);
        current_instruction[3] = mem_search(&sys_memory,mem_counter+3);
    }
}

/*excutes proper functions based on OPCODE
returns following:
0 - success
1 - unsupported opcode
2 - unsupported branch type*/
int decode(){

    //extracts opcode from current instruction
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
        // OPCODE 4: MULTIPLY
        case 4:
            multiplyr();
            mem_counter+=2;
            return 0;
        // OPCODE 5: SUBTRACT
        case 5:
            subtractr();
            mem_counter+=2;
            return 0;
        // OPCODE 6: OR
        case 6:
            orr();
            mem_counter+=2;
            return 0;
        // OPCODE 7: BRANCH
        case 7:
            //decode branch by type
            if(decode_branch()!=0)
                return 2;

            /*Since memory moving depends on result of branchif
            memory counter will handled on execution of each function*/
            return 0;
        // OPCODE 8: LOAD
        case 8:
            load_memory();
            mem_counter+=2;
            return 0;
        // OPCODE 9: STORE
        case 9:
            store_memory();
            mem_counter+=2;
            return 0;
        // OPCODE 10(A): STACK instruction
        case 10:
            if(decode_stack()!=0)
                return 3;

            //Due to the return operation memory counter will handled on excution of function*/
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


/*Internal register handler
handler-type:
type 1: 3R instructions
type 2: branch instructions
type 3: load/store instructions
*/
void get_registers(int **reg, int handler_type){

    //Handler for 3R instructions
    if(handler_type==1){
        int index[3];

        //Obtains cpu_register number for OP1
        index[0] = current_instruction[0] % 16;
        //Obtains cpu_register number for OP2
        index[1] = current_instruction[1] >> 4;
        //Obtains cpu_register number for result(target)
        index[2] = current_instruction[1] % 16;

        //Assigns proper cpu_registers to internal registers
        reg[0] = &cpu_register[index[0]];
        reg[1] = &cpu_register[index[1]];
        reg[2] = &cpu_register[index[2]];
    }

    //Handler for branch instructions
    else if(handler_type==2){
        int index[2];

        //Obtains cpu_register number for OP1
        index[0] = current_instruction[1] >> 4;
        //Obtains cpu_register number for OP2
        index[1] = current_instruction[1] % 16;

        //Assigns poper cpu_registers to internal registers
        reg[0] = &cpu_register[index[0]];
        reg[1] = &cpu_register[index[1]];
    }

    //Handler for ls instructions
    else if(handler_type==3){
        int index[2];

        //Obtains cpu_register for ls
        index[0] = current_instruction[0] % 16;
        //Obtains cpu_register for address register
        index[1] = current_instruction[1] >> 4;

        //Assigns proper cpu_register to internal registers
        reg[0] = &cpu_register[index[0]];
        reg[1] = &cpu_register[index[1]];
    }
}