#include "instruction_assembly.h"
#include <stdio.h>
#include <stdlib.h>

int string_to_hexa(char *instruction){
	int hexa = 0;
	int *operands = malloc(3*sizeof(int));

	if ( compare_string(instruction , "ADD")) {
		get_operands(instruction, operands, 3);
		hexa += block_offset(32,0);
		hexa += block_offset( operands[0] ,11);
		hexa += block_offset( operands[1] ,21);
		hexa += block_offset( operands[2] ,16);
	}
	else if ( compare_string(instruction , "ADDI")) {
		get_operands(instruction, operands, 4);
		hexa += block_offset(8,26);
		hexa += block_offset( operands[0] ,16);
		hexa += block_offset( operands[1] ,21);
		hexa += block_offset( operands[2] ,0);
	}

	free(operands);
	return hexa;
}



int compare_string(char *string1, char * string2){
	int same = 1;
	int i = 0;

	while ( same && (string1[i] != ' ' || string2[i] != '\0') ) {
		if ( string1[i] != string2[i]) {
			same = 0;
		}
		i++;
	}
	return same;
}

int block_offset(int value, int index){

	return value << index;
}

void get_operands(char *instruction,int *operands, int index){
	char *cut = malloc(sizeof(char)*10); //On prend 10 car aucun offset ou registre dépasse 10 caractères
	int i = index;
	int cut_i = 0;
	int ope_i = 0;

	//Boucle qui parcours toute l'instruction
	while ( !end_of_instruction(instruction, i) && instruction[i] != '\0') {

		//Première boucle qui va au début du 'nombre'
		while (instruction[i] == ' '){
			i++;
		}

		while ( instruction[i] != ',' && !end_of_instruction(instruction, i)) {
			cut[cut_i] = instruction[i];
			i++;
			cut_i++;
		}
		printf("test\n");
		if (cut[0] == '$') {
			operands[ope_i] = register_to_int(cut, cut_i);
		}
		else if ( !end_of_instruction(instruction, i) ){
			operands[ope_i] = string_to_decimal(cut, 0,cut_i - 1);
		}
		i++;
		ope_i++;
		cut_i = 0;
	}
	free(cut);
}

int end_of_instruction(char *string, int index){
	int space = 1;
	int i = index;
	while ( space  && string[i] != '\0' && string[i] != '#') {
		if ( string[i] != ' ') {
			space = 0;
		}
		i++;
	}
	return space;
}


//Ajouter le cas des registres avec les noms
int register_to_int(char *string, int size){
	int value = 0;

	value = string_to_decimal(string,1,size - 1);
	return value;
}

int string_to_decimal(char *string, int start, int end){
	int value = 0;
	for (int i = start; i <= end; i++) {
		value = 10*value + (string[i]-'0');
	}
	return value;
}
