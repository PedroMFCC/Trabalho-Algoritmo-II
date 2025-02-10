#ifndef PECAS_H
#define PECAS_H

typedef struct{
    int codpec;
    int definecod;
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
    int codnota;
    int definecod;
    char forn[50];
    char cnpj[20];
    float imposto;
    float frete;
    float precgeral;
}regfisc;



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
void reallocnotafisc(dadopec **dadonota, int *tamanho, dadopec novaPeca);

void notafiscaltxt();
void notafiscalbin();
void notafiscal();

void lerpecabin();
void lerpecatxt();
void lerpeca();

void lernotafiscbin();
void lernotafisctxt();
void lernotafisc();

void excluinotafiscalbin();
void excluinotafiscaltxt();
void excluinotafiscal();


void restauranotaficbin();
void restauranotafictxt();
void restauranotafic();

void pecapornometxt();
void pecapornomebin();
void pecapornome();

void riscopecatxt();
void riscopecabin();
void riscopeca();


void pecaporcodbin();
void pecaporcodtxt();
void pecaporcod();


void removerpecabin();
void removerpecatxt();
void removerpeca();

void restaurapecabin();
void restaurapecatxt();
void restaurapeca();


void detectapecabin();
void detectapecatxt();
void detectapeca(); 

void relatoriopeca();

#endif