#ifndef CONTAS_RECEBER_H
#define CONTAS_RECEBER_H

#include <stdio.h>
#include <time.h>

typedef struct {
    int codigo;
    char nomeCliente[100];
    float valor;
    time_t vencimento;
    time_t dataRecebido;
    int recebido; // 0 = pendente, 1 = recebido
    char numeroCartao[20];
    int codigoSeguranca;
} ContaReceber;

void regContaReceberBin(ContaReceber conta);
void regContaReceberTxt(ContaReceber conta);
void regContaReceberPath(ContaReceber conta);
void regContaReceber(void);

void listarContasReceberBin(void);
void listarContasReceberTxt(void);
void listarContasReceber(void);

void baixarContaReceberBin(int codigo);
void baixarContaReceberTxt(int codigo);
void baixarContaReceber(int codigo);

void  excluirContasReceberBin(int codigo);
void  excluirContasReceberTxt(int codigo);
void  excluirContasReceber(int codigo);

#endif // CONTAS_RECEBER_H
