#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "contasAreceber.h"
#include "controleC.h"

void regContaReceberBin(ContaReceber conta) {
    FILE *bin = fopen("arquivos/contas_receber.bin", "ab");
    if (bin == NULL) {
        printf("Erro ao abrir o arquivo binário! regContaReceberBin\n");
        return;
    }

    fwrite(&conta, sizeof(ContaReceber), 1, bin);
    fclose(bin);
    printf("Conta registrada em binário com sucesso!\n");
}

void regContaReceberTxt(ContaReceber conta) {
    FILE *txt = fopen("arquivos/contas_receber.txt", "a");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo texto! regContaReceberTxt\n");
        return;
    }

    fprintf(txt, "%d|%s|%.2f|%ld|%ld|%d\n", conta.codigo, conta.nomeCliente, conta.valor, conta.vencimento, conta.dataRecebido, conta.recebido);
    fclose(txt);
    printf("Conta registrada em texto com sucesso!\n");
}

void regContaReceberPath(ContaReceber conta) {
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL) {
        printf("Erro na interpretação do formato do arquivo!\n");
        return;
    }

    fread(&formatoReg, sizeof(int), 1, formatoArq);
    fclose(formatoArq);

    if (formatoReg == 1) {
        regContaReceberBin(conta);
    } else {
        regContaReceberTxt(conta);
    }
}

void regContaReceber() {
    ContaReceber conta;
    int dia, mes, ano;

    printf("Digite o código da conta: ");
    scanf("%d", &conta.codigo);
    getchar();

    printf("Digite o nome do cliente: ");
    fgets(conta.nomeCliente, sizeof(conta.nomeCliente), stdin);
    conta.nomeCliente[strcspn(conta.nomeCliente, "\n")] = 0; // Remove a nova linha

    printf("Digite o valor: ");
    scanf("%f", &conta.valor);
    printf("Digite a data de vencimento (dd mm aaaa): ");
    scanf("%d %d %d", &dia, &mes, &ano);

    struct tm tm = {0};
    tm.tm_mday = dia;
    tm.tm_mon = mes - 1;
    tm.tm_year = ano - 1900;
    conta.vencimento = mktime(&tm);
    conta.dataRecebido = 0;  // Inicialmente não recebido
    conta.recebido = 0;      // Inicialmente pendente

    regContaReceberPath(conta);
}

void listarContasReceberBin() {
    FILE *bin = fopen("arquivos/contas_receber.bin", "rb");
    if (bin == NULL) {
        printf("Erro ao abrir o arquivo binário! listarContasReceberBin\n");
        return;
    }

    ContaReceber conta;
    int i = 0;
    printf("\nContas a Receber armazenadas em binário:\n");
    while (fread(&conta, sizeof(ContaReceber), 1, bin)) {
        char vencimentoStr[20], dataRecebidoStr[20];
        strftime(vencimentoStr, sizeof(vencimentoStr), "%d/%m/%Y", localtime(&conta.vencimento));
        strftime(dataRecebidoStr, sizeof(dataRecebidoStr), "%d/%m/%Y", localtime(&conta.dataRecebido));

        printf("Conta %d:\n Código: %d\n Nome do Cliente: %s\n Valor: R$ %.2f\n Vencimento: %s\n Status: %s\n", 
            ++i, conta.codigo, conta.nomeCliente, conta.valor, vencimentoStr, conta.recebido ? "Recebido" : "Pendente");

        if (conta.recebido) {
            printf("  Data Recebimento: %s\n", dataRecebidoStr);
        }
    }

    fclose(bin);
}

void listarContasReceberTxt() {
    FILE *txt = fopen("arquivos/contas_receber.txt", "r");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo texto! listarContasReceberTxt\n");
        return;
    }

    ContaReceber conta;
    int i = 0;
    printf("\nContas a Receber armazenadas em texto:\n");
    while (fscanf(txt, "%d|%99[^|]|%f|%ld|%ld|%d\n", &conta.codigo, conta.nomeCliente, &conta.valor, &conta.vencimento, &conta.dataRecebido, &conta.recebido) != EOF) {
        char vencimentoStr[20], dataRecebidoStr[20];
        strftime(vencimentoStr, sizeof(vencimentoStr), "%d/%m/%Y", localtime(&conta.vencimento));
        strftime(dataRecebidoStr, sizeof(dataRecebidoStr), "%d/%m/%Y", localtime(&conta.dataRecebido));

        printf("Conta %d:\n Código: %d\n Nome do Cliente: %s\n Valor: R$ %.2f\n Vencimento: %s\n Status: %s\n", 
            ++i, conta.codigo, conta.nomeCliente, conta.valor, vencimentoStr, conta.recebido ? "Recebido" : "Pendente");

        if (conta.recebido) {
            printf("  Data Recebimento: %s\n", dataRecebidoStr);
        }
    }

    fclose(txt);
}

void listarContasReceber() {
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL) {
        printf("Erro na interpretação do formato do arquivo!\n");
        return;
    }

    fread(&formatoReg, sizeof(int), 1, formatoArq);
    fclose(formatoArq);

    if (formatoReg == 1) {
        listarContasReceberBin();
    } else {
        listarContasReceberTxt();
    }
}

void excluirContasReceberBin(int codigo) {
    FILE *bin = fopen("arquivos/contas_receber.bin", "rb");
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

    ContaReceber conta;
    int encontrado = 0;

    while (fread(&conta, sizeof(ContaReceber), 1, bin)) {
        if (conta.codigo == codigo) {
            encontrado = 1;
        } else {
            fwrite(&conta, sizeof(ContaReceber), 1, temp);
        }
    }

    fclose(bin);
    fclose(temp);

    if (encontrado) {
        remove("arquivos/contas_receber.bin");
        rename("arquivos/temp.bin", "arquivos/contas_receber.bin");
        printf("Conta removida com sucesso!\n");
    } else {
        remove("arquivos/temp.bin");
        printf("Conta com código %d não encontrada!\n", codigo);
    }
}

void excluirContasReceberTxt(int codigo) {
    FILE *txt = fopen("arquivos/contas_receber.txt", "r");
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

    ContaReceber conta;
    int encontrado = 0;

    while (fscanf(txt, "%d|%99[^|]|%f|%ld|%ld|%d\n", &conta.codigo, conta.nomeCliente, &conta.valor, &conta.vencimento, &conta.dataRecebido, &conta.recebido) != EOF) {
        if (conta.codigo == codigo) {
            encontrado = 1;
        } else {
            fprintf(temp, "%d|%s|%.2f|%ld|%ld|%d\n", conta.codigo, conta.nomeCliente, conta.valor, conta.vencimento, conta.dataRecebido, conta.recebido);
        }
    }

    fclose(txt);
    fclose(temp);

    if (encontrado) {
        remove("arquivos/contas_receber.txt");
        rename("arquivos/temp.txt ", "arquivos/contas_receber.txt");
        printf("Conta removida com sucesso!\n");
    } else {
        remove("arquivos/temp.txt");
        printf("Conta com código %d não encontrada!\n", codigo);
    }
}

void excluirContasReceber(int codigo) {
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL) {
        printf("Erro na interpretação do formato do arquivo!\n");
        return;
    }

    fread(&formatoReg, sizeof(int), 1, formatoArq);
    fclose(formatoArq);

    if (formatoReg == 1) {
        excluirContasReceberBin(codigo);
    } else {
        excluirContasReceberTxt(codigo);
    }
}

void baixarContaReceberBin(int codigo) {
    FILE *bin = fopen("arquivos/contas_receber.bin", "rb");
    if (bin == NULL) {
        printf("Erro ao abrir o arquivo binário! baixarContaReceberBin\n");
        return;
    }

    FILE *temp = fopen("arquivos/temp.bin", "wb");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(bin);
        return;
    }

    ContaReceber conta;
    int encontrado = 0;

    while (fread(&conta, sizeof(ContaReceber), 1, bin)) {
        if (conta.codigo == codigo && conta.recebido == 0) {
            encontrado = 1;
            conta.recebido = 1;  // Marca como recebido
            conta.dataRecebido = time(NULL);  // Marca a data de recebimento

            // Chama a função somarcaixa para registrar no caixa
            somarcaixa(conta.codigo, conta.nomeCliente, conta.valor, conta.dataRecebido);
        }
        fwrite(&conta, sizeof(ContaReceber), 1, temp);  // Escreve no arquivo temporário
    }

    fclose(bin);
    fclose(temp);

    if (encontrado) {
        remove("arquivos/contas_receber.bin");
        rename("arquivos/temp.bin", "arquivos/contas_receber.bin");
        printf("Conta %d marcada como recebida!\n", codigo);
    } else {
        remove("arquivos/temp.bin");
        printf("Conta com código %d não encontrada ou já foi recebida.\n", codigo);
    }
}

void baixarContaReceberTxt(int codigo) {
    FILE *txt = fopen("arquivos/contas_receber.txt", "r");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo texto! baixarContaReceberTxt\n");
        return;
    }

    FILE *temp = fopen("arquivos/temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(txt);
        return;
    }

    ContaReceber conta;
    int encontrado = 0;

    while (fscanf(txt, "%d|%99[^|]|%f|%ld|%ld|%d\n", &conta.codigo, conta.nomeCliente, &conta.valor, &conta.vencimento, &conta.dataRecebido, &conta.recebido) != EOF) {
        if (conta.codigo == codigo && conta.recebido == 0) {
            encontrado = 1;
            conta.recebido = 1;  // Marca como recebido
            conta.dataRecebido = time(NULL);  // Marca a data de recebimento

            // Chama a função somarcaixa para registrar no caixa
            somarcaixa(conta.codigo, conta.nomeCliente, conta.valor, conta.dataRecebido);
        }
        fprintf(temp, "%d|%s|%.2f|%ld|%ld|%d\n", conta.codigo, conta.nomeCliente, conta.valor, conta.vencimento, conta.dataRecebido, conta.recebido);
    }

    fclose(txt);
    fclose(temp);

    if (encontrado) {
        remove("arquivos/contas_receber.txt");
        rename("arquivos/temp.txt", "arquivos/contas_receber.txt");
        printf("Conta %d marcada como recebida!\n", codigo);
    } else {
        remove("arquivos/temp.txt");
        printf("Conta com código %d não encontrada ou já foi recebida.\n", codigo);
    }
}

void baixarContaReceber(int codigo) {
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL) {
        printf("Erro na interpretação do formato do arquivo!\n");
        return;
    }

    fread(&formatoReg, sizeof(int), 1, formatoArq);
    fclose(formatoArq);

    if (formatoReg == 1) {
        baixarContaReceberBin(codigo);
    } else {
        baixarContaReceberTxt(codigo);
    }
}



