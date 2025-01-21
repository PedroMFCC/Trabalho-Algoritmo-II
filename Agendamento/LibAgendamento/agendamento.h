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
    char cliente[50];
    char veiculo[50];
    char servicos[100]; 
    char pecas[100];
    int numPecas; 
    int qtdPecas; // estoque atualizado
    float vlrTot;

} OrdemServico;

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