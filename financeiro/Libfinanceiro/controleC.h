#ifndef CONTROLE_H
#define CONTROLE_H

#include <time.h>

#define CONTA_PAGA 2          // Define o tipo de pagamento como "Conta Paga"
#define DINHEIRO_DEBITO 1     // Tipo de pagamento Dinheiro/Débito
#define CARTAO_CREDITO 3      // Tipo de pagamento Cartão de Crédito
#define DEDUCAO_CAIXA 3 

// Estrutura do registro no caixa
typedef struct {
    int codigo;
    char nomeCliente[100];
    float valor;
    int tipoPagamento; // 1: Dinheiro/Débito, 2: Conta Paga, 3: Cartão de Crédito
    time_t dataPagamento;
} Caixa;

// Funções para registrar pagamentos
void registrarPagamentoBin(int codigo, const char *nomeCliente, int tipoPagamento, float valor);
void registrarPagamentoTxt(int codigo, const char *nomeCliente, int tipoPagamento, float valor);
void registrarPagamento();

void registrarPagamentoCartaoCredito(int codigo, float valor);

// saldo do caixa
float obterSaldoCaixa();
//listar caixa
void consultarSaldoCaixaBin();
void consultarSaldoCaixaTxt();
void consultarSaldoCaixa();
void deduzirCaixaBin(int codigoConta, const char *nomeFornecedor, float valor, time_t dataPagamento);
void deduzirCaixaTxt(int codigoConta, const char *nomeFornecedor, float valor, time_t dataPagamento);
void deduzirCaixa(int codigoConta, const char *nomeFornecedor, float valor, time_t dataPagamento);

// Funções para listar lançamentos do caixa
void listarLancamentosCaixaBin();
void listarLancamentosCaixaTxt();
void listarLancamentosCaixa();

// Função para registrar no caixa quando uma conta é marcada como recebida. 
void somarcaixaBin(int codigoConta, const char *nomeCliente, float valor, time_t dataRecebimento);
void somarcaixaTxt(int codigoConta, const char *nomeCliente, float valor, time_t dataRecebimento);
void somarcaixa(int codigoConta, const char *nomeCliente, float valor, time_t dataRecebimento);

// Funções para excluir lançamentos do caixa
void excluirContaCaixaBin();
void excluirContaCaixaTxt();
void excluirContaCaixa();



#endif 
