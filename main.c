#include <stdio.h>
#include "mips_controller.h"
#include "instruction_assembly.h"
#include "instruction_execution.h"


int main(int argc, char const *argv[]) {
	printf("%.8x\n", String_To_Hexa("ADD $2, $3, $4"));
	printf("%.8x\n", String_To_Hexa("ADDI $2, $3, 200"));
	printf("%.8x\n", String_To_Hexa("AND $13,$2,$3"));

	printf("%.8x\n", String_To_Hexa("ADD $v0, $v1, $a0"));
	printf("%.8x\n", String_To_Hexa("ADDI $v0, $v1, 200"));
	printf("%.8x\n", String_To_Hexa("AND $t5,$v0,$v1"));


	/*printf("%d\n", end_of_instruction("ADD $2, $3, $4", 3));
	printf("%d\n", end_of_instruction("ADD $2, $3, $4", 7));
	printf("%d\n", end_of_instruction("ADD $2, $3, $4", 11));
	printf("%d\n", end_of_instruction("ADD $2, $3, $4", 44));*/

	return 0;
}
