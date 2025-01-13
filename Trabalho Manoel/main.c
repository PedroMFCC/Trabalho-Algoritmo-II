#include <stdio.h>
#include <stdlib.h>
#include "Liboficina/oficina.h"
#include "Libpecas/pecas.h"
#include "libfuncionarios/funcionarios.h"
#include "libveiculos/veiculos.h"
#include "libservicos/servicos.h"
#include "Libclientes/clientes.h"
#include "Libfornecedor/fornecedor.h"
#include "Libformato/conversor.h"



int formaregistro(){
    int i = 0;
    int formato;

    FILE *ler = fopen("arquivos/formato.bin", "rb");
    fread(&formato, sizeof(int), 1, ler);
    fclose(ler);

    FILE *arq = fopen("arquivos/formato.bin","wb");
    if (arq == NULL){
        printf("Erro na abertura do arquivo!");
        return 1;
    }
    while(i != 3){
        printf("Forma em que os arquivos serao armazenados durante o processo:\n 1 - Binario\n 2 - Texto\nDigite sua opcao:");
        scanf("%d", &i);
        if(formato == i){
            i = 3;
        }
        else{
            switch (i){
                case 1:
                    converteparabin();
                    formato = 1;            
                    i = 3;

                break;

                case 2:
                    converteparatxt();
                    formato = 2;      
                    i = 3;      
                break;

                default:
                    i = 0;
                    printf("Formato não identificado, favor digitar um valor válido!");
                break;
            }
        }   
    }

    fwrite(&formato, sizeof(int), 1, arq);
        
    fclose(arq);
    return 0;
}

void detectaformato(){
    FILE *arq = fopen("arquivos/formato.bin", "rb");
    int formato;
    fread(&formato, sizeof(int), 1, arq);
    if (arq == NULL){
        printf("Erro ao abrir o arquivo de formato. Configure o formato primeiro.\n");
        formaregistro();
        return;
    }
    if(formato != 1 && formato != 2){
        printf("Formato não identificado, favor configurar o formato de registro!\n");
        formaregistro();
    }
    else if(formato == 1){
        printf("Formato de registro: Binario\n");
    }
    else if(formato == 2){
        printf("Formato de registro: Texto\n");
    }
}

void detectaofic(){
    FILE *bin = fopen("arquivos/oficina.bin", "rb");
    FILE *txt = fopen("arquivos/oficina.txt", "r");
    if (bin != NULL || txt != NULL){
        printf("O registro da oficina foi encontrado!\n\n");
        fclose(bin);
        fclose(txt);
        return;
    }
    else{
        printf("\nNenhum registro de oficina foi encontrado!\nPorfavor registre uma oficina!\n\n");
        regoficina();
    }
    fclose(bin);
    fclose(txt);
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

int menuoficina(){
    int i = 0;
    while(i != 6){
    i = 0;

    printf("\n====================================== MENU OFICINA ======================================\n");
    printf("opcoes:\n 1 - Registrar oficina\n 2 - Consultar o arquivo da oficina\n 3 - Editar arquivo da oficina\n 4 - Excluir os dados da oficina\n 5 - Resetar todos os dados relacionados a oficina\n 6 - Cancelar\n digite a opção:");
    scanf("%d", &i);

    
        switch(i){
            case 1:
                regoficina();
            break;

            case 2:
                lerofic();
            break;

            case 3:
                editofic();
            break;

            case 4:
                removerofic();
            break;

            case 5:
                resetofic();
                return 9;
            break;

            case 6:
                printf("\n\noperação cancelada!");
                return 0;
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

    while(i != 6) {
        i = 0;

        printf("\n=========================================== MENU CLIENTE ===========================================\n");
        printf("opções:\n");
        printf("1 - Registrar novo cliente\n");
        printf("2 - Editar cliente já registrado\n");
        printf("3 - Consultar cliente\n");
        printf("4 - Excluir registro de cliente\n");
        printf("5 - Excluir Cliente\n");
        printf("6 - Sair do menu\n");
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
            excluirRegistro();
            break;

        case 5:
            excluirCliente();
            break;

        case 6:
        default:
            printf("\nOperação cancelada!\n");
        }
    }
}

void menuprincipal(){
    int i = 0;

    while(i != 9){
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
            printf("Menu de opcoes, area a ser trabalhada:\n 1 - Oficina\n 2 - Pecas\n 3 - Funcionários\n 4 - Veículos\n 5 - Serviços\n 6 - Clientes\n 7 - Fornecedores\n 8 - Forma de registro\n 9 - Encerrar operacao\nDigite a opcao escolhida:");
        }
        else{
            printf("(!)* - Estoque em falta!\n\nMenu de opcoes, area a ser trabalhada:\n 1 - Oficina\n 2 - Pecas(!)\n 3 - Funcionários\n 4 - Veículos\n 5 - Serviços\n 6 - Clientes\n 7 - Fornecedores\n 8 - Forma de registro\n 9 - Encerrar operacao\nDigite a opcao escolhida:");
        }
        scanf("%d", &i);

        switch (i){
            case 1:
                i = menuoficina();
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
                printf("\n\nOPERACAO ENCERRADA!");
                printf("\n================================================================================\n");
                return;
            break;
        }
    }
}




//------------------------
int main(){

    detectaformato();
    detectaofic();
    menuprincipal();
    
    return 0;
}