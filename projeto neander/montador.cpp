/*
DUPLA:
GUSTAVO DE JESUS MOREIRA: SP3294528
LUCAS MOURA: SP3306577 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar uma instrução do Neander
typedef struct {
    char nome[10];      // Nome do mnemônico (ex: LDA, ADD)
    unsigned char opcode; // Código de operação em hexadecimal
    int temOperando;    // Booleano (1 se a instrução exige um endereço, 0 caso contrário)
} Instrucao;

// Tabela de instruções suportadas pela arquitetura Neander
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

// Calcula dinamicamente o número de instruções na tabela
int TAM_TABELA = sizeof(tabela) / sizeof(tabela[0]);

/**
 * Busca uma instrução na tabela de símbolos pelo seu mnemônico.
 * Retorna o índice na tabela ou -1 se não encontrar.
 */
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

    // Abre o arquivo de texto com o código assembly (entrada.asm)
    entrada = fopen("entrada.asm", "r");
    if(entrada == NULL)
    {
        printf("Erro ao abrir arquivo de entrada.\n");
        return 1;
    }

    // Cria o arquivo binário de saída (formato .mem do Neander)
    saida = fopen("prog1.mem", "wb");
    if(saida == NULL)
    {
        printf("Erro ao criar arquivo de saida.\n");
        fclose(entrada);
        return 1;
    }

    /* Cabeçalho obrigatório do arquivo .mem do Neander: 0x03, 'N', 'D', 'R' */
    unsigned char cabecalho[] = { 0x03, 0x4E, 0x44, 0x52 };
    fwrite(cabecalho, 1, 4, saida);

    // Processa o arquivo de entrada linha por linha
    while(fgets(linha, sizeof(linha), entrada))
    {
        int indice;
        unsigned char zero = 0x00;

        /* Ignora linhas vazias ou apenas com espaços */
        if(sscanf(linha, "%s", instrucao) != 1)
            continue;

        // Verifica se a instrução existe na tabela de símbolos
        indice = buscarInstrucao(instrucao);
        if(indice == -1)
        {
            printf("Instrucao invalida: %s\n", instrucao);
            continue;
        }

        unsigned char opcode = tabela[indice].opcode;

        /* Escreve o opcode e um byte de preenchimento (00) 
           conforme o padrão do simulador Neander */
        fwrite(&opcode, 1, 1, saida);
        fwrite(&zero, 1, 1, saida);

        // Se a instrução exigir um operando (endereço de memória)
        if(tabela[indice].temOperando)
        {
            unsigned int endereco;

            /* Tenta ler o endereço em hexadecimal da linha atual */
            if(sscanf(linha, "%s %x", instrucao, &endereco) != 2)
            {
                printf("Erro: operando ausente em %s\n", instrucao);
                continue;
            }

            unsigned char end = (unsigned char) endereco;

            /* Escreve o endereço e outro byte de preenchimento (00) */
            fwrite(&end, 1, 1, saida);
            fwrite(&zero, 1, 1, saida);
        }
    }

    // Fecha os arquivos para garantir que os dados foram gravados corretamente
    fclose(entrada);
    fclose(saida);

    printf("Montagem concluida!\n");
    printf("Arquivo gerado: prog1.mem\n");

    return 0;
}
