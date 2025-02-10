#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pecas.h"

//Subrotina para o cálculo de preço da venda de peça


//Subrotina para registro em binário
void regpecabin(dadopec peca){ 
    FILE *bin = fopen("arquivos/peca.bin", "ab");
    if(bin == NULL){
        printf("Erro ao abrir o arquivo! regbin");
        return;
    }

    fwrite(&peca, sizeof(dadopec), 1, bin);

    fclose(bin);
}
//Subrotina para registro em texto
void regpecatxt(dadopec peca){
    FILE *txt = fopen("arquivos/peca.txt", "a");
    if(txt == NULL){
        printf("erro ao abrir  arquivo! regtxt");
        return;
    }

    fprintf(txt,
    "%d, %s, %s, %s, %s, %f, %f, %d, %d\n",
    peca.codpec, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, peca.custpeca, peca.vendpeca, peca.npeca, peca.minpeca);


    fclose(txt);
    printf("Peça registrada com sucesso!");
}
//Subrotina para encaminhar os dados das variáveis para as formas de registro disponíveis
void regpecapath(dadopec peca){
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL){
        printf("Erro na interpretação do formato do arquivo!");
        return;
    }
    fread(&formatoReg, sizeof(int), 1, formatoArq);

    //separa entre os formatos definidos no arquivo de formato
    if (formatoReg == 1){
        regpecabin(peca);
    }
    else{
        regpecatxt(peca);
    }

    fclose(formatoArq);
}
//Subrotina para registro das variáveis
void regpeca(){
    dadopec peca;
    
    printf("\nInsira o código da peça:");
    scanf("%d", &peca.codpec);
    getchar();
    printf("Insira o nome da peça:");
    scanf("%19[^\n]", peca.nomepec);
    getchar();
    printf("Insira uma descrição breve da peça:");
    scanf("%59[^\n]", peca.descpec);
    getchar();
    printf("Insira o Fabricante das peças:");
    scanf("%29[^\n]", peca.fabpec);
    getchar();
    printf("Insira o Fornecedor das peças:");
    scanf("%29[^\n]", peca.fornpec);
    getchar();
    printf("Insira o custo das peças em R$:");
    scanf("%f", &peca.custpeca);

    peca.vendpeca = 0;

    peca.npeca = 0;

    printf("Insira o número mínimo que essa peça deve ter em estoque:");
    scanf("%d", &peca.minpeca);
    getchar();

    printf("\n----------------\nAcesse './pecas/manusear estoque/registrar compra' para adicionar suas pecas ao estoque\n----------------\n");

    regpecapath(peca);
}


void addpecasbin(){
    int codBusca;
    int npeca;
    char o = 's';
    int encontrado = 0;

    FILE *bin = fopen("arquivos/peca.bin", "rb");
    if (bin == NULL) {
        printf("Erro ao abrir o arquivo para conferir dados atuais\n");
        return;
    }

    FILE *temp = fopen("arquivos/temp.bin", "wb");
    if (temp == NULL) {
        printf("Erro ao carregar o arquivo de adição das peças\n");
        fclose(bin);
        return;
    }

    FILE *nota = fopen("arquivos/notafiscal.bin", "ab");
    if (nota == NULL) {
        printf("Erro ao abrir o arquivo de nota fiscal!\n");
        return;
    }

    notafisc peca2;
    dadopec peca;

    printf("Digite o código da peça que deseja registrar a compra: ");
    scanf("%d", &codBusca);

    rewind (bin);
    encontrado=0;

    while (fread(&peca, sizeof(dadopec), 1, bin)) { 
        if (peca.codpec == codBusca) {
            encontrado = 1;
            printf("Insira a quantia de peças de código %d que foram adquiridas:", peca.codpec);
            scanf("%d", &npeca);
            peca.npeca += npeca;

            peca2.codpec = peca.codpec;
            peca2.npeca = npeca;
            strcpy(peca2.nomepec, peca.nomepec);
            peca2.custpeca = peca.custpeca;+

            fwrite(&peca2, sizeof(notafisc), 1, nota);
        }
        fwrite(&peca, sizeof(dadopec), 1, temp);
            
    }
    if(encontrado == 0){
        printf("Peça com código %d não encontrada!\n", codBusca);
    }
    
    fclose(bin);
    fclose(temp);
    fclose(nota);

    if (encontrado) {
        remove("arquivos/peca.bin");
        rename("arquivos/temp.bin", "arquivos/peca.bin");
        printf("Peças adiquiridas com sucesso!\n");
    } else {
        remove("arquivos/temp.bin");
    }

    
}
void addpecastxt(){
    int codBusca;
    int npeca;
    char o = 's';
    int encontrado = 0;

    FILE *txt = fopen("arquivos/peca.txt", "r");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo para conferir dados atuais\n");
        return;
    }

    FILE *temp = fopen("arquivos/temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao carregar o arquivo de adição das peças\n");
        fclose(txt);
        return;
    }

    FILE *nota = fopen("arquivos/notafiscal.bin", "ab");
    if (nota == NULL) {
        printf("Erro ao abrir o arquivo de nota fiscal!\n");
        return;
    }

    notafisc peca2;
    dadopec peca;

    printf("Digite o código da peça que deseja registrar a compra: ");
    scanf("%d", &codBusca);

    rewind (txt);
    encontrado=0;

    while (fscanf(txt, 
                "%d, %19[^,], %59[^,], %29[^,], %29[^,], %f, %f, %d, %d\n", 
                &peca.codpec, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, 
                &peca.custpeca, &peca.vendpeca, &peca.npeca, &peca.minpeca) == 9) { 
        if (peca.codpec == codBusca) {
            encontrado = 1;
            printf("Insira a quantia de peças de código %d que foram adquiridas:", peca.codpec);
            scanf("%d", &npeca);
            peca.npeca += npeca;

            peca2.codpec = peca.codpec;
            peca2.npeca = npeca;
            strcpy(peca2.nomepec, peca.nomepec);
            peca2.custpeca = peca.custpeca;+

            fwrite(&peca2, sizeof(notafisc), 1, nota);
        }
        fprintf(temp,
            "%d, %s, %s, %s, %s, %f, %f, %d, %d\n",
            peca.codpec, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, 
            peca.custpeca, peca.vendpeca, peca.npeca, peca.minpeca);
            
    }
    if(encontrado == 0){
        printf("Peça com código %d não encontrada!\n", codBusca);
    }
    
    fclose(txt);
    fclose(temp);
    fclose(nota);

    if (encontrado) {
        remove("arquivos/peca.txt");
        rename("arquivos/temp.txt", "arquivos/peca.txt");
        printf("Peças adiquiridas com sucesso!\n");
    } else {
        remove("arquivos/temp.txt");
    }
}
void addpecas(){
    int formato;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL){
        printf("Erro na interpretação do formato do arquivo!");
        return;
    }
    fread(&formato, sizeof(int), 1, formatoArq);

    if (formato == 1){
        addpecasbin();
    }
    else{
        addpecastxt();
    }
}

void rempecasbin(){
    int codBusca;
    int npeca;
    int encontrado = 0;

    FILE *bin = fopen("arquivos/peca.bin", "rb");
    if (bin == NULL) {
        printf("Erro ao abrir o arquivo para conferir dados atuais\n");
        return;
    }

    FILE *temp = fopen("arquivos/temp.bin", "wb");
    if (temp == NULL) {
        printf("Erro ao carregar o arquivo de venda das peças\n");
        fclose(bin);
        return;
    }

    dadopec peca;

    printf("Digite o código da peça que deseja registrar a venda: ");
    scanf("%d", &codBusca);

    while (fread(&peca, sizeof(dadopec), 1, bin)) { 
        if (peca.codpec == codBusca) {
            encontrado = 1;
            printf("Insira a quantia de peças de código %d que foram adquiridas:", peca.codpec);
            scanf("%d", &npeca);
            peca.npeca -= npeca;
        }
        fwrite(&peca, sizeof(dadopec), 1, temp);
            
    }
    if(encontrado == 0){
        printf("Peça com código %d não encontrada!\n", codBusca);
    }
    
    fclose(bin);
    fclose(temp);

    if (encontrado) {
        remove("arquivos/peca.bin");
        rename("arquivos/temp.bin", "arquivos/peca.bin");
        printf("Peças retiradas com sucesso!\n");
    } else {
        remove("arquivos/temp.bin");
    }
}
void rempecastxt(){
    int codBusca;
    int npeca;
    int encontrado = 0;

    FILE *txt = fopen("arquivos/peca.txt", "r");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo para conferir dados atuais\n");
        return;
    }

    FILE *temp = fopen("arquivos/temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao carregar o arquivo de venda das peças\n");
        fclose(txt);
        return;
    }

    dadopec peca;

    printf("Digite o código da peça que deseja registrar a venda: ");
    scanf("%d", &codBusca);


    while (fscanf(txt, 
                "%d, %19[^,], %59[^,], %29[^,], %29[^,], %f, %f, %d, %d\n", 
                &peca.codpec, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, 
                &peca.custpeca, &peca.vendpeca, &peca.npeca, &peca.minpeca) == 9) { 
        if (peca.codpec == codBusca) {
            encontrado = 1;
            printf("Insira a quantia de peças de código %d que foram adquiridas:", peca.codpec);
            scanf("%d", &npeca);
            peca.npeca -= npeca;
        }
        fprintf(temp,
            "%d, %s, %s, %s, %s, %f, %f, %d, %d\n",
            peca.codpec, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, 
            peca.custpeca, peca.vendpeca, peca.npeca, peca.minpeca);
            
    }
    if(encontrado == 0){
        printf("Peça com código %d não encontrada!\n", codBusca);
    }
    
    fclose(txt);
    fclose(temp);

    if (encontrado) {
        remove("arquivos/peca.txt");
        rename("arquivos/temp.txt", "arquivos/peca.txt");
        printf("Peças retiradas com sucesso!\n");
    } else {
        remove("arquivos/temp.txt");
    }
}
void rempecas(){
    int formato;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL){
        printf("Erro na interpretação do formato do arquivo!");
        return;
    }
    fread(&formato, sizeof(int), 1, formatoArq);

    if (formato == 1){
        rempecasbin();
    }
    else{
        rempecastxt();
    }
}

void gerenciarpecasmen(){
    int i = 0;
    char o = 's';
    int formato;
    
    FILE *formatoarq = fopen("arquivos/formato.bin", "rb");
    if (formatoarq == NULL){
        printf("erro ao identificar formato!");
        fclose(formatoarq);
        return;
    }
    fread(&formato, sizeof(int), 1, formatoarq);
    fclose(formatoarq);
    while(i != 4){
        char o = 's';
        detectapeca();
        FILE *arq = fopen("arquivos/pecanmin.bin", "rb");
        if (arq == NULL){
            printf("Erro ao abrir o arquivo de peças mínimas!");
            fclose(arq);
            return;
        }
        

        int nmin;

        fread(&nmin, sizeof(int), 1, arq);
        fclose(arq);
        int i = 0;

            printf("\n======================================== MENU GERENCIAR PEÇAS ========================================\n");
        if(nmin == 0){
            printf("opcoes:\n 1 - Registrar compra de pecas ao estoque\n 2 - Registrar venda de peças do estoque\n 3 - Consultar estoque\n 4 - Cancelar\n digite a opção:");
        }
        else{
            printf("(!)* - Estoque em falta!\n\nopcoes:\n 1 - Adicionar peças ao estoque\n 2 - Remover peças do estoque\n 3 - Consultar estoque(!)\n 4 - Cancelar\n digite a opção:");
        }
            scanf("%d", &i);


        switch(i){
            case 1:
                while(o != 'n' && o != 'N'){
                    addpecas();
                    printf("Deseja adicionar outras peças ao estoque?\nAs pecas adiconadas serao registradas na notafiscal desta opeeracaos\n(s/n): ");
                    scanf(" %c", &o);
                }
                if(formato == 1){
                    notafiscalbin();
                    remove("arquivos/notafiscal.bin");
                }
                else if(formato == 2){
                    notafiscaltxt();
                    remove("arquivos/notafiscal.txt");
                }
            break;

            case 2:
                rempecas();
            break;

            case 3:
                lerpeca();
            break;

            case 4:
                printf("\n\noperação cancelada!");
                return;
            break;
        }
    }
}

void notafiscalbin(){
    char forn[50]; //provisório
    float frete; //provisório
    char cnpj[19]; //provisório
    float imposto; //provisório
    int quantsup = 0;
    float precgeral = 0;
    FILE* nota = fopen("arquivos/notafiscal.bin", "rb");
    if (nota == NULL){
        printf("Erro ao abrir o arquivo de nota fiscal!");
        fclose(nota);
        return;
    }
    FILE* notabin = fopen("arquivos/peca.bin", "rb");
    if (notabin == NULL){
        printf("Erro ao abrir o arquivo de peças!");
        fclose(nota);
        fclose(notabin);
        return;
    }
    FILE* notatemp = fopen("arquivos/temp.bin", "wb");
    if (notatemp == NULL){
        printf("Erro ao criar o arquivo temporário!");
        fclose(nota);
        fclose(notabin);
        fclose(notatemp);
        return;
    }
    FILE *lucroarq = fopen("arquivos/lucro.bin", "rb");
    if (lucroarq == NULL){
        printf("Erro ao abrir o arquivo de lucro!");
        fclose(nota);
        fclose(notabin);
        fclose(notatemp);
        fclose(lucroarq);
        return;
    }
    float lucro;
    fread(&lucro, sizeof(float), 1, lucroarq);
    fclose(lucroarq);
    dadopec peca;
    notafisc peca2;
    
    getchar();
    printf("Insira o nome do fornecedor: "); //provisório
    scanf("%49[^\n]", forn); //provisório
    getchar();
    printf("Insira o CNPJ do fornecedor: "); //provisório
    scanf("%19[^\n]", cnpj);    //provisório
    getchar();
    printf("Insira o valor do frete: "); //provisório
    scanf("%f", &frete);   //provisório
    printf("Insira o valor do imposto: "); //provisório
    scanf("%f", &imposto); //provisório
    getchar();
    

    printf("===================================== Nota Fiscal =====================================\n");
    printf("Fornecedor: %s\n", forn);
    printf("CNPJ: %s\n", cnpj);
    printf("Frete: %.2f  |", frete); printf("Imposto: %.2f\n", imposto);
    printf("------------------------------ Produtos ------------------------------\n");
    printf("Nome da peça            | Custo unitário      | Quantidade    | Valor total\n");
    while (fread(&peca2, sizeof(notafisc), 1, nota)) {
        printf("Nome da peça: %s  |", peca2.nomepec);printf("Custo unitário: %.2f  |", peca2.custpeca);printf("Quantidade: %d  |", peca2.npeca);printf("Valor total: %.2f\n", peca2.custpeca * peca2.npeca);       
        quantsup += peca2.npeca;
        precgeral += peca2.custpeca * peca2.npeca;
    }
    precgeral += imposto + frete;
    imposto = imposto/quantsup;
    frete = frete/quantsup;
    printf("------------------------------\n");
    printf("Valor total da compra: %.2f\n", precgeral);
    printf("==============================\n");
    rewind(nota);
    int cont = 0;
    while(fread(&peca, sizeof(dadopec), 1, notabin)){
        rewind (nota);
        while(fread(&peca2, sizeof(notafisc), 1, nota)){                  
            if(peca.codpec == peca2.codpec){
                peca.vendpeca = peca2.custpeca + imposto + frete;
                peca.vendpeca = peca.vendpeca + (peca.vendpeca * (lucro/100));
                cont = 1;
                break;
            }
        }
        if(cont == 1){            
            printf("Nome da peça: %s  |", peca.nomepec);printf("Custo unitário: %.2f  |", peca.custpeca);printf("Frete: %.2f  |", frete);printf("Imposto: %.2f  |", imposto);
            printf("Lucro: %.2f  |",(peca.vendpeca - (peca2.custpeca + imposto + frete))); printf("Preço de venda: %.2f\n", peca.vendpeca);
            fwrite(&peca, sizeof(dadopec), 1, notatemp);
        }
        else{
            fwrite(&peca, sizeof(dadopec), 1, notatemp);
        }
        
        cont = 0;
    }
    
    
    printf("=====================================\n");

    fclose(nota);
    fclose(notatemp);
    fclose(notabin);

    remove("arquivos/peca.bin");
    rename("arquivos/temp.bin", "arquivos/peca.bin");
}
void notafiscaltxt(){
    char forn[50]; //provisório
    float frete; //provisório
    char cnpj[19]; //provisório
    float imposto; //provisório
    int quantsup = 0;
    float precgeral = 0;
    FILE* nota = fopen("arquivos/notafiscal.bin", "rb");
    if (nota == NULL){
        printf("Erro ao abrir o arquivo de nota fiscal!");
        fclose(nota);
        return;
    }
    FILE* notatxt = fopen("arquivos/peca.txt", "r");
    if (notatxt == NULL){
        printf("Erro ao abrir o arquivo de peças!");
        fclose(nota);
        fclose(notatxt);
        return;
    }
    FILE* notatemp = fopen("arquivos/temp.txt", "w");
    if (notatemp == NULL){
        printf("Erro ao criar o arquivo temporário!");
        fclose(nota);
        fclose(notatxt);
        fclose(notatemp);
        return;
    }
    FILE *lucroarq = fopen("arquivos/lucro.bin", "rb");
    if (lucroarq == NULL){
        printf("Erro ao abrir o arquivo de lucro!");
        fclose(nota);
        fclose(notatxt);
        fclose(notatemp);
        fclose(lucroarq);
        return;
    }
    float lucro;
    fread(&lucro, sizeof(float), 1, lucroarq);
    fclose(lucroarq);
    dadopec peca;
    notafisc peca2;
    
    getchar();
    printf("Insira o nome do fornecedor: "); //provisório
    scanf("%49[^\n]", forn); //provisório
    getchar();
    printf("Insira o CNPJ do fornecedor: "); //provisório
    scanf("%19[^\n]", cnpj);    //provisório
    getchar();
    printf("Insira o valor do frete: "); //provisório
    scanf("%f", &frete);   //provisório
    printf("Insira o valor do imposto: "); //provisório
    scanf("%f", &imposto); //provisório
    getchar();
    

    printf("===================================== Nota Fiscal =====================================\n");
    printf("Fornecedor: %s\n", forn);
    printf("CNPJ: %s\n", cnpj);
    printf("Frete: %.2f  |", frete); printf("Imposto: %.2f\n", imposto);
    printf("------------------------------ Produtos ------------------------------\n");
    printf("Nome da peça            | Custo unitário      | Quantidade    | Valor total\n");
    while (fread(&peca2, sizeof(notafisc), 1, nota)){
        printf("Nome da peça: %s  |", peca2.nomepec);printf("Custo unitário: %.2f  |", peca2.custpeca);printf("Quantidade: %d  |", peca2.npeca);printf("Valor total: %.2f\n", peca2.custpeca * peca2.npeca);       
        quantsup += peca2.npeca;
        precgeral += peca2.custpeca * peca2.npeca;
    }
    precgeral += imposto + frete;
    imposto = imposto/quantsup;
    frete = frete/quantsup;
    printf("------------------------------\n");
    printf("Valor total da compra: %.2f\n", precgeral);
    printf("==============================\n");
    int cont = 0;
    while(fscanf(notatxt,"%d, %19[^,], %59[^,], %29[^,], %29[^,], %f, %f, %d, %d\n", 
            &peca.codpec, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, 
            &peca.custpeca, &peca.vendpeca, &peca.npeca, &peca.minpeca) == 9)
        {
            rewind(nota);
        while(fread(&peca2, sizeof(notafisc), 1, nota)){
                if(peca.codpec == peca2.codpec){
                peca.vendpeca = peca2.custpeca + imposto + frete;
                peca.vendpeca = peca.vendpeca + (peca.vendpeca * (lucro/100));
                cont = 1;
                break;
            }
        }
        if(cont == 1){            
            printf("Nome da peça: %s  |", peca.nomepec);printf("Custo unitário: %.2f  |", peca.custpeca);printf("Frete: %.2f  |", frete);printf("Imposto: %.2f  |", imposto);
            printf("Lucro: %.2f  |",(peca.vendpeca - (peca2.custpeca + imposto + frete))); printf("Preço de venda: %.2f\n", peca.vendpeca);
            fprintf(notatemp,
                    "%d, %s, %s, %s, %s, %f, %f, %d, %d\n",
                    peca.codpec, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, 
                    peca.custpeca, peca.vendpeca, peca.npeca, peca.minpeca);
        }
        else{
            fprintf(notatemp,
                    "%d, %s, %s, %s, %s, %f, %f, %d, %d\n",
                    peca.codpec, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, 
                    peca.custpeca, peca.vendpeca, peca.npeca, peca.minpeca);
        }
        
        cont = 0;
    }
    
    printf("=====================================\n");

    fclose(nota);
    fclose(notatemp);
    fclose(notatxt);

    remove("arquivos/peca.txt");
    rename("arquivos/temp.txt", "arquivos/peca.txt");
}

//Subrotina para edição de peças em binário
void editpecabin(){
    int codBusca;
    printf("Digite o código da peça que deseja editar: ");
    scanf("%d", &codBusca);

    FILE *bin = fopen("arquivos/peca.bin", "rb");
    if (bin == NULL) {
        printf("Erro ao abrir o arquivo binário para leitura!\n");
        return;
    }

    FILE *temp = fopen("arquivos/temp.bin", "wb");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(bin);
        return;
    }

    dadopec peca;
    int encontrado = 0;


    //função que separa o arquivo localizado para edição
    while (fread(&peca, sizeof(dadopec), 1, bin)) { 
        if (peca.codpec == codBusca) {
            encontrado = 1;
                printf("\nInsira o novo código da peça:");
                scanf("%d", &peca.codpec);
                getchar();
                printf("Insira o novo nome da peça:");
                scanf("%19[^\n]", peca.nomepec);
                getchar();
                printf("Insira uma n descrição breve da peça:");
                scanf("%59[^\n]", peca.descpec);
                getchar();
                printf("Insira o novo Fabricante das peças:");
                scanf("%29[^\n]", peca.fabpec);
                getchar();
                printf("Insira o novo Fornecedor das peças:");
                scanf("%29[^\n]", peca.fornpec);
                getchar();
                printf("Insira o novo custo das peças em R$:");
                scanf("%f", &peca.custpeca);
                printf("Insira o novo número mínimo que essa peça deve ter em estoque:");
                scanf("%d", &peca.minpeca);
                getchar();

            //----------------------
                peca.npeca = 0;
                peca.vendpeca = 0;
            //----------------------

        }
        //Registra as variáveis modificadas ou não no arquivo temporário
        fwrite(&peca, sizeof(dadopec), 1, temp);
    }

    fclose(bin);
    fclose(temp);

    //processo de mudança do arquivo temporário para o principal
    if (encontrado) {
        remove("arquivos/peca.bin");
        rename("arquivos/temp.bin", "arquivos/peca.bin");
        printf("Peça editada com sucesso!\n");
    } else {
        remove("arquivos/temp.bin");
        printf("Peça com código %d não encontrada!\n", codBusca);
    }
}
//Subrotina para edição de peças em texto
void editpecatxt(){
    int codBusca;
    printf("Digite o código da peça que deseja editar: ");
    scanf("%d", &codBusca);

    FILE *txt = fopen("arquivos/peca.txt", "r");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo texto para leitura!\n");
        return;
    }

    FILE *temp = fopen("arquivos/temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(txt);
        return;
    }

    dadopec peca;
    int encontrado = 0;

    //função que separa o arquivo localizado para edição
    while (fscanf(txt, 
                "%d, %19[^,], %59[^,], %29[^,], %29[^,], %f, %f, %d, %d\n", 
                &peca.codpec, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, 
                &peca.custpeca, &peca.vendpeca, &peca.npeca, &peca.minpeca) == 9) {
        if (peca.codpec == codBusca) {
            encontrado = 1;

            printf("\nInsira o novo código da peça:");
            scanf("%d", &peca.codpec);
            getchar();
            printf("Insira o novo nome da peça:");
            scanf("%19[^\n]", peca.nomepec);
            getchar();
            printf("Insira uma nova descrição breve da peça:");
            scanf("%59[^\n]", peca.descpec);
            getchar();
            printf("Insira o novo Fabricante das peças:");
            scanf("%29[^\n]", peca.fabpec);
            getchar();
            printf("Insira o novo Fornecedor das peças:");
            scanf("%29[^\n]", peca.fornpec);
            getchar();
            printf("Insira o novo custo das peças em R$:");
            scanf("%f", &peca.custpeca);
            printf("Insira o novo número mínimo que essa peça deve ter em estoque:");
            scanf("%d", &peca.minpeca);
            getchar();

            peca.npeca = 0;
            peca.vendpeca = 0;

            // Salvar peça atualizada no arquivo temporário
            fprintf(temp,
                    "%d, %s, %s, %s, %s, %f, %f, %d, %d\n",
                    peca.codpec, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, 
                    peca.custpeca, peca.vendpeca, peca.npeca, peca.minpeca);
        }
    }

    fclose(txt);
    fclose(temp);


    //processo de mudança do arquivo temporário para o principal
    if (encontrado) {
        remove("arquivos/peca.txt");
        rename("arquivos/temp.txt", "arquivos/peca.txt");
        printf("Peça editada com sucesso!\n");
    } else {
        remove("arquivos/temp.txt");
        printf("Peça com código %d não encontrada!\n", codBusca);
    }
}
//Subrotina para encaminhar o tipo de edição a ser realizada
void editpeca(){
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL){
        printf("Erro na interpretação do formato do arquivo!");
        return;
    }
    fread(&formatoReg, sizeof(int), 1, formatoArq);

    //separa entre os formatos definidos no arquivo de formato
    if (formatoReg == 1){
        editpecabin();
    }
    else{
        editpecatxt();
    }

    fclose(formatoArq);
}


//Subrotina para leitura dos dados em binário
void lerpecabin(){
    dadopec peca;
    FILE *bin = fopen("arquivos/peca.bin", "rb");
    if (bin == NULL){
        printf("erro lerbin");
        return;
    }
    
    //função de leitura do arquivo
    printf("===================================== Lista de Peças =====================================\n");
    while (fread(&peca, sizeof(dadopec), 1, bin)) {
        if(peca.npeca < peca.minpeca){
            printf("\n*ESTOQUE LIMITADO\n\nCodigo: %d\nNome: %s\nDescrição: %s\nFabricante: %s\nFornecedor: %s \nCusto: %.2f \nVenda: %.2f \n-------\nUnidades Disponiveis: %d(!)\nQuantidade Mínima: %d(!)",
         peca.codpec, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, peca.custpeca, peca.vendpeca, peca.npeca, peca.minpeca);
        }
        else{
            printf("\nCodigo: %d\nNome: %s\nDescrição: %s\nFabricante: %s\nFornecedor: %s \nCusto: %.2f \nVenda: %.2f \nUnidades Disponiveis: %d\nQuantidade Mínima: %d",
         peca.codpec, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, peca.custpeca, peca.vendpeca, peca.npeca, peca.minpeca);
        }
        
         printf("\n--------------------------------------------------------------------------------------\n");
    }
    
    fclose(bin);

}
//Subrotina para leitura dos dados em texto
void lerpecatxt(){
    dadopec peca;
    FILE *txt = fopen("arquivos/peca.txt", "r");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo texto!\n");
        return;
    }

    //função de leitura do arquivo
    printf("===================================== Lista de Peças =====================================\n");
    while (fscanf(txt, "%d, %19[^,], %59[^,], %29[^,], %29[^,], %f, %f, %d, %d\n", 
                   &peca.codpec, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, 
                   &peca.custpeca, &peca.vendpeca, &peca.npeca, &peca.minpeca) == 9) {
        if(peca.npeca < peca.minpeca){
            printf("Código da peça: %d\n", peca.codpec);
            printf("Nome da peça: %s\n", peca.nomepec);
            printf("Descrição: %s\n", peca.descpec);
            printf("Fabricante: %s\n", peca.fabpec);
            printf("Fornecedor: %s\n", peca.fornpec);
            printf("Custo: R$ %.2f\n", peca.custpeca);
            printf("Preço de venda: R$ %.2f\n", peca.vendpeca);
            printf("-------\n");
            printf("Estoque disponível: %d\n", peca.npeca);
            printf("Estoque mínimo: %d\n", peca.minpeca);
        }
        else{
            printf("Código da peça: %d\n", peca.codpec);
            printf("Nome da peça: %s\n", peca.nomepec);
            printf("Descrição: %s\n", peca.descpec);
            printf("Fabricante: %s\n", peca.fabpec);
            printf("Fornecedor: %s\n", peca.fornpec);
            printf("Custo: R$ %.2f\n", peca.custpeca);
            printf("Preço de venda: R$ %.2f\n", peca.vendpeca);
            printf("Estoque disponível: %d\n", peca.npeca);
            printf("Estoque mínimo: %d\n", peca.minpeca);
        }
        printf("--------------------------------------------------------------------------------------\n");
    }

    fclose(txt);
}
//Subrotina para encaminhar o tipo de leitura a ser realizada
void lerpeca(){
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL){
        printf("Erro na interpretação do formato do arquivo!");
        return;
    }
    fread(&formatoReg, sizeof(int), 1, formatoArq);

    //separa entre os formatos definidos no arquivo de formato
    if (formatoReg == 1){
        lerpecabin();
    }
    else{
        lerpecatxt();
    }

    fclose(formatoArq);
}


//Subrotina para remover dados em binário
void removerpecatxt(){
    int codBusca;
    printf("Digite o código da peça que deseja remover: ");
    scanf("%d", &codBusca);

    FILE *txt = fopen("arquivos/peca.txt", "r");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo texto para leitura!\n");
        return;
    }

    FILE *temp = fopen("arquivos/temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(txt);
        return;
    }

    dadopec peca;
    int encontrado = 0;

    //Lê os dados a serem removidos
    while (fscanf(txt, 
                  "%d\n%19[^\n]\n%59[^\n]\n%29[^\n]\n%29[^\n]\n%f\n%f\n%d\n%d\n", 
                  &peca.codpec, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, 
                  &peca.custpeca, &peca.vendpeca, &peca.npeca, &peca.minpeca) == 9) {
        if (peca.codpec == codBusca) {
            encontrado = 1;
            //Deixa o novo registro vazio
        } else {
            // Copiar peça não removida para o arquivo temporário
            fprintf(temp,
                    "%d\n%s\n%s\n%s\n%s\n%f\n%f\n%d\n%d\n",
                    peca.codpec, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, 
                    peca.custpeca, peca.vendpeca, peca.npeca, peca.minpeca);
        }
    }

    fclose(txt);
    fclose(temp);

    if (encontrado) {
        remove("arquivos/peca.txt");
        rename("arquivos/temp.txt", "arquivos/peca.txt");
        printf("Peça removida com sucesso!\n");
    } else {
        remove("arquivos/temp.txt");
        printf("Peça com código %d não encontrada!\n", codBusca);
    }
}
//SUbrotina para remover dados em texto
void removerpecabin(){
    int codBusca;
    printf("Digite o código da peça que deseja remover: ");
    scanf("%d", &codBusca);

    FILE *bin = fopen("arquivos/peca.bin", "rb");
    if (bin == NULL) {
        printf("Erro ao abrir o arquivo binário para leitura!\n");
        return;
    }

    FILE *temp = fopen("arquivos/temp.bin", "wb");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(bin);
        return;
    }

    dadopec peca;
    int encontrado = 0;

    // Lendo os dados da peça do arquivo binário
    while (fread(&peca, sizeof(dadopec), 1, bin)) {
        if (peca.codpec == codBusca) {
            encontrado = 1;
            // Não escreve o registro no arquivo temporário, efetivamente removendo-o
        } else {
            // Copiar peça não removida para o arquivo temporário
            fwrite(&peca, sizeof(dadopec), 1, temp);
        }
    }

    fclose(bin);
    fclose(temp);

    if (encontrado) {
        remove("arquivos/peca.bin");
        rename("arquivos/temp.bin", "arquivos/peca.bin");
        printf("Peça removida com sucesso!\n");
    } else {
        remove("arquivos/temp.bin");
        printf("Peça com código %d não encontrada!\n", codBusca);
    }
}
//Subrotina para encaminhar o tipo de remoção a ser realizada
void removerpeca(){
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL){
        printf("Erro na interpretação do formato do arquivo!");
        return;
    }
    fread(&formatoReg, sizeof(int), 1, formatoArq);

    if (formatoReg == 1){
        removerpecabin();
    }
    else{
        removerpecatxt();
    }

    fclose(formatoArq);
}

void detectapecabin(){
    int nmin = 0;
    FILE *bin = fopen("arquivos/peca.bin", "rb");
    if (bin == NULL) {
        printf("Erro ao abrir o arquivo para conferir dados atuais\n");
        return;
    }
    FILE *pecamin = fopen("arquivos/pecanmin.bin", "wb");
            if (pecamin == NULL){
                printf("Erro ao abrir o arquivo de peças mínimas!");
                return;
            }
    dadopec peca;
    while (fread(&peca, sizeof(dadopec), 1, bin)) { 
        if(peca.npeca < peca.minpeca){            
            nmin++;
        }        
    }
    fclose(bin);
    fwrite(&nmin, sizeof(int), 1, pecamin);
    fclose(pecamin);
}
void detectapecatxt(){
    int nmin = 0;
    FILE *txt = fopen("arquivos/peca.txt", "r");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo para conferir dados atuais\n");
        return;
    }
    FILE *pecamin = fopen("arquivos/pecanmin.bin", "wb");
            if (pecamin == NULL){
                printf("Erro ao abrir o arquivo de peças mínimas!");
                return;
            }
    dadopec peca;
    while (fscanf(txt, 
        "%d, %19[^,], %59[^,], %29[^,], %29[^,], %f, %f, %d, %d\n", 
        &peca.codpec, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, 
        &peca.custpeca, &peca.vendpeca, &peca.npeca, &peca.minpeca) == 9) 
    {
        if(peca.npeca < peca.minpeca){
            nmin++;
        }   
    }
    fwrite(&nmin, sizeof(int), 1, pecamin);
    fclose(txt);
    fclose(pecamin);
}
void detectapeca(){
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL){
        printf("Erro na interpretação do formato do arquivo!");
        return;
    }
    fread(&formatoReg, sizeof(int), 1, formatoArq);

    if (formatoReg == 1){
        detectapecabin();
    }
    else{
        detectapecatxt();
    }

    fclose(formatoArq);
}

void AtualizarEstoque(const char *pecaDescricao, int quantidade) {
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL) {
        printf("Erro ao interpretar formato, padrão binário será usado.\n");
        formatoReg = 1; // Padrão binário
    } else {
        fread(&formatoReg, sizeof(int), 1, formatoArq);
        fclose(formatoArq);
    }

    if (formatoReg == 1) {
        // Atualizar estoque em formato binário
        FILE *bin = fopen("arquivos/peca.bin", "rb+");
        if (bin == NULL) {
            printf("Erro ao abrir o arquivo de peças!\n");
            return;
        }

        FILE *temp = fopen("arquivos/temp.bin", "wb");
        if (temp == NULL) {
            printf("Erro ao criar arquivo temporário!\n");
            fclose(bin);
            return;
        }

        dadopec peca;
        int encontrado = 0;

        while (fread(&peca, sizeof(dadopec), 1, bin)) {
            if (strcmp(peca.descpec, pecaDescricao) == 0) {
                encontrado = 1;
                peca.npeca -= quantidade;
                if (peca.npeca < 0) {
                    peca.npeca = 0; // Evita estoque negativo
                }
            }
            fwrite(&peca, sizeof(dadopec), 1, temp);
        }

        fclose(bin);
        fclose(temp);

        if (encontrado) {
            remove("arquivos/peca.bin");
            rename("arquivos/temp.bin", "arquivos/peca.bin");
            printf("Estoque atualizado com sucesso!\n");
        } else {
            remove("arquivos/temp.bin");
            printf("Peça com descrição '%s' não encontrada!\n", pecaDescricao);
        }
    } else {
        // Atualizar estoque em formato de texto
        FILE *txt = fopen("arquivos/peca.txt", "r");
        if (txt == NULL) {
            printf("Erro ao abrir o arquivo de peças!\n");
            return;
        }

        FILE *temp = fopen("arquivos/temp.txt", "w");
        if (temp == NULL) {
            printf("Erro ao criar arquivo temporário!\n");
            fclose(txt);
            return;
        }

        dadopec peca;
        int encontrado = 0;

        while (fscanf(txt, "%d, %19[^,], %59[^,], %29[^,], %29[^,], %f, %f, %d, %d\n",
                      &peca.codpec, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec,
                      &peca.custpeca, &peca.vendpeca, &peca.npeca, &peca.minpeca) == 9) {
            if (strcmp(peca.descpec, pecaDescricao) == 0) {
                encontrado = 1;
                peca.npeca -= quantidade;
                if (peca.npeca < 0) {
                    peca.npeca = 0; // Evita estoque negativo
                }
            }
            fprintf(temp, "%d, %s, %s, %s, %s, %.2f, %.2f, %d, %d\n",
                    peca.codpec, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec,
                    peca.custpeca, peca.vendpeca, peca.npeca, peca.minpeca);
        }

        fclose(txt);
        fclose(temp);

        if (encontrado) {
            remove("arquivos/peca.txt");
            rename("arquivos/temp.txt", "arquivos/peca.txt");
            printf("Estoque atualizado com sucesso!\n");
        } else {
            remove("arquivos/temp.txt");
            printf("Peça com descrição '%s' não encontrada!\n", pecaDescricao);
        }
    }
}