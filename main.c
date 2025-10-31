//_____BIBLIOTECAS______<
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//______________________


//______CABEÇALHO DE FUNÇÕES________<

// Calcular horas extras.
int acumularhorasfuncao(int a, int b) 
{
    int horasextrascalculo;
    horasextrascalculo = abs(a - b);
    
    if (horasextrascalculo > 8) {
    horasextrascalculo -= 8;
	}
    else {
        horasextrascalculo = 0;
	}
	
    return horasextrascalculo;
}

// Registrar horas.
void registrarHoras(int entrada, int saida, int horasextras, int negado) {
    FILE *arquivo;
    time_t agora;
    struct tm *infoTempo;

    time(&agora);
    infoTempo = localtime(&agora);

    arquivo = fopen("relatorio_horas.txt", "a");
    if (arquivo == NULL) {
        return;
    }

    fprintf(arquivo, "-------------------------------------\n");
    fprintf(arquivo, "Data: %02d/%02d/%04d\n", infoTempo->tm_mday, infoTempo->tm_mon + 1, infoTempo->tm_year + 1900);
    fprintf(arquivo, "Hora do registro: %02d:%02d:%02d\n", infoTempo->tm_hour, infoTempo->tm_min, infoTempo->tm_sec);

    if (negado) {
        fprintf(arquivo, "Status: Hora extra NEGADA pelo gestor.\n");
        fprintf(arquivo, "Entrada: -- | Saida: -- | Horas Extras: 0h\n");
    } 
	else {
        fprintf(arquivo, "Status: Hora extra APROVADA.\n");
        fprintf(arquivo, "Entrada: %dh | Saida: %dh | Horas Extras: %dh\n", entrada, saida, horasextras);
    }

    fprintf(arquivo, "-------------------------------------\n\n");
    fclose(arquivo);
}

// Contar registros aprovados e negados.
int contarRegistros() {
    FILE *arquivo;
    char linha[200];
    int contador = 0;

    arquivo = fopen("relatorio_horas.txt", "r");
    if (arquivo == NULL)
        return 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (strstr(linha, "Status:"))
            contador++;
    }

    fclose(arquivo);
    return contador;
}

// Somar apenas horas extras aprovadas.
int somarHorasExtras() {
    FILE *arquivo;
    char linha[200];
    int total = 0, horas;
    arquivo = fopen("relatorio_horas.txt", "r");
    if (arquivo == NULL)
        return 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (sscanf(linha, "Entrada: %*dh | Saida: %*dh | Horas Extras: %dh", &horas) == 1)
            total += horas;
    }

    fclose(arquivo);
    return total;
}

// Exibir relatório completo
void visualizarRelatorio() {
    FILE *arquivo;
    char linha[200];
    int totalHoras = somarHorasExtras();
    int qtdRegistros = contarRegistros();
    int opcaoRelatorio;

    arquivo = fopen("relatorio_horas.txt", "r");
    if (arquivo == NULL) {
        printf("\nNenhum registro encontrado.\n");
        system("pause");
        return;
    }

    // Exibir conteúdo do relatório
    system("cls");
    printf("\n===== RELATORIO DE HORAS EXTRAS =====\n\n");
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
    }
    fclose(arquivo);

    printf("Total de registros (aprovados e negados): %d\n", qtdRegistros);
    printf("Total de horas extras acumuladas: %dh\n", totalHoras);
    printf("\n=====================================\n");

    // Menu interno do relatório
    printf("\n(1) Voltar ao menu principal\n(2) Fechar relatorio\n-> ");
    scanf("%d", &opcaoRelatorio);

    if (opcaoRelatorio == 2) {
  		
        printf("\nTotal final de horas extras: %dh\n", totalHoras);

        arquivo = fopen("relatorio_horas.txt", "w"); 
		system("pause");
	}

}

//__________________________________


int main() {
    int resposta, respostagestor, entradafuncionario, saidafuncionario, acumulohorasextras;

    do {
        system("cls");
        printf("<===== REGISTRO DE HORAS EXTRAS ====>\n");
        printf("(1) Solicitar hora extra\n(2) Relatorio\n(3) Controle de Horas\n(4) Sair\n-> ");
        scanf("%d", &resposta);

        switch (resposta) {
            case 1:
                system("cls");
                do {
                    printf("=== GESTOR === \n");
                    printf("Liberar hora extra diaria?\n(1) Sim    (2) Nao\n-> ");
                    scanf("%d", &respostagestor);

                    if (respostagestor == 1) {
                        system("cls");
                        printf("Horario de Entrada (somente hora inteira): ");
                        scanf("%d", &entradafuncionario);
                        printf("Horario de Saida (somente hora inteira): ");
                        scanf("%d", &saidafuncionario);

                        acumulohorasextras = acumularhorasfuncao(entradafuncionario, saidafuncionario);

                        printf("\nHoras extras registradas: %dh\n", acumulohorasextras);

                        registrarHoras(entradafuncionario, saidafuncionario, acumulohorasextras, 0);

                        printf("Registro salvo com sucesso no arquivo relatorio_horas.txt!\n\n");
                        system("pause");
                    } 
                    else if (respostagestor == 2) {
                        printf("Horas extras negadas!\n");
                        registrarHoras(0, 0, 0, 1);
                        system("pause");
                    } 
                    else {
                        printf("Opcao invalida! Tente novamente.\n");
                        system("pause");
                    }

                    system("cls");
                } while (respostagestor != 1 && respostagestor != 2);
                break;

            case 2:
                system("cls");
                visualizarRelatorio();
                break;

            case 3:
                system("cls");
                printf("Funcionalidade de controle ainda em desenvolvimento.\n");
                system("pause");
                break;

            case 4:
                printf("Programa finalizado.\n");
                exit(EXIT_SUCCESS);
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
                system("pause");
                break;
        }

    } while (resposta != 4);

    return 0;
}
