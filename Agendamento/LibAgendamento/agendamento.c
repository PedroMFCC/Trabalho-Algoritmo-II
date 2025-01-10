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
    printf("Agendamento registrado com sucesso!");
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
    printf("\nInsira o funcionario que irá fazer o serviço:");
    scanf("%49[^\n]", Agend.funcionario);
    getchar();
    printf("\nInsira a data do serviço:");
    scanf("%10[^\n]", Agend.data);
    getchar();
    printf("\nInsira a hora do serviço:");
    scanf("%5[^\n]", Agend.hora);
    getchar();

    int formatoReg;
    FILE *formatoArq = fopen("arquivos/formato.bin", "rb");
    if (formatoArq == NULL) {
        printf("Erro ao interpretar formato, padrão binário será usado.\n");
        formatoReg = 1; // Padrão binário
    } else {
        fread(&formatoReg, sizeof(int), 1, formatoArq);
        fclose(formatoArq);
    }

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