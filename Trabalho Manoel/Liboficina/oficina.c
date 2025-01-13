#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "oficina.h"

int confereofic(){
    FILE *bin = fopen("arquivos/oficina.bin", "rb");
    FILE *txt = fopen("arquivos/oficina.txt", "r");
    if (bin != NULL || txt != NULL){
        printf("Já existe um registro de oficina!\n");
        fclose(bin);
        fclose(txt);
        return 1;
    }
    fclose(bin);
    fclose(txt);
}
//Função de registro da oficina em binário
void regoficinabin(dadooficina oficina){
    //Abre o arquivo referente
    FILE *bin = fopen("arquivos/oficina.bin", "ab");
    if(bin == NULL){
        printf("Erro ao abrir o arquivo!");
        return;
    }

    fwrite(&oficina, sizeof(dadooficina), 1, bin);

    fclose(bin);
}
//Função de registro da oficina em texto
void regoficinatxt(dadooficina oficina){
    FILE *txt = fopen("arquivos/oficina.txt", "a");
    if(txt == NULL){
        printf("erro ao abrir  arquivo!");
        return;
    }

    fprintf(txt,
    "%s\n%s\n%s\n%s\n%s\n%f\n",
    oficina.nomeofic, oficina.cnpjofic, oficina.ruaofic, oficina.telefofic, oficina.emailofic, oficina.lucro);

    fclose(txt);
}
//Função de definição do formato a ser seguido
void regoficinapath(dadooficina oficina){
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    FILE *lucro = fopen("arquivos/lucro.bin", "wb");

    if(formatoArq == NULL){
        printf("erro formato reg");
        return;
    }
    if(lucro == NULL){
        printf("erro lucro reg");
        return;
    }
    
    

    fread(&formatoReg, sizeof(int), 1, formatoArq);
    fwrite(&oficina.lucro, sizeof(float), 1, lucro);
    

    if (formatoReg == 1){
        regoficinabin(oficina);
    }
    else{
        regoficinatxt(oficina);
    }

    fclose(formatoArq);
    fclose(lucro);
}
//Função para receber o valor das variáveis
void regoficina(){

    if (confereofic() == 1){
        return;
    }
    

    dadooficina oficina;

    printf("\nInsira o nome da oficina: ");
    scanf(" %39[^\n]", oficina.nomeofic);
    getchar();
    printf("Insira o CNPJ da oficina: ");
    scanf(" %19[^\n]", oficina.cnpjofic);
    getchar();
    printf("Insira o endereço da oficina: ");
    scanf(" %49[^\n]", oficina.ruaofic);
    getchar();
    printf("Insira o telefone da oficina: ");
    scanf(" %21[^\n]", oficina.telefofic);
    getchar();
    printf("Insira o e-mail da oficina: ");
    scanf(" %39[^\n]", oficina.emailofic);
    getchar();
    printf("Insira a porcentagem almejada de lucro em valor inteiro (%%): ");
    scanf("%f", &oficina.lucro);
    getchar();
       

    regoficinapath(oficina);
}


//Função de leitura da oficina em binário
void leroficbin(){
    dadooficina ofic;
    FILE *bin = fopen("arquivos/oficina.bin", "rb");
    if (bin == NULL){
        printf("erro lerbin");
        return;
    }
        printf("================================= Consulta da Oficina =================================\n");
    while (fread(&ofic, sizeof(dadooficina), 1, bin)) {
        printf("Nome da Oficina: %s\nCNPJ: %s\nRua da oficina: %s\nTelefome: %s\nEmail: %s\nLucro estimado: %.2f%%",
        ofic.nomeofic, ofic.cnpjofic, ofic.ruaofic, ofic.telefofic, ofic.emailofic, ofic.lucro);
    }

    fclose(bin);
}
//Função de leitura da oficina em texto
void lerofictxt(){
    dadooficina ofic;
    FILE *txt = fopen("arquivos/oficina.txt", "r");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo texto!\n");
        return;
    } 

    while (fscanf(txt, "%39[^\n]\n%19[^\n]\n%49[^\n]\n%21[^\n]\n%39[^\n]\n%f\n", 
    ofic.nomeofic, ofic.cnpjofic, ofic.ruaofic, ofic.telefofic, ofic.emailofic, &ofic.lucro) == 6) {
        printf("================================== Consulta da Oficina ==================================\n");
        printf("Nome da Oficina: %s\n", ofic.nomeofic);
        printf("CNPJ: %s\n", ofic.cnpjofic);
        printf("Rua da Oficina: %s\n", ofic.ruaofic);
        printf("Telefone: %s\n", ofic.telefofic);
        printf("Email: %s\n", ofic.emailofic);
        printf("Lucro Estimado: %.2f%%\n", ofic.lucro);
    }

    fclose(txt);
}
//função de definição de formato
void lerofic(){
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL){
        printf("Erro na interpretação do formato do arquivo!");
        return;
    }
    fread(&formatoReg, sizeof(int), 1, formatoArq);
    
    if (formatoReg == 1){
        leroficbin();
    }
    else{
        lerofictxt();
    }

    fclose(formatoArq);
}

void resetofic(){
    
    char a;
    int formato;
    FILE *bin = fopen("arquivos/formato.bin", "rb");
    if (bin == NULL){
        printf("Erro ao abrir o arquivo de formato!");
        return;
    }

    fread(&formato, sizeof(int), 1, bin);

    fclose (bin);

    printf("Deseja realmente resetar o arquivo da oficina?\nNote que isso resetará todo o sistema da oficina, como registros e configurações\nO Programa também será fechado\n(S/N): ");
    scanf(" %c", &a);

    switch (a)
    {
        case 'S': case 's':           

            remove("arquivos/lucro.bin");
            remove("arquivos/formato.bin");
            if(formato == 1){
                remove("arquivos/oficina.bin");
                remove("arquivos/pecas.bin");
                remove("arquivos/servicos.bin");
                remove("arquivos/funcionarios.bin");
                remove("arquivos/veiculos.bin");
                remove("arquivos/clientes.bin");
                remove("arquivos/fornecedores.bin");
            }
            else if(formato == 2){
                remove("arquivos/oficina.txt");
                remove("arquivos/pecas.txt");
                remove("arquivos/servicos.txt");
                remove("arquivos/funcionarios.txt");
                remove("arquivos/veiculos.txt");
                remove("arquivos/clientes.txt");
                remove("arquivos/fornecedores.txt");
            }
            else{
                printf("Erro ao identificar os arquivos!");
                return;
            }

        
            printf("Oficina resetada com sucesso!\n");
        break;
    
        case 'N': case 'n':
        return;
        break;
    }
}

void editofic(){
    remove("arquivos/oficina.bin");
    remove("arquivos/oficina.txt");

    dadooficina oficina;

    printf("\nInsira o nome da oficina: ");
    scanf(" %39[^\n]", oficina.nomeofic);
    getchar();
    printf("Insira o CNPJ da oficina: ");
    scanf(" %19[^\n]", oficina.cnpjofic);
    getchar();
    printf("Insira o endereço da oficina: ");
    scanf(" %49[^\n]", oficina.ruaofic);
    getchar();
    printf("Insira o telefone da oficina: ");
    scanf(" %21[^\n]", oficina.telefofic);
    getchar();
    printf("Insira o e-mail da oficina: ");
    scanf(" %39[^\n]", oficina.emailofic);
    getchar();
    printf("Insira a porcentagem almejada de lucro em valor inteiro (%%): ");
    scanf("%f", &oficina.lucro);
    getchar();

    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL){
        printf("Erro na interpretação do formato do arquivo!");
        return;
    }
    fread(&formatoReg, sizeof(int), 1, formatoArq);
    
    if (formatoReg == 1){
        regoficinabin(oficina);
    }
    else{
        regoficinatxt(oficina);
    }

    fclose(formatoArq);
}


void removeroficbin(){
    remove("arquivos/oficina.bin");
    printf("Arquivo da oficina removido com sucesso!\n");
}
void removerofictxt(){
    remove("arquivos/oficina.txt");
    printf("Arquivo da oficina removido com sucesso!\n");
}
void removerofic(){
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL){
        printf("Erro na interpretação do formato do arquivo!");
        return;
    }
    fread(&formatoReg, sizeof(int), 1, formatoArq);
    
    if (formatoReg == 1){
        removeroficbin();
    }
    else{
        removerofictxt();
    }

    fclose(formatoArq);
}   