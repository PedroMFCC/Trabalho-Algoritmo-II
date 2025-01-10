#ifndef AGENDAMENTO_H
#define AGENDAMENTO_H

#define MAX_AGENDAMENTOS 100

typedef struct {
    int codAgend;
    char cliente[50];
    char veiculo[50];
    char servico[50];
    char funcionario[50];
    char data[11];
    char hora[6];
} Agendamento;

void RegAgendBin();
void RegAgendTxt();
void RegAgend();

void LerAgendBin();
void LerAgendTxt();
void LerAgend();

void EditAgendBin();
void EditAgendTxt();
void EditAgend();

void RemoverAgendBin();
void RemoverAgendTxt();
void RemoverAgend();


int adcAgendamento(Agendamento agendamentos[], int *qtd, Agendamento novo);

#endif