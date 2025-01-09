#ifndef CONTASAPAGAR_H
#define CONTASAPAGAR_H

#include <time.h>

// Definição da estrutura ContaPagar
typedef struct {
    int codigo;              
    char fornecedor[100];    
    float valor;             
    time_t vencimento;      
    int pago;                // Status de pagamento (0 = não pago, 1 = pago)
} ContaPagar;

// Declarações de funções para contas a pagar
void regConta();                     
void regContaBin(ContaPagar conta);   
void regContaTxt(ContaPagar conta);  
void regContaPath(ContaPagar conta);  

void listarContas();                  
void listarContasBin();              
void listarContasTxt();               

void excluirConta(int codigo);       
void excluirContaBin(int codigo);     
void excluirContaTxt(int codigo);     

void baixarConta(int codigo);         // Marcar uma conta como paga
void baixarContaBin(int codigo);     
void baixarContaTxt(int codigo);     


#endif // CONTASAPAGAR_H
