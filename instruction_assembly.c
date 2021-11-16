#include "instruction_assembly.h"
#include <stdio.h>
#include <stdlib.h>










/*

REGION :   HEXA -> INSTRUCTION

*/



/*

REGION :   STRING -> HEXA

*/


/*
Summary : Get the Hexa representation of this instruction
*/
int String_to_Hexa(char *instruction){
	int hexa = 0;
	int *operands = malloc(3*sizeof(int));

	if ( Is_Operand(instruction , "ADD")) {

		Get_Operands(instruction, operands, 3);
		hexa += 32;
		hexa += operands[0] << 11;
		hexa += operands[1] << 21;
		hexa += operands[2] << 16;
	}
	else if ( Is_Operand(instruction , "ADDI")) {

		Get_Operands(instruction, operands, 4);
		hexa += 8 << 26;
		hexa += operands[0] << 16;
		hexa += operands[1] << 21;
		hexa += operands[2] << 0;
	}
	
	free(operands);
	return hexa;
}


/*
Summary : Return all operands in decimal
*/
void Get_Operands(char *s ,int *operands ,int start){
	char *s_part = malloc( sizeof(char)*10 );
	int index = start;
	int i_s_part = 0;
	int i_operands = 0;

	while ( !Instruction_Is_Finish(s , index) ){
		while(s[index] == ' ' || s[index] == ','){
			index++;
		}
		
		while( s[index] != ',' && !Instruction_Is_Finish(s , index) ) {
			s_part[i_s_part] = s[index];
			index++;
			i_s_part++;
		}
		if ( s_part[0] == '$') {
			operands[i_operands] = Get_Register( s_part, i_s_part);
		}
		else {
			operands[i_operands] = String_To_Int( s_part , 0,i_s_part - 1);
		}
		i_operands++;
		i_s_part = 0;
	}
}

/*
Summary : Boolean to tell if the start of s1 is the same as s2.
*/
int Is_Operand(char *s1, char * s2){
	int same = 1;
	int i = 0;
	while ( same && (s1[i] != ' ' || s2[i] != '\0') ) {
		if ( s1[i] != s2[i]) {
			same = 0;
		}
		i++;
	}
	return same;
}

/*
Summary : Boolean to tell if the Instruction is Finish.
*/
int Instruction_Is_Finish( char *s, int start){
	int is_finish = 1;
	int i = start;
	while	( s[i] == ' '){
		i++;
	}
	if ( s[i] != '#' && s[i] != '\0' )
	{
		is_finish = 0;
	}
	return is_finish;
}

/*
Summary : Getting the correct register number.
TODO : Adding the register based on their Name
*/
int Get_Register(char *s, int size){
	int value = String_To_Int(s ,1 ,size - 1);
	return value;
}

/*
Summary : Convert a string into an Int.
*/
int String_To_Int(char *s, int start, int end){
	int value = 0;
	for (int i = start; i <= end; i++) {
		value = 10*value + (s[i]-'0');
	}
	return value;
}
