#ifndef _INSTRUCTION_ASSEMBLY_H_
#define _INSTRUCTION_ASSEMBLY_H_

	#include "instruction_execution.h"
	#include "mips_controller.h"



	/*
	REGION :   HEXA -> INSTRUCTION
	*/



	/*
	REGION :   STRING -> HEXA
	*/
	void Get_Operands(char *s ,int *operands ,int start);
	int String_To_Hexa(char *instruction);
	int Is_Operand(char *s1, char * s2);
	int Instruction_Is_Finish( char *s, int start);
	int Get_Register(char *s, int size);
	int String_To_Int(char *s, int start, int end);

#endif
