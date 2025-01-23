#ifndef FINANCEIRO_H
#define FINANCEIRO_H
#include <stdio.h>
#include <time.h>

#define CONTA_PAGA 2          // Define o tipo de pagamento como "Conta Paga"
#define DINHEIRO_DEBITO 1     // Tipo de pagamento Dinheiro/Débito
#define CARTAO_CREDITO 3      // Tipo de pagamento Cartão de Crédito
#define DEDUCAO_CAIXA 3 

// Definição da estrutura ContaPagar
typedef struct {
    int codigo;             
    char fornecedor[100];    
    float valor;             
    time_t vencimento;      
    time_t dataPagamento;
    int pago;                // Status de pagamento (0 = não pago, 1 = pago)
} ContaPagar;

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

typedef struct {
    int codigo;
    char nomeCliente[100];
    float valor;
    int tipoPagamento; 
    time_t dataPagamento;
} Caixa;

//contas a pagar
void regConta();                      
void regContaBin(ContaPagar conta);   
void regContaTxt(ContaPagar conta);   
void regContaPath(ContaPagar conta);  
 // Listar todas as contas
void listarContas();                 
void listarContasBin();              
void listarContasTxt();               
  // Excluir uma conta
void excluirConta();      
void excluirContaBin();    
void excluirContaTxt();
  // Marcar uma conta como paga
void baixarConta();       
void baixarContaBin();      
void baixarContaTxt();  
//contas a receber
void regContaReceberBin(ContaReceber conta);
void regContaReceberTxt(ContaReceber conta);
void regContaReceberPath(ContaReceber conta);
void regContaReceber(void);

void listarContasReceberBin(void);
void listarContasReceberTxt(void);
void listarContasReceber(void);

void baixarContaReceberBin();
void baixarContaReceberTxt();
void baixarContaReceber();

void  excluirContasReceberBin();
void  excluirContasReceberTxt();
void  excluirContasReceber();
//controle de caixa 

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
#endif // CONTASAPAGAR_H
