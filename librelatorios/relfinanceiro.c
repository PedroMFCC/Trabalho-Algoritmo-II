#include "relatorios.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <financeiro.h>

FiltrosRelatorio obterFiltrosRelatorio() {
    FiltrosRelatorio filtros = {0}; 

    printf("Deseja aplicar filtro de data? (1 para sim, 0 para não): ");
    scanf("%d", &filtros.filtroData);

    if (filtros.filtroData) {
        int dia, mes, ano;
        printf("Digite a data de início (dd mm aaaa): ");
        scanf("%d %d %d", &dia, &mes, &ano);
        struct tm tm_inicio = {0};
        tm_inicio.tm_mday = dia;
        tm_inicio.tm_mon = mes - 1;
        tm_inicio.tm_year = ano - 1900;
        filtros.dataInicio = mktime(&tm_inicio);

        printf("Digite a data de fim (dd mm aaaa): ");
        scanf("%d %d %d", &dia, &mes, &ano);
        struct tm tm_fim = {0};
        tm_fim.tm_mday = dia;
        tm_fim.tm_mon = mes - 1;
        tm_fim.tm_year = ano - 1900;
        filtros.dataFim = mktime(&tm_fim);
    }

    printf("Deseja aplicar filtro por nome? (1 para sim, 0 para não): ");
    int filtroNome;
    scanf("%d", &filtroNome);

    if (filtroNome) {
        printf("Digite o nome do cliente ou fornecedor: ");
        scanf(" %99[^\n]", filtros.filtro);
    } else {
        filtros.filtro[0] = '\0';
    }

    return filtros;
}


int obterFormatoRegistro() {
    int formato;
    FILE *arq = fopen("arquivos/formato.bin", "rb");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo de formato!\n");
        return -1; 
    }
    fread(&formato, sizeof(int), 1, arq);
    fclose(arq);
    return formato;
}


void gerarRelatorioCaixaBinario(FiltrosRelatorio filtros, FILE *saida) {
    char caminhoArquivo[100];
    sprintf(caminhoArquivo, "arquivos/caixa.bin");

    FILE *arquivo = fopen(caminhoArquivo, "rb");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de caixa: %s\n", caminhoArquivo);
        return;
    }

    Caixa lancamento;
    char dataFormatada[20];

    fprintf(saida, "Relatório de Caixa (Binário)\n");
    if (filtros.filtroData) {
        strftime(dataFormatada, sizeof(dataFormatada), "%d/%m/%Y", localtime(&filtros.dataInicio));
        fprintf(saida, "Data de início: %s\n", dataFormatada);
        strftime(dataFormatada, sizeof(dataFormatada), "%d/%m/%Y", localtime(&filtros.dataFim));
        fprintf(saida, "Data de fim: %s\n", dataFormatada);
    }
    fprintf(saida, "=====================================\n");
    fprintf(saida, "Código | Nome do Cliente | Valor | Data\n");
    fprintf(saida, "----------------------------------------\n");

    while (fread(&lancamento, sizeof(Caixa), 1, arquivo) == 1) {
       
        if (filtros.filtroData && (lancamento.dataPagamento < filtros.dataInicio || lancamento.dataPagamento > filtros.dataFim)) {
            continue; 
        }

        
        if (strlen(filtros.filtro) > 0 && strstr(lancamento.nomeCliente, filtros.filtro) == NULL) {
            continue; 
        }

        
        strftime(dataFormatada, sizeof(dataFormatada), "%d/%m/%Y", localtime(&lancamento.dataPagamento));
        fprintf(saida, "%d | %s | %.2f | %s\n", lancamento.codigo, lancamento.nomeCliente, lancamento.valor, dataFormatada);
    }

    fclose(arquivo);
}


void gerarRelatorioCaixaTexto(FiltrosRelatorio filtros, FILE *saida) {
    char caminhoArquivo[100];
    sprintf(caminhoArquivo, "arquivos/caixa.txt");

    FILE *arquivo = fopen(caminhoArquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de caixa: %s\n", caminhoArquivo);
        return;
    }

    Caixa lancamento;
    char dataFormatada[20];
    char linha[256];

    fprintf(saida, "Relatório de Caixa (Texto)\n");
    if (filtros.filtroData) {
        strftime(dataFormatada, sizeof(dataFormatada), "%d/%m/%Y", localtime(&filtros.dataInicio));
        fprintf(saida, "Data de início: %s\n", dataFormatada);
        strftime(dataFormatada, sizeof(dataFormatada), "%d/%m/%Y", localtime(&filtros.dataFim));
        fprintf(saida, "Data de fim: %s\n", dataFormatada);
    }
    fprintf(saida, "=====================================\n");
    fprintf(saida, "Código | Nome do Cliente | Valor | Data\n");
    fprintf(saida, "----------------------------------------\n");

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (sscanf(linha, "%d|%99[^|]|%d|%f|%ld", &lancamento.codigo, lancamento.nomeCliente, &lancamento.tipoPagamento, &lancamento.valor, &lancamento.dataPagamento) == 5) {
          
            if (filtros.filtroData && (lancamento.dataPagamento < filtros.dataInicio || lancamento.dataPagamento > filtros.dataFim)) {
                continue; 
            }

            
            if (strlen(filtros.filtro) > 0 && strstr(lancamento.nomeCliente, filtros.filtro) == NULL) {
                continue;
            }

            
            strftime(dataFormatada, sizeof(dataFormatada), "%d/%m/%Y", localtime(&lancamento.dataPagamento));
            fprintf(saida, "%d | %s | %.2f | %s\n", lancamento.codigo, lancamento.nomeCliente, lancamento.valor, dataFormatada);
        }
    }

    fclose(arquivo);
}


void gerarRelatorioContasReceberBinario(FiltrosRelatorio filtros, FILE *saida) {
    char caminhoArquivo[100];
    sprintf(caminhoArquivo, "arquivos/contas_receber.bin");

    FILE *arquivo = fopen(caminhoArquivo, "rb");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de contas a receber: %s\n", caminhoArquivo);
        return;
    }

    ContaReceber conta;
    char dataFormatada[20];

    fprintf(saida, "Relatório de Contas a Receber (Binário)\n");
    if (filtros.filtroData) {
        strftime(dataFormatada, sizeof(dataFormatada), "%d/%m/%Y", localtime(&filtros.dataInicio));
        fprintf(saida, "Data de início: %s\n", dataFormatada);
        strftime(dataFormatada, sizeof(dataFormatada), "%d/%m/%Y", localtime(&filtros.dataFim));
        fprintf(saida, "Data de fim: %s\n", dataFormatada);
    }
    fprintf(saida, "=====================================\n");
    fprintf(saida, "Código | Nome do Cliente | Valor | Vencimento | Status\n");
    fprintf(saida, "-----------------------------------------------------\n");

    while (fread(&conta, sizeof(ContaReceber), 1, arquivo) == 1) {
        
        if (filtros.filtroData && (conta.vencimento < filtros.dataInicio || conta.vencimento > filtros.dataFim)) {
            continue; 
        }

       
        if (strlen(filtros.filtro) > 0 && strstr(conta.nomeCliente, filtros.filtro) == NULL) {
            continue; 
        }

       
        strftime(dataFormatada, sizeof(dataFormatada), "%d/%m/%Y", localtime(&conta.vencimento));
        fprintf(saida, "%d | %s | %.2f | %s | %s\n", conta.codigo, conta.nomeCliente, conta.valor, dataFormatada, conta.recebido ? "Recebido" : "Pendente");
    }

    fclose(arquivo);
}


void gerarRelatorioContasReceberTexto(FiltrosRelatorio filtros, FILE *saida) {
    char caminhoArquivo[100];
    sprintf(caminhoArquivo, "arquivos/contas_receber.txt");

    FILE *arquivo = fopen(caminhoArquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de contas a receber: %s\n", caminhoArquivo);
        return;
    }

    ContaReceber conta;
    char dataFormatada[20];
    char linha[256];

    fprintf(saida, "Relatório de Contas a Receber (Texto)\n");
    if (filtros.filtroData) {
        strftime(dataFormatada, sizeof(dataFormatada), "%d/%m/%Y", localtime(&filtros.dataInicio));
        fprintf(saida, "Data de início: %s\n", dataFormatada);
        strftime(dataFormatada, sizeof(dataFormatada), "%d/%m/%Y", localtime(&filtros.dataFim));
        fprintf(saida, "Data de fim: %s\n", dataFormatada);
    }
    fprintf(saida, "======================================================\n");
    fprintf(saida, "Código | Nome do Cliente | Valor | Vencimento | Status\n");
    fprintf(saida, "--------------------------------------------------------\n");

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (sscanf(linha, "%d|%99[^|]|%f|%ld|%ld|%d", &conta.codigo, conta.nomeCliente, &conta.valor, &conta.vencimento, &conta.dataRecebido, &conta.recebido) == 6) {
            
            if (filtros.filtroData && (conta.vencimento < filtros.dataInicio || conta.vencimento > filtros.dataFim)) {
                continue; 
            }

            
            if (strlen(filtros.filtro) > 0 && strstr(conta.nomeCliente, filtros.filtro) == NULL) {
                continue; 
            }

            
            strftime(dataFormatada, sizeof(dataFormatada), "%d/%m/%Y", localtime(&conta.vencimento));
            fprintf(saida, "%d | %s | %.2f | %s | %s\n", conta.codigo, conta.nomeCliente, conta.valor, dataFormatada, conta.recebido ? "Recebido" : "Pendente");
        }
    }

    fclose(arquivo);
}


void gerarRelatorioContasPagarBinario(FiltrosRelatorio filtros, FILE *saida) {
    char caminhoArquivo[100];
    sprintf(caminhoArquivo, "arquivos/contas.bin");

    FILE *arquivo = fopen(caminhoArquivo, "rb");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de contas a pagar: %s\n", caminhoArquivo);
        return;
    }

    ContaPagar conta;
    char dataFormatada[20];

    fprintf(saida, "Relatório de Contas a Pagar (Binário)\n");
    if (filtros.filtroData) {
        strftime(dataFormatada, sizeof(dataFormatada), "%d/%m/%Y", localtime(&filtros.dataInicio));
        fprintf(saida, "Data de início: %s\n", dataFormatada);
        strftime(dataFormatada, sizeof(dataFormatada), "%d/%m/%Y", localtime(&filtros.dataFim));
        fprintf(saida, "Data de fim: %s\n", dataFormatada);
    }
    fprintf(saida, "=================================================\n");
    fprintf(saida, "Código | Fornecedor | Valor | Vencimento | Status\n");
    fprintf(saida, "------------------------------------------------\n");

    while (fread(&conta, sizeof(ContaPagar), 1, arquivo) == 1) {
        
        if (filtros.filtroData && (conta.vencimento < filtros.dataInicio || conta.vencimento > filtros.dataFim)) {
            continue; 
        }

       
        if (strlen(filtros.filtro) > 0 && strstr(conta.fornecedor, filtros.filtro) == NULL) {
            continue; 
        }

       
        strftime(dataFormatada, sizeof(dataFormatada), "%d/%m/%Y", localtime(&conta.vencimento));
        fprintf(saida, "%7d | %s | %.2f | %s | %s\n", conta.codigo, conta.fornecedor, conta.valor, dataFormatada, conta.pago ? "Pago" : "Pendente");
    }

    fclose(arquivo);
}


void gerarRelatorioContasPagarTexto(FiltrosRelatorio filtros, FILE *saida) {
    char caminhoArquivo[100];
    sprintf(caminhoArquivo, "arquivos/contas.txt");

    FILE *arquivo = fopen(caminhoArquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de contas a pagar: %s\n", caminhoArquivo);
        return;
    }

    ContaPagar conta;
    char dataFormatada[20];
    char linha[256];

    fprintf(saida, "Relatório de Contas a Pagar (Texto)\n");
    if (filtros.filtroData) {
        strftime(dataFormatada, sizeof(dataFormatada), "%d/%m/%Y", localtime(&filtros.dataInicio));
        fprintf(saida, "Data de início: %s\n", dataFormatada);
        strftime(dataFormatada, sizeof(dataFormatada), "%d/%m/%Y", localtime(&filtros.dataFim));
        fprintf(saida, "Data de fim: %s\n", dataFormatada);
    }
    fprintf(saida, "==================================================\n");
    fprintf(saida, "Código | Fornecedor | Valor | Vencimento | Status\n");
    fprintf(saida, "--------------------------------------------------\n");

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (sscanf(linha, "%d|%99[^|]|%f|%ld|%ld|%d", &conta.codigo, conta.fornecedor, &conta.valor, &conta.vencimento, &conta.dataPagamento, &conta.pago) == 6) {
          
            if (filtros.filtroData && (conta.vencimento < filtros.dataInicio || conta.vencimento > filtros.dataFim)) {
                continue; 
            }

            
            if (strlen(filtros.filtro) > 0 && strstr(conta.fornecedor, filtros.filtro) == NULL) {
                continue; 
            }

           
            strftime(dataFormatada, sizeof(dataFormatada), "%d/%m/%Y", localtime(&conta.vencimento));
            fprintf(saida, "%7d | %s | %.2f | %s | %s\n", conta.codigo, conta.fornecedor, conta.valor, dataFormatada, conta.pago ? "Pago" : "Pendente");
        }
    }

    fclose(arquivo);
}


void gerarRelatorio(TipoRelatorio tipo, FiltrosRelatorio filtros, FILE *saida) {
    int formato = obterFormatoRegistro();

    if (formato == -1) {
        printf("Erro ao determinar o formato de registro.\n");
        return;
    }

    switch (tipo) {
        case RELATORIO_CAIXA:
            if (formato == 1) {
                gerarRelatorioCaixaBinario(filtros, saida);
            } else {
                gerarRelatorioCaixaTexto(filtros, saida);
            }
            break;

        case RELATORIO_CONTAS_RECEBER:
            if (formato == 1) {
                gerarRelatorioContasReceberBinario(filtros, saida);
            } else {
                gerarRelatorioContasReceberTexto(filtros, saida);
            }
            break;

        case RELATORIO_CONTAS_PAGAR:
            if (formato == 1) {
                gerarRelatorioContasPagarBinario(filtros, saida);
            } else {
                gerarRelatorioContasPagarTexto(filtros, saida);
            }
            break;

        default:
            printf("Tipo de relatório não reconhecido.\n");
            break;
    }
}