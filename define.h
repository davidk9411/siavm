//Includes memory structure
#include "memory.h"

//Function indicator goes here

//Functions in main.c
void init();
void print_vm_resource();
int load(char *file_name);

//Functions in run.c
void ci_reset();
void fetch();
int decode();

//Functions in basic.c
void interrupt();
void move();
void addr();
void andr();
void divider();
void multiplyr();
void subtractr();
void orr();
void get_registers(int **reg);

//Functions for memory stack, DO NOT MODIFY!!!
//Note that memory related function is prefixed with mem_
void mem_init(Memory *sys_mem);
int mem_is_empty(Memory *sys_mem);
int mem_push(Memory *sys_mem, unsigned char data);
int mem_pop(Memory *sys_mem);
unsigned char mem_search(Memory *sys_mem, int index);

//Functions for printf colors
void print_red();
void print_yellow();
void print_green();
void print_reset();

//Predefine constant goes here
#define TRUE 1
#define FALSE 0
#define NUM_REG 16

