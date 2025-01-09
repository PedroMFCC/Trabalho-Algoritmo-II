#ifndef CONTASAPAGAR_H
#define CONTASAPAGAR_H

#include <time.h>

// Definição da estrutura ContaPagar
typedef struct {
    int codigo;              // Código da conta
    char fornecedor[100];    // Nome do fornecedor
    float valor;             // Valor da conta
    time_t vencimento;       // Data de vencimento (timestamp)
    int pago;                // Status de pagamento (0 = não pago, 1 = pago)
} ContaPagar;

// Declarações de funções para contas a pagar
void regConta();                      // Registrar nova conta
void regContaBin(ContaPagar conta);   // Registrar conta no arquivo binário
void regContaTxt(ContaPagar conta);   // Registrar conta no arquivo texto
void regContaPath(ContaPagar conta);  // Registrar conta de acordo com o formato definido

void listarContas();                  // Listar todas as contas
void listarContasBin();               // Listar contas do arquivo binário
void listarContasTxt();               // Listar contas do arquivo texto

void excluirConta(int codigo);        // Excluir uma conta
void excluirContaBin(int codigo);     // Excluir uma conta do arquivo binário
void excluirContaTxt(int codigo);     // Excluir uma conta do arquivo texto

void baixarConta(int codigo);         // Marcar uma conta como paga
void baixarContaBin(int codigo);      // Baixar conta no arquivo binário
void baixarContaTxt(int codigo);      // Baixar conta no arquivo texto


#endif // CONTASAPAGAR_H
