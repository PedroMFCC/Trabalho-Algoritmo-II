#include "financeiro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 

// Função para obter o saldo do caixa
float obterSaldoCaixa() {
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL) {
        printf("Erro ao acessar o formato do arquivo!\n");
        return 0.0f;
    }

    fread(&formatoReg, sizeof(int), 1, formatoArq);
    fclose(formatoArq);

    FILE *arquivoCaixa;
    Caixa lancamento;
    float saldo = 0.0f;

    if (formatoReg == 1) { 
        arquivoCaixa = fopen("arquivos/caixa.bin", "rb");
        if (arquivoCaixa == NULL) {
            printf("Erro ao abrir o arquivo binário de caixa!\n");
            return 0.0f;
        }

        while (fread(&lancamento, sizeof(Caixa), 1, arquivoCaixa) == 1) {
            saldo += lancamento.valor; // Soma ou subtrai diretamente o valor
        }

    } else { // Arquivo em formato texto
        arquivoCaixa = fopen("arquivos/caixa.txt", "r");
        if (arquivoCaixa == NULL) {
            printf("Erro ao abrir o arquivo texto de caixa!\n");
            return 0.0f;
        }

        while (fscanf(arquivoCaixa, "%d|%99[^|]|%d|%f|%ld\n",
                      &lancamento.codigo, lancamento.nomeCliente, &lancamento.tipoPagamento,
                      &lancamento.valor, &lancamento.dataPagamento) == 5) {
            saldo += lancamento.valor; // Soma ou subtrai diretamente o valor
        }
    }

    fclose(arquivoCaixa);
    return saldo;
}

// Função para registrar o pagamento no formato binário
void registrarPagamentoBin(Caixa registro) {
    FILE *caixaBin = fopen("arquivos/caixa.bin", "ab");
    if (caixaBin == NULL) {
        printf("Erro ao abrir o arquivo binário do caixa!\n");
        return;
    }

    fwrite(&registro, sizeof(Caixa), 1, caixaBin);
    fclose(caixaBin);
    printf("Pagamento de %s registrado no caixa (binário)!\n", registro.nomeCliente);
}

// Função para registrar o pagamento no formato texto
void registrarPagamentoTxt(Caixa registro) {
    FILE *caixaTxt = fopen("arquivos/caixa.txt", "a");
    if (caixaTxt == NULL) {
        printf("Erro ao abrir o arquivo de texto do caixa!\n");
        return;
    }

    fprintf(caixaTxt, "%d|%s|%d|+%.2f|%ld\n", registro.codigo, registro.nomeCliente, registro.tipoPagamento, registro.valor, registro.dataPagamento);
    fclose(caixaTxt);
    printf("Pagamento de %s registrado no caixa (texto)!\n", registro.nomeCliente);
}

// Função para registrar o pagamento (determina o formato)
void registrarPagamento() {
    Caixa registro;
    int tipoPagamento;
    float valor;

    printf("Digite o código do cliente: ");
    if (scanf("%d", &registro.codigo) != 1) {
        while (getchar() != '\n'); // Limpa o buffer
        printf("Entrada inválida! Tente novamente.\n");
        return;
    }

    printf("Digite o nome do cliente: ");
    getchar(); // Limpa o buffer
    fgets(registro.nomeCliente, sizeof(registro.nomeCliente), stdin);
    registro.nomeCliente[strcspn(registro.nomeCliente, "\n")] = 0; // Remove o '\n' da string

    printf("Digite o valor do pagamento: R$ ");
    if (scanf("%f", &valor) != 1) {
        while (getchar() != '\n'); // Limpa o buffer
        printf("Entrada inválida! Tente novamente.\n");
        return;
    }
    registro.valor = valor > 0 ? valor : +valor;

    printf("Digite o tipo de pagamento (1 para dinheiro, 2 para débito): ");
    if (scanf("%d", &tipoPagamento) != 1 || (tipoPagamento != 1 && tipoPagamento != 2)) {
        while (getchar() != '\n'); // Limpa o buffer
        printf("Entrada inválida! Tente novamente.\n");
        return;
    }
    registro.tipoPagamento = tipoPagamento;

    registro.dataPagamento = time(NULL);

    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL) {
        printf("Erro na interpretação do formato do arquivo!\n");
        return;
    }

    fread(&formatoReg, sizeof(int), 1, formatoArq);
    fclose(formatoArq);

    if (formatoReg == 1) {
        registrarPagamentoBin(registro);
    } else {
        registrarPagamentoTxt(registro);
    }
}



void registrarPagamentoCartaoCredito() {
    ContaReceber conta;
    regContaReceber(); 
}



// Função para deduzir um valor do caixa no formato binário
void deduzirCaixaBin(int codigoConta, const char *nomeFornecedor, float valor, time_t dataPagamento) {
    FILE *caixaBin = fopen("arquivos/caixa.bin", "ab");
    if (caixaBin == NULL) {
        printf("Erro ao abrir o arquivo binário de caixa!\n");
        return;
    }

    Caixa registro;
    registro.codigo = codigoConta;
    strcpy(registro.nomeCliente, nomeFornecedor);
    registro.tipoPagamento = DEDUCAO_CAIXA;
    registro.valor = -valor; // Deduzindo o valor
    registro.dataPagamento = dataPagamento;

    fwrite(&registro, sizeof(Caixa), 1, caixaBin);
    fclose(caixaBin);
    printf("Valor de %s deduzido do caixa (binário)!\n", nomeFornecedor);
}

// Função para deduzir um valor do caixa no formato texto
void deduzirCaixaTxt(int codigoConta, const char *nomeFornecedor, float valor, time_t dataPagamento) {
    FILE *caixaTxt = fopen("arquivos/caixa.txt", "a");
    if (caixaTxt == NULL) {
        printf("Erro ao abrir o arquivo de texto de caixa!\n");
        return;
    }

    fprintf(caixaTxt, "%d|%s|%d|%.2f|%ld\n", codigoConta, nomeFornecedor, DEDUCAO_CAIXA, -valor, dataPagamento);
    fclose(caixaTxt);
    printf("Valor de %s deduzido do caixa (texto)!\n", nomeFornecedor);
}

// Função para deduzir o caixa (determinando o formato)
void deduzirCaixa(int codigoConta, const char *nomeFornecedor, float valor, time_t dataPagamento) {
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL) {
        printf("Erro na interpretação do formato do arquivo!\n");
        return;
    }

    fread(&formatoReg, sizeof(int), 1, formatoArq);
    fclose(formatoArq);

    if (formatoReg == 1) {
        deduzirCaixaBin(codigoConta, nomeFornecedor, valor, dataPagamento);
    } else {
        deduzirCaixaTxt(codigoConta, nomeFornecedor, valor, dataPagamento);
    }
}

// Função para listar os lançamentos no caixa no formato binário
void listarLancamentosCaixaBin() {
    FILE *caixaBin = fopen("arquivos/caixa.bin", "rb");
    if (caixaBin == NULL) {
        printf("Erro ao abrir o arquivo binário de caixa!\n");
        return;
    }

    Caixa lancamento;
    printf("Lançamentos de Caixa (binário):\n");
    printf("Código | Em parte de:    | Forma de Pagamento       | Valor    | Data de Pagamento\n");
    printf("--------------------------------------------------------------------------------------\n");
    while (fread(&lancamento, sizeof(Caixa), 1, caixaBin) == 1) {
        const char *formaPagamento;
        char dataPagamento[20];
        struct tm *data = localtime(&lancamento.dataPagamento);

        // Determinar a forma de pagamento
        switch (lancamento.tipoPagamento) {
            case 1:
                formaPagamento = "Dinheiro";
                break;
            case 2:
                formaPagamento = "Cartão de Débito";
                break;
            case 3:
                formaPagamento = "Conta paga pela oficina";
                break;
            case 4:
                formaPagamento = "Cartão de Crédito";
                break;
            default:
                formaPagamento = "Desconhecido";
        }

        // Formatando a data
        strftime(dataPagamento, sizeof(dataPagamento), "%d/%m/%Y", data);

        printf("%7d | %-19s | %-24s | %10.2f | %s\n",
               lancamento.codigo, lancamento.nomeCliente, formaPagamento, lancamento.valor, dataPagamento);
    }

    fclose(caixaBin);
}


// Função para listar os lançamentos no caixa no formato texto
void listarLancamentosCaixaTxt() {
    FILE *caixaTxt = fopen("arquivos/caixa.txt", "r");
    if (caixaTxt == NULL) {
        printf("Erro ao abrir o arquivo texto de caixa!\n");
        return;
    }

    Caixa lancamento;
    printf("Lançamentos de Caixa (texto):\n");
    printf(" Código | Nome do Cliente          | Forma de Pagamento          |    Valor    | Data de Pagamento\n");
    printf("====================================================================================================\n");

    while (fscanf(caixaTxt, "%d|%99[^|]|%d|%f|%ld\n",
                  &lancamento.codigo, lancamento.nomeCliente, &lancamento.tipoPagamento,
                  &lancamento.valor, &lancamento.dataPagamento) == 5) {
        const char *formaPagamento;
        char dataPagamento[11];

        // Determinar a forma de pagamento
        switch (lancamento.tipoPagamento) {
            case 1:
                formaPagamento = "Dinheiro";
                break;
            case 2:
                formaPagamento = "Cartão de Débito";
                break;
            case 3:
                formaPagamento = "Conta paga pela oficina";
                break;
            case 4:
                formaPagamento = "Cartão de Crédito";
                break;
            default:
                formaPagamento = "Desconhecido";
        }

        // Formatar a data no estilo DD/MM/YYYY
        struct tm *data = localtime(&lancamento.dataPagamento);
        strftime(dataPagamento, sizeof(dataPagamento), "%d/%m/%Y", data);

        // Ajustar os espaços das colunas para alinhamento
        printf("%8d | %-24s | %-27s | %10.2f | %s\n",
               lancamento.codigo, lancamento.nomeCliente, formaPagamento, lancamento.valor, dataPagamento);
    }

    fclose(caixaTxt);
}


// Função para listar os lançamentos no caixa (determinando o formato)
void listarLancamentosCaixa() {
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL) {
        printf("Erro na interpretação do formato do arquivo!\n");
        return;
    }

    fread(&formatoReg, sizeof(int), 1, formatoArq);
    fclose(formatoArq);

    if (formatoReg == 1) {
        listarLancamentosCaixaBin();
    } else {
        listarLancamentosCaixaTxt();
    }
}


// Função para registrar no caixa no formato binário
void somarcaixaBin(int codigoConta, const char *nomeCliente, float valor, time_t dataRecebimento) {
    FILE *caixaBin = fopen("arquivos/caixa.bin", "ab");
    if (caixaBin == NULL) {
        printf("Erro ao abrir o arquivo binário de caixa!\n");
        return;
    }

    Caixa registro;
    registro.codigo = codigoConta;
    strcpy(registro.nomeCliente, nomeCliente);
    registro.tipoPagamento = 4; 
    registro.valor = valor;      
    registro.dataPagamento = dataRecebimento;

    fwrite(&registro, sizeof(Caixa), 1, caixaBin);
    fclose(caixaBin);
    printf("Conta %d registrada no caixa (binário)!\n", codigoConta);
}

// Função para registrar no caixa no formato texto
void somarcaixaTxt(int codigoConta, const char *nomeCliente, float valor, time_t dataRecebimento) {
    FILE *caixaTxt = fopen("arquivos/caixa.txt", "a");
    if (caixaTxt == NULL) {
        printf("Erro ao abrir o arquivo de texto de caixa!\n");
        return;
    }

    fprintf(caixaTxt, "%d|%s|%d|%.2f|%ld\n", codigoConta, nomeCliente, 4, valor, dataRecebimento);
    fclose(caixaTxt);
    printf("Conta %d registrada no caixa (texto)!\n", codigoConta);
}

// Função para registrar no caixa (determinando o formato)
void somarcaixa(int codigoConta, const char *nomeCliente, float valor, time_t dataRecebimento) {
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL) {
        printf("Erro na interpretação do formato do arquivo!\n");
        return;
    }

    fread(&formatoReg, sizeof(int), 1, formatoArq);
    fclose(formatoArq);

    if (formatoReg == 1) {
        somarcaixaBin(codigoConta, nomeCliente, valor, dataRecebimento);
    } else {
        somarcaixaTxt(codigoConta, nomeCliente, valor, dataRecebimento);
    }
}

void excluirContaCaixaBin() {
    FILE *bin = fopen("arquivos/caixa.bin", "rb");
    if (bin == NULL) {
        printf("Erro: Não foi possível abrir o arquivo binário para leitura.\n");
        return;
    }

    FILE *temp = fopen("arquivos/temp.bin", "wb");
    if (temp == NULL) {
        printf("Erro: Não foi possível criar o arquivo temporário.\n");
        fclose(bin);
        return;
    }

    int codigoExcluir;
    printf("Digite o código do lançamento a excluir: ");
    if (scanf("%d", &codigoExcluir) != 1) {
        printf("Erro: Entrada inválida. Tente novamente.\n");
        fclose(bin);
        fclose(temp);
        remove("arquivos/temp.bin");
        return;
    }

    Caixa registro;
    int encontrado = 0;

    while (fread(&registro, sizeof(Caixa), 1, bin) == 1) {
        if (registro.codigo == codigoExcluir) {
            encontrado = 1; // Registro encontrado, não será copiado para o arquivo temporário
        } else {
            fwrite(&registro, sizeof(Caixa), 1, temp);
        }
    }

    fclose(bin);
    fclose(temp);

    if (encontrado) {
        if (remove("arquivos/caixa.bin") == 0 && rename("arquivos/temp.bin", "arquivos/caixa.bin") == 0) {
            printf("Lançamento removido com sucesso!\n");
        } else {
            printf("Erro: Não foi possível atualizar o arquivo binário.\n");
        }
    } else {
        remove("arquivos/temp.bin");
        printf("Erro: Lançamento com código %d não encontrado.\n", codigoExcluir);
    }
}

void excluirContaCaixaTxt() {
    FILE *txt = fopen("arquivos/caixa.txt", "r");
    if (txt == NULL) {
        printf("Erro: Não foi possível abrir o arquivo texto para leitura.\n");
        return;
    }

    FILE *temp = fopen("arquivos/temp.txt", "w");
    if (temp == NULL) {
        printf("Erro: Não foi possível criar o arquivo temporário.\n");
        fclose(txt);
        return;
    }

    int codigoExcluir;
    printf("Digite o código do lançamento a excluir: ");
    if (scanf("%d", &codigoExcluir) != 1) {
        printf("Erro: Entrada inválida. Tente novamente.\n");
        fclose(txt);
        fclose(temp);
        remove("arquivos/temp.txt");
        return;
    }

    Caixa registro;
    int encontrado = 0;

    while (fscanf(txt, "%d|%99[^|]|%d|%f|%ld\n",
                  &registro.codigo, registro.nomeCliente, &registro.tipoPagamento,
                  &registro.valor, &registro.dataPagamento) == 5) {
        if (registro.codigo == codigoExcluir) {
            encontrado = 1; // Registro encontrado, não será copiado para o arquivo temporário
        } else {
            fprintf(temp, "%d|%s|%d|%.2f|%ld\n", registro.codigo, registro.nomeCliente,
                    registro.tipoPagamento, registro.valor, registro.dataPagamento);
        }
    }

    fclose(txt);
    fclose(temp);

    if (encontrado) {
        if (remove("arquivos/caixa.txt") == 0 && rename("arquivos/temp.txt", "arquivos/caixa.txt") == 0) {
            printf("Lançamento removido com sucesso!\n");
        } else {
            printf("Erro: Não foi possível atualizar o arquivo texto.\n");
        }
    } else {
        remove("arquivos/temp.txt");
        printf("Erro: Lançamento com código %d não encontrado.\n", codigoExcluir);
    }
}


void excluirContaCaixa() {
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL) {
        printf("Erro: Não foi possível abrir o arquivo de formato.\n");
        return;
    }

    if (fread(&formatoReg, sizeof(int), 1, formatoArq) != 1) {
        printf("Erro: Não foi possível ler o formato do arquivo.\n");
        fclose(formatoArq);
        return;
    }
    fclose(formatoArq);

    if (formatoReg == 1) {
        excluirContaCaixaBin();
    } else {
        excluirContaCaixaTxt();
    }
}
