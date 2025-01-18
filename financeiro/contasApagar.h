#ifndef CONTASAPAGAR_H
#define CONTASAPAGAR_H

#include <time.h>

// Definição da estrutura ContaPagar
typedef struct {
    int codigo;             
    char fornecedor[100];    
    float valor;             
    time_t vencimento;      
    time_t dataPagamento;
    int pago;                // Status de pagamento (0 = não pago, 1 = pago)
} ContaPagar;


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


#endif // CONTASAPAGAR_H
