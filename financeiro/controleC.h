#ifndef CONTROLE_H
#define CONTROLE_H

#include <time.h>

#define CONTA_PAGA 2          // Define o tipo de pagamento como "Conta Paga"
#define DINHEIRO_DEBITO 1     // Tipo de pagamento Dinheiro/Débito
#define CARTAO_CREDITO 3      // Tipo de pagamento Cartão de Crédito
#define DEDUCAO_CAIXA 3 


typedef struct {
    int codigo;
    char nomeCliente[100];
    float valor;
    int tipoPagamento; 
    time_t dataPagamento;
} Caixa;

// Funções para registrar pagamentos
void registrarPagamentoBin(Caixa registro);
void registrarPagamentoTxt(Caixa registro);
void registrarPagamento();

void registrarPagamentoCartaoCredito();

// saldo do caixa
float obterSaldoCaixa();
// Funções para listar lançamentos do caixa
void listarLancamentosCaixaBin();
void listarLancamentosCaixaTxt();
void listarLancamentosCaixa();

// Funções para excluir lançamentos do caixa
void excluirContaCaixaBin();
void excluirContaCaixaTxt();
void excluirContaCaixa();

void deduzirCaixaBin(int codigoConta, const char *nomeFornecedor, float valor, time_t dataPagamento);
void deduzirCaixaTxt(int codigoConta, const char *nomeFornecedor, float valor, time_t dataPagamento);
void deduzirCaixa(int codigoConta, const char *nomeFornecedor, float valor, time_t dataPagamento);


 
void somarcaixaBin(int codigoConta, const char *nomeCliente, float valor, time_t dataRecebimento);
void somarcaixaTxt(int codigoConta, const char *nomeCliente, float valor, time_t dataRecebimento);
void somarcaixa(int codigoConta, const char *nomeCliente, float valor, time_t dataRecebimento);





#endif 
