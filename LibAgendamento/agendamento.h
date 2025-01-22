#ifndef AGENDAMENTO_H
#define AGENDAMENTO_H

#define MAX_AGENDAMENTOS 100

typedef struct {
    int codAgend;
    char cliente[50];
    char veiculo[50];
    char servico[50];
    int peso;
    char funcionario[50];
    char data[11];
    char hora[6];
} Agendamento;

typedef struct {
    int codOS;
    int cliente;
    int veiculo;
    int servicos; 
    char pecas[100];
    int numPecas; 
    float vlrTot;

} OrdemServico;

typedef struct {
    int id;
    char nome[100];
    char cpfCnpj[20];
    char endereco[100];
    char telefone[20];
    char email[50];

} ClienteInfo;

typedef struct {
    int id;
    char placa[10];
    char modelo[50];
    char marca[50];
    int anoFabricacao;
    char chassi[25];
    char proprietario[100];
} VeiculoInfo;

typedef struct{
    int codpec;
    char nomepec[20];    
    char descpec[60];
    char fabpec[30];
    char fornpec[30];
    float custpeca;
    float vendpeca;
    int npeca; // estoque disponivel
    int minpeca;
} PecaDados;

void RegAgendBin();
void RegAgendTxt();
void RegAgend();
void RegOSBin();
void RegOSTxt();
void RegOS();

void LerAgendBin();
void LerAgendTxt();
void LerAgend();
void LerOSBin();
void LerOSTxt();
void LerOS();

void EditAgendBin();
void EditAgendTxt();
void EditAgend();
void EditOSBin();
void EditOSTxt();
void EditOS();

void RemoverAgendBin();
void RemoverAgendTxt();
void RemoverAgend();
void RemoverOSBin();
void RemoverOSTxt();
void RemoverOS();

#endif