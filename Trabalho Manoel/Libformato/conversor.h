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

typedef struct {
    char nome[100];
    char cpf[15];
    char cargo[50];
    float salario;
} FuncionarioC;

typedef struct {
    char placa[10];
    char modelo[50];
    char marca[50];
    int anoFabricacao;
    char chassi[25];
    char proprietario[100];
} VeiculoC;

typedef struct {
    char nome[50];
    char cpfCnpj[20];
    char endereco[100];
    char telefone[20];
    char email[50];

} cliDadosC;

typedef struct {
    int codigo;
    char descricao[100];
    float preco;
    float comissao;
} ServicoC;
typedef struct {
    int codigo;
    char nomeFts[60]; // Nome Fantasia
    char Cnpj[20];
    char razSc[150]; // Razão Social
    char insEE[20]; // Inscrição Estadual
    char endCp[150]; // Endereço Completo
    char Telef[20];
    char email[150];

} FornecedorC;

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