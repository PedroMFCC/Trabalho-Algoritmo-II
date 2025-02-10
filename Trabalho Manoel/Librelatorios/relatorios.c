#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "relatorios.h"
#include "../libfuncionarios/funcionarios.h"
#include "../libservicos/servicos.h"
#include "../libclientes/clientes.h"
#include "../libveiculos/veiculos.h"
#include "../LibAgendamento/agendamento.h"

// Função para coletar dados de produtividade dos funcionários
void coletarDadosProdutividade(ProdutividadeFuncionario *produtividade, int *numFuncionarios, int formato) {
    *numFuncionarios = 0;

    // Abre o arquivo de funcionários no formato correto
    FILE *arquivoFuncionarios;
    if (formato == 1) {
        arquivoFuncionarios = fopen("arquivos/funcionarios.bin", "rb");
    } else {
        arquivoFuncionarios = fopen("arquivos/funcionarios.txt", "r");
    }

    if (arquivoFuncionarios == NULL) {
        printf("Erro ao abrir o arquivo de funcionários.\n");
        return;
    }

    // Lê os funcionários
    Funcionario funcionario;
    if (formato == 1) {
        while (fread(&funcionario, sizeof(Funcionario), 1, arquivoFuncionarios)) {
            produtividade[*numFuncionarios].idFuncionario = funcionario.id;
            strcpy(produtividade[*numFuncionarios].nomeFuncionario, funcionario.nome);
            produtividade[*numFuncionarios].totalServicos = 0;
            produtividade[*numFuncionarios].totalComissao = 0.0;
            produtividade[*numFuncionarios].totalTempo = 0;
            (*numFuncionarios)++;
        }
    } else {
        char linha[256];
        while (fgets(linha, sizeof(linha), arquivoFuncionarios)) {
            sscanf(linha, "%d,%99[^,],%14[^,],%49[^,],%f",
                   &funcionario.id, funcionario.nome, funcionario.cpf, funcionario.cargo, &funcionario.salario);
            produtividade[*numFuncionarios].idFuncionario = funcionario.id;
            strcpy(produtividade[*numFuncionarios].nomeFuncionario, funcionario.nome);
            produtividade[*numFuncionarios].totalServicos = 0;
            produtividade[*numFuncionarios].totalComissao = 0.0;
            produtividade[*numFuncionarios].totalTempo = 0;
            (*numFuncionarios)++;
        }
    }
    fclose(arquivoFuncionarios);

    // Abre o arquivo de serviços no formato correto
    FILE *arquivoServicos;
    if (formato == 1) {
        arquivoServicos = fopen("arquivos/servicos.bin", "rb");
    } else {
        arquivoServicos = fopen("arquivos/servicos.txt", "r");
    }

    if (arquivoServicos == NULL) {
        printf("Erro ao abrir o arquivo de serviços.\n");
        return;
    }

    // Lê os serviços e atualiza a produtividade
    Servico servico;
    if (formato == 1) {
        while (fread(&servico, sizeof(Servico), 1, arquivoServicos)) {
            for (int i = 0; i < *numFuncionarios; i++) {
                if (servico.codigo == produtividade[i].idFuncionario) {
                    produtividade[i].totalServicos++;
                    produtividade[i].totalComissao += servico.comissao;
                    produtividade[i].totalTempo += servico.tempo;
                }
            }
        }
    } else {
        char linha[256];
        while (fgets(linha, sizeof(linha), arquivoServicos)) {
            sscanf(linha, "%d,%99[^,],%f,%f,%d,%d",
                   &servico.codigo, servico.descricao, &servico.preco, &servico.comissao, &servico.tempo, &servico.peca);
            for (int i = 0; i < *numFuncionarios; i++) {
                if (servico.codigo == produtividade[i].idFuncionario) {
                    produtividade[i].totalServicos++;
                    produtividade[i].totalComissao += servico.comissao;
                    produtividade[i].totalTempo += servico.tempo;
                }
            }
        }
    }
    fclose(arquivoServicos);
}

// Função para aplicar filtros ao relatório
void aplicarFiltros(ProdutividadeFuncionario *produtividade, int *numFuncionarios, int filtroFuncionario, int filtroServico, char *dataInicio, char *dataFim) {
    // Implementação dos filtros (pode ser expandida conforme necessário)
    if (filtroFuncionario != -1) {
        for (int i = 0; i < *numFuncionarios; i++) {
            if (produtividade[i].idFuncionario != filtroFuncionario) {
                for (int j = i; j < *numFuncionarios - 1; j++) {
                    produtividade[j] = produtividade[j + 1];
                }
                (*numFuncionarios)--;
                i--;
            }
        }
    }
}

void gerarRelatorioProdutividade(ProdutividadeFuncionario *produtividade, int numFuncionarios, int imprimirTela) {
    if (imprimirTela) {
        // Cabeçalho da tabela
        printf("\n================================================================================\n");
        printf("| %-20s | %-15s | %-15s | %-15s |\n", "Funcionário", "Total Serviços", "Total Comissão", "Total Tempo");
        printf("================================================================================\n");

        // Dados da tabela
        for (int i = 0; i < numFuncionarios; i++) {
            printf("| %-20s | %-15d | %-15.2f | %-15d |\n",
                   produtividade[i].nomeFuncionario,
                   produtividade[i].totalServicos,
                   produtividade[i].totalComissao,
                   produtividade[i].totalTempo);
        }

        // Rodapé da tabela
        printf("================================================================================\n");
    } else {
        // Caminho pré-definido para o arquivo CSV
        char caminhoArquivo[256] = "relatorios/relatorio_produtividade.csv";

        // Salva em arquivo CSV
        FILE *arquivo = fopen(caminhoArquivo, "w");
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo para escrita.\n");
            return;
        }
        fprintf(arquivo, "Funcionário,Total de Serviços,Total de Comissão,Total de Tempo\n");
        for (int i = 0; i < numFuncionarios; i++) {
            fprintf(arquivo, "%s,%d,%.2f,%d\n", produtividade[i].nomeFuncionario, produtividade[i].totalServicos, produtividade[i].totalComissao, produtividade[i].totalTempo);
        }
        fclose(arquivo);
        printf("Relatório salvo em %s\n", caminhoArquivo);
    }
}

void RelatorioProd() {
    ProdutividadeFuncionario produtividade[100];
    int numFuncionarios = 0;
    int filtroFuncionario = -1; // -1 significa sem filtro
    int filtroServico = -1; // -1 significa sem filtro
    char dataInicio[11], dataFim[11];
    int imprimirTela;

    // Lê o formato de armazenamento (binário ou texto)
    int formato;
    FILE *formatoFile = fopen("arquivos/formato.bin", "rb");
    if (formatoFile == NULL) {
        printf("Erro ao abrir o arquivo de formato.\n");
        return;
    }
    fread(&formato, sizeof(int), 1, formatoFile);
    fclose(formatoFile);

    // Coletar dados de produtividade
    coletarDadosProdutividade(produtividade, &numFuncionarios, formato);

    // Oferecer opções de filtro
    printf("Deseja aplicar filtros? (1 - Sim, 0 - Não): ");
    int aplicarFiltro;
    scanf("%d", &aplicarFiltro);
    if (aplicarFiltro) {
        printf("Digite o ID do funcionário para filtrar (ou -1 para todos): ");
        scanf("%d", &filtroFuncionario);
        printf("Digite o código do serviço para filtrar (ou -1 para todos): ");
        scanf("%d", &filtroServico);
        printf("Digite a data de início (DD/MM/AAAA): ");
        scanf("%s", dataInicio);
        printf("Digite a data de fim (DD/MM/AAAA): ");
        scanf("%s", dataFim);
    }

    // Aplicar filtros
    aplicarFiltros(produtividade, &numFuncionarios, filtroFuncionario, filtroServico, dataInicio, dataFim);

    // Escolher destino do relatório
    printf("Deseja imprimir o relatório na tela (1) ou salvar em arquivo CSV (0)? ");
    scanf("%d", &imprimirTela);

    // Gerar relatório
    gerarRelatorioProdutividade(produtividade, numFuncionarios, imprimirTela);
}

// Relatório de Serviços Realizados -------------------------------------------------------------------------------------------------------

void coletarDadosServicosRealizados(ServicoRealizado *servicos, int *numServicos, int formato) {
    *numServicos = 0;

    // Abre o arquivo de serviços realizados no formato correto
    FILE *arquivoServicos;
    if (formato == 1) {
        arquivoServicos = fopen("arquivos/agendamento.bin", "rb");
    } else {
        arquivoServicos = fopen("arquivos/agendamento.txt", "r");
    }

    if (arquivoServicos == NULL) {
        printf("Erro ao abrir o arquivo de serviços realizados.\n");
        return;
    }

    // Lê os serviços realizados
    Agendamento agendamento;
    if (formato == 1) {
        while (fread(&agendamento, sizeof(Agendamento), 1, arquivoServicos)) {
            strcpy(servicos[*numServicos].cliente.nome, agendamento.cliente);
            strcpy(servicos[*numServicos].veiculo.placa, agendamento.veiculo);
            strcpy(servicos[*numServicos].servico.descricao, agendamento.servico);
            strcpy(servicos[*numServicos].funcionario.nome, agendamento.funcionario);
            strcpy(servicos[*numServicos].servico.data, agendamento.data);
            (*numServicos)++;
        }
    } else {
        char linha[256];
        while (fgets(linha, sizeof(linha), arquivoServicos)) {
            sscanf(linha, "%99[^,],%99[^,],%99[^,],%99[^,],%10[^,]",
                   servicos[*numServicos].cliente.nome, servicos[*numServicos].veiculo.placa, servicos[*numServicos].servico.descricao,
                   servicos[*numServicos].funcionario.nome, servicos[*numServicos].servico.data);
            (*numServicos)++;
        }
    }
    fclose(arquivoServicos);

    // Abre o arquivo de clientes no formato correto
    FILE *arquivoClientes;
    if (formato == 1) {
        arquivoClientes = fopen("arquivos/clientes.bin", "rb");
    } else {
        arquivoClientes = fopen("arquivos/clientes.txt", "r");
    }

    if (arquivoClientes == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return;
    }

    // Lê os clientes
    ClienteInfo cliente;
    if (formato == 1) {
        while (fread(&cliente, sizeof(ClienteInfo), 1, arquivoClientes)) {
            for (int i = 0; i < *numServicos; i++) {
                if (strcmp(cliente.nome, servicos[i].cliente.nome) == 0) {
                    strcpy(servicos[i].cliente.nome, cliente.nome);
                }
            }
        }
    } else {
        char linha[256];
        while (fgets(linha, sizeof(linha), arquivoClientes)) {
            sscanf(linha, "%d,%99[^,],%19[^,],%99[^,],%19[^,],%49[^,]",
                   &cliente.id, cliente.nome, cliente.cpfCnpj, cliente.endereco, cliente.telefone, cliente.email);
            for (int i = 0; i < *numServicos; i++) {
                if (strcmp(cliente.nome, servicos[i].cliente.nome) == 0) {
                    strcpy(servicos[i].cliente.nome, cliente.nome);
                }
            }
        }
    }
    fclose(arquivoClientes);

    // Abre o arquivo de veículos no formato correto
    FILE *arquivoVeiculos;
    if (formato == 1) {
        arquivoVeiculos = fopen("arquivos/veiculos.bin", "rb");
    } else {
        arquivoVeiculos = fopen("arquivos/veiculos.txt", "r");
    }

    if (arquivoVeiculos == NULL) {
        printf("Erro ao abrir o arquivo de veículos.\n");
        return;
    }

    // Lê os veículos
    VeiculoInfo veiculo;
    if (formato == 1) {
        while (fread(&veiculo, sizeof(VeiculoInfo), 1, arquivoVeiculos)) {
            for (int i = 0; i < *numServicos; i++) {
                if (strcmp(veiculo.placa, servicos[i].veiculo.placa) == 0) {
                    strcpy(servicos[i].veiculo.placa, veiculo.placa);
                }
            }
        }
    } else {
        char linha[256];
        while (fgets(linha, sizeof(linha), arquivoVeiculos)) {
            sscanf(linha, "%d,%9[^,],%49[^,],%49[^,],%d,%24[^,],%99[^,]",
                   &veiculo.id, veiculo.placa, veiculo.modelo, veiculo.marca, &veiculo.anoFabricacao, veiculo.chassi, veiculo.proprietario);
            for (int i = 0; i < *numServicos; i++) {
                if (strcmp(veiculo.placa, servicos[i].veiculo.placa) == 0) {
                    strcpy(servicos[i].veiculo.placa, veiculo.placa);
                }
            }
        }
    }
    fclose(arquivoVeiculos);
}

void aplicarFiltrosServicosRealizados(ServicoRealizado *servicos, int *numServicos, int filtroServico, int filtroCliente, int filtroFuncionario, char *dataInicio, char *dataFim) {
    int diaInicio, mesInicio, anoInicio, diaFim, mesFim, anoFim;
    sscanf(dataInicio, "%d/%d/%d", &diaInicio, &mesInicio, &anoInicio);
    sscanf(dataFim, "%d/%d/%d", &diaFim, &mesFim, &anoFim);

    for (int i = 0; i < *numServicos; i++) {
        int diaServico, mesServico, anoServico;
        sscanf(servicos[i].servico.data, "%d/%d/%d", &diaServico, &mesServico, &anoServico);

        if ((filtroServico != -1 && servicos[i].servico.id != filtroServico) ||
            (filtroCliente != -1 && servicos[i].cliente.id != filtroCliente) ||
            (filtroFuncionario != -1 && servicos[i].funcionario.id != filtroFuncionario) ||
            (anoServico < anoInicio || (anoServico == anoInicio && mesServico < mesInicio) || (anoServico == anoInicio && mesServico == mesInicio && diaServico < diaInicio) ||
             anoServico > anoFim || (anoServico == anoFim && mesServico > mesFim) || (anoServico == anoFim && mesServico == mesFim && diaServico > diaFim))) {
            for (int j = i; j < *numServicos - 1; j++) {
                servicos[j] = servicos[j + 1];
            }
            (*numServicos)--;
            i--;
        }
    }
}

void gerarRelatorioServicosRealizados(ServicoRealizado *servicos, int numServicos, int imprimirTela) {
    if (imprimirTela) {
        // Cabeçalho da tabela
        printf("\n================================================================================\n");
        printf("| %-20s | %-15s | %-15s | %-15s | %-15s |\n", "Cliente", "Veículo", "Serviço", "Valor Total", "Funcionário");
        printf("================================================================================\n");

        // Dados da tabela
        for (int i = 0; i < numServicos; i++) {
            printf("| %-20s | %-15s | %-15s | %-15.2f | %-15s |\n",
                   servicos[i].cliente.nome,
                   servicos[i].veiculo.modelo,
                   servicos[i].servico.descricao,
                   servicos[i].servico.valor,
                   servicos[i].funcionario.nome);
        }

        // Rodapé da tabela
        printf("================================================================================\n");
    } else {
        // Caminho pré-definido para o arquivo CSV
        char caminhoArquivo[256] = "relatorios/relatorio_servicos_realizados.csv";

        // Salva em arquivo CSV
        FILE *arquivo = fopen(caminhoArquivo, "w");
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo para escrita.\n");
            return;
        }
        fprintf(arquivo, "Cliente,Veículo,Serviço,Valor Total,Funcionário\n");
        for (int i = 0; i < numServicos; i++) {
            fprintf(arquivo, "%s,%s,%s,%.2f,%s\n",
                    servicos[i].cliente.nome,
                    servicos[i].veiculo.modelo,
                    servicos[i].servico.descricao,
                    servicos[i].servico.valor,
                    servicos[i].funcionario.nome);
        }
        fclose(arquivo);
        printf("Relatório salvo em %s\n", caminhoArquivo);
    }
}

void RelatorioServ() {
    ServicoRealizado servicos[100];
    int numServicos = 0;
    int filtroServico = -1; // Filtro de serviço por ID
    int filtroCliente = -1; // Filtro de cliente por ID
    int filtroFuncionario = -1; // Filtro de funcionário por ID
    char dataInicio[11], dataFim[11];
    int imprimirTela;

    // Lê o formato de armazenamento (binário ou texto)
    int formato;
    FILE *formatoFile = fopen("arquivos/formato.bin", "rb");
    if (formatoFile == NULL) {
        printf("Erro ao abrir o arquivo de formato.\n");
        return;
    }
    fread(&formato, sizeof(int), 1, formatoFile);
    fclose(formatoFile);

    // Coletar dados de serviços realizados
    coletarDadosServicosRealizados(servicos, &numServicos, formato);

    // Oferecer opções de filtro
    printf("Deseja aplicar filtros? (1 - Sim, 0 - Não): ");
    int aplicarFiltro;
    scanf("%d", &aplicarFiltro);
    if (aplicarFiltro) {
        printf("Digite o ID do serviço para filtrar (ou -1 para todos): ");
        scanf("%d", &filtroServico);
        printf("Digite o ID do cliente para filtrar (ou -1 para todos): ");
        scanf("%d", &filtroCliente);
        printf("Digite o ID do funcionário para filtrar (ou -1 para todos): ");
        scanf("%d", &filtroFuncionario);
        printf("Digite a data de início (DD/MM/AAAA): ");
        scanf("%s", dataInicio);
        printf("Digite a data de fim (DD/MM/AAAA): ");
        scanf("%s", dataFim);
    }

    // Aplicar filtros
    aplicarFiltrosServicosRealizados(servicos, &numServicos, filtroServico, filtroCliente, filtroFuncionario, dataInicio, dataFim);

    // Escolher destino do relatório
    printf("Deseja imprimir o relatório na tela (1) ou salvar em arquivo CSV (0)? ");
    scanf("%d", &imprimirTela);

    // Gerar relatório
    gerarRelatorioServicosRealizados(servicos, numServicos, imprimirTela);
}