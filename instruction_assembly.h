#ifndef _INSTRUCTION_ASSEMBLY_H_
#define _INSTRUCTION_ASSEMBLY_H_

	#include "instruction_execution.h"
	#include "mips_controller.h"

	int string_to_hexa(char *instruction);
	int block_offset(int value, int index);
	int compare_string(char *string1, char * string2);
	void get_operands(char *instruction,int *operands, int index);
	int end_of_instruction(char *string, int index);
	int register_to_int(char *string, int size);
	int string_to_decimal(char *string, int start, int end);
#endif
