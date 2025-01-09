#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "contasApagar.h"
#include "controleC.h"


// Funções para registro
void regContaBin(ContaPagar conta) {
    FILE *bin = fopen("arquivos/contas.bin", "ab");
    if (bin == NULL) {
        printf("Erro ao abrir o arquivo binário! regContaBin\n");
        return;
    }
    fwrite(&conta, sizeof(ContaPagar), 1, bin);
    fclose(bin);
    printf("Conta registrada em binário com sucesso!\n");
}

void regContaTxt(ContaPagar conta) {
    FILE *txt = fopen("arquivos/contas.txt", "a");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo texto! regContaTxt\n");
        return;
    }
    fprintf(txt, "%d|%s|%.2f|%ld|%d\n", conta.codigo, conta.fornecedor, conta.valor, conta.vencimento, conta.pago);
    fclose(txt);
    printf("Conta registrada em texto com sucesso!\n");
}

void regContaPath(ContaPagar conta) {
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL) {
        printf("Erro na interpretação do formato do arquivo!\n");
        return;
    }
    fread(&formatoReg, sizeof(int), 1, formatoArq);
    fclose(formatoArq);

    if (formatoReg == 1) {
        regContaBin(conta);
    } else {
        regContaTxt(conta);
    }
}

void regConta() {
    ContaPagar conta;
    int dia, mes, ano;

    printf("Digite o código da conta: ");
    scanf("%d", &conta.codigo);
    getchar();  

    printf("Digite o fornecedor: ");
    scanf(" %[^\n]", conta.fornecedor);

    printf("Digite o valor: ");
    scanf("%f", &conta.valor);
    printf("Digite a data de vencimento (dd mm aaaa): ");
    scanf("%d %d %d", &dia, &mes, &ano);

    struct tm tm = {0};
    tm.tm_mday = dia;
    tm.tm_mon = mes - 1;
    tm.tm_year = ano - 1900;
    conta.vencimento = mktime(&tm);
    conta.pago = 0;

    regContaPath(conta);  // Chama a função regContaPath para registrar a conta
}

// Funções para listagem
void listarContasBin() {
    FILE *bin = fopen("arquivos/contas.bin", "rb");
    if (bin == NULL) {
        printf("Erro ao abrir o arquivo binário! listarContasBin\n");
        return;
    }

    ContaPagar conta;
    int i = 0;
    printf("\nContas armazenadas em binário:\n");
    while (fread(&conta, sizeof(ContaPagar), 1, bin)) {
        char vencimentoStr[20];
        strftime(vencimentoStr, sizeof(vencimentoStr), "%d/%m/%Y", localtime(&conta.vencimento));
        printf("Conta %d:\n  Código: %d\n  Fornecedor: %s\n  Valor: R$ %.2f\n  Vencimento: %s\n  Status: %s\n", 
            ++i, conta.codigo, conta.fornecedor, conta.valor, vencimentoStr, conta.pago ? "Pago" : "Pendente");
    }

    fclose(bin);
}

void listarContasTxt() {
    FILE *txt = fopen("arquivos/contas.txt", "r");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo texto! listarContasTxt\n");
        return;
    }

    ContaPagar conta;
    int i = 0;
    printf("\nContas armazenadas em texto:\n");
    while (fscanf(txt, "%d|%[^|]|%f|%ld|%d\n", &conta.codigo, conta.fornecedor, &conta.valor, &conta.vencimento, &conta.pago) != EOF) {
        char vencimentoStr[20];
        strftime(vencimentoStr, sizeof(vencimentoStr), "%d/%m/%Y", localtime(&conta.vencimento));
        printf("Conta %d:\n  Código: %d\n  Fornecedor: %s\n  Valor: R$ %.2f\n  Vencimento: %s\n  Status: %s\n", 
            ++i, conta.codigo, conta.fornecedor, conta.valor, vencimentoStr, conta.pago ? "Pago" : "Pendente");
    }

    fclose(txt);
}

void listarContas() {
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL) {
        printf("Erro na interpretação do formato do arquivo!\n");
        return;
    }
    fread(&formatoReg, sizeof(int), 1, formatoArq);
    fclose(formatoArq);

    if (formatoReg == 1) {
        listarContasBin();
    } else {
        listarContasTxt();
    }
}

void excluirContaBin(int codigo) {
    FILE *bin = fopen("arquivos/contas.bin", "rb");
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

    ContaPagar conta;
    int encontrado = 0;

    while (fread(&conta, sizeof(ContaPagar), 1, bin)) {
        if (conta.codigo == codigo) {
            encontrado = 1;
        } else {
            fwrite(&conta, sizeof(ContaPagar), 1, temp);
        }
    }

    fclose(bin);
    fclose(temp);

    if (encontrado) {
        remove("arquivos/contas.bin");
        rename("arquivos/temp.bin", "arquivos/contas.bin");
        printf("Conta removida com sucesso!\n");
    } else {
        remove("arquivos/temp.bin");
        printf("Conta com código %d não encontrada!\n", codigo);
    }
}

void excluirContaTxt(int codigo) {
    FILE *txt = fopen("arquivos/contas.txt", "r");
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

    ContaPagar conta;
    int encontrado = 0;

    while (fscanf(txt, "%d|%[^|]|%f|%ld|%d\n", &conta.codigo, conta.fornecedor, &conta.valor, &conta.vencimento, &conta.pago) != EOF) {
        if (conta.codigo == codigo) {
            encontrado = 1;
        } else {
            fprintf(temp, "%d|%s|%.2f|%ld|%d\n", conta.codigo, conta.fornecedor, conta.valor, conta.vencimento, conta.pago);
        }
    }

    fclose(txt);
    fclose(temp);

    if (encontrado) {
        remove("arquivos/contas.txt");
        rename("arquivos/temp.txt", "arquivos/contas.txt");
        printf("Conta removida com sucesso!\n");
    } else {
        remove("arquivos/temp.txt");
        printf("Conta com código %d não encontrada!\n", codigo);
    }
}

void excluirConta(int codigo) {
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL) {
        printf("Erro na interpretação do formato do arquivo!\n");
        return;
    }

    fread(&formatoReg, sizeof(int), 1, formatoArq);
    fclose(formatoArq);

    if (formatoReg == 1) {
        excluirContaBin(codigo);
    } else {
        excluirContaTxt(codigo);
    }
}

void baixarConta(int codigo) {
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL) {
        printf("Erro ao interpretar o formato do arquivo!\n");
        return;
    }
    fread(&formatoReg, sizeof(int), 1, formatoArq);
    fclose(formatoArq);

    if (formatoReg == 1) {
        baixarContaBin(codigo);
    } else {
        baixarContaTxt(codigo);
    }
}

void baixarContaBin(int codigo) {
    FILE *bin = fopen("arquivos/contas.bin", "rb");
    if (bin == NULL) {
        printf("Erro ao abrir o arquivo binário!\n");
        return;
    }

    FILE *temp = fopen("arquivos/temp.bin", "wb");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(bin);
        return;
    }

    ContaPagar conta;
    int encontrado = 0;

    while (fread(&conta, sizeof(ContaPagar), 1, bin)) {
        if (conta.codigo == codigo && !conta.pago) {
            encontrado = 1;
            conta.pago = 1;

            // Chamada corrigida com todos os parâmetros necessários
            deduzirCaixa(conta.codigo, conta.fornecedor, conta.valor, time(NULL));
        }
        fwrite(&conta, sizeof(ContaPagar), 1, temp);
    }

    fclose(bin);
    fclose(temp);

    if (encontrado) {
        remove("arquivos/contas.bin");
        rename("arquivos/temp.bin", "arquivos/contas.bin");
        printf("Conta com código %d marcada como paga.\n", codigo);
    } else {
        remove("arquivos/temp.bin");
        printf("Conta com código %d não encontrada ou já paga.\n", codigo);
    }
}


void baixarContaTxt(int codigo) {
    FILE *txt = fopen("arquivos/contas.txt", "r");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo texto!\n");
        return;
    }

    FILE *temp = fopen("arquivos/temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(txt);
        return;
    }

    ContaPagar conta;
    int encontrado = 0;

while (fscanf(txt, "%d|%[^|]|%f|%ld|%d\n", &conta.codigo, conta.fornecedor, &conta.valor, &conta.vencimento, &conta.pago) != EOF) {
    if (conta.codigo == codigo && !conta.pago) {
        encontrado = 1;
        conta.pago = 1;

        // Chamada corrigida com todos os parâmetros
        deduzirCaixa(conta.codigo, conta.fornecedor, conta.valor, time(NULL)); 
    }
    fprintf(temp, "%d|%s|%.2f|%ld|%d\n", conta.codigo, conta.fornecedor, conta.valor, conta.vencimento, conta.pago);
}


    fclose(txt);
    fclose(temp);

    if (encontrado) {
        remove("arquivos/contas.txt");
        rename("arquivos/temp.txt", "arquivos/contas.txt");
        printf("Conta com código %d marcada como paga.\n", codigo);
    } else {
        remove("arquivos/temp.txt");
        printf("Conta com código %d não encontrada ou já paga.\n", codigo);
    }
}



