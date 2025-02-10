#ifndef RELATORIOS_H
#define RELATORIOS_H

typedef struct {
    int idFuncionario;
    char nomeFuncionario[100];
    int totalServicos;
    float totalComissao;
    int totalTempo;
} ProdutividadeFuncionario;

typedef struct {
    int id;
    char nome[100];
    char telefone[20];
} ClienteRelatorio;

// Estrutura para armazenar informações do veículo
typedef struct {
    int id;
    char modelo[100];
    char placa[10];
} VeiculoRelatorio;

// Estrutura para armazenar informações do serviço
typedef struct {
    int id;
    char descricao[200];
    float valor;
    char data[11]; // Data no formato DD/MM/AAAA
} ServicoRelatorio;

// Estrutura para armazenar informações do funcionário
typedef struct {
    int id;
    char nome[100];
} FuncionarioRelatorio;

// Estrutura para armazenar informações do serviço realizado
typedef struct {
    ClienteRelatorio cliente;
    VeiculoRelatorio veiculo;
    ServicoRelatorio servico;
    FuncionarioRelatorio funcionario;
} ServicoRealizado;


void coletarDadosProdutividade(ProdutividadeFuncionario *produtividade, int *numFuncionarios, int formato);
void aplicarFiltros(ProdutividadeFuncionario *produtividade, int *numFuncionarios, int filtroFuncionario, int filtroServico, char *dataInicio, char *dataFim);
void gerarRelatorioProdutividade(ProdutividadeFuncionario *produtividade, int numFuncionarios, int imprimirTela); // Removido o parâmetro caminhoArquivo
void RelatorioProd();

void gerarRelatorioServicosRealizados(ServicoRealizado *servicos, int numServicos, int imprimirTela);
void aplicarFiltrosServicosRealizados(ServicoRealizado *servicos, int *numServicos, int filtroServico, int filtroCliente, int filtroFuncionario, char *dataInicio, char *dataFim);
void RelatorioServ();

#endif