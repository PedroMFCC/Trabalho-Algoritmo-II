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


    while (fscanf(txt, "%d, %19[^,], %59[^,], %29[^,], %29[^,], %f, %f, %d, %d\n", 
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
    FuncionarioC funcionario;
    FILE *txt = fopen("arquivos/funcionarios.txt", "r+");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo texto!\n");
        return;
    }

    FILE *bin = fopen("arquivos/funcionarios.bin", "ab");
    if(bin == NULL){
        printf("Erro ao abrir o arquivo! regbin");
        return;
    }


    while (fscanf(txt, " %99[^,], %14[^,], %49[^,], %f\n", funcionario.nome, funcionario.cpf, funcionario.cargo, &funcionario.salario)== 4) 
    {                    
    fwrite(&funcionario, sizeof(FuncionarioC), 1, bin);
    }

    fclose(bin);
    fclose(txt);

    remove("arquivos/funcionarios.txt");
}
void veicbin(){
    VeiculoC veiculo;
    FILE *txt = fopen("arquivos/veiculos.txt", "r+");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo texto!\n");
        return;
    }

    FILE *bin = fopen("arquivos/veiculos.bin", "ab");
    if(bin == NULL){
        printf("Erro ao abrir o arquivo! regbin");
        return;
    }

    while (fscanf(txt, "%9[^,], %49[^,], %49[^,], %d, %24[^,], %99[^\n]\n", 
                   veiculo.placa, veiculo.modelo, veiculo.marca, &veiculo.anoFabricacao, veiculo.chassi, veiculo.proprietario) == 6) 
    {
        fwrite(&veiculo, sizeof(VeiculoC), 1, bin);
    }

    fclose(bin);
    fclose(txt);

    remove("arquivos/veiculos.txt");
}
void clientbin(){
    cliDadosC cliente;
    FILE *txt = fopen("arquivos/clientes.txt", "r+");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo texto!\n");
        return;
    }
    FILE *bin = fopen("arquivos/clientes.bin", "ab");
    if (bin == NULL) {
        printf("Erro ao abrir o arquivo! regbin");
        return;
    }

    while(fscanf(txt, "%49[^,], %19[^,], %99[^,], %19[^,], %49[^\n]\n", 
                 cliente.nome, cliente.cpfCnpj, cliente.endereco, cliente.telefone, cliente.email) == 5) {
        fwrite(&cliente, sizeof(cliDadosC), 1, bin);
    }
    fclose(bin);
    fclose(txt);

    remove("arquivos/clientes.txt");
}
void servicobin(){
    ServicoC servico;
    FILE *txt = fopen("arquivos/servicos.txt", "r+");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo texto!\n");
        return;
    }
    FILE *bin = fopen("arquivos/servicos.bin", "ab");
    if (bin == NULL) {
        printf("Erro ao abrir o arquivo! regbin");
        return;
    }

    while(fscanf(txt, "%d, %99[^,], %f, %f\n", 
                 &servico.codigo, servico.descricao, &servico.preco, &servico.comissao) == 4) {
        fwrite(&servico, sizeof(ServicoC), 1, bin);
    }

    fclose(bin);
    fclose(txt);

    remove("arquivos/servicos.txt");
}
void fornecbin(){
    FornecedorC fornecedor;
    FILE *txt = fopen("arquivos/fornecedores.txt", "r+");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo texto!\n");
        return;
    }
    FILE *bin = fopen("arquivos/fornecedores.bin", "ab");
    if (bin == NULL) {
        printf("Erro ao abrir o arquivo! regbin");
        return;
    }

    while(fscanf(txt, "%d, %59[^,], %19[^,], %149[^,], %19[^,], %149[^,], %19[^,], %149[^\n]\n", 
                 &fornecedor.codigo, fornecedor.nomeFts, fornecedor.Cnpj, fornecedor.razSc, fornecedor.insEE, fornecedor.endCp, fornecedor.Telef, fornecedor.email) == 8) {
        fwrite(&fornecedor, sizeof(FornecedorC), 1, bin);
    }

    fclose(bin);
    fclose(txt);

    remove("arquivos/fornecedores.txt");
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
        "%d, %s, %s, %s, %s, %f, %f, %d, %d\n",
        peca.codpec, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, peca.custpeca, peca.vendpeca, peca.npeca, peca.minpeca);
    }

    fclose(txt);
    fclose(bin);

    remove("arquivos/peca.bin");
}
void functxt(){
    FuncionarioC funcionario;

    FILE *txt = fopen("arquivos/funcionarios.txt", "a");
    if(txt == NULL){
        printf("erro ao converter arquivo funcionário para txt");
        return;
    }
    FILE *bin = fopen("arquivos/funcionarios.bin", "r+b");
    if(bin == NULL){
        printf("erro ao abrir arquivo funcionário bin");
        return;
    }


    while(fread(&funcionario, sizeof(FuncionarioC), 1, bin)){
        fprintf(txt, "%s,%s,%s,%.2f\n", funcionario.nome, funcionario.cpf, funcionario.cargo, funcionario.salario);
    }

    fclose(txt);
    fclose(bin);

    remove("arquivos/funcionarios.bin");
}
void veictxt(){
    VeiculoC veiculo;
    FILE *txt = fopen("arquivos/veiculos.txt", "a");
    if(txt == NULL){
        printf("erro ao abrir  arquivo! regtxt");
        return;
    }
    FILE *bin = fopen("arquivos/veiculos.bin", "r+b");
    if(bin == NULL){
        printf("erro ao abrir  arquivo! regtxt");
        return;
    }

    while (fread(&veiculo, sizeof(VeiculoC), 1, bin)) {
        fprintf(txt,
        "%s, %s, %s, %d, %s, %s\n",
        veiculo.placa, veiculo.modelo, veiculo.marca, veiculo.anoFabricacao, veiculo.chassi, veiculo.proprietario);
    }

    fclose(txt);
    fclose(bin);

    remove("arquivos/veiculos.bin");


}
void clienttxt(){
    cliDadosC cliente;
    FILE *txt = fopen("arquivos/clientes.txt", "a");
    if(txt == NULL){
        printf("erro ao abrir  arquivo! regtxt");
        return;
    }
    FILE *bin = fopen("arquivos/clientes.bin", "r+b");
    if(bin == NULL){
        printf("erro ao abrir  arquivo! regtxt");
        return;
    }

    while(fread(&cliente, sizeof(cliDadosC), 1, bin)){
        fprintf(txt, "%s, %s, %s, %s, %s\n", cliente.nome, cliente.cpfCnpj, cliente.endereco, cliente.telefone, cliente.email);
    }

    fclose(txt);
    fclose(bin);

    remove("arquivos/clientes.bin");
}
void servicotxt(){
    ServicoC servico;
    FILE *txt = fopen("arquivos/servicos.txt", "a");
    if(txt == NULL){
        printf("erro ao abrir  arquivo! regtxt");
        return;
    }
    FILE *bin = fopen("arquivos/servicos.bin", "r+b");
    if(bin == NULL){
        printf("erro ao abrir  arquivo! regtxt");
        return;
    }

    while(fread(&servico, sizeof(ServicoC), 1, bin)){
        fprintf(txt, "%d, %s, %.2f, %.2f\n", servico.codigo, servico.descricao, servico.preco, servico.comissao);
    }

    fclose(txt);
    fclose(bin);

    remove("arquivos/servicos.bin");
}
void fornectxt(){
    FornecedorC fornecedor;
    FILE *txt = fopen("arquivos/fornecedores.txt", "a");
    if(txt == NULL){
        printf("erro ao abrir  arquivo! regtxt");
        return;
    }
    FILE *bin = fopen("arquivos/fornecedores.bin", "r+b");
    if(bin == NULL){
        printf("erro ao abrir  arquivo! regtxt");
        return;
    }

    while(fread(&fornecedor, sizeof(FornecedorC), 1, bin)){
        fprintf(txt, "%d, %s, %s, %s, %s, %s, %s, %s\n", fornecedor.codigo, fornecedor.nomeFts, fornecedor.Cnpj, fornecedor.razSc, fornecedor.insEE, fornecedor.endCp, fornecedor.Telef, fornecedor.email);
    }

    fclose(txt);
    fclose(bin);

    remove("arquivos/fornecedores.bin");
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