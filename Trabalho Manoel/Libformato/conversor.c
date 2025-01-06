#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "conversor.h"

void oficbin(){
    dadooficC ofic;
    FILE *txt = fopen("arquivos/oficina.txt", "r+");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo texto!\n");
        return;
    }

    FILE *bin = fopen("arquivos/oficina.bin", "ab");
    if(bin == NULL){
        printf("Erro ao abrir o arquivo! regbin");
        return;
    }


    while (fscanf(txt, "%39[^\n]\n%19[^\n]\n%29[^\n]\n%21[^\n]\n%39[^\n]\n%f\n", 
        ofic.nomeofic, ofic.cnpjofic, ofic.ruaofic, ofic.telefofic, ofic.emailofic, &ofic.lucro) == 6) 
    {                    
    fwrite(&ofic, sizeof(dadooficC), 1, bin);
    }

    fclose(bin);
    fclose(txt);

    remove("arquivos/oficina.txt");    
}
void pecabin(){
    dadopecC peca;
    FILE *txt = fopen("arquivos/peca.txt", "r+");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo texto!\n");
        return;
    }

    FILE *bin = fopen("arquivos/peca.bin", "ab");
    if(bin == NULL){
        printf("Erro ao abrir o arquivo! regbin");
        return;
    }


    while (fscanf(txt, "%d\n%19[^\n]\n%59[^\n]\n%29[^\n]\n%29[^\n]\n%f\n%f\n%d\n%d\n", 
                   &peca.codpec, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, 
                   &peca.custpeca, &peca.vendpeca, &peca.npeca, &peca.minpeca) == 9) 
    {                    
    fwrite(&peca, sizeof(dadopecC), 1, bin);
    }


    fclose(bin);
    fclose(txt);

    remove("arquivos/peca.txt");
}
void funcbin(){

}
void veicbin(){

}
void clientbin(){

}
void servicobin(){

}
void fornecbin(){

}
void converteparabin(){
    oficbin();
    pecabin();
    funcbin();
    veicbin();
    clientbin();
    servicobin();
    fornecbin();
}



void ofictxt(){
    FILE *txt = fopen("arquivos/oficina.txt", "a");
    if(txt == NULL){
        printf("erro ao abrir  arquivo! regtxt");
        return;
    }  

    dadooficC ofic;
    FILE *bin = fopen("arquivos/oficina.bin", "r+b");
    if (bin == NULL){
        printf("erro lerbin");
        return;
    }
    
    while (fread(&ofic, sizeof(dadooficC), 1, bin)) {
        fprintf(txt,
        "%s\n%s\n%s\n%s\n%s\n%f\n",
        ofic.nomeofic, ofic.cnpjofic, ofic.ruaofic, ofic.telefofic, ofic.emailofic, ofic.lucro);
    }   

    fclose(txt);
    fclose(bin);

    remove("arquivos/oficina.bin");
}
void pecatxt(){
    FILE *txt = fopen("arquivos/peca.txt", "a");
    if(txt == NULL){
        printf("erro ao abrir  arquivo! regtxt");
        return;
    }  

    dadopecC peca;
    FILE *bin = fopen("arquivos/peca.bin", "r+b");
    if (bin == NULL){
        printf("erro lerbin");
        return;
    }
    
    while (fread(&peca, sizeof(dadopecC), 1, bin)) {
        fprintf(txt,
        "%d\n%s\n%s\n%s\n%s\n%f\n%f\n%d\n%d\n",
        peca.codpec, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, peca.custpeca, peca.vendpeca, peca.npeca, peca.minpeca);
    }

    fclose(txt);
    fclose(bin);

    remove("arquivos/peca.bin");
}
void functxt(){

}
void veictxt(){

}
void clienttxt(){

}
void servicotxt(){

}
void fornectxt(){

}
void converteparatxt(){
    ofictxt();
    pecatxt();
    functxt();
    veictxt();
    clienttxt();
    servicotxt();   
    fornectxt();
}