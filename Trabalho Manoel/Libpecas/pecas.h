#ifndef PECAS_H
#define PECAS_H

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
}dadopec;

typedef struct{
    int codpec;
    char nomepec[20];
    int npeca;
    float custpeca;
}notafisc;


float calculo(float custo);

void regpecabin(dadopec peca);
void regpecatxt(dadopec peca);
void regpecapath(dadopec peca);
void regpeca();

void editpecabin();
void editpecatxt();
void editpeca();

void addpecasbin();
void addpecastxt();
void addpecas();
void rempecasbin();
void rempecastxt();
void rempecas();
void gerenciarpecasmen();

void notafiscaltxt();
void notafiscalbin();

void lerpecabin();
void lerpecatxt();
void lerpeca();

void removerpecabin();
void removerpecatxt();
void removerpeca();

void detectapecabin();
void detectapecatxt();
void detectapeca(); 

#endif