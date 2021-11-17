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
int Instruction_To_Hexa(char *instruction){
	int hexa = 0;
	int *operands = malloc(3*sizeof(int));
	Upper_Case_String(instruction);
	int start = Get_Front_Space(instruction);


	if ( Is_Operand(start, instruction , "ADD")) {

		Get_Operands(instruction, operands, 3 + start);
		hexa += 32;
		hexa += operands[0] << 11;
		hexa += operands[1] << 21;
		hexa += operands[2] << 16;
	}
	else if ( Is_Operand(start, instruction , "ADDI")) {

		Get_Operands(instruction, operands, 4 + start);
		hexa += 8 << 26;
		hexa += operands[0] << 16;
		hexa += operands[1] << 21;
		hexa += operands[2];
	}
	else if ( Is_Operand(start, instruction , "AND")) {

		Get_Operands(instruction, operands, 3 + start);
		hexa += 36;
		hexa += operands[0] << 11;
		hexa += operands[1] << 21;
		hexa += operands[2] << 16;
	}
	else if ( Is_Operand(start, instruction , "BEQ")) {
		Get_Operands(instruction, operands, 3 + start);
		hexa += 4 << 26;
		hexa += operands[0] << 21;
		hexa += operands[1] << 16;
		hexa += operands[2];
	}
	else if ( Is_Operand(start, instruction , "BGTZ")) {

		Get_Operands(instruction, operands, 4 + start);
		hexa += 7 << 26;
		hexa += operands[0] << 21;
		hexa += operands[1];
	}
	else if ( Is_Operand(start, instruction , "BLEZ")) {
		Get_Operands(instruction, operands, 4 + start);
		hexa += 6 << 26;
		hexa += operands[0] << 21;
		hexa += operands[1];
	}
	else if ( Is_Operand(start, instruction , "DIV")) {
		Get_Operands(instruction, operands, 3 + start);
		hexa += 26;
		hexa += operands[0] << 21;
		hexa += operands[1] << 16;
	}
	else if ( Is_Operand(start, instruction , "BNE")) {
		Get_Operands(instruction, operands, 3 + start);
		hexa += 5 << 26;
		hexa += operands[0] << 21;
		hexa += operands[1] << 16;
		hexa += operands[2];
	}
	else if ( Is_Operand(start, instruction , "J")) {
		Get_Operands(instruction, operands, 1 + start);
		hexa += 2 << 26;
		hexa += operands[0];
	}
	else if ( Is_Operand(start, instruction , "JR")) {
		Get_Operands(instruction, operands, 2 + start);
		hexa += 8;
		hexa += operands[0] << 21;
	}
	else if ( Is_Operand(start, instruction , "JAL")) {
		Get_Operands(instruction, operands, 3 + start);
		hexa += 3 << 26;
		hexa += operands[0];
	}
	else if ( Is_Operand(start, instruction , "LUI")) {
		Get_Operands(instruction, operands, 3 + start);
		hexa += 15 << 26;
		hexa += operands[0] << 16;
		hexa += operands[1];
	}
	else if ( Is_Operand(start, instruction , "LW")) {

		Get_Operands(instruction, operands, 2 + start);
		hexa += 35 << 26;
		hexa += operands[0] << 16;
		hexa += operands[1];
		hexa += operands[2] << 21;
	}
	else if ( Is_Operand(start, instruction , "MFHI")) {
		Get_Operands(instruction, operands, 4 + start);
		hexa += 16;
		hexa += operands[0] << 11;
	}
	else if ( Is_Operand(start, instruction , "MULT")) {
		Get_Operands(instruction, operands, 4 + start);
		hexa += 24;
		hexa += operands[0] << 21;
		hexa += operands[1] << 16;
	}
	else if ( Is_Operand(start, instruction , "MFLO")) {
		Get_Operands(instruction, operands, 4 + start);
		hexa += 18;
		hexa += operands[0] << 11;
	}
	else if ( Is_Operand(start, instruction , "NOP")) {
	}
	else if ( Is_Operand(start, instruction , "OR")) {
		Get_Operands(instruction, operands, 2 + start);
		hexa += 37;
		hexa += operands[0] << 11;
		hexa += operands[1] << 21
		hexa += operands[2] << 16;
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
		int as_bracket = Is_in_String(s_part, '(');
		if ( s_part[0] == '$') {
			operands[i_operands] = Get_Register( s_part,0 , i_s_part - 1);
		}
		else if (as_bracket != -1){
			if ( Is_in_Hexa(s_part, as_bracket))
			{
				operands[i_operands] = String_To_Int( s_part, 2, as_bracket - 1, 16);
			}
			else{
				operands[i_operands] = String_To_Int( s_part , 0,as_bracket - 1, 10);
			}
			i_operands++;
			operands[i_operands] = Get_Register( s_part, as_bracket + 1 , i_s_part - 2);
		}
		else if ( Is_in_Hexa(s_part, i_s_part)){
			operands[i_operands] = String_To_Int( s_part , 2,i_s_part - 1, 16);
		}
		else {
			operands[i_operands] = String_To_Int( s_part , 0,i_s_part - 1, 10);
		}
		i_operands++;
		i_s_part = 0;
	}
}

/*
Summary : Boolean to tell if the number is in hexa
*/
int Is_in_Hexa(char *s,int size){
	int value = 0;

	if ( size > 2 )
	{
		if ( s[0] == '0' && s[1] == 'X')
		{
			value = 1;
		}
	}
	return value;
}

/*
Summary : Change all lower case to upper case
*/
void Upper_Case_String(char *s){
	int i = 0;
	while( s[i] != '\0' ){
		if ( s[i] >= 'a' && s[i] <= 'z')
		{
			s[i] -= 'a' - 'A';
		}
		i++;
	}
}


/*
Summary : Get how many space there is in front of the instruction
*/
int Get_Front_Space(char *s){
	int value = 0;

	while( s[value] == ' '){
		value++;
	}

	return value;
}
/*
Summary : Boolean to tell if the start of s1 is the same as s2.
*/
int Is_Operand(int start, char *s1, char * s2){
	int same = 1;
	int i = start,j = 0;
	while ( same && (s1[i] != ' ' || s2[j] != '\0') ) {
		if ( s1[i] != s2[j]) {
			same = 0;
		}
		i++;j++;
	}
	return same;
}

/*
Summary : Boolean to tell if the Instruction is Finish.
*/
int Instruction_Is_Finish( char *s, int start){
	int is_finish = 1;
	int i = start;
	while( s[i] == ' '){
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
*/
int Get_Register(char *s,int start, int end){
	int value;
	int size = end - start;
	//Cas des nombres
	if ( s[start + 1] <= '9' )
	{
		value = String_To_Int(s , start + 1 ,end, 10);
	}
	else if (size >= 3){
		if ( size == 5 )
		{
			if ( s[start + 1] == 'Z' && s[start + 2] == 'E' && s[start + 3] == 'R' && s[start + 4] == 'O')
			{
				value = 0;
			}
		}
		else if ( s[start + 1] == 'A' && s[start + 2] == 'T'){
			value = 1;
		}
		else if ( s[start + 1] == 'G' && s[start + 2] == 'P'){
			value = 28;
		}
		else if ( s[start + 1] == 'S' && s[start + 2] == 'P'){
			value = 29;
		}
		else if ( s[start + 1] == 'F' && s[start + 2] == 'P'){
			value = 30;
		}
		else if ( s[start + 1] == 'R' && s[start + 2] == 'A'){
			value = 31;
		}
		else if ( s[start + 1] == 'V' && s[start + 2] <= '1' ){
			value = 2 + (s[2] - '0');
		}
		else if ( s[start + 1] == 'A' && s[start + 2] <= '3' ){
			value = 4 + (s[2] - '0');
		}
		else if ( s[start + 1] == 'S' && s[start + 2] <= '7' ){
			value = 16 + (s[2] - '0');
		}
		else if ( s[start + 1] == 'K' && s[start + 2] <= '1' ){
			value = 26 + (s[2] - '0');
		}
		else if ( s[start + 1] == 'T' && s[start + 2] <= '9' ){
			if ( s[start + 2] >= '8')
			{
				value = 24 + (s[start + 2] - '8');
			}
			else{
				value = 8 + (s[start + 2] - '0');
			}
		}
	}
	return value;
}

/*
Summary : Convert a string into an Int.
*/
int String_To_Int(char *s, int start, int end, int base){
	int value = 0;
	int negatif = s[0] == '-';
	int first = '0';
	for (int i = start + negatif; i <= end; i++) {

		if (s[i] <= '9' && s[i] >= '0')
		{
			first = '0';
		}
		else
		{
			first = 'A' - 10;
		}

		value = base*value + (s[i]- first);
	}
	if (negatif)
	{
		value = 65536 - value;
	}
	return value;
}


/*
Summary : Convert a txt file into a hexa file
*/
void String_To_Hexa(char *fileName, char *output){
	FILE* fileRead = NULL;
	FILE* fileWrite = NULL;

	fileRead = fopen(fileName, "r");
	fileWrite = fopen(output, "w");

	char ligne[INSTRUCTION_MAX_LENGTH];


	if ( fileRead != NULL && fileWrite != NULL)
	{
		
		while( fgets(ligne, INSTRUCTION_MAX_LENGTH, fileRead) != NULL ){

			int status = Is_in_String(ligne, '\n');
			if ( status == -1 )
			{
				int value;
				do
				{
					value = fgetc(fileRead);
				} while ( value != '\n' && value != EOF );
			}
			else
			{
				ligne[status] = ' ';
			}

			int hexa = Instruction_To_Hexa(ligne);

			if ( hexa != 0)
			{
				fprintf(fileWrite, "%08x\n", hexa);
			}
		}
		
		fclose(fileWrite);
		fclose(fileRead);
	}
	else
	{
		printf("Erreur avec le fichier source.");
	}
}

/*
Summary : return the first index of a in s, if a is not in s return -1
*/
int Is_in_String(char *s, char a){
	int i = 0;
	while( s[i] != a && s[i] != '\0' ){
		i++;
	}
	return s[i] == a ? i : -1;
}