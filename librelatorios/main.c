//ALUNOS
//LÚCIO O.N.G.
//HEITOR DE S. E S.
//PEDRO MIGUEL F.C.C.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Liboficina/oficina.h"
#include "Libpecas/pecas.h"
#include "libfuncionarios/funcionarios.h"
#include "libveiculos/veiculos.h"
#include "libservicos/servicos.h"
#include "Libclientes/clientes.h"
#include "Libfornecedor/fornecedor.h"
#include "Libfinanceiro/financeiro.h"
#include "librelatorios/relatorios.h"



int formaregistro(){
    int i = 0;
    int formato;

    FILE *arq;
    arq = fopen("arquivos/formato.bin","wb");
    if (arq == NULL){
        printf("Erro na abertura do arquivo!");
        return 1;
    }
    while(i != 3){
        printf("Forma em que os arquivos serao armazenados durante o processo:\n*Tenha em mente que o formato escolhido altera o local de registro tambem*\n 1 - Binario\n 2 - Texto\nDigite sua opcao:");
        scanf("%d", &i);

        switch (i){
            case 1:
                formato = 1;            
                i = 3;
            break;

            case 2:
                formato = 2;      
                i = 3;      
            break;

            default:
                i = 0;
                printf("Formato não identificado, favor digitar um valor válido!");
            break;
        }   
    }

    fwrite(&formato, sizeof(int), 1, arq);
        
    fclose(arq);
    return 0;
}

void menupecas(){
    int i = 0;
    while(i != 5){
    i = 0;

    printf("\n======================================== MENU PEÇAS ========================================\n");
    printf("opcoes:\n 1 - Registrar nova peca\n 2 - Editar peca ja registrada\n 3 - Consultar o arquivo\n 4 - Remover registro\n 5 - Cancelar\n digite a opção:");
    scanf("%d", &i);

    
        switch(i){
            case 1:
                regpeca();
            break;

            case 2:
                editpeca();
            break;

            case 3:
                lerpeca();
            break;

            case 4:
                removerpeca();
            break;

            case 5:
                printf("\n\noperacao cancelada!");
                printf("\n================================================================================\n");
                return;
            break;
        }
    }
}

void menuoficina(){
    int i = 0;
    while(i != 3){
    i = 0;

    printf("\n====================================== MENU OFICINA ======================================\n");
    printf("opcoes:\n 1 - Registrar/editar oficina\n 2 - Consultar o arquivo da oficina\n 3 - Cancelar\n digite a opção:");
    scanf("%d", &i);

    
        switch(i){
            case 1:
                regoficina();
            break;

            case 2:
                lerofic();
            break;

            case 3:
                printf("\n\noperação cancelada!");
                return;
            break;
        }
    }
}

void menuFuncionarios() {
    int opcao;
    while (1) {
        printf("\n======================================== MENU DE FUNCIONÁRIOS ========================================\n");
        printf("1. Registrar Novo Funcionário\n");
        printf("2. Editar Funcionário Existente\n");
        printf("3. Consultar Funcionários\n");
        printf("4. Excluir Funcionário\n");
        printf("5. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n'); // Limpa o buffer
            printf("Entrada inválida! Tente novamente.\n");
            continue;
        }

        switch (opcao) {
            case 1:
                regfuncionario();
                break;
            case 2:
                editfuncionario();
                break;
            case 3:
                lerfuncionario();
                break;
            case 4:
                excluirFuncionario();
                break;
            case 5:
                return;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
}

void menuVeiculos() {
    int opcao;
    while (1) {
        printf("\n======================================== MENU DE VEÍCULOS ========================================\n");
        printf("1. Registrar Novo Veículo\n");
        printf("2. Editar Veículo Existente\n");
        printf("3. Consultar Veículos\n");
        printf("4. Excluir Veículo\n");
        printf("5. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n'); // Limpa o buffer
            printf("Entrada inválida! Tente novamente.\n");
            continue;
        }

        switch (opcao) {
            case 1:
                regveiculo();
                break;
            case 2:
                editveiculo();
                break;
            case 3:
                lerveiculo();
                break;
            case 4:
                excluirVeiculo();
                break;
            case 5:
                return;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
}

void menuServicos() {
    int opcao;
    while (1) {
        printf("\n======================================== MENU DE SERVIÇOS ========================================\n");
        printf("1. Registrar Novo Serviço\n");
        printf("2. Editar Serviço Existente\n");
        printf("3. Consultar Serviços\n");
        printf("4. Excluir Serviço\n");
        printf("5. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n'); // Limpa o buffer
            printf("Entrada inválida! Tente novamente.\n");
            continue;
        }

        switch (opcao) {
            case 1:
                regservico();
                break;
            case 2:
                editservico();
                break;
            case 3:
                lerservico();
                break;
            case 4:
                excluirServico();
                break;
            case 5:
                return;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
}

void menufornecedor() {
    int i = 0;

    while(i != 6) {
        i = 0;

        printf("\n======================================== MENU FORNECEDOR ========================================\n");
        printf("opções:\n");
        printf("1 - Registrar novo fornecedor\n");
        printf("2 - Editar fornecedor já registrado\n");
        printf("3 - Consultar fornecedor\n");
        printf("4 - Excluir registro de fornecedor\n");
        printf("5 - Excluir fornecedor\n");
        printf("6 - Sair do menu\n");
        printf("Digite a opção escolhida: ");
        scanf("%d", &i);

        switch (i) {
        case 1:
            regforn(); 
            break;
        
        case 2:
            editforn();
            break;

        case 3:
            lerforn();
            break;

        case 4:
            excluirReg();
            break;

        case 5:
            excluirFornecedor();
            break;

        case 6:
        default:
            printf("\nOperação cancelada!\n");
        }
    }
}

void menucliente() {
    int i = 0;

    while(i != 5) {
        i = 0;

        printf("\n=========================================== MENU CLIENTE ===========================================\n");
        printf("opções:\n");
        printf("1 - Registrar novo cliente\n");
        printf("2 - Editar cliente já registrado\n");
        printf("3 - Consultar cliente\n");
        printf("4 - Excluir Cliente\n");
        printf("5 - Sair do menu\n");
        printf("Digite a opção escolhida: ");
        scanf("%d", &i);

        switch (i) {
        case 1:
            regcli();
            break;

        case 2:
            editcli();
            break;

        case 3:
            lercli();
            break;

        case 4:
            excluirCliente();
            break;

        case 5:
        default:
            printf("\nOperação cancelada!\n");
        }
    }
}


void menuContasPagar() {
    int opcao;
    while (1) {
        printf("\n========================== MENU CONTAS A PAGAR ==========================\n");
        printf("1. Registrar Nova Conta a Pagar\n");
        printf("2. Listar Contas a Pagar\n");
        printf("3. Excluir Conta a Pagar\n");
        printf("4. Baixar Conta (Marcar como Paga)\n");
        printf("5. Voltar ao Menu Financeiro\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n'); // Limpa o buffer
            printf("Entrada inválida! Tente novamente.\n");
            continue;
        }

        switch (opcao) {
            case 1:
                regConta();
                break;
            case 2:
                listarContas();
                break;
            case 3:
                excluirConta(); 
                break;
            case 4:
                baixarConta();   
                break;
            case 5:
                return;  // Retorna ao menu financeiro
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
}


void menuContasReceber() {
    int opcao;
    while (1) {
        printf("\n==================== MENU CONTAS A RECEBER ====================\n");
        printf("1. Registrar Nova Conta a Receber\n");
        printf("2. Listar Contas a Receber\n");
        printf("3. Excluir Conta a Receber\n");
        printf("4. Baixar Conta (Marcar como Recebida)\n");
        printf("5. Voltar ao Menu Financeiro\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');  // Limpa o buffer
            printf("Entrada inválida! Tente novamente.\n");
            continue;
        }

        switch (opcao) {
            case 1:
                regContaReceber();
                break;
            case 2:
                listarContasReceber();
                break;
            case 3:
                excluirContasReceber();
                break;
            case 4:
                baixarContaReceber();
                break;
            case 5:
                return;  
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
}

void menuControleCaixa() {
    int opcao;
    
    while (1) {
        printf("\n====================================== MENU CONTROLE DE CAIXA ======================================\n");
        printf("1. Registrar Pagamento em Dinheiro/Débito\n");
        printf("2. Registrar Pagamento com Cartão de Crédito\n");
        printf("3. Ver Lançamentos no Caixa.\n");
        printf("4. Consultar Saldo do Caixa\n");
        printf("5. Excluir uma conta.\n");
        printf("6. Voltar ao Menu Financeiro\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n'); // Limpa o buffer
            printf("Entrada inválida! Tente novamente.\n");
            continue;
        }

        switch (opcao) {
            case 1:
                registrarPagamento();
                break;

            case 2: {
                registrarPagamentoCartaoCredito();
                break;
            }

            case 3: {
                // Consultar lançamentos no caixa
                listarLancamentosCaixa();
                break;
            }

            case 4: {
                // Consultar saldo do caixa
                float saldo = obterSaldoCaixa();
                printf("Saldo atual do caixa: R$ %.2f\n", saldo);
                break;
            }
            case 5:{
             
              excluirContaCaixa();
                break;
            }

            case 6:
                return;  // Volta ao menu financeiro
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
}

void menuFinanceiro() {
    int opcao;
    
    while (1) {
        printf("\n========================== MENU FINANCEIRO ==========================\n");
        printf("1. Controle de Caixa\n");
        printf("2. Contas a Pagar\n");
        printf("3. Contas a Receber\n");
        printf("4. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n'); // Limpa o buffer
            printf("Entrada inválida! Tente novamente.\n");
            continue;
        }

        switch (opcao) {
            case 1:
                menuControleCaixa();
                break;
            case 2:
                menuContasPagar();
                break;
            case 3:
                menuContasReceber();
                break;
            case 4:
                return;  // Volta ao menu principal
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
}

// Função para exibir o menu e processar escolhas
void menuRelfinanceiro() {
    FiltrosRelatorio filtros = obterFiltrosRelatorio();

    printf("Escolha o tipo de relatório:\n");
    printf("1 - Caixa\n");
    printf("2 - Contas a Receber\n");
    printf("3 - Contas a Pagar\n");
    int tipo;
    scanf("%d", &tipo);

    printf("Deseja exibir na tela ou exportar para CSV? (1 - Tela, 2 - CSV): ");
    int destino;
    scanf("%d", &destino);

    FILE *saida;
    if (destino == 2) {
        char caminhoCSV[100];
        sprintf(caminhoCSV, "Relatorios/relatorio.csv");
        saida = fopen(caminhoCSV, "w");
        if (!saida) {
            printf("Erro ao criar arquivo CSV em: %s\n", caminhoCSV);
            return;
        }
    } else {
        saida = stdout;
    }

    switch (tipo) {
        case 1:
            gerarRelatorio(RELATORIO_CAIXA, filtros, saida);
            break;
        case 2:
            gerarRelatorio(RELATORIO_CONTAS_RECEBER, filtros, saida);
            break;
        case 3:
            gerarRelatorio(RELATORIO_CONTAS_PAGAR, filtros, saida);
            break;
        default:
            printf("Opção inválida!\n");
            break;
    }

    if (destino == 2) {
        fclose(saida);
        printf("Relatório exportado para Relatorios/relatorio.csv\n");
    }
}

// Função para exibir o menu de relatórios de cadastros e processar escolhas
void menuVeiculosR() {
    FiltrosRelatorioCadastros filtros = obterFiltrosVeiculos();

    printf("Escolha o tipo de relatório de cadastros:\n");
    printf("1 - Veículos\n");
    
    int tipo;
    scanf("%d", &tipo);

    printf("Deseja exibir na tela ou exportar para CSV? (1 - Tela, 2 - CSV): ");
    int destino;
    scanf("%d", &destino);

    FILE *saida;
    if (destino == 2) {
        char caminhoCSV[100];
        sprintf(caminhoCSV, "Relatorios/relatorio_cadastros.csv");
        saida = fopen(caminhoCSV, "w");
        if (!saida) {
            printf("Erro ao criar arquivo CSV em: %s\n", caminhoCSV);
            return;
        }
    } else {
        saida = stdout;
    }

    switch (tipo) {
        case 1:
            gerarRelatorioVeiculos(filtros, saida);
            break;
       
        default:
            printf("Opção inválida!\n");
            break;
    }

    if (destino == 2) {
        fclose(saida);
        printf("Relatório exportado para Relatorios/relatorio_cadastros.csv\n");
    }
}
// Função para exibir o menu de relatórios de serviços e processar escolhas
void menuServicosR() {
    FiltrosRelatorioServicos filtros = obterFiltrosServicos();

    printf("Deseja exibir na tela ou exportar para CSV? (1 - Tela, 2 - CSV): ");
    int destino;
    scanf("%d", &destino);

    FILE *saida;
    if (destino == 2) {
        char caminhoCSV[100];
        sprintf(caminhoCSV, "Relatorios/relatorio_servicos.csv");
        saida = fopen(caminhoCSV, "w");
        if (!saida) {
            printf("Erro ao criar arquivo CSV em: %s\n", caminhoCSV);
            return;
        }
    } else {
        saida = stdout;
    }

    gerarRelatorioServicos(filtros, saida);

    if (destino == 2) {
        fclose(saida);
        printf("Relatório exportado para Relatorios/relatorio_servicos.csv\n");
    }
}

// Função para exibir o menu de relatórios de funcionários e processar escolhas
void menuFuncionariosR() {
    FiltrosRelatorioFuncionarios filtros = obterFiltrosFuncionarios();

    printf("Deseja exibir na tela ou exportar para CSV? (1 - Tela, 2 - CSV): ");
    int destino;
    scanf("%d", &destino);

    FILE *saida;
    if (destino == 2) {
        char caminhoCSV[100];
        sprintf(caminhoCSV, "Relatorios/relatorio_funcionarios.csv");
        saida = fopen(caminhoCSV, "w");
        if (!saida) {
            printf("Erro ao criar arquivo CSV em: %s\n", caminhoCSV);
            return;
        }
    } else {
        saida = stdout;
    }

    gerarRelatorioFuncionarios(filtros, saida);

    if (destino == 2) {
        fclose(saida);
        printf("Relatório exportado para Relatorios/relatorio_funcionarios.csv\n");
    }
}
// Função para exibir o menu de relatórios de clientes e processar escolhas
void menuClientesR() {
    FiltrosRelatorioCadastros filtros = obterFiltrosClientes();

    printf("Deseja exibir na tela ou exportar para CSV? (1 - Tela, 2 - CSV): ");
    int destino;
    scanf("%d", &destino);

    FILE *saida;
    if (destino == 2) {
        char caminhoCSV[100];
        sprintf(caminhoCSV, "Relatorios/relatorio_clientes.csv");
        saida = fopen(caminhoCSV, "w");
        if (!saida) {
            printf("Erro ao criar arquivo CSV em: %s\n", caminhoCSV);
            return;
        }
    } else {
        saida = stdout;
    }

    gerarRelatorioClientes(filtros, saida);

    if (destino == 2) {
        fclose(saida);
        printf("Relatório exportado para Relatorios/relatorio_clientes.csv\n");
    }
}
// Função para exibir o menu de relatórios de fornecedores e processar escolhas
void menuFornecedoresR() {
    FiltrosRelatorioFornecedores filtros = obterFiltrosFornecedores();

    printf("Deseja exibir na tela ou exportar para CSV? (1 - Tela, 2 - CSV): ");
    int destino;
    scanf("%d", &destino);

    FILE *saida;
    if (destino == 2) {
        char caminhoCSV[100];
        sprintf(caminhoCSV, "Relatorios/relatorio_fornecedores.csv");
        saida = fopen(caminhoCSV, "w");
        if (!saida) {
            printf("Erro ao criar arquivo CSV em: %s\n", caminhoCSV);
            return;
        }
    } else {
        saida = stdout;
    }

    gerarRelatorioFornecedores(filtros, saida);

    if (destino == 2) {
        fclose(saida);
        printf("Relatório exportado para Relatorios/relatorio_fornecedores.csv\n");
    }
}

// Atualização no menu de relatórios de cadastros (acrescentar nova opção)
void menuRelCadastros() {
    int opcao;

    do {
        printf("\n=== Menu de Relatórios de Cadastros ===\n");
        printf("1 - Relatório de Veículos\n");
        printf("2 - Relatório de Serviços\n");
        printf("3 - Relatório de Funcionários\n");
        printf("4 - Relatório de Clientes\n");
        printf("5 - Relatório de Fornecedores\n");  // Nova opção
        printf("0 - Voltar ao menu principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menuVeiculosR();
                break;
            case 2:
                menuServicosR();
                break;
            case 3:
                menuFuncionariosR();
                break;
            case 4:
                menuClientesR();
                break;
            case 5:  // Novo caso para fornecedores
                menuFornecedoresR();
                break;
            case 0:
                printf("Retornando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

// Função para exibir o menu geral de relatórios
void menuRelatorios() {
    int opcao;
    while (1) {
        printf("\n========================== MENU RELATÓRIOS ==========================\n");
        printf("1. Relatórios Financeiros\n");
        printf("2. Relatórios de Cadastros\n");
        printf("3. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n'); // Limpa o buffer
            printf("Entrada inválida! Tente novamente.\n");
            continue;
        }

        switch (opcao) {
            case 1:
                menuRelfinanceiro();
                break;
            case 2:
                menuRelCadastros();
                break;
            case 3:
                return;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
}



void menuprincipal() {
    int i = 0;

    while(i != 11) {
        i = 0;

        printf("\n======================================== MENU ========================================\n");
        printf("Menu de opcoes, area a ser trabalhada:\n 1 - Oficina\n 2 - Peças\n 3 - Funcionários\n 4 - Veículos\n 5 - Serviços\n 6 - Clientes\n 7 - Fornecedores\n 8 - Forma de registro\n 9 - Financeiro\n 10 - Relatórios \n 11 - Encerrar operação\nDigite a opcao escolhida:");
        scanf("%d", &i);

        switch (i) {
            case 1:
                menuoficina();
                break;
            case 2:
                menupecas();
                break;
            case 3:
                menuFuncionarios();
                break;
            case 4:
                menuVeiculos();
                break;
            case 5:
                menuServicos();
                break;
            case 6:
                menucliente();
                break;
            case 7:
                menufornecedor();
                break;
            case 8:
                formaregistro();
                break;
            case 9:
                menuFinanceiro();  // Chama o menu financeiro quando o usuário escolher a opção 9
                break;
            case 10:
                menuRelatorios();
                break;
            case 11:
                printf("\n\nOPERACAO ENCERRADA!");
                printf("\n================================================================================\n");
                return;
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
}






//------------------------
int main(){

    formaregistro();
    menuprincipal();
    
    return 0;
}