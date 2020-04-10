/*
Assignment 3 _ SIA VM
Made by David Kim
Last Modified: 04/09/2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <libgen.h>

//Personally defined header
//refer to the define.h file for further details
#include "define.h"

//Global Variable goes here
Memory sys_memory;
int cpu_register[NUM_REG];
unsigned char current_instruction[4];
int halt;
int mem_counter;

int main(int argc, char *argv[]){

	//input argument chekcer
	if(argc!=2){
		print_red();
		printf("ERROR: NO INPUT FILE DETECTED\n");
		print_reset();
		printf("siavm filename\n");
		return 1;
	}

	//initializes system resource
	init();
	//prints system rexource in yellow color
	print_vm_resource();
	//loads input file into system memory with error handler
	if(	load(argv[1]) != 0 )
		return 1;

	//sets R15 to default value
	cpu_register[15] = 1020;

	//while loop controller
	halt = FALSE;

	//memory address counter for instruction decoding
	mem_counter=0;

	//fetch->decode -> execute -> store loop until HALT
	do{
		//Error checking purpose
		int result;
		//resets current instruction register every time
		ci_reset();
		//fetch from memory
		fetch(mem_counter);
		//decode, excute, and store handler
		if((result=decode())!=0){
			print_red();
			//invlaid opcode
			if(result==1)
				puts("ERROR: UNSUPPORTED OPCODE TYPE");
			//invalid branch type
			else if(result==2)
				puts("ERROR: UNSUPPORTED BRANCH TYPE");
			print_reset();
			//terminates program with error code
			return 1;
		}

	//continues until HALT(0x0000)
	}while(halt == FALSE);
	
	printf("Done!\n");
	//terminates VM with no error code
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
		/*
		Note that I am initializing each register to smallest value of integer
		in order to avoid error resulted from possible value that each register can hold
		MOVE ops can only assign signed 8 bit value (-127 to 128) 
		*/
		cpu_register[index]=INT_MAX;
	}
	printf("OK!!\n");


}

//Prints system specification
void print_vm_resource(){

	//const int mem_size = sizeof(memory)/sizeof(unsigned char);
	print_yellow();
	printf("SIA Virtual Machine System Specification\n");
	printf("Memory: %lu Bytes\n", sizeof(sys_memory.address)/sizeof(unsigned char));
	printf("Registers: %lu registers & 1 register = %lu bytes \n", sizeof(cpu_register)/sizeof(int), sizeof(int));
	print_reset();

	return;
}

int load(char *file_name){

	printf("Opening input file...\t");

	//Opens the file read-only binary mode
	FILE *input = fopen(file_name,"rb");
	
	//File open error checking and return error if not opened
	if(input == NULL){
		print_red();
		printf("\nERROR: UNABLE TO OPEN INPUT FILE\n");
		print_reset();
		return 1;
	}

	printf("OK!!\n");
	printf("Input file: %s\n", basename(file_name));
	printf("Loading input file to system memory...\t");

	fseek(input, 0, SEEK_SET);

	while(!feof(input)){
		/*
		Raw input data array.
		Note that typecast to unsigned char is required to avoid bitoverflow
		when handling hex values
		*/
		char raw[2];
		//Read data byte by byte
		fread(raw,1,1,input);
		
		//Test printf and typecast to unsigned char for bit overflow
		//printf("Converted: %02X\n", (unsigned char)(raw[0]));
		if(mem_push(&sys_memory,(unsigned char)raw[0])!=0){
			print_red();
			printf("\nERROR: UNABLE TO WRITE DATA ON MEMORY\n");
			print_reset();
			return 1;
		}

		if(feof(input))
			break;
	}

	printf("OK!!\n");

	fclose(input);

	return 0;
}