#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ula.h"

int main(int argc, char** argv) {
	
	
	char line[7];
	scanf("%[^\n]s", &line);
	
	char* instruction = strtok(line, " ");
	char* address = strtok(NULL, " ");

	const char* opcode = getOpcodeBy(instruction);
	
	if(address != NULL){
		printf("%s %s\n",opcode, address);
	} else {
		printf("%s\n",opcode);
	}
	
	return 0;
}
