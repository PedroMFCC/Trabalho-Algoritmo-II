#ifndef RELATORIOS_H
#define RELATORIOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct {
    int filtroData;          
    time_t dataInicio;       
    time_t dataFim;         
    char filtro[100];        
} FiltrosRelatorio;

typedef struct {
    int filtroCodigo;        
    int filtroNome;          
    int codigo;              
    char nome[100];          
} FiltrosRelatorioCadastros;


typedef enum {
    RELATORIO_CAIXA,         
    RELATORIO_CONTAS_RECEBER,
    RELATORIO_CONTAS_PAGAR   
} TipoRelatorio;


typedef enum {
    RELATORIO_VEICULOS,      
    RELATORIO_SERVICOS,      
    RELATORIO_FUNCIONARIOS   
} TipoRelatorioCadastros;

typedef struct {
    int filtroCodigo;        
    int filtroDescricao;     
    int codigo;              
    char descricao[100];     
} FiltrosRelatorioServicos;


typedef struct {
    int filtroCodigo;       
    int filtroNome;         
    int filtroCargo;         
    int codigo;              
    char nome[100];          
    char cargo[100];         
} FiltrosRelatorioFuncionarios;

typedef struct {
    int filtroCodigo;        
    int filtroNome;          
    int codigo;              
    char nome[100];         
} FiltrosRelatorioFornecedores;


void gerarRelatorioServicos(FiltrosRelatorioServicos filtros, FILE *saida);
FiltrosRelatorioServicos obterFiltrosServicos();


void gerarRelatorioVeiculos(FiltrosRelatorioCadastros filtros, FILE *saida);
void gerarRelatorioFuncionarios(FiltrosRelatorioFuncionarios filtros, FILE *saida);

// Função para coletar filtros do usuário
FiltrosRelatorio obterFiltrosRelatorio();
FiltrosRelatorioCadastros obterFiltrosVeiculos();
FiltrosRelatorioFuncionarios obterFiltrosFuncionarios();


int obterFormatoRegistro();


void gerarRelatorioCaixaBinario(FiltrosRelatorio filtros, FILE *saida);
void gerarRelatorioCaixaTexto(FiltrosRelatorio filtros, FILE *saida);


void gerarRelatorioContasReceberBinario(FiltrosRelatorio filtros, FILE *saida);
void gerarRelatorioContasReceberTexto(FiltrosRelatorio filtros, FILE *saida);


void gerarRelatorioContasPagarBinario(FiltrosRelatorio filtros, FILE *saida);
void gerarRelatorioContasPagarTexto(FiltrosRelatorio filtros, FILE *saida);


void gerarRelatorioClientes(FiltrosRelatorioCadastros filtros, FILE *saida);
FiltrosRelatorioCadastros obterFiltrosClientes();


void gerarRelatorioFornecedores(FiltrosRelatorioFornecedores filtros, FILE *saida);
FiltrosRelatorioFornecedores obterFiltrosFornecedores();

// Função mãe para gerar relatórios
void gerarRelatorio(TipoRelatorio tipo, FiltrosRelatorio filtros, FILE *saida);


#endif