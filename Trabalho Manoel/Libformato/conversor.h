#ifndef CONVERSOR_H
#define CONVERSOR_H

typedef struct{
    int codpec;
    char nomepec[20];    
    char descpec[60];
    char fabpec[30];
    char fornpec[30];
    float custpeca;
    float vendpeca;
    int npeca;
    int minpeca;
}dadopecC;

typedef struct{
    char nomeofic[40];
    char cnpjofic[20];
    char ruaofic[50];
    char telefofic[22];
    char emailofic[40];
    float lucro;
    
}dadooficC;


void oficbin();
void pecabin();
void funcbin();
void veicbin();
void clientbin();
void servicobin();
void fornecbin();
void converteparabin();

void ofictxt();
void pecatxt();
void functxt();
void veictxt();
void clienttxt();
void servicotxt();
void fornectxt();
void converteparatxt();

#endif