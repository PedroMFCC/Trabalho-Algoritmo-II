#include "relatorios.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "veiculos.h" 
#include "servicos.h"
#include "funcionarios.h"
#include "clientes.h"
#include "fornecedor.h" 

void gerarRelatorioVeiculos(FiltrosRelatorioCadastros filtros, FILE *saida) {
    char caminhoArquivo[100];
    int formato = obterFormatoRegistro(); 

    if (formato == 1) {
        sprintf(caminhoArquivo, "arquivos/veiculos.bin");
    } else if (formato == 2) {
        sprintf(caminhoArquivo, "arquivos/veiculos.txt");
    } else {
        printf("Formato de registro desconhecido.\n");
        return;
    }

    FILE *arquivo = fopen(caminhoArquivo, formato == 1 ? "rb" : "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de veículos: %s\n", caminhoArquivo);
        return;
    }

    Veiculo veiculo;
    int primeiroRegistro = 1;

    
    fprintf(saida, "Relatório de Veículos\n");
    fprintf(saida, "===============================================================================================\n");
    fprintf(saida, "ID   | Placa   | Modelo           | Marca           | Ano  | Chassi          | Proprietário\n");
    fprintf(saida, "------------------------------------------------------------------------------------------------\n");

    if (formato == 1) {
       
        while (fread(&veiculo, sizeof(Veiculo), 1, arquivo) == 1) {
           
            if (filtros.filtroCodigo && veiculo.idveiculo != filtros.codigo) {
                continue;
            }

            
            if (filtros.filtroNome && strstr(veiculo.proprietario, filtros.nome) == NULL) {
                continue;
            }

           
            fprintf(saida, "%-4d | %-7s | %-15s | %-15s | %-4d | %-15s | %s\n",
                    veiculo.idveiculo, veiculo.placa, veiculo.modelo, veiculo.marca,
                    veiculo.anoFabricacao, veiculo.chassi, veiculo.proprietario);
        }
    } else {
       
        while (fscanf(arquivo, "%d, %9[^,], %49[^,], %49[^,], %d, %24[^,], %99[^\n]\n",
                      &veiculo.idveiculo, veiculo.placa, veiculo.modelo, veiculo.marca,
                      &veiculo.anoFabricacao, veiculo.chassi, veiculo.proprietario) == 7) {
           
            if (filtros.filtroCodigo && veiculo.idveiculo != filtros.codigo) {
                continue;
            }

            
            if (filtros.filtroNome && strstr(veiculo.proprietario, filtros.nome) == NULL) {
                continue;
            }

           
            fprintf(saida, "%-4d | %-7s | %-15s | %-15s | %-4d | %-15s | %s\n",
                    veiculo.idveiculo, veiculo.placa, veiculo.modelo, veiculo.marca,
                    veiculo.anoFabricacao, veiculo.chassi, veiculo.proprietario);
        }
    }

    fclose(arquivo);

    
    if (saida != stdout) {
        printf("Relatório de veículos gerado com sucesso!\n");
    }
}

FiltrosRelatorioCadastros obterFiltrosVeiculos() {
    FiltrosRelatorioCadastros filtros = {0};

    printf("Deseja filtrar por código? (1 para sim, 0 para não): ");
    scanf("%d", &filtros.filtroCodigo);

    if (filtros.filtroCodigo) {
        printf("Digite o código do veículo: ");
        scanf("%d", &filtros.codigo);
    }

    printf("Deseja filtrar por nome do proprietário? (1 para sim, 0 para não): ");
    scanf("%d", &filtros.filtroNome);

    if (filtros.filtroNome) {
        printf("Digite o nome do proprietário: ");
        scanf(" %99[^\n]", filtros.nome);
    }

    return filtros;
}
//-------------serviços---------------------------------------------------------------------------------------

void gerarRelatorioServicos(FiltrosRelatorioServicos filtros, FILE *saida) {
    char caminhoArquivo[100];
    int formato = obterFormatoRegistro(); 

    if (formato == 1) {
        sprintf(caminhoArquivo, "arquivos/servicos.bin");
    } else if (formato == 2) {
        sprintf(caminhoArquivo, "arquivos/servicos.txt");
    } else {
        printf("Formato de registro desconhecido.\n");
        return;
    }

    FILE *arquivo = fopen(caminhoArquivo, formato == 1 ? "rb" : "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de serviços: %s\n", caminhoArquivo);
        return;
    }

    Servico servico;
    int primeiroRegistro = 1;

    
    fprintf(saida, "Relatório de Serviços\n");
    fprintf(saida, "===============================================================================================\n");
    fprintf(saida, "Código | Descrição           | Preço  | Comissão | Tempo (min) | Código Peça\n");
    fprintf(saida, "------------------------------------------------------------------------------------------------\n");

    if (formato == 1) {
        
        while (fread(&servico, sizeof(Servico), 1, arquivo) == 1) {
           
            if (filtros.filtroCodigo && servico.codigo != filtros.codigo) {
                continue;
            }

            
            if (filtros.filtroDescricao && strstr(servico.descricao, filtros.descricao) == NULL) {
                continue;
            }

            
            fprintf(saida, "%-6d | %-19s | %-6.2f | %-8.2f | %-11d | %d\n",
                    servico.codigo, servico.descricao, servico.preco, servico.comissao,
                    servico.tempo, servico.peca);
        }
    } else {
    
        while (fscanf(arquivo, "%d, %99[^,], %f, %f, %d, %d\n",
                      &servico.codigo, servico.descricao, &servico.preco, &servico.comissao,
                      &servico.tempo, &servico.peca) == 6) {
            
            if (filtros.filtroCodigo && servico.codigo != filtros.codigo) {
                continue;
            }

           
            if (filtros.filtroDescricao && strstr(servico.descricao, filtros.descricao) == NULL) {
                continue;
            }

            
            fprintf(saida, "%-6d | %-19s | %-6.2f | %-8.2f | %-11d | %d\n",
                    servico.codigo, servico.descricao, servico.preco, servico.comissao,
                    servico.tempo, servico.peca);
        }
    }

    fclose(arquivo);

    
    if (saida != stdout) {
        printf("Relatório de serviços gerado com sucesso!\n");
    }
}
FiltrosRelatorioServicos obterFiltrosServicos() {
    FiltrosRelatorioServicos filtros = {0};

    printf("Deseja filtrar por código? (1 para sim, 0 para não): ");
    scanf("%d", &filtros.filtroCodigo);

    if (filtros.filtroCodigo) {
        printf("Digite o código do serviço: ");
        scanf("%d", &filtros.codigo);
    }

    printf("Deseja filtrar por descrição? (1 para sim, 0 para não): ");
    scanf("%d", &filtros.filtroDescricao);

    if (filtros.filtroDescricao) {
        printf("Digite a descrição do serviço: ");
        scanf(" %99[^\n]", filtros.descricao);
    }

    return filtros;
}
//-------------funcionários---------------------------------------------------------------------------------------
void gerarRelatorioFuncionarios(FiltrosRelatorioFuncionarios filtros, FILE *saida) {
    char caminhoArquivo[100];
    int formato = obterFormatoRegistro(); 
    
    
    if (formato == 1) {
        sprintf(caminhoArquivo, "arquivos/funcionarios.bin");
    } else if (formato == 2) {
        sprintf(caminhoArquivo, "arquivos/funcionarios.txt");
    } else {
        printf("Formato de registro desconhecido.\n");
        return;
    }

   
    FILE *arquivo = fopen(caminhoArquivo, formato == 1 ? "rb" : "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de funcionários: %s\n", caminhoArquivo);
        return;
    }

    Funcionario funcionario;
    
   
    fprintf(saida, "\nRelatório de Funcionários\n");
    fprintf(saida, "================================================================================\n");
    fprintf(saida, "Nome          | CPF           | Cargo          | Salário\n");
    fprintf(saida, "--------------------------------------------------------------------------------\n");

    
    if (formato == 1) {
      
        while (fread(&funcionario, sizeof(Funcionario), 1, arquivo) == 1) {
           
            if (filtros.filtroCodigo && funcionario.id != filtros.codigo) continue;
            if (filtros.filtroNome && strstr(funcionario.nome, filtros.nome) == NULL) continue;
            if (filtros.filtroCargo && strstr(funcionario.cargo, filtros.cargo) == NULL) continue;

           
            fprintf(saida, "%-13s | %-13s | %-14s | R$ %.2f\n",
                    funcionario.nome, funcionario.cpf, funcionario.cargo, funcionario.salario);
        }
    } else {
        
        while (fscanf(arquivo, "%d, %99[^,], %14[^,], %49[^,], %f\n", 
            &funcionario.id, funcionario.nome, funcionario.cpf, funcionario.cargo, &funcionario.salario) == 5) {
  
  if (filtros.filtroCodigo && funcionario.id != filtros.codigo) continue;
  if (filtros.filtroNome && strstr(funcionario.nome, filtros.nome) == NULL) continue;
  if (filtros.filtroCargo && strstr(funcionario.cargo, filtros.cargo) == NULL) continue;

  
  fprintf(saida, "%-13s | %-13s | %-14s | R$ %.2f\n",
          funcionario.nome, funcionario.cpf, funcionario.cargo, funcionario.salario);
}
    }

    fclose(arquivo);
    if (saida != stdout) printf("Relatório de funcionários gerado com sucesso!\n");
}


FiltrosRelatorioFuncionarios obterFiltrosFuncionarios() {
    FiltrosRelatorioFuncionarios filtros = {0};

    printf("Deseja filtrar por código? (1 para sim, 0 para não): ");
    scanf("%d", &filtros.filtroCodigo);
    if (filtros.filtroCodigo) {
        printf("Digite o código do funcionário: ");
        scanf("%d", &filtros.codigo);
    }

    printf("Deseja filtrar por nome? (1 para sim, 0 para não): ");
    scanf("%d", &filtros.filtroNome);
    if (filtros.filtroNome) {
        printf("Digite o nome do funcionário: ");
        scanf(" %99[^\n]", filtros.nome);
    }

    return filtros;
}
//----------------------------Clientes-----------------------------------------

void gerarRelatorioClientes(FiltrosRelatorioCadastros filtros, FILE *saida) {
    char caminhoArquivo[100];
    int formato = obterFormatoRegistro(); 

    if (formato == 1) {
        sprintf(caminhoArquivo, "arquivos/clientes.bin");
    } else if (formato == 2) {
        sprintf(caminhoArquivo, "arquivos/clientes.txt");
    } else {
        printf("Formato de registro desconhecido.\n");
        return;
    }

    FILE *arquivo = fopen(caminhoArquivo, formato == 1 ? "rb" : "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de clientes: %s\n", caminhoArquivo);
        return;
    }

    cliDados cliente;
    int primeiroRegistro = 1;

    
    fprintf(saida, "Relatório de Clientes\n");
    fprintf(saida, "===============================================================================================\n");
    fprintf(saida, "ID   | Nome               | CPF/CNPJ         | Endereço          | Telefone         | Email\n");
    fprintf(saida, "------------------------------------------------------------------------------------------------\n");

    if (formato == 1) {
        
        while (fread(&cliente, sizeof(cliDados), 1, arquivo) == 1) {
            
            if (filtros.filtroCodigo && cliente.id != filtros.codigo) {
                continue;
            }

           
            if (filtros.filtroNome && strstr(cliente.nome, filtros.nome) == NULL) {
                continue;
            }

            
            fprintf(saida, "%-4d | %-18s | %-16s | %-17s | %-15s | %s\n",
                    cliente.id, cliente.nome, cliente.cpfCnpj, cliente.endereco,
                    cliente.telefone, cliente.email);
        }
    } else {
        
        char linha[256];
        while (fgets(linha, sizeof(linha), arquivo)) {
            if (sscanf(linha, "%d,%99[^,],%19[^,],%99[^,],%19[^,],%99[^\n]",
                       &cliente.id, cliente.nome, cliente.cpfCnpj, cliente.endereco,
                       cliente.telefone, cliente.email) == 6) {
               
                if (filtros.filtroCodigo && cliente.id != filtros.codigo) {
                    continue;
                }

                
                if (filtros.filtroNome && strstr(cliente.nome, filtros.nome) == NULL) {
                    continue;
                }

                
                fprintf(saida, "%-4d | %-18s | %-16s | %-17s | %-15s | %s\n",
                        cliente.id, cliente.nome, cliente.cpfCnpj, cliente.endereco,
                        cliente.telefone, cliente.email);
            }
        }
    }

    fclose(arquivo);

    
    if (saida != stdout) {
        printf("Relatório de clientes gerado com sucesso!\n");
    }
}


FiltrosRelatorioCadastros obterFiltrosClientes() {
    FiltrosRelatorioCadastros filtros = {0};

    printf("Deseja filtrar por código? (1 para sim, 0 para não): ");
    scanf("%d", &filtros.filtroCodigo);

    if (filtros.filtroCodigo) {
        printf("Digite o código do cliente: ");
        scanf("%d", &filtros.codigo);
    }

    printf("Deseja filtrar por nome? (1 para sim, 0 para não): ");
    scanf("%d", &filtros.filtroNome);

    if (filtros.filtroNome) {
        printf("Digite o nome do cliente: ");
        scanf(" %99[^\n]", filtros.nome);
    }

    return filtros;
}
//-------------------------------Fornecedor---------------------------------------------

void gerarRelatorioFornecedores(FiltrosRelatorioFornecedores filtros, FILE *saida) {
    char caminhoArquivo[100];
    int formato = obterFormatoRegistro(); 

    if (formato == 1) {
        sprintf(caminhoArquivo, "arquivos/fornecedores.bin");
    } else if (formato == 2) {
        sprintf(caminhoArquivo, "arquivos/fornecedores.txt");
    } else {
        printf("Formato de registro desconhecido.\n");
        return;
    }

    FILE *arquivo = fopen(caminhoArquivo, formato == 1 ? "rb" : "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de fornecedores: %s\n", caminhoArquivo);
        return;
    }

    Forn fornecedor;
    int primeiroRegistro = 1;

   
    fprintf(saida, "Relatório de Fornecedores\n");
    fprintf(saida, "===============================================================================================\n");
    fprintf(saida, "Código | Nome Fantasia       | Razão Social       | CNPJ               | Telefone         | Email\n");
    fprintf(saida, "------------------------------------------------------------------------------------------------\n");

    if (formato == 1) {
       
        while (fread(&fornecedor, sizeof(Forn), 1, arquivo) == 1) {
           
            if (filtros.filtroCodigo && fornecedor.codigo != filtros.codigo) {
                continue;
            }

            
            if (filtros.filtroNome && strstr(fornecedor.nomeFts, filtros.nome) == NULL) {
                continue;
            }

            fprintf(saida, "%-6d | %-19s | %-19s | %-18s | %-15s | %s\n",
                    fornecedor.codigo, fornecedor.nomeFts, fornecedor.razSc,
                    fornecedor.Cnpj, fornecedor.Telef, fornecedor.email);
        }
    } else {
        
        char linha[256];
        while (fgets(linha, sizeof(linha), arquivo)) {
            if (sscanf(linha, "%d, %59[^,], %149[^,], %19[^,], %19[^,], %149[^,], %19[^,], %149[^\n]",
                       &fornecedor.codigo, fornecedor.nomeFts, fornecedor.razSc, fornecedor.insEE,
                       fornecedor.Cnpj, fornecedor.endCp, fornecedor.Telef, fornecedor.email) == 8) {
                
                if (filtros.filtroCodigo && fornecedor.codigo != filtros.codigo) {
                    continue;
                }

               
                if (filtros.filtroNome && strstr(fornecedor.nomeFts, filtros.nome) == NULL) {
                    continue;
                }

               
                fprintf(saida, "%-6d | %-19s | %-19s | %-18s | %-15s | %s\n",
                        fornecedor.codigo, fornecedor.nomeFts, fornecedor.razSc,
                        fornecedor.Cnpj, fornecedor.Telef, fornecedor.email);
            }
        }
    }

    fclose(arquivo);

    
    if (saida != stdout) {
        printf("Relatório de fornecedores gerado com sucesso!\n");
    }
}

FiltrosRelatorioFornecedores obterFiltrosFornecedores() {
    FiltrosRelatorioFornecedores filtros = {0};

    printf("Deseja filtrar por código? (1 para sim, 0 para não): ");
    scanf("%d", &filtros.filtroCodigo);

    if (filtros.filtroCodigo) {
        printf("Digite o código do fornecedor: ");
        scanf("%d", &filtros.codigo);
    }

    printf("Deseja filtrar por nome? (1 para sim, 0 para não): ");
    scanf("%d", &filtros.filtroNome);

    if (filtros.filtroNome) {
        printf("Digite o nome do fornecedor: ");
        scanf(" %99[^\n]", filtros.nome);
    }

    return filtros;
}