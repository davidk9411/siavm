/*
Assignment 3 _ SIA VM
Made by David Kim
Last Modified: 03/23/2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Personally defined header
//refer to the define.h file for further details
#include "define.h"

//Global Variable goes here
Memory sys_memory;
int cpu_register[NUM_REG];

int main(int argc, char *argv[]){

	init();
	print_vm_resource();

	return 0;
}

//Initializes system resource
void init(){

	printf("Initializing SIA Virtual Machine\n");
	printf("%s\t", "Initializing System Memory..." );
	//Checks initial memory condition
	while(mem_is_empty(&sys_memory)==FALSE){

		//Initializes memory
		mem_init(&sys_memory);
	}
	printf("OK!!\n");

	printf("%s\t", "Initializing System Registers..." );
	for(int index=0; index<NUM_REG; index++){
		cpu_register[index]=0;
		/*
		TO-DO: ASSIGN EITHER LARGEST NUMBER OR SMALLEST NUMBER INT TYPE CAN HAVE
		SINCE MEMORY SIZE IS 1024 AND MOVE INSTRUCTION CAN ONLY HOLD
		SIGNED 8 BIT VALUE	
		*/
	}
	printf("OK!!\n");


}

//Prints system specification
void print_vm_resource(){

	//const int mem_size = sizeof(memory)/sizeof(unsigned char);

	printf("Virtual Machine System Specification\n");
	printf("Memory: %lu Bytes\n", sizeof(sys_memory.address)/sizeof(unsigned char));
	printf("Registers: %lu registers & 1 register = %lu bytes \n", sizeof(cpu_register)/sizeof(int), sizeof(int));

	return;
}