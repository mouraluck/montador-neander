typedef struct {
    char nome[4];
    char opcode[3];
} Instrucao;

const Instrucao TABELA_OPCODES[] = {
    {"NOP", '00'},
    {"STA", '10'},
	{"LDA", '20'},
    {"ADD", '30'},
    {"OR",  '40'},
    {"AND", '50'},
    {"NOT", '60'},
    {"JMP", '80'},
    {"JN",	'90'},
    {"JZ",	'A0'},
    {"HLT",	'F0'}
    
};

const int TOTAL_INSTRUCOES = sizeof(TABELA_OPCODES) / sizeof(TABELA_OPCODES[0]);

const char* getOpcodeBy(char aInstruction[4]) {
    for (int i = 0; i < TOTAL_INSTRUCOES; i++) {
        if (strcmp(aInstruction, TABELA_OPCODES[i].nome) == 0) {
            return TABELA_OPCODES[i].opcode;
        }
    }
    return NULL;
}
