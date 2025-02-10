#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pecas.h"


//Subrotina para registro em binário
void regpecabin(dadopec peca){ 
    FILE *bin = fopen("arquivos/peca.bin", "a+b");
    if(bin == NULL){
        printf("Erro ao abrir o arquivo! regbin");
        return;
    }
    dadopec codigo;
    while(fread(&codigo, sizeof(dadopec), 1, bin)){
        if(codigo.codpec > peca.codpec){
            peca.codpec = codigo.codpec;
        }
        else{
            peca.codpec = 0;
        }
    }

    peca.codpec += 1;

    fwrite(&peca, sizeof(dadopec), 1, bin);

    fclose(bin);
}
//Subrotina para registro em texto
void regpecatxt(dadopec peca){
    FILE *txt = fopen("arquivos/peca.txt", "a+");
    if(txt == NULL){
        printf("erro ao abrir  arquivo! regtxt");
        return;
    }

    dadopec codigo;

    while(fscanf(txt, "%d, %d, %19[^,], %59[^,], %29[^,], %29[^,], %f, %f, %d, %d", &codigo.codpec, &codigo.definecod, codigo.nomepec, codigo.descpec, codigo.fabpec, codigo.fornpec, &codigo.custpeca, &codigo.vendpeca, &codigo.npeca, &codigo.minpeca) == 10){
        if(codigo.codpec > peca.codpec){
            peca.codpec = codigo.codpec;
        }
    }

    peca.codpec += 1;



    fprintf(txt,
    "%d, %d, %s, %s, %s, %s, %f, %f, %d, %d\n",
    peca.codpec, peca.definecod, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, peca.custpeca, peca.vendpeca, peca.npeca, peca.minpeca);


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
    
    peca.codpec = 0;

    peca.definecod = 0;
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
                "%d, %d,%19[^,], %59[^,], %29[^,], %29[^,], %f, %f, %d, %d\n", 
                &peca.codpec, &peca.definecod,peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, 
                &peca.custpeca, &peca.vendpeca, &peca.npeca, &peca.minpeca) == 9) { 
        if (peca.codpec == codBusca) {
            encontrado = 1;
            printf("Insira a quantia de peças de código %d que foram adquiridas:", peca.codpec);
            scanf("%d", &npeca);
            peca.npeca -= npeca;
        }
        fprintf(temp,
            "%d, %d, %s, %s, %s, %s, %f, %f, %d, %d\n",
            peca.codpec, peca.definecod, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, 
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
    while(i != 8){
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
            printf("opcoes:\n 1 - Registrar compra de pecas ao estoque\n 2 - Registrar venda de peças do estoque\n 3 - Consultar estoque\n 4 - Restaurar peca\n 5 - Ler notafiscal\n 6 - Excluir notafiscal\n 7 - restaurar notafiscal\n 8 - Cancelar\n digite a opção:");
        }
        else{
            printf("(!)* - Estoque em falta!\n\nopcoes:\n 1 - Adicionar peças ao estoque\n 2 - Remover peças do estoque\n 3 - Consultar estoque(!)\n 4 - Restaurar peca\n 5 - Ler notafiscal\n 6 - Excluir notafiscal\n 7 - restaurar notafiscal\n 8 - Cancelar\n digite a opção:");
        }
            scanf("%d", &i);


        switch(i){
            case 1:
                notafiscal();
            break;

            case 2:
                rempecas();
            break;

            case 3:
                lerpeca();
            break;

            case 4:
                restaurapeca();
            break;

            case 5:
                lernotafisc();
            break;

            case 6:
                excluinotafiscal();
            break;

            case 7:
                restauranotafic();
            break;

            case 8:
                printf("\n\noperação cancelada!");
                return;
            break;
        }
    }
}
void reallocnotafisc(dadopec **dadonota, int *tamanho, dadopec novaPeca) {
    *tamanho += 1;
    *dadonota = (dadopec *)realloc(*dadonota, (*tamanho) * sizeof(dadopec));

    if (*dadonota == NULL) {
        printf("Erro ao realocar memória!\n");
        exit(1);
    }

    (*dadonota)[(*tamanho) - 1] = novaPeca;
}


void notafiscalbin(){
    FILE *lucroarq = fopen("arquivos/lucro.bin", "rb");
    if (lucroarq == NULL){
        printf("Erro ao carregar o arquivo de lucro das peças\n");
        fclose(lucroarq);
        return;
    }

    FILE *notafiscal = fopen("arquivos/notafiscal.bin", "ab");
    if (notafiscal == NULL){
        printf("Erro ao carregar o arquivo de notafiscal das peças\n");
        fclose(lucroarq);
        fclose(notafiscal);
    }
    int *vetnpeca = NULL;
    int *vetcodpeca = NULL;
    int tamanho = 0;

    char o = 's';
    int codBuscapeca;
    while(o != 'n' && o != 'N'){
        
        int npeca;

        FILE *bin = fopen("arquivos/peca.bin", "rb");
        if (bin == NULL) {
            printf("Erro ao abrir o arquivo para conferir dados atuais\n");
            fclose(bin);
            fclose(lucroarq);
            fclose(notafiscal);
            return;
        }
        FILE *pecaadd = fopen("arquivos/pecaadd.bin", "wb");
        if (pecaadd == NULL) {
            printf("Erro ao carregar o arquivo de adição das peças\n");
            fclose(bin);
            fclose(lucroarq);
            fclose(notafiscal);
            fclose(pecaadd);
            return;
        }       

        printf("Digite o código da peça que deseja registrar a compra: ");
        scanf("%d", &codBuscapeca);

        rewind (bin);
        dadopec peca;
        int encontrado = 0;
        while (fread(&peca, sizeof(dadopec), 1, bin)) { 
            if (peca.codpec == codBuscapeca) {                
                encontrado = 1;
                printf("Insira a quantia de peças de código %d que foram adquiridas:", peca.codpec);
                scanf("%d", &npeca);
                peca.npeca += npeca;


                tamanho++;
                vetcodpeca = (int *)realloc(vetcodpeca, tamanho * sizeof(int));
                vetnpeca = (int *)realloc(vetnpeca, tamanho * sizeof(int));

                vetcodpeca[tamanho - 1] = codBuscapeca;
                vetnpeca[tamanho - 1] = npeca;
            }
            fwrite(&peca, sizeof(dadopec), 1, pecaadd);
                
        }
        if(encontrado == 0){
            printf("Peça com código %d não encontrada!\n", codBuscapeca);
        }
        
        printf("Deseja adicionar outras peças ao estoque?\nAs pecas adiconadas serao registradas na notafiscal desta opeeracaos\n(s/n): ");
        scanf(" %c", &o);
        

        fclose(pecaadd);
        fclose(bin);
        if (encontrado) {
            remove("arquivos/peca.bin");
            rename("arquivos/pecaadd.bin", "arquivos/peca.bin");
            printf("Peças adiquiridas com sucesso!\n");
        } else {
            remove("arquivos/pecaadd.bin");
        }
    }


    FILE *bin = fopen("arquivos/peca.bin", "rb");
    if (bin == NULL) {
        printf("Erro ao abrir o arquivo para conferir dados atuais\n");
        fclose(bin);
        fclose(lucroarq);
        fclose(notafiscal);
        return;
    }
    FILE *notatemp = fopen("arquivos/novapeca.bin", "wb");
    if(notatemp == NULL){
        fclose(bin);
        fclose(lucroarq);
        fclose(notafiscal);
        return;
    }

    float lucro;
    fread(&lucro, sizeof(float), 1, lucroarq);
    
    int quantsup = 0;
    regfisc notafinal;
    dadopec leiturai;
    
    getchar();
    printf("codigo da nota: %d");
    scanf("%d", &notafinal.codnota);
    getchar();
    printf("Insira o nome do fornecedor: ");
    scanf("%49[^\n]", notafinal.forn);
    getchar();
    printf("Insira o CNPJ do fornecedor: ");
    scanf("%19[^\n]", notafinal.cnpj);
    getchar();
    printf("Insira o valor do frete: "); //provisório
    scanf("%f", &notafinal.frete);   //provisório
    printf("Insira o valor do imposto: "); //provisório
    scanf("%f", &notafinal.imposto); //provisório
    getchar();
    

    printf("===================================== Nota Fiscal =====================================\n");
    
    printf("Fornecedor: %s\n", notafinal.forn);
    printf("CNPJ: %s\n", notafinal.cnpj);
    printf("Frete: %.2f  |", notafinal.frete); printf("Imposto: %.2f\n", notafinal.imposto);
    printf("------------------------------ Produtos ------------------------------\n");
    printf("Nome da peça            | Custo unitário      | Quantidade    | Valor total\n");
    notafinal.precgeral = 0;
    while(fread(&leiturai, sizeof(dadopec), 1, bin)){
        for(int i = 0; i < tamanho; i++){
            if(vetcodpeca[i] == leiturai.codpec){
                printf("Nome da peça: %-22s  |", leiturai.nomepec);printf("Custo unitário: %-10.2f  |", leiturai.custpeca);printf("Quantidade: %-13d  |", leiturai.npeca);printf("Valor total: %.2f\n", leiturai.custpeca * leiturai.npeca);       
                quantsup += leiturai.npeca;
                notafinal.precgeral += leiturai.custpeca * leiturai.npeca;
            }   
        }     
    }
    notafinal.precgeral += notafinal.imposto + notafinal.frete;
    notafinal.imposto = notafinal.imposto/quantsup;
    notafinal.frete = notafinal.frete/quantsup;
    notafinal.definecod = 0;
    fwrite(&notafinal, sizeof(regfisc), 1, notafiscal);
    printf("------------------------------\n");
    printf("Valor total da compra: %.2f\n", notafinal.precgeral);
    printf("==============================\n");
    rewind(bin);
    int cont = 0;
    while(fread(&leiturai, sizeof(dadopec), 1, bin)){   
        for(int i = 0; i < tamanho; i++){
            if(leiturai.codpec == vetcodpeca[i]){
                leiturai.vendpeca = leiturai.custpeca + notafinal.imposto + notafinal.frete;
                leiturai.vendpeca = leiturai.vendpeca + (leiturai.vendpeca * (lucro/100));
                cont = 1;
                break;
            }
        }
        if(cont == 1){            
            printf("Nome da peça: %-22s  |", leiturai.nomepec);printf("Custo unitário: %-10.2f  |", leiturai.custpeca);printf("Frete: %-13.2f  |", notafinal.frete);printf("Imposto: %-13.2f  |", notafinal.imposto);
            printf("Lucro: %-13.2f  |",(leiturai.vendpeca - (leiturai.custpeca + notafinal.imposto + notafinal.frete))); printf("Preço de venda: %.2f\n", leiturai.vendpeca);
            fwrite(&leiturai, sizeof(dadopec), 1, notatemp);
        }
        else{
            fwrite(&leiturai, sizeof(dadopec), 1, notatemp);
        }
        
        cont = 0;
    }

    fclose(bin);
    fclose(notatemp);
    fclose(notafiscal);
    fclose(lucroarq);
    remove("arquivos/peca.bin");
    rename("arquivos/novapeca.bin", "arquivos/peca.bin");

    free(vetcodpeca);
    free(vetnpeca);

    return;
}
void notafiscaltxt(){
    FILE *lucroarq = fopen("arquivos/lucro.bin", "rb");
    if (lucroarq == NULL) {
        printf("Erro ao carregar o arquivo de lucro das peças\n");
        return;
    }

    FILE *notafiscal = fopen("arquivos/notafiscal.txt", "a");
    if (notafiscal == NULL) {
        printf("Erro ao carregar o arquivo de notafiscal das peças\n");
        fclose(lucroarq);
        return;
    }

    int *vetnpeca = NULL;
    int *vetcodpeca = NULL;
    int tamanho = 0;

    char o = 's';
    int codBuscapeca;
    while (o != 'n' && o != 'N') {
        int npeca;

        FILE *txt = fopen("arquivos/peca.txt", "r");
        if (txt == NULL) {
            printf("Erro ao abrir o arquivo para conferir dados atuais\n");
            fclose(lucroarq);
            fclose(notafiscal);
            return;
        }

        FILE *pecaadd = fopen("arquivos/pecaadd.txt", "w");
        if (pecaadd == NULL) {
            printf("Erro ao carregar o arquivo de adição das peças\n");
            fclose(txt);
            fclose(lucroarq);
            fclose(notafiscal);
            return;
        }

        printf("Digite o código da peça que deseja registrar a compra: ");
        scanf("%d", &codBuscapeca);

        rewind(txt);
        dadopec peca;
        int encontrado = 0;
        while (fscanf(txt, "%d, %d, %19[^,], %59[^,], %29[^,], %29[^,], %f, %f, %d, %d\n", 
                      &peca.codpec, &peca.definecod, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, 
                      &peca.custpeca, &peca.vendpeca, &peca.npeca, &peca.minpeca) == 10) {
            if (peca.codpec == codBuscapeca) {
                encontrado = 1;
                printf("Insira a quantia de peças de código %d que foram adquiridas:", peca.codpec);
                scanf("%d", &npeca);
                peca.npeca += npeca;

                tamanho++;
                vetcodpeca = (int *)realloc(vetcodpeca, tamanho * sizeof(int));
                vetnpeca = (int *)realloc(vetnpeca, tamanho * sizeof(int));

                vetcodpeca[tamanho - 1] = codBuscapeca;
                vetnpeca[tamanho - 1] = npeca;
            }
            fprintf(pecaadd, "%d, %d, %s, %s, %s, %s, %.2f, %.2f, %d, %d\n", 
                    peca.codpec, peca.definecod, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, 
                    peca.custpeca, peca.vendpeca, peca.npeca, peca.minpeca);
        }

        if (encontrado == 0) {
            printf("Peça com código %d não encontrada!\n", codBuscapeca);
        }

        printf("Deseja adicionar outras peças ao estoque?\nAs pecas adicionadas serao registradas na notafiscal desta operacao\n(s/n): ");
        scanf(" %c", &o);

        fclose(pecaadd);
        fclose(txt);

        if (encontrado) {
            remove("arquivos/peca.txt");
            rename("arquivos/pecaadd.txt", "arquivos/peca.txt");
            printf("Peças adquiridas com sucesso!\n");
        } else {
            remove("arquivos/pecaadd.txt");
        }
    }

    FILE *txt = fopen("arquivos/peca.txt", "r");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo para conferir dados atuais\n");
        fclose(lucroarq);
        fclose(notafiscal);
        return;
    }

    FILE *notatemp = fopen("arquivos/novapeca.txt", "w");
    if (notatemp == NULL) {
        fclose(txt);
        fclose(lucroarq);
        fclose(notafiscal);
        return;
    }

    float lucro;
    fread(&lucro, sizeof(float), 1, lucroarq);

    int quantsup = 0;
    regfisc notafinal;
    dadopec leiturai;

    getchar();
    printf("codigo da nota: %d");
    scanf("%d", &notafinal.codnota);
    getchar();
    printf("Insira o nome do fornecedor: ");
    scanf("%49[^\n]", notafinal.forn);
    getchar();
    printf("Insira o CNPJ do fornecedor: ");
    scanf("%19[^\n]", notafinal.cnpj);
    getchar();
    printf("Insira o valor do frete: ");
    scanf("%f", &notafinal.frete);
    printf("Insira o valor do imposto: ");
    scanf("%f", &notafinal.imposto);
    getchar();

    printf("===================================== Nota Fiscal =====================================\n");
    printf("Fornecedor: %s\n", notafinal.forn);
    printf("CNPJ: %s\n", notafinal.cnpj);
    printf("Frete: %.2f  |", notafinal.frete); printf("Imposto: %.2f\n", notafinal.imposto);
    printf("------------------------------ Produtos ------------------------------\n");
    printf("Nome da peça            | Custo unitário      | Quantidade    | Valor total\n");
    notafinal.precgeral = 0;
    while (fscanf(txt, "%d, %d, %19[^,], %59[^,], %29[^,], %29[^,], %f, %f, %d, %d\n", 
                  &leiturai.codpec, &leiturai.definecod, leiturai.nomepec, leiturai.descpec, leiturai.fabpec, leiturai.fornpec, 
                  &leiturai.custpeca, &leiturai.vendpeca, &leiturai.npeca, &leiturai.minpeca) == 10) {
        for (int i = 0; i < tamanho; i++) {
            if (vetcodpeca[i] == leiturai.codpec) {
                printf("Nome da peça: %-22s  |", leiturai.nomepec); printf("Custo unitário: %-10.2f  |", leiturai.custpeca); printf("Quantidade: %-13d  |", leiturai.npeca); printf("Valor total: %.2f\n", leiturai.custpeca * leiturai.npeca);
                quantsup += leiturai.npeca;
                notafinal.precgeral += leiturai.custpeca * leiturai.npeca;
            }
        }
    }
    notafinal.precgeral += notafinal.imposto + notafinal.frete;
    notafinal.imposto = notafinal.imposto / quantsup;
    notafinal.frete = notafinal.frete / quantsup;
    notafinal.definecod = 0;
    fprintf(notafiscal, "%d, %d, %s, %s, %f, %f, %f", notafinal.codnota, notafinal.definecod, notafinal.forn, notafinal.cnpj, notafinal.imposto, notafinal.frete, notafinal.precgeral);
    printf("------------------------------\n");
    printf("Valor total da compra: %.2f\n", notafinal.precgeral);
    printf("==============================\n");
    rewind(txt);
    int cont = 0;
    while (fscanf(txt, "%d, %d, %19[^,], %59[^,], %29[^,], %29[^,], %f, %f, %d, %d\n", 
                  &leiturai.codpec, &leiturai.definecod, leiturai.nomepec, leiturai.descpec, leiturai.fabpec, leiturai.fornpec, 
                  &leiturai.custpeca, &leiturai.vendpeca, &leiturai.npeca, &leiturai.minpeca) == 10) {
        for (int i = 0; i < tamanho; i++) {
            if (leiturai.codpec == vetcodpeca[i]) {
                leiturai.vendpeca = leiturai.custpeca + notafinal.imposto + notafinal.frete;
                leiturai.vendpeca = leiturai.vendpeca + (leiturai.vendpeca * (lucro / 100));
                cont = 1;
                break;
            }
        }
        if (cont == 1) {
            printf("Nome da peça: %-22s  |", leiturai.nomepec); printf("Custo unitário: %-10.2f  |", leiturai.custpeca); printf("Frete: %-13.2f  |", notafinal.frete); printf("Imposto: %-13.2f  |", notafinal.imposto);
            printf("Lucro: %-13.2f  |", (leiturai.vendpeca - (leiturai.custpeca + notafinal.imposto + notafinal.frete))); printf("Preço de venda: %.2f\n", leiturai.vendpeca);
            fprintf(notatemp, "%d, %d, %s, %s, %s, %s, %.2f, %.2f, %d, %d\n", 
                    leiturai.codpec, leiturai.definecod, leiturai.nomepec, leiturai.descpec, leiturai.fabpec, leiturai.fornpec, 
                    leiturai.custpeca, leiturai.vendpeca, leiturai.npeca, leiturai.minpeca);
        } else {
            fprintf(notatemp, "%d, %d, %s, %s, %s, %s, %.2f, %.2f, %d, %d\n", 
                    leiturai.codpec, leiturai.definecod, leiturai.nomepec, leiturai.descpec, leiturai.fabpec, leiturai.fornpec, 
                    leiturai.custpeca, leiturai.vendpeca, leiturai.npeca, leiturai.minpeca);
        }
        cont = 0;
    }

    fclose(txt);
    fclose(notatemp);
    fclose(notafiscal);
    fclose(lucroarq);
    remove("arquivos/peca.txt");
    rename("arquivos/novapeca.txt", "arquivos/peca.txt");

    free(vetcodpeca);
    free(vetnpeca);

    return;
}
void notafiscal(){
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL){
        printf("Erro na interpretação do formato do arquivo!");
        return;
    }
    fread(&formatoReg, sizeof(int), 1, formatoArq);

    //separa entre os formatos definidos no arquivo de formato
    if (formatoReg == 1){
        notafiscalbin();
    }
    else{
        notafiscaltxt();
    }

    fclose(formatoArq);
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
                "%d, %d, %19[^,], %59[^,], %29[^,], %29[^,], %f, %f, %d, %d\n", 
                &peca.codpec, &peca.definecod, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, 
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
                    "%d, %d, %s, %s, %s, %s, %f, %f, %d, %d\n",
                    peca.codpec, peca.definecod,peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, 
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
    while (fscanf(txt, "%d, %d, %19[^,], %59[^,], %29[^,], %29[^,], %f, %f, %d, %d\n", 
                   &peca.codpec, &peca.definecod, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, 
                   &peca.custpeca, &peca.vendpeca, &peca.npeca, &peca.minpeca) == 10) {
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


void lernotafiscbin() {
    FILE *notafiscal = fopen("arquivos/notafiscal.bin", "rb");
    if (notafiscal == NULL) {
        printf("Erro ao abrir o arquivo de nota fiscal!\n");
        return;
    }

    regfisc notafinal;
    dadopec peca;

    // Lê os dados da nota fiscal
    printf("===================================== Nota Fiscal =====================================\n");
    while (fread(&notafinal, sizeof(regfisc), 1, notafiscal) == 1) {
        printf("Código da Nota: %d\n", notafinal.codnota);
        printf("Fornecedor: %s\n", notafinal.forn);
        printf("CNPJ: %s\n", notafinal.cnpj);
        printf("Frete: %.2f  | Imposto: %.2f\n", notafinal.frete, notafinal.imposto);
        printf("Valor total da compra: %.2f\n", notafinal.precgeral);
        printf("------------------------------ Produtos ------------------------------\n");
        printf("Nome da peça            | Custo unitário      | Quantidade    | Valor total\n");

        // Lê os produtos da nota fiscal
        while (fread(&peca, sizeof(dadopec), 1, notafiscal) == 1) {
            printf("Nome da peça: %-22s  |", peca.nomepec);
            printf("Custo unitário: %-10.2f  |", peca.custpeca);
            printf("Quantidade: %-13d  |", peca.npeca);
            printf("Valor total: %.2f\n", peca.custpeca * peca.npeca);
        }
        printf("--------------------------------------------------------------------------------------\n");
    }

    fclose(notafiscal);
}
void lernotafisctxt() {
    FILE *notafiscal = fopen("arquivos/notafiscal.txt", "r");
    if (notafiscal == NULL) {
        printf("Erro ao abrir o arquivo de nota fiscal!\n");
        return;
    }

    regfisc notafinal;
    dadopec peca;

    // Lê os dados da nota fiscal
    printf("===================================== Nota Fiscal =====================================\n");
    while (fscanf(notafiscal, "%d, %d, %49[^,], %19[^,], %f, %f, %f\n", 
                  &notafinal.codnota, &notafinal.definecod, notafinal.forn, notafinal.cnpj, 
                  &notafinal.imposto, &notafinal.frete, &notafinal.precgeral) == 7) {
        printf("Código da Nota: %d\n", notafinal.codnota);
        printf("Fornecedor: %s\n", notafinal.forn);
        printf("CNPJ: %s\n", notafinal.cnpj);
        printf("Frete: %.2f  | Imposto: %.2f\n", notafinal.frete, notafinal.imposto);
        printf("Valor total da compra: %.2f\n", notafinal.precgeral);
        printf("------------------------------ Produtos ------------------------------\n");
        printf("Nome da peça            | Custo unitário      | Quantidade    | Valor total\n");

        // Lê os produtos da nota fiscal
        while (fscanf(notafiscal, "%d, %d, %19[^,], %59[^,], %29[^,], %29[^,], %f, %f, %d, %d\n", 
                      &peca.codpec, &peca.definecod, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, 
                      &peca.custpeca, &peca.vendpeca, &peca.npeca, &peca.minpeca) == 10) {
            printf("Nome da peça: %-22s  |", peca.nomepec);
            printf("Custo unitário: %-10.2f  |", peca.custpeca);
            printf("Quantidade: %-13d  |", peca.npeca);
            printf("Valor total: %.2f\n", peca.custpeca * peca.npeca);
        }
        printf("--------------------------------------------------------------------------------------\n");
    }

    fclose(notafiscal);
}
void lernotafisc(){
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL){
        printf("Erro na interpretação do formato do arquivo!");
        return;
    }
    fread(&formatoReg, sizeof(int), 1, formatoArq);

    //separa entre os formatos definidos no arquivo de formato
    if (formatoReg == 1){
        lernotafiscbin();
    }
    else{
        lernotafisctxt();
    }

    fclose(formatoArq);
}

//Subrotina para remover dados em binário
void removerpecabin(){
    int codBusca;
    printf("Digite o código da peça que deseja remover: ");
    scanf("%d", &codBusca);

    FILE *bin = fopen("arquivos/peca.bin", "rb");
    if (bin == NULL) {
        printf("Erro ao abrir o arquivo binário para leitura!\n");
        fclose(bin);
        return;
    }

    FILE *temp = fopen("arquivos/temp.bin", "wb");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(bin);
        fclose(temp);
        return;
    }


    dadopec peca;
    int encontrado = 0;

    // Lendo os dados da peça do arquivo binário
    while (fread(&peca, sizeof(dadopec), 1, bin)) {
        if (peca.codpec == codBusca) {
            encontrado = 1;
            peca.definecod = 1;
        }
        fwrite(&peca, sizeof(dadopec), 1, temp);
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
//SUbrotina para remover dados em texto
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
                  "%d,%d,%19[^,],%59[^,],%29[^,],%29[^,],%f,%f,%d,%d\n", 
                  &peca.codpec, &peca.definecod, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, 
                  &peca.custpeca, &peca.vendpeca, &peca.npeca, &peca.minpeca) == 10) {
        if (peca.codpec == codBusca) {
            encontrado = 1;
            peca.definecod = 1;
            
        }
        fprintf(temp, "%d,%d,%s,%s,%s,%s,%f,%f,%d,%d\n",
                peca.codpec, peca.definecod, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, 
                peca.custpeca, peca.vendpeca, peca.npeca, peca.minpeca);
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


void excluinotafiscaltxt() {
    int codBusca;
    printf("Digite o código da nota fiscal que deseja excluir: ");
    scanf("%d", &codBusca);

    FILE *txt = fopen("arquivos/notafiscal.txt", "r");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo de nota fiscal para leitura!\n");
        return;
    }

    FILE *temp = fopen("arquivos/temp_notafiscal.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(txt);
        return;
    }

    regfisc notafinal;
    dadopec peca;
    int encontrado = 0;

    // Lê a nota fiscal e os produtos associados
    while (fscanf(txt, "%d, %d, %49[^,], %19[^,], %f, %f, %f\n", 
                  &notafinal.codnota, &notafinal.definecod, notafinal.forn, notafinal.cnpj, 
                  &notafinal.imposto, &notafinal.frete, &notafinal.precgeral) == 7) {
        if (notafinal.codnota == codBusca) {
            encontrado = 1;
            notafinal.definecod = 1; // Marca a nota como excluída
        }
        fprintf(temp, "%d, %d, %s, %s, %.2f, %.2f, %.2f\n", 
                notafinal.codnota, notafinal.definecod, notafinal.forn, notafinal.cnpj, 
                notafinal.imposto, notafinal.frete, notafinal.precgeral);

    }

    fclose(txt);
    fclose(temp);

    if (encontrado) {
        remove("arquivos/notafiscal.txt");
        rename("arquivos/temp_notafiscal.txt", "arquivos/notafiscal.txt");
        printf("Nota fiscal excluída com sucesso!\n");
    } else {
        remove("arquivos/temp_notafiscal.txt");
        printf("Nota fiscal com código %d não encontrada!\n", codBusca);
    }
}
void excluinotafiscalbin() {
    int codBusca;
    printf("Digite o código da nota fiscal que deseja excluir: ");
    scanf("%d", &codBusca);

    FILE *bin = fopen("arquivos/notafiscal.bin", "rb");
    if (bin == NULL) {
        printf("Erro ao abrir o arquivo de nota fiscal para leitura!\n");
        return;
    }

    FILE *temp = fopen("arquivos/temp_notafiscal.bin", "wb");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(bin);
        return;
    }

    regfisc notafinal;
    dadopec peca;
    int encontrado = 0;

    // Lê a nota fiscal e os produtos associados
    while (fread(&notafinal, sizeof(regfisc), 1, bin) == 1) {
        if (notafinal.codnota == codBusca) {
            encontrado = 1;
            notafinal.definecod = 1; // Marca a nota como excluída
        }
        fwrite(&notafinal, sizeof(regfisc), 1, temp);
    }

    fclose(bin);
    fclose(temp);

    if (encontrado) {
        remove("arquivos/notafiscal.bin");
        rename("arquivos/temp_notafiscal.bin", "arquivos/notafiscal.bin");
        printf("Nota fiscal excluída com sucesso!\n");
    } else {
        remove("arquivos/temp_notafiscal.bin");
        printf("Nota fiscal com código %d não encontrada!\n", codBusca);
    }
}
void excluinotafiscal(){
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL){
        printf("Erro na interpretação do formato do arquivo!");
        return;
    }
    fread(&formatoReg, sizeof(int), 1, formatoArq);

    if (formatoReg == 1){
        excluinotafiscalbin();
    }
    else{
        excluinotafiscaltxt();
    }

    fclose(formatoArq);
}


void restaurapecabin(){
    int codBusca;
    printf("Digite o código da peça que deseja restaurar: ");
    scanf("%d", &codBusca);

    FILE *bin = fopen("arquivos/peca.bin", "rb");
    if (bin == NULL) {
        printf("Erro ao abrir o arquivo binário para leitura!\n");
        fclose(bin);
        return;
    }

    FILE *temp = fopen("arquivos/temp.bin", "wb");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(bin);
        fclose(temp);
        return;
    }

    dadopec peca;
    int encontrado = 0;

    // Lendo os dados da peça do arquivo binário
    while (fread(&peca, sizeof(dadopec), 1, bin)) {
        if (peca.codpec == codBusca) {
            encontrado = 1;
            peca.definecod = 0;
        } 
        fwrite(&peca, sizeof(dadopec), 1, temp);
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
void restaurapecatxt(){
    int codBusca;
    printf("Digite o código da peça que deseja restaurar: ");
    scanf("%d", &codBusca);

    FILE *txt = fopen("arquivos/peca.txt", "r");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo texto para leitura!\n");
        fclose(txt);
        return;
    }

    FILE *temp = fopen("arquivos/temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(txt);
        fclose(temp);
        return;
    }

    dadopec peca;
    int encontrado = 0;

    while (fscanf(txt, 
            "%d,%d,%19[^,],%59[^,],%29[^,],%29[^,],%f,%f,%d,%d\n", 
            &peca.codpec, &peca.definecod, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, 
            &peca.custpeca, &peca.vendpeca, &peca.npeca, &peca.minpeca) == 10) {

        if (peca.codpec == codBusca) {
            encontrado = 1;
            peca.definecod = 0;
        } 
        fprintf(temp, "%d,%d,%s,%s,%s,%s,%f,%f,%d,%d\n",
                peca.codpec, peca.definecod, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, 
                peca.custpeca, peca.vendpeca, peca.npeca, peca.minpeca);
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
void restaurapeca(){
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL){
        printf("Erro na interpretação do formato do arquivo!");
        return;
    }
    fread(&formatoReg, sizeof(int), 1, formatoArq);

    if (formatoReg == 1){
        restaurapecabin();
    }
    else{
        restaurapecatxt();
    }

    fclose(formatoArq);
}

void restauranotafiscaltxt() {
    int codBusca;
    printf("Digite o código da nota fiscal que deseja restaurar: ");
    scanf("%d", &codBusca);

    FILE *txt = fopen("arquivos/notafiscal.txt", "r");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo de nota fiscal para leitura!\n");
        return;
    }

    FILE *temp = fopen("arquivos/temp_notafiscal.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(txt);
        return;
    }

    regfisc notafinal;
    int encontrado = 0;

    // Lê a nota fiscal e os produtos associados
    while (fscanf(txt, "%d, %d, %49[^,], %19[^,], %f, %f, %f\n", 
                  &notafinal.codnota, &notafinal.definecod, notafinal.forn, notafinal.cnpj, 
                  &notafinal.imposto, &notafinal.frete, &notafinal.precgeral) == 7) {
        if (notafinal.codnota == codBusca) {
            encontrado = 1;
            notafinal.definecod = 0; // Marca a nota como inativa
        }
        fprintf(temp, "%d, %d, %s, %s, %.2f, %.2f, %.2f\n", 
                notafinal.codnota, notafinal.definecod, notafinal.forn, notafinal.cnpj, 
                notafinal.imposto, notafinal.frete, notafinal.precgeral);
    }

    fclose(txt);
    fclose(temp);

    if (encontrado) {
        remove("arquivos/notafiscal.txt");
        rename("arquivos/temp_notafiscal.txt", "arquivos/notafiscal.txt");
        printf("Nota fiscal restaurada com sucesso!\n");
    } else {
        remove("arquivos/temp_notafiscal.txt");
        printf("Nota fiscal com código %d não encontrada!\n", codBusca);
    }
}
void restauranotafiscalbin() {
    int codBusca;
    printf("Digite o código da nota fiscal que deseja restaurar: ");
    scanf("%d", &codBusca);

    FILE *bin = fopen("arquivos/notafiscal.bin", "rb");
    if (bin == NULL) {
        printf("Erro ao abrir o arquivo de nota fiscal para leitura!\n");
        return;
    }

    FILE *temp = fopen("arquivos/temp_notafiscal.bin", "wb");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(bin);
        return;
    }

    regfisc notafinal;
    dadopec peca;
    int encontrado = 0;

    while (fread(&notafinal, sizeof(regfisc), 1, bin) == 1) {
        if (notafinal.codnota == codBusca) {
            encontrado = 1;
            notafinal.definecod = 0;
        }
        fwrite(&notafinal, sizeof(regfisc), 1, temp);
    }

    fclose(bin);
    fclose(temp);

    if (encontrado) {
        remove("arquivos/notafiscal.bin");
        rename("arquivos/temp_notafiscal.bin", "arquivos/notafiscal.bin");
        printf("Nota fiscal restaurada com sucesso!\n");
    } else {
        remove("arquivos/temp_notafiscal.bin");
        printf("Nota fiscal com código %d não encontrada!\n", codBusca);
    }
}
void restauranotafic(){
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL){
        printf("Erro na interpretação do formato do arquivo!");
        return;
    }
    fread(&formatoReg, sizeof(int), 1, formatoArq);

    if (formatoReg == 1){
        restauranotafiscalbin();
    }
    else{
        restauranotafiscaltxt();
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
        "%d, %d, %19[^,], %59[^,], %29[^,], %29[^,], %f, %f, %d, %d\n", 
        &peca.codpec, &peca.definecod, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, 
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

void pecapornomebin(){
    char nomepeca[30];
    printf("Digite o nome, ou uma parte do nome, da peça que deseja ver: ");
    scanf(" %29[^\n]", nomepeca);

    FILE *bin = fopen("arquivos/peca.bin", "rb");
    if (bin == NULL) {
        printf("Erro ao abrir o arquivo binário para leitura!\n");
        return;
    }

    dadopec peca;
    int encontrado = 0;

    while (fread(&peca, sizeof(dadopec), 1, bin)) { 
        if (strstr(peca.nomepec,nomepeca)) {
            encontrado = 1;
            if(peca.npeca < peca.minpeca){
                printf("\n*ESTOQUE LIMITADO\n\nCodigo: %d\nNome: %s\nDescrição: %s\nFabricante: %s\nFornecedor: %s \nCusto: %.2f \nVenda: %.2f \n-------\nUnidades Disponiveis: %d(!)\nQuantidade Mínima: %d(!)",
             peca.codpec, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, peca.custpeca, peca.vendpeca, peca.npeca, peca.minpeca);
            }
            else{
                printf("\nCodigo: %d\nNome: %s\nDescrição: %s\nFabricante: %s\nFornecedor: %s \nCusto: %.2f \nVenda: %.2f \nUnidades Disponiveis: %d\nQuantidade Mínima: %d",
             peca.codpec, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, peca.custpeca, peca.vendpeca, peca.npeca, peca.minpeca);
            }
            printf("--------------------------------------------------------------------------------------\n");
        }
    }
    if(encontrado == 0){
        printf("Peça com nome %s não encontrada!\n", nomepeca);
    }

    fclose(bin);
}
void pecapornometxt(){
    char nomepeca[30];
    printf("Digite o nome, ou uma parte do nome, da peça que deseja ver: ");
    scanf(" %29[^\n]", nomepeca);

    FILE *txt = fopen("arquivos/peca.txt", "r");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo texto para leitura!\n");
        return;
    }

    dadopec peca;
    int encontrado = 0;

    while (fscanf(txt, 
                "%d, %d, %19[^,], %59[^,], %29[^,], %29[^,], %f, %f, %d, %d\n", 
                &peca.codpec, &peca.definecod, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, 
                &peca.custpeca, &peca.vendpeca, &peca.npeca, &peca.minpeca) == 9) {
        if (strstr(peca.nomepec,nomepeca)) {
            encontrado = 1;
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
    }
    if(encontrado == 0){
        printf("Peça com nome %s não encontrada!\n", nomepeca);
    }

    fclose(txt);
}
void pecapornome(){
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL){
        printf("Erro na interpretação do formato do arquivo!");
        return;
    }
    fread(&formatoReg, sizeof(int), 1, formatoArq);

    if (formatoReg == 1){
        pecapornomebin();
    }
    else{
        pecapornometxt();
    }

    fclose(formatoArq);
}


void riscopecabin(){
    FILE *bin = fopen("arquivos/peca.bin", "rb");
    if (bin == NULL) {
        printf("Erro ao abrir o arquivo binário para leitura!\n");
        return;
    }
    dadopec peca;


    //função que separa o arquivo localizado para edição
    while (fread(&peca, sizeof(dadopec), 1, bin)) { 
        if(peca.npeca < peca.minpeca){
        printf("\n*ESTOQUE LIMITADO\n\nCodigo: %d\nNome: %s\nDescrição: %s\nFabricante: %s\nFornecedor: %s \nCusto: %.2f \nVenda: %.2f \n-------\nUnidades Disponiveis: %d(!)\nQuantidade Mínima: %d(!)",
            peca.codpec, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, peca.custpeca, peca.vendpeca, peca.npeca, peca.minpeca);
            printf("--------------------------------------------------------------------------------------\n");
        }
            
    }
    

    fclose(bin);
}
void riscopecatxt(){
    FILE *txt = fopen("arquivos/peca.txt", "r");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo texto para leitura!\n");
        return;
    }

    dadopec peca;
    int encontrado = 0;
    
    while (fscanf(txt, 
                "%d, %d, %19[^,], %59[^,], %29[^,], %29[^,], %f, %f, %d, %d\n", 
                &peca.codpec, &peca.definecod, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, 
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
    
    }

    fclose(txt);
}
void riscopeca(){
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL){
        printf("Erro na interpretação do formato do arquivo!");
        return;
    }
    fread(&formatoReg, sizeof(int), 1, formatoArq);

    if (formatoReg == 1){
        riscopecabin();
    }
    else{
        riscopecatxt();
    }

    fclose(formatoArq);
}


void pecaporcodbin(){
    int codpeca;
    printf("Digite o nome, ou uma parte do nome, da peça que deseja ver: ");
    scanf("%d", &codpeca);

    FILE *bin = fopen("arquivos/peca.bin", "rb");
    if (bin == NULL) {
        printf("Erro ao abrir o arquivo binário para leitura!\n");
        return;
    }

    dadopec peca;
    int encontrado = 0;

    while (fread(&peca, sizeof(dadopec), 1, bin)) { 
        if (codpeca == peca.codpec) {
            encontrado = 1;
            if(peca.npeca < peca.minpeca){
                printf("\n*ESTOQUE LIMITADO\n\nCodigo: %d\nNome: %s\nDescrição: %s\nFabricante: %s\nFornecedor: %s \nCusto: %.2f \nVenda: %.2f \n-------\nUnidades Disponiveis: %d(!)\nQuantidade Mínima: %d(!)",
             peca.codpec, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, peca.custpeca, peca.vendpeca, peca.npeca, peca.minpeca);
            }
            else{
                printf("\nCodigo: %d\nNome: %s\nDescrição: %s\nFabricante: %s\nFornecedor: %s \nCusto: %.2f \nVenda: %.2f \nUnidades Disponiveis: %d\nQuantidade Mínima: %d",
             peca.codpec, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, peca.custpeca, peca.vendpeca, peca.npeca, peca.minpeca);
            }
            printf("--------------------------------------------------------------------------------------\n");
        }
    }
    if(encontrado == 0){
        printf("Peça com codigo %d não encontrada!\n", codpeca);
    }

    fclose(bin);
}
void pecaporcodtxt(){
    int codpeca;
    printf("Digite o nome, ou uma parte do nome, da peça que deseja ver: ");
    scanf("%d", &codpeca);

    FILE *txt = fopen("arquivos/peca.txt", "r");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo txt para leitura!\n");
        return;
    }

    dadopec peca;
    int encontrado = 0;

    while (fscanf(txt, 
                "%d, %d, %19[^,], %59[^,], %29[^,], %29[^,], %f, %f, %d, %d\n", 
                &peca.codpec, &peca.definecod, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, 
                &peca.custpeca, &peca.vendpeca, &peca.npeca, &peca.minpeca) == 9) {
        if (codpeca == peca.codpec) {
            encontrado = 1;
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
    }
    if(encontrado == 0){
        printf("Peça com codigo %d não encontrada!\n", codpeca);
    }

    fclose(txt);
}
void pecaporcod(){
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL){
        printf("Erro na interpretação do formato do arquivo!");
        return;
    }
    fread(&formatoReg, sizeof(int), 1, formatoArq);

    if (formatoReg == 1){
        pecaporcodbin();
    }
    else{
        pecaporcodtxt();
    }

    fclose(formatoArq);
}


void relatoriopeca(){
    int i;
    printf("Deseja apenas ver as todas as peças presentes no estoque ou deseja filtrar os resultados?\nFiltros:\n 1 - nome\n 2 -produtos em estoqueminimo\n 3 - peca por codigo\n");
    scanf("%d", &i);

    switch(i){
        case 1:
            printf("digite o nome da peça procurada: ");
            scanf("%d", &i);
            pecapornome();
        break;

        case 2:
            riscopeca();
        break;

        case 3:
            pecaporcod();
        break;
    }
}