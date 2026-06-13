# Montador Neander

Este projeto é um montador simples para a arquitetura Neander, desenvolvido em C++. Ele converte um código fonte em assembly Neander (`.asm`) para um arquivo binário de memória (`.mem`) compatível com simuladores Neander.

## Como usar

### 1. Preparar o código fonte
Crie um arquivo chamado `entrada.asm` na mesma pasta do executável. Este arquivo deve conter as instruções do Neander, uma por linha. 

Exemplo de `entrada.asm`:
```asm
LDA 80
ADD 81
STA 82
HLT
```

### 2. Compilar o Montador
Se você tiver o `g++` instalado, compile o código com o seguinte comando no terminal:

```bash
g++ montador.cpp -o montador
```

### 3. Executar o Montador
Após a compilação, execute o programa:

**No Linux/macOS:**
```bash
./montador
```

**No Windows:**
```bash
montador.exe
```

O programa lerá o arquivo `entrada.asm` e gerará automaticamente o arquivo `prog1.mem`.

### 4. Usar no Simulador
O arquivo `prog1.mem` gerado possui o cabeçalho oficial do Neander (`0x03 4E 44 52`) e pode ser carregado diretamente no simulador para execução.

## Instruções Suportadas

| Mnemônico | Opcode | Exige Operando? |
|-----------|--------|-----------------|
| NOP       | 0x00   | Não             |
| STA       | 0x10   | Sim             |
| LDA       | 0x20   | Sim             |
| ADD       | 0x30   | Sim             |
| OR        | 0x40   | Sim             |
| AND       | 0x50   | Sim             |
| NOT       | 0x60   | Não             |
| JMP       | 0x80   | Sim             |
| JN        | 0x90   | Sim             |
| JZ        | 0xA0   | Sim             |
| HLT       | 0xF0   | Não             |

## Autores
- Gustavo de Jesus Moreira
- Lucas Moura
