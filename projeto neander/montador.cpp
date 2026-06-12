#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[10];
    unsigned char opcode;
    int temOperando;
} Instrucao;

Instrucao tabela[] = {
    {"NOP", 0x00, 0},
    {"STA", 0x10, 1},
    {"LDA", 0x20, 1},
    {"ADD", 0x30, 1},
    {"OR",  0x40, 1},
    {"AND", 0x50, 1},
    {"NOT", 0x60, 0},
    {"JMP", 0x80, 1},
    {"JN",  0x90, 1},
    {"JZ",  0xA0, 1},
    {"HLT", 0xF0, 0}
};

int TAM_TABELA = sizeof(tabela) / sizeof(tabela[0]);

int buscarInstrucao(char *mnemonico)
{
    for(int i = 0; i < TAM_TABELA; i++)
    {
        if(strcmp(mnemonico, tabela[i].nome) == 0)
            return i;
    }

    return -1;
}

int main(int argc, char *argv[])
{
    FILE *entrada;
    FILE *saida;

    char linha[100];
    char instrucao[10];


    entrada = fopen("entrada.asm", "r");

    if(entrada == NULL)
    {
        printf("Erro ao abrir arquivo de entrada.\n");
        return 1;
    }

    saida = fopen("prog1.mem", "wb");

    if(saida == NULL)
    {
        printf("Erro ao criar arquivo de saida.\n");
        fclose(entrada);
        return 1;
    }

    /* Cabeçalho obrigatório */
    unsigned char cabecalho[] = {
        0x03, 0x4E, 0x44, 0x52
    };

    fwrite(cabecalho, 1, 4, saida);

    while(fgets(linha, sizeof(linha), entrada))
    {
        int indice;
        unsigned char zero = 0x00;

        /* Ignora linhas vazias */
        if(sscanf(linha, "%s", instrucao) != 1)
            continue;

        indice = buscarInstrucao(instrucao);

        if(indice == -1)
        {
            printf("Instrucao invalida: %s\n", instrucao);
            continue;
        }

        unsigned char opcode = tabela[indice].opcode;

        /* Escreve opcode e byte 00 */
        fwrite(&opcode, 1, 1, saida);
        fwrite(&zero, 1, 1, saida);

        if(tabela[indice].temOperando)
        {
            unsigned int endereco;

            if(sscanf(linha, "%s %x", instrucao, &endereco) != 2)
            {
                printf("Erro: operando ausente em %s\n", instrucao);
                continue;
            }

            unsigned char end = (unsigned char) endereco;

            fwrite(&end, 1, 1, saida);
            fwrite(&zero, 1, 1, saida);
        }
    }

    fclose(entrada);
    fclose(saida);

    printf("Montagem concluida!\n");
    printf("Arquivo gerado: prog1.mem\n");

    return 0;
}
