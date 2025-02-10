#include <stdio.h>
#include <stdlib.h>
#include "Liboficina/oficina.h"
#include "Libpecas/pecas.h"
#include "libfuncionarios/funcionarios.h"
#include "libveiculos/veiculos.h"
#include "libservicos/servicos.h"
#include "Libclientes/clientes.h"
#include "Libfornecedor/fornecedor.h"
#include "LibAgendamento/agendamento.h"
#include "Librelatorios/relatorios.h"

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

    while(i != 6){
    detectapeca();
    FILE *arq = fopen("arquivos/pecanmin.bin", "rb");
    if (arq == NULL){
        printf("Erro ao abrir o arquivo de peças mínimas!");
        return;
    }

    int nmin;
    
    fread(&nmin, sizeof(int), 1, arq);
    i = 0;

    printf("\n======================================== MENU PEÇAS ========================================\n");
    if(nmin < 1){
        printf("opções:\n 1 - Registrar nova peça\n 2 - Editar peca ja registrada\n 3 - Consultar o arquivo\n 4 - Remover registro\n 5 - Manusear estoque\n 6 - Cancelar\n digite a opção:");
    }
    else{
        printf("(!)* - Estoque em falta!\n\nopções:\n 1 - Registrar nova peça\n 2 - Editar peca ja registrada\n 3 - Consultar o arquivo\n 4 - Remover registro\n 5 - Manusear estoque(!)\n 6 - Cancelar\n digite a opção:");
    }
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
                gerenciarpecasmen();
            break;

            case 6:
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
    int opcao = 0;
    while (opcao != 16) {
        int opcao = 0;
        printf("\n======================================== MENU DE SERVIÇOS ========================================\n");
        printf("1. Registrar Novo Serviço\n");
        printf("2. Editar Serviço Existente\n");
        printf("3. Consultar Serviços\n");
        printf("4. Excluir Serviço\n");
        printf("5. Registrar Novo agendamento:\n");
        printf("6. Editar agendamento já registrado\n");
        printf("7. Consultar agendamento\n");
        printf("8. Excluir agendamento\n");
        printf("9. Consultar Ordem de Serviço\n");
        printf("10. Editar Ordem de Serviço já registrado\n");
        printf("11. Excluir Ordem de Serviço\n");
        printf("12. Registrar Novo Controle de Produtividade\n");
        printf("13. Editar Controle de Produtividade já registrado\n");
        printf("14. Consultar Controle de Produtividade\n");
        printf("15. Excluir Controle de Produtividade\n");
        printf("16. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
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
                RegAgend();
                RegOS();
            break;

            case 6:
                EditAgend();
            break;

            case 7:
                LerAgend();
            break;

            case 8:
                RemoverAgend();
            break;

            case 9:
                LerOS();
            break;
            
            case 10:
                EditOS();
            break;
            
            case 11:
                RemoverOS();
            break;
            
            case 12:
                RegControle();
            break;
            
            case 13:
                EditControle();
            break;
            
            case 14:
                LerControle();
            break;
            
            case 15:
                RemoverControle();
            break;

            case 16:
                return;
                break;
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

void menuRelatorios() {
    int opcao;
    while (1) {
        printf("\n========================== MENU RELATÓRIOS ==========================\n");
        printf("1. Relatórios Financeiros\n");
        printf("2. Relatórios de Produtividade\n");
        printf("3. Relatórios de Serviços Realizados\n");
        printf("4. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n'); 
            printf("Entrada inválida! Tente novamente.\n");
            continue;
        }

        switch (opcao) {
            case 1:
                printf("aa"); 
                break;
            
            case 2:
                RelatorioProd(); 
                break;
            
            case 3:
                RelatorioServ(); 
                break;
            
            case 4:
                return; 
            
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
}

void menuprincipal(){
    int i = 0;

    while(i != 10){
        detectapeca();
        FILE *arq = fopen("arquivos/pecanmin.bin", "rb");
        if (arq == NULL){
           printf("Erro ao abrir o arquivo de peças mínimas!");
           return;
        }

        int nmin;

        fread(&nmin, sizeof(int), 1, arq);

        i = 0;

        printf("\n======================================== MENU ========================================\n");
        if(nmin < 1){
            printf("Menu de opcoes, area a ser trabalhada:\n 1 - Oficina\n 2 - Pecas\n 3 - Funcionários\n 4 - Veículos\n 5 - Serviços\n 6 - Clientes\n 7 - Fornecedores\n 8 - Forma de registro\n 9 - Relatorios\n 10 - Encerrar operacao\nDigite a opcao escolhida:");
        }
        else{
            printf("(!)* - Estoque em falta!\n\nMenu de opcoes, area a ser trabalhada:\n 1 - Oficina\n 2 - Pecas(!)\n 3 - Funcionários\n 4 - Veículos\n 5 - Serviços\n 6 - Clientes\n 7 - Fornecedores\n 8 - Forma de registro\n 9 - Encerrar operacao\nDigite a opcao escolhida:");
        }
        scanf("%d", &i);

        switch (i){
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
                menuRelatorios();
            break;

            case 10:
                printf("\n\nOPERACAO ENCERRADA!");
                printf("\n================================================================================\n");
                return;
            break;
        }
    }
}



//------------------------
int main(){

    formaregistro();
    menuprincipal();
    
    return 0;
}