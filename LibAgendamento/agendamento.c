#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agendamento.h"

void RegAgendBin(Agendamento Agend) {
    FILE *bin = fopen("arquivos/agendamento.bin", "ab");
    if (bin == NULL) {
        printf("Erro ao abrir o arquivo!! RegBin");
        return;
    }

    fwrite(&Agend, sizeof(Agendamento), 1, bin);

    fclose(bin);
}

void RegAgendTxt(Agendamento Agend) {
    FILE *txt = fopen("arquivos/agendamento.txt", "a");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo!! RegTxt");
        return;
    }

    fprintf(txt, "%d,%s,%s,%s,%s,%s,%s\n", Agend.codAgend, Agend.cliente, Agend.veiculo, Agend.servico, Agend.funcionario, Agend.data, Agend.hora);


    fclose(txt);
    printf("Agendamento registrado com sucesso!\n");
}

int horaParaMinutos(const char *hora) {
    int horas, minutos;
    sscanf(hora, "%d:%d", &horas, &minutos);
    return horas * 60 + minutos;
}

// Verifica se há conflito entre horários
int VerificaDisponibilidade(Agendamento novoAgend, const char *arquivo) {
    FILE *arq = fopen(arquivo, "a");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo de agendamentos.\n");
        return 1; // Permitir agendamento caso o arquivo não exista
    }

    Agendamento existente;
    while (fread(&existente, sizeof(Agendamento), 1, arq) == 1) {
        if (strcmp(existente.funcionario, novoAgend.funcionario) == 0 &&
            strcmp(existente.data, novoAgend.data) == 0) {
            // Conflito na mesma data para o mesmo funcionário
            int inicioNovo = horaParaMinutos(novoAgend.hora);
            int fimNovo = inicioNovo + novoAgend.peso;
            int inicioExistente = horaParaMinutos(existente.hora);
            int fimExistente = inicioExistente + existente.peso;

            if (inicioNovo < fimExistente && fimNovo > inicioExistente) {
                fclose(arq);
                return 0; // Conflito encontrado
            }
        }
    }
    fclose(arq);
    return 1; // Sem conflitos
}

void RegAgend() {
    Agendamento Agend;

    printf("\nPreencha os dados do cliente para realizar o agendamento:");
    
    printf("\nInsira o código do agendamento:");
    scanf("%d", &Agend.codAgend);
    getchar();
    printf("\nInsira o nome:");
    scanf("%49[^\n]", Agend.cliente);
    getchar();
    printf("\nInsira o veiculo:");
    scanf("%49[^\n]", Agend.veiculo);
    getchar();
    printf("\nInsira o serviço:");
    scanf("%49[^\n]", Agend.servico);
    getchar();
    printf("\nInsira o limite de serviço do dia (em minutos):");
    scanf("%d", &Agend.peso);
    getchar();
    printf("\nInsira o funcionario que irá fazer o serviço:");
    scanf("%49[^\n]", Agend.funcionario);
    getchar();
    printf("\nInsira a data do serviço (DD/MM/AAAA):");
    scanf("%10[^\n]", Agend.data);
    getchar();
    printf("\nInsira a hora do serviço (HH:MM):");
    scanf("%5[^\n]", Agend.hora);
    getchar();

    // Verifica disponibilidade
    if (!VerificaDisponibilidade(Agend, "arquivos/agendamento.txt")) {
        printf("Conflito de horários! Não foi possível agendar.\n");
        return;
    }

    // Verifica o formato de registro
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.txt", "a");
    if (formatoArq == NULL) {
        printf("Erro ao interpretar formato, padrão binário será usado.\n");
        formatoReg = 1; // Padrão binário
    } else {
        fread(&formatoReg, sizeof(int), 1, formatoArq);
        fclose(formatoArq);
    }

    // Registra o agendamento no formato escolhido
    if (formatoReg == 1) {
        RegAgendBin(Agend);
    } else {
        RegAgendTxt(Agend);
    }
}

void EditAgendBin() {
    int codBusca;
    printf("Digite o código do agendamento que deseja editar: ");
    scanf("%d", &codBusca);

    FILE *bin = fopen("arquivos/agendamento.bin", "rb");
    if (bin == NULL) {
        printf("Erro ao abrir o arquivo binário para leitura!\n");
        return;
    }

    FILE *temp = fopen("arquivos/temp.bin", "wb");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(bin);
        return;
    }

    Agendamento Agend;
    int encontrado = 0;

    while (fread(&Agend, sizeof(Agendamento), 1, bin)) {
        if (Agend.codAgend == codBusca) {
            encontrado = 1;
            printf("\nInsira o novo código do agendamento:");
            scanf("%d", &Agend.codAgend);
            getchar();
            printf("\nInsira o novo cliente:");
            scanf("%49[^\n]", Agend.cliente);
            getchar();
            printf("\nInsira o novo veiculo:");
            scanf("%49[^\n]", Agend.veiculo);
            getchar();
            printf("\nInsira o novo serviço:");
            scanf("%49[^\n]", Agend.servico);
            getchar();
            printf("\nInsira o novo funcionario que irá fazer o serviço:");
            scanf("%49[^\n]", Agend.funcionario);
            getchar();
            printf("\nInsira a nova data do serviço:");
            scanf("%10[^\n]", Agend.data);
            getchar();
            printf("\nInsira a nova hora do serviço:");
            scanf("%5[^\n]", Agend.hora);
            getchar();
        }
        // Registra as variaveis modificadas no arquivo temporario 
        fwrite(&Agend, sizeof(Agendamento), 1, temp);
    }

    fclose(bin);
    fclose(temp);

    if (encontrado) {
        remove("arquivos/agendamento.bin");
        rename("arquivos/temp.bin", "arquivos/agendamento.bin");
        printf("Agendamento editado com sucesso!\n");
    } else {
        remove("arquivos/temp.bin");
        printf("Agendamento com código %d não encontrada!\n", codBusca);
    }
}

void EditAgendTxt() {
    int codAgendBusca;

    printf("Insira o código do agendamento que deseja editar: ");
    scanf("%d", &codAgendBusca);
    getchar(); // Limpa o buffer do teclado

    FILE *txt = fopen("arquivos/agendamento.txt", "r");
    if (txt == NULL) {
        printf("Erro: Nenhum agendamento registrado ainda ou arquivo inexistente.\n");
        return;
    }

    FILE *temp = fopen("arquivos/temp.txt", "w");
    if (temp == NULL) {
        printf("Erro: Não foi possível criar um arquivo temporário.\n");
        fclose(txt);
        return;
    }

    Agendamento agend;
    int encontrado = 0;
    char linha[256];

    while (fgets(linha, sizeof(linha), txt)) {
        if (sscanf(linha, "%d,%49[^,],%49[^,],%49[^,],%49[^,],%10[^,],%5[^\n]", 
                   &agend.codAgend, agend.cliente, agend.veiculo, agend.servico, 
                   agend.funcionario, agend.data, agend.hora) == 7) {
            if (agend.codAgend == codAgendBusca) {
                encontrado = 1;
                printf("Agendamento encontrado para o cliente: %s\n", agend.cliente);
                printf("Insira os novos dados do agendamento:\n");

                printf("Novo nome do cliente: ");
                fgets(agend.cliente, sizeof(agend.cliente), stdin);
                agend.cliente[strcspn(agend.cliente, "\n")] = '\0';

                printf("Novo veículo: ");
                fgets(agend.veiculo, sizeof(agend.veiculo), stdin);
                agend.veiculo[strcspn(agend.veiculo, "\n")] = '\0';

                printf("Novo tipo de serviço: ");
                fgets(agend.servico, sizeof(agend.servico), stdin);
                agend.servico[strcspn(agend.servico, "\n")] = '\0';

                printf("Novo funcionário: ");
                fgets(agend.funcionario, sizeof(agend.funcionario), stdin);
                agend.funcionario[strcspn(agend.funcionario, "\n")] = '\0';

                printf("Nova data (DD/MM/AAAA): ");
                fgets(agend.data, sizeof(agend.data), stdin);
                agend.data[strcspn(agend.data, "\n")] = '\0';

                getchar();

                printf("Novo horário (HH:MM): ");
                fgets(agend.hora, sizeof(agend.hora), stdin);
                agend.hora[strcspn(agend.hora, "\n")] = '\0';

                // Escreve os novos dados no arquivo temporário
                fprintf(temp, "%d,%s,%s,%s,%s,%s,%s\n", agend.codAgend, agend.cliente, agend.veiculo,
                        agend.servico, agend.funcionario, agend.data, agend.hora);
            } else {
                // Copia os dados originais para o arquivo temporário
                fprintf(temp, "%s", linha);
            }
        }
    }

    fclose(txt);
    fclose(temp);

    if (encontrado) {
        remove("arquivos/agendamento.txt");
        if (rename("arquivos/temp.txt", "arquivos/agendamento.txt") == 0) {
            printf("Agendamento atualizado com sucesso!\n");
        } else {
            printf("Erro ao substituir o arquivo original.\n");
        }
    } else {
        remove("arquivos/temp.txt");
        printf("Agendamento com código %d não encontrado.\n", codAgendBusca);
    }
}

void EditAgend() {
    int formatoReg;

    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL) {
        printf("Erro na interpretação do formato do arquivo!");
        return;
    }
    fread(&formatoReg, sizeof(int), 1, formatoArq);

    // separa entre os formatos definidos no arquivo formato
    if (formatoReg == 1) {
        EditAgendBin();
    } else {
        EditAgendTxt();
    }

    fclose(formatoArq);
}

void LerAgendBin() {
    Agendamento Agend;

    FILE *bin = fopen("arquivos/agendamento.bin", "rb");
    if (bin == NULL) {
        printf("Erro ao Ler Bin");
        return;
    }

    printf("===================================== Lista de Agendamentos =====================================\n");
    while (fread(&Agend, sizeof(Agendamento), 1, bin)) {
        printf("\nCódigo: %d\nNome: %s\nVeiculo: %s\nServiço: %s\nFuncionario: %s\nData: %s\nHoras: %s", 
                Agend.codAgend, Agend.cliente, Agend.veiculo, Agend.servico, Agend.funcionario, Agend.data, Agend.hora);
        printf("--------------------------------------------------------------------------------------\n");
    }
    
    fclose(bin);
}

void LerAgendTxt() {
    Agendamento Agend;
    char linha[256];
    
    FILE *txt = fopen("arquivos/agendamento.txt", "r");
    if (txt == NULL) {
        printf("Nenhum agendamento registrado ainda!\n");
        return;
    }

    printf("===================================== Lista de Agendamentos =====================================\n");
    while (fgets(linha, sizeof(linha), txt)) {
        // Processa a linha usando sscanf
        if (sscanf(linha, "%d,%49[^,],%49[^,],%49[^,],%49[^,],%10[^,],%5[^\n]", 
                   &Agend.codAgend, 
                   Agend.cliente, 
                   Agend.veiculo, 
                   Agend.servico, 
                   Agend.funcionario, 
                   Agend.data, 
                   Agend.hora) == 7) {
            // Imprime os dados do agendamento
            printf("Código do agendamento: %d\n", Agend.codAgend);
            printf("Nome do cliente: %s\n", Agend.cliente);
            printf("Nome do veículo: %s\n", Agend.veiculo);
            printf("Tipo de serviço: %s\n", Agend.servico);
            printf("Funcionário responsável: %s\n", Agend.funcionario);
            printf("Data do agendamento: %s\n", Agend.data);
            printf("Horário do agendamento: %s\n", Agend.hora);
            printf("--------------------------------------------------------------------------------------\n");
        } else {
            printf("Erro ao processar linha: %s\n", linha);
        }
    }
    fclose(txt);
}


void LerAgend() {
    int formatoReg;

    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL) {
        printf("Erro na interpretação do formato do arquivo!");
        return;
    }
    fread(&formatoReg, sizeof(int), 1, formatoArq);

    if (formatoReg == 1) {
        LerAgendBin();
    } else {
        LerAgendTxt();
    }

    fclose(formatoArq);
}

void RemoverAgendTxt() {
    int codAgendBusca;
    char confirmacao;
    int formato;
    int encontrado = 0;

    // Lê o formato do arquivo
    FILE *formatoFile = fopen("arquivos/formato.bin", "rb");
    if (formatoFile == NULL) {
        printf("Erro ao abrir o arquivo de formato. Certifique-se de que ele existe!\n");
        return;
    }
    fread(&formato, sizeof(int), 1, formatoFile);
    fclose(formatoFile);

    printf("Digite o código do agendamento a ser excluído: ");
    scanf("%d", &codAgendBusca);
    while (getchar() != '\n'); // Limpa o buffer do teclado

    if (formato == 1) {
        // Modo binário
        FILE *arquivo = fopen("arquivos/agendamento.bin", "rb");
        FILE *temp = fopen("arquivos/temp.bin", "wb");

        if (arquivo == NULL || temp == NULL) {
            printf("Erro ao abrir os arquivos necessários.\n");
            if (arquivo) fclose(arquivo);
            if (temp) fclose(temp);
            return;
        }

        Agendamento agend;

        while (fread(&agend, sizeof(Agendamento), 1, arquivo)) {
            if (agend.codAgend == codAgendBusca) {
                encontrado = 1;
                printf("Agendamento com código %d encontrado. Deseja realmente excluí-lo? (S/N): ", codAgendBusca);
                scanf(" %c", &confirmacao);
                while (getchar() != '\n'); // Limpa o buffer do teclado

                if (confirmacao == 'S' || confirmacao == 's') {
                    printf("Agendamento excluído com sucesso!\n");
                    continue;
                } else {
                    printf("Operação cancelada.\n");
                }
            }
            fwrite(&agend, sizeof(Agendamento), 1, temp);
        }

        fclose(arquivo);
        fclose(temp);

        if (encontrado) {
            remove("arquivos/agendamento.bin");
            rename("arquivos/temp.bin", "arquivos/agendamento.bin");
        } else {
            remove("arquivos/temp.bin");
        }
    } else if (formato == 2) {
        // Modo texto
        FILE *arquivo = fopen("arquivos/agendamento.txt", "r");
        FILE *temp = fopen("arquivos/temp.txt", "w");

        if (arquivo == NULL || temp == NULL) {
            printf("Erro ao abrir os arquivos necessários.\n");
            if (arquivo) fclose(arquivo);
            if (temp) fclose(temp);
            return;
        }

        char linha[256];

        while (fgets(linha, sizeof(linha), arquivo)) {
            int codAgend;
            sscanf(linha, "%d,%*s", &codAgend); // Lê apenas o código de agendamento

            if (codAgend == codAgendBusca) {
                encontrado = 1;
                printf("Agendamento com código %d encontrado. Deseja realmente excluí-lo? (S/N): ", codAgendBusca);
                scanf(" %c", &confirmacao);
                while (getchar() != '\n'); // Limpa o buffer do teclado

                if (confirmacao == 'S' || confirmacao == 's') {
                    printf("Agendamento excluído com sucesso!\n");
                    continue;
                } else {
                    printf("Operação cancelada.\n");
                }
            }
            fprintf(temp, "%s", linha); // Reescreve a linha no arquivo temporário
        }

        fclose(arquivo);
        fclose(temp);

        if (encontrado) {
            remove("arquivos/agendamento.txt");
            rename("arquivos/temp.txt", "arquivos/agendamento.txt");
        } else {
            remove("arquivos/temp.txt");
        }
    } else {
        printf("Formato inválido definido no arquivo de configuração.\n");
        return;
    }

    if (!encontrado) {
        printf("Agendamento com código %d não encontrado.\n", codAgendBusca);
    }
}


void RemoverAgendBin() {
    int codBusca;

    printf("Digite o código do agendamento que deseja remover: ");
    scanf("%d", &codBusca);

    FILE *bin = fopen("arquivos/agendamento.bin", "rb");
    if (bin == NULL) {
        printf("Erro ao abrir o arquivo binário para leitura!\n");
        return;
    }

    FILE *temp = fopen("arquivos/temp.bin", "wb");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(bin);
        return;
    }

    Agendamento Agend;
    int encontrado = 0;

    while (fread(&Agend, sizeof(Agendamento), 1, bin)) {
        if (Agend.codAgend == codBusca) {
            encontrado = 1;
        } else {
            fwrite(&Agend, sizeof(Agendamento), 1, temp);
        }
    }

    fclose(bin);
    fclose(temp);

    if (encontrado) {
        remove("arquivos/agendamento.bin");
        rename("arquivos/temp.bin", "arquivos/agendamento.bin");
        printf("Agendamento removido com sucesso!\n");
    } else {
        remove("arquivos/temp.bin"); 
        printf("Agendamento com código %d não encontrado!\n", codBusca);
    }
}

void RemoverAgend() {
    int formatoReg;

    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL) {
        printf("Erro na interpretação do formato do arquivo!");
        return;
    }
    fread(&formatoReg, sizeof(int), 1, formatoArq);

    if (formatoReg == 1) {
        RemoverAgendBin();
    } else {
        RemoverAgendTxt();
    }

    fclose(formatoArq);
}

// Ordem de Serviços -----------------------------------------------------------

void RegOSBin(OrdemServico OS) {
    FILE *bin = fopen("arquivos/ordemservico.bin", "ab");
    if (bin == NULL) {
        printf("Erro ao abrir o arquivo binário!\n");
        return;
    }

    fwrite(&OS, sizeof(OrdemServico), 1, bin);
    fclose(bin);
}

void RegOSTxt(OrdemServico OS) {
    FILE *txt = fopen("arquivos/ordemservico.txt", "a");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo texto!\n");
        return;
    }

    fprintf(txt, "%d,%d,%d,%d,%s,%d,%.2f\n", OS.codOS, OS.cliente, OS.veiculo, OS.servicos, OS.pecas, OS.numPecas, OS.vlrTot);
    fclose(txt);
}

void RegOS() {
    OrdemServico OS;

    printf("\nPreencha os dados para a Ordem de Serviço:\n");
    printf("\nCódigo da Ordem de Serviço: ");
    scanf("%d", &OS.codOS);
    getchar();
    printf("\nInsira o código do cliente: ");
    scanf("%d", &OS.cliente);
    getchar();
    printf("\nInsira o código do veículo: ");
    scanf("%d", &OS.veiculo);
    getchar();
    printf("\nInsira o código do serviço: ");
    scanf("%d", &OS.servicos);
    getchar();
    printf("\nDescriçao das peças utilizadas: ");
    scanf("%99[^\n]", OS.pecas);
    getchar();
    printf("\nNúmero de peças utilizadas: ");
    scanf("%d", &OS.numPecas);
    getchar();
    printf("\nValor do serviço: R$ ");
    scanf("%f", &OS.vlrTot);

    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL) {
        printf("Erro ao interpretar o formato. Padrão binário será usado.\n");
        formatoReg = 1; // Padrão binário
    } else {
        fread(&formatoReg, sizeof(int), 1, formatoArq);
        fclose(formatoArq);
    }

    if (formatoReg == 1) {
        RegOSBin(OS);
    } else {
        RegOSTxt(OS);
    }
}

void EditOSBin() {
    int CodBusca;
    printf("Digite o código da Ordem de Serviço que deseja editar: ");
    scanf("%d", &CodBusca);

    FILE *bin = fopen("arquivos/ordemservico.bin", "rb");
    if (bin == NULL) {
        printf("Erro ao abrir o arquivo binário para leitura!\n");
        return;
    }

    FILE *temp = fopen("arquivos/temp.bin", "wb");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(bin);
        return;
    }

    OrdemServico OS;
    int encontrado = 0;

    while (fread(&OS, sizeof(OrdemServico), 1, bin)) {
        if (OS.codOS == CodBusca) {
            encontrado = 1;
            printf("\nInsira os novos dados da Ordem de Serviço:\n");
            printf("Código da Ordem de Serviço: ");
            scanf("%d", &OS.codOS);
            getchar();
            printf("novo código do cliente: ");
            scanf("%d", &OS.cliente);
            getchar();
            printf("Novo código do veículo: ");
            scanf("%d", &OS.veiculo);
            getchar();
            printf("Novo código do serviço: ");
            scanf("%d", &OS.servicos);
            getchar();
            printf("Descrição das peças utilizadas: ");
            scanf("%99[^\n]", OS.pecas);
            getchar();
            printf("\nNúmero de peças utilizadas: ");
            scanf("%d", &OS.numPecas);
            getchar();
            printf("\nValor do serviço: R$ ");
            scanf("%f", &OS.vlrTot);
        }

        fwrite(&OS, sizeof(OrdemServico), 1, temp);
    }

    fclose(bin);
    fclose(temp);

    if (encontrado) {
        remove("arquivos/ordemservico.bin");
        rename("arquivos/temp.bin", "arquivos/ordemservico.bin");
        printf("Ordem de Serviço editada com sucesso!\n");
    } else {
        remove("arquivos/temp.bin");
        printf("OS com código %d não encontrada!\n", CodBusca);
    }
}

void EditOSTxt() {
    int CodOSBusca;

    printf("Digite o código da ordem de serviço que deseja editar: ");
    scanf("%d", &CodOSBusca);
    getchar();

    FILE *txt = fopen("arquivos/ordemservico.txt", "r");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo texto para leitura!\n");
        return;
    }

    FILE *temp = fopen("arquivos/temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(txt);
        return;
    }

    OrdemServico OS;
    char linha[256];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), txt)) {
        if (sscanf(linha, "%d,%d,%d,%d,%99[^\n],%d,%.2f", &OS.codOS, OS.cliente, OS.veiculo, OS.servicos, OS.pecas, OS.numPecas, OS.vlrTot) == 7) {
            if (OS.codOS == CodOSBusca) {
                encontrado = 1;
                printf("Ordem de Serviço encontrado para o cliente: %s\n", OS.cliente);
                printf("Insira os novos dados da Ordem de Serviço:\n");

                printf("Novo código da ordem de serviço: ");
                scanf("%d", &OS.codOS);

                printf("Novo código do cliente: ");
                scanf("%d", &OS.cliente);

                printf("Novo código do veículo: ");
                scanf("%d", &OS.veiculo);
                
                printf("Novo código do serviço: ");
                scanf("%d", &OS.servicos);
                
                printf("Nova descrição de peças utilizadas: ");
                fgets(OS.pecas, sizeof(OS.pecas), stdin);
                OS.pecas[strcspn(OS.pecas, "\n")] = '\0';
                
                printf("Novo número de peças utilizadas: ");
                scanf("%d", &OS.numPecas);
                getchar();
                printf("Novo valor do serviço: R$ ");
                scanf("%.2f", &OS.vlrTot);
            
                fprintf(temp, "%d,%d,%d,%d,%s,%d,%.2f\n", OS.codOS, OS.cliente, OS.veiculo,
                        OS.servicos, OS.pecas, OS.numPecas, OS.vlrTot);
            } else {
                
                fprintf(temp, "%s", linha);
            }
        }
    }

    fclose(txt);
    fclose(temp);

    if (encontrado) {
        remove("arquivos/ordemservico.txt");
        if (rename("arquivos/temp.txt", "arquivos/ordemservico.txt") == 0) {
            printf("Ordem de Serviço atualizado com sucesso!\n");
        } else {
            printf("Erro ao substituir o arquivo original.\n");
        }
    } else {
        remove("arquivos/temp.txt");
        printf("Ordem de serviço com código %d não encontrado.\n", CodOSBusca);
    }
}

void EditOS() {
    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL) {
        printf("Erro ao interpretar formato do arquivo!\n");
        return;
    }
    fread(&formatoReg, sizeof(int), 1, formatoArq);
    fclose(formatoArq);

    if (formatoReg == 1) {
        EditOSBin();
    } else {
        EditOSTxt();
    }
}

void LerOSBin() {
    OrdemServico OS;
    
    FILE *bin = fopen("arquivos/ordemservico.bin", "rb");
    if (bin == NULL) {
        printf("Nenhuma Ordem de Serviço registrado ainda!!\n");
        return;
    }

    FILE *InfoCli = fopen("arquivos/clientes.bin", "rb");
    if (InfoCli == NULL) {
        printf("Erro ao abrir o arquivo de clientes!\n");
        return;
    }
    ClienteInfo cli;

    FILE *InfoVec = fopen("arquivos/veiculos.bin", "rb");
    if (InfoVec == NULL) {
        printf("Erro ao abrir o arquivo de veículos!\n");
        return;
    }
    VeiculoInfo vec;


    FILE *InfoPeca = fopen("arquivos/peca.bin", "rb");
    if (InfoPeca == NULL) {
        printf("Erro ao abrir o arquivo de peças!\n");
        return;
    }
    PecaDados peca;

    printf("================================== Lista das Ordens de Serviços ==================================\n");
    while (fread(&OS, sizeof(OrdemServico), 1, bin)) {
        printf("Código: %d\n", &OS.codOS);
        
        while (fread(&cli, sizeof(ClienteInfo), 1, InfoCli)) {
            if (cli.id == OS.cliente) {
                printf("Nome do Cliente: %s\n", cli.nome);
                break;
            }
        }

        while (fread(&vec, sizeof(VeiculoInfo), 1, InfoVec)) {
            if (vec.id == OS.veiculo) {
                printf("Veículo: %s\n", vec.modelo);
                break;
            }
        }
        
        printf("Descrição do serviço: %s\n", OS.servicos);
        printf("Descrição das peças utilizadas: %s\n", OS.pecas);
        printf("Número de peças utilizadas: %d\n", &OS.numPecas);

        printf("Valor do serviço: R$%.2f\n", &OS.vlrTot);
        printf("--------------------------------------------------------------------------------------\n");
    }
    fclose(bin);
    fclose(InfoCli);
    fclose(InfoVec);
    fclose(InfoPeca);
}

void LerOSTxt() {
    OrdemServico OS;
    FILE *txt = fopen("arquivos/ordemservico.txt", "r");
    if (txt == NULL) {
        printf("Nenhuma Ordem de Serviço registrada ainda!!\n");
        return;
    }

    FILE *InfoCli = fopen("arquivos/clientes.txt", "r");
    if (InfoCli == NULL) {
        printf("Erro ao abrir o arquivo de clientes!\n");
        fclose(txt);
        return;
    }

    FILE *InfoVec = fopen("arquivos/veiculos.txt", "r");
    if (InfoVec == NULL) {
        printf("Erro ao abrir o arquivo de veículos!\n");
        fclose(txt);
        fclose(InfoCli);
        return;
    }

    FILE *InfoPeca = fopen("arquivos/peca.txt", "r");
    if (InfoPeca == NULL) {
        printf("Erro ao abrir o arquivo de peças!\n");
        fclose(txt);
        fclose(InfoCli);
        fclose(InfoVec);
        return;
    }

    PecaDados peca;
    ClienteInfo cli;
    VeiculoInfo vec;

    printf("================================== Lista das Ordens de Serviços ==================================\n");
    while (fscanf(txt, "%d,%d,%d,%d,%99[^,],%d,%f", &OS.codOS, &OS.cliente, &OS.veiculo, &OS.servicos, OS.pecas, &OS.numPecas, &OS.vlrTot) == 7) {
        printf("Código: %d\n", OS.codOS);

        rewind(InfoCli);
        while (fscanf(InfoCli, "%d,%99[^,],%19[^,],%99[^,],%19[^,],%49[^\n]", &cli.id, cli.nome, cli.cpfCnpj, cli.endereco, cli.telefone, cli.email) == 6) {
            if (cli.id == OS.cliente) {
                printf("Nome do Cliente: %s\n", cli.nome);
                break;
            }
        }

        rewind(InfoVec);
        while (fscanf(InfoVec, "%d,%9[^,],%49[^,],%49[^,],%d,%24[^,],%99[^\n]", &vec.id, vec.placa, vec.modelo, vec.marca, &vec.anoFabricacao, vec.chassi, vec.proprietario) == 7) {
            if (vec.id == OS.veiculo) {
                printf("Veículo: %s\n", vec.modelo);
                break;
            }
        }

        rewind(InfoPeca);
        while (fscanf(InfoPeca, "%d,%19[^,],%59[^,],%29[^,],%29[^,],%f,%f,%d,%d", &peca.codpec, peca.nomepec, peca.descpec, peca.fabpec, peca.fornpec, peca.custpeca, peca.vendpeca, &peca.npeca, &peca.minpeca) == 9) {
            if (strcmp(peca.nomepec, OS.pecas) == 0) {
                int quantidadeRestante = peca.npeca - OS.numPecas;
                if (quantidadeRestante < 0) {
                    quantidadeRestante = 0; // Evita valores negativos
                }
                printf("Quantidade da peça utilizada no estoque: %d\n", quantidadeRestante);
                break;
            }
        }

        printf("Descrição do serviço: %s\n", OS.servicos);
        printf("Número de peças utilizadas: %d\n", OS.numPecas);
        printf("Valor do serviço: R$ %.2f\n", OS.vlrTot);
        printf("--------------------------------------------------------------------------------------\n");
    }

    fclose(txt);
    fclose(InfoCli);
    fclose(InfoVec);
    fclose(InfoPeca);
}

void LerOS(){
    int formatoReg;
    
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL){
        printf("Erro na interpretação do formato do arquivo!");
        return;
    }
    fread(&formatoReg, sizeof(int), 1, formatoArq);

    //separa entre os formatos definidos no arquivo de formato
    if (formatoReg == 1){
        LerOSBin();
    }
    else{
        LerOSTxt();
    }

    fclose(formatoArq);
}

void RemoverOSTxt() {
    int codOSBusca;
    char confirmacao;
    int formato;
    int encontrado = 0;

    FILE *formatoFile = fopen("arquivos/formato.bin", "rb");
    if (formatoFile == NULL) {
        printf("Erro ao abrir o arquivo de formato. Certifique-se de que ele existe!\n");
        return;
    }
    fread(&formato, sizeof(int), 1, formatoFile);
    fclose(formatoFile);

    printf("Digite o código da Ordem de Serviço a ser excluído: ");
    scanf("%d", &codOSBusca);
    while (getchar() != '\n'); // Limpa o buffer do teclado

    if (formato == 1) {
       
        FILE *arquivo = fopen("arquivos/ordemservico.bin", "rb");
        FILE *temp = fopen("arquivos/temp.bin", "wb");

        if (arquivo == NULL || temp == NULL) {
            printf("Erro ao abrir os arquivos necessários.\n");
            if (arquivo) fclose(arquivo);
            if (temp) fclose(temp);
            return;
        }

        OrdemServico OS;

        while (fread(&OS, sizeof(OrdemServico), 1, arquivo)) {
            if (OS.codOS == codOSBusca) {
                encontrado = 1;
                printf("Ordem de Serviço com código %d encontrado. Deseja realmente excluí-lo? (S/N): ", codOSBusca);
                scanf(" %c", &confirmacao);
                while (getchar() != '\n'); 

                if (confirmacao == 'S' || confirmacao == 's') {
                    printf("Ordem de Serviço excluído com sucesso!\n");
                    continue;
                } else {
                    printf("Operação cancelada.\n");
                }
            }
            fwrite(&OS, sizeof(OrdemServico), 1, temp);
        }

        fclose(arquivo);
        fclose(temp);

        if (encontrado) {
            remove("arquivos/ordemservico.bin");
            rename("arquivos/temp.bin", "arquivos/ordemservico.bin");
        } else {
            remove("arquivos/temp.bin");
        }
    } else if (formato == 2) {
    
        FILE *arquivo = fopen("arquivos/ordemservico.txt", "r");
        FILE *temp = fopen("arquivos/temp.txt", "w");

        if (arquivo == NULL || temp == NULL) {
            printf("Erro ao abrir os arquivos necessários.\n");
            if (arquivo) fclose(arquivo);
            if (temp) fclose(temp);
            return;
        }

        char Linha[256];

        while (fgets(Linha, sizeof(Linha), arquivo)) {
            int codOS;
            sscanf(Linha, "%d,%*s", &codOS); // Lê apenas o código de OS

            if (codOS == codOSBusca) {
                encontrado = 1;
                printf("Ordem de Serviço com código %d encontrado. Deseja realmente excluí-lo? (S/N): ", codOSBusca);
                scanf(" %c", &confirmacao);
                while (getchar() != '\n'); // Limpa o buffer do teclado

                if (confirmacao == 'S' || confirmacao == 's') {
                    printf("Ordem de Serviço excluído com sucesso!\n");
                    continue;
                } else {
                    printf("Operação cancelada.\n");
                }
            }
            fprintf(temp, "%s", Linha); // Reescreve a linha no arquivo temporário
        }

        fclose(arquivo);
        fclose(temp);

        if (encontrado) {
            remove("arquivos/ordemservico.txt");
            rename("arquivos/temp.txt", "arquivos/ordemservico.txt");
        } else {
            remove("arquivos/temp.txt");
        }
    } else {
        printf("Formato inválido definido no arquivo de configuração.\n");
        return;
    }

    if (!encontrado) {
        printf("Ordem de Serviço com código %d não encontrado.\n", codOSBusca);
    }
}


void RemoverOSBin() {
    int CodBusca;

    printf("Digite o código da Ordem de Serviço que deseja remover: ");
    scanf("%d", &CodBusca);

    FILE *bin = fopen("arquivos/ordemservico.bin", "rb");
    if (bin == NULL) {
        printf("Erro ao abrir o arquivo binário para leitura!\n");
        return;
    }

    FILE *temp = fopen("arquivos/temp.bin", "wb");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(bin);
        return;
    }

    OrdemServico OS;
    int encontrado = 0;

    while (fread(&OS, sizeof(OrdemServico), 1, bin)) {
        if (OS.codOS == CodBusca) {
            encontrado = 1;
        } else {
            fwrite(&OS, sizeof(OrdemServico), 1, temp);
        }
    }

    fclose(bin);
    fclose(temp);

    if (encontrado) {
        remove("arquivos/ordemservico.bin");
        rename("arquivos/temp.bin", "arquivos/ordemservico.bin");
        printf("Ordem de Serviço removido com sucesso!\n");
    } else {
        remove("arquivos/temp.bin"); 
        printf("Ordem de Serviço com código %d não encontrado!\n", CodBusca);
    }
}

void RemoverOS() {
    int formatoReg;

    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL) {
        printf("Erro na interpretação do formato do arquivo!");
        return;
    }
    fread(&formatoReg, sizeof(int), 1, formatoArq);

    if (formatoReg == 1) {
        RemoverOSBin();
    } else {
        RemoverOSTxt();
    }

    fclose(formatoArq);
}