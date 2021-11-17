#ifndef _INSTRUCTION_ASSEMBLY_H_
#define _INSTRUCTION_ASSEMBLY_H_

	#include "instruction_execution.h"
	#include "mips_controller.h"

	#define INSTRUCTION_MAX_LENGTH 30

	/*
	REGION :   HEXA -> INSTRUCTION
	*/
	int Get_Hexa_From_File();


	/*
	REGION :   STRING -> HEXA
	*/
	void Get_Operands(char *s ,int *operands ,int start);
	int Instruction_To_Hexa(char *instruction);
	int Is_in_Hexa(char *s,int size);
	void Upper_Case_String(char *s);
	int Get_Front_Space(char *s);
	int Is_Operand(int start, char *s1, char * s2);
	int Instruction_Is_Finish( char *s, int start);
	int Get_Register(char *s,int start, int end);
	int String_To_Int(char *s, int start, int end, int base);
	int Is_in_String(char *s, char a);

	void String_To_Hexa(char *fileName, char *output);


#endif
