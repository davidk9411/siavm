/*
Assignment 3 _ SIA VM
Made by David Kim
Last Modified: 04/13/2020
*/

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
void get_registers(int **reg, int handler_type);

//Functions in basic.c
void interrupt();
void move();
void addr();
void andr();
void divider();
void multiplyr();
void subtractr();
void orr();

//Functions in branch.c
int decode_branch();
void if_less();
void if_less_equal();
void if_equal();
void if_not_equal();
void if_greater();
void if_greater_equal();
void call_fn();
void jump();

//Functions in stack.c
void load_memory();
void store_memory();
int decode_stack();
void return_R15();
void push_R15();
void pop_R15();
void handle_val(int reg_val, unsigned char *arr);

//Functions for memory stack, DO NOT MODIFY!!!
//Note that memory related function is prefixed with mem_
void mem_init(Memory *sys_mem);
int mem_is_empty(Memory *sys_mem);
int mem_push(Memory *sys_mem, unsigned char data);
int check_point(Memory *sys_mem);
unsigned char mem_search(Memory *sys_mem, int index);
int mem_wirte(Memory *sys_mem, unsigned char data, int index);

//Functions for printf colors
void print_red();
void print_yellow();
void print_green();
void print_blue();
void print_reset();

//Predefine constant goes here
#define TRUE 1
#define FALSE 0
#define NUM_REG 16
#define DEFAULT_VAL 2147483647

