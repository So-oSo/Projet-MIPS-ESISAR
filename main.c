#include <stdio.h>
#include "mips_controller.h"
#include "instruction_assembly.h"
#include "instruction_execution.h"


int main(int argc, char const *argv[]) {
	printf("%.8x\n", string_to_hexa("ADD $2, $3, $4"));
	printf("%.8x\n", string_to_hexa("ADDI $2, $3, 200"));

	/*printf("%d\n", end_of_instruction("ADD $2, $3, $4", 3));
	printf("%d\n", end_of_instruction("ADD $2, $3, $4", 7));
	printf("%d\n", end_of_instruction("ADD $2, $3, $4", 11));
	printf("%d\n", end_of_instruction("ADD $2, $3, $4", 44));*/

	return 0;
}
