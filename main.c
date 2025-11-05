
//_____BIBLIOTECAS______
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//______________________

//______ESTRUTURAS E DEFINIÇÕES________
#define MAX_NOME 100
#define MAX_PESSOAS 100
#define VALOR_HORA_EXTRA 80

typedef struct {
  char nome[MAX_NOME];
  int id;
} Pessoa;

typedef struct {
  int idPessoa;
  int entrada;
  int saida;
  int horasextras;
  int negado;
  time_t dataRegistro;
} RegistroHoras;
//______________________


//______CABEÇALHO DE FUNÇÕES________

// Funções de cadastro
void cadastrarPessoa();
void listarPessoas();
int pessoaExiste(int id);

// Funções de horas extras
int acumularhorasfuncao(int a, int b);
void registrarHoras(int idPessoa, int entrada, int saida, int horasextras,
                    int negado);
int contarRegistrosPessoa(int idPessoa);
int somarHorasExtrasPessoa(int idPessoa);

// Funções de relatório
void visualizarRelatorioGeral();
void visualizarRelatorioIndividual(int idPessoa);
void fecharHorasExtras();

// Funções auxiliares
void limparBuffer();
void carregarPessoas();
void salvarPessoas();

//__________________________________

//______VARIÁVEIS GLOBAIS________
Pessoa pessoas[MAX_PESSOAS];
int totalPessoas = 0;
//______________________________

//______FUNÇÕES DE CADASTRO________
void carregarPessoas() {
  FILE *arquivo = fopen("pessoas.txt", "r");
  if (arquivo == NULL)
    return;

  totalPessoas = 0;
  while (fscanf(arquivo, "%d %[^\n]", &pessoas[totalPessoas].id,
                pessoas[totalPessoas].nome) == 2) {
    totalPessoas++;
    if (totalPessoas >= MAX_PESSOAS)
      break;
  }
  fclose(arquivo);
}

void salvarPessoas() {
  FILE *arquivo = fopen("pessoas.txt", "w");
  if (arquivo == NULL)
    return;

  for (int i = 0; i < totalPessoas; i++) {
    fprintf(arquivo, "%d %s\n", pessoas[i].id, pessoas[i].nome);
  }
  fclose(arquivo);
}

void cadastrarPessoa() {
  system("clear");
  printf("=== CADASTRO DE FUNCIONÁRIO ===\n\n");

  if (totalPessoas >= MAX_PESSOAS) {
    printf("Limite maximo de pessoas atingido!\n");
    printf("\nPressione qualquer tecla para voltar...");
    getchar();
    getchar();
    return;
  }

  printf("ID do Funcionário: ");
  scanf("%d", &pessoas[totalPessoas].id);
  limparBuffer();

  if (pessoaExiste(pessoas[totalPessoas].id)) {
    printf("ID já existente.\n");
    printf("\nPressione qualquer tecla para voltar...");
    getchar();
     getchar();
    return;
  }

  printf("Nome do funcionário: ");
  fgets(pessoas[totalPessoas].nome, MAX_NOME, stdin);
  pessoas[totalPessoas].nome[strcspn(pessoas[totalPessoas].nome, "\n")] = 0;

  totalPessoas++;
  salvarPessoas();

  printf("\nCadastro realizado.!\n");
    printf("\nPressione qualquer tecla para voltar...");
    getchar();
    getchar();
}

void listarPessoas() {
  system("clear");
  printf("=== FUNCIONÁRIOS CADASTRADOS ===\n\n");

  if (totalPessoas == 0) {
    printf("Nenhum funcionário cadastrado.\n");
  } 
  else {
    for (int i = 0; i < totalPessoas; i++) {
      printf("ID: %d | Nome: %s\n", pessoas[i].id, pessoas[i].nome);
    }
  }
  printf("\n");
    printf("\nPressione qualquer tecla para voltar...");
    getchar();
    getchar();
}

int pessoaExiste(int id) {
  for (int i = 0; i < totalPessoas; i++) {
    if (pessoas[i].id == id)
      return 1;
  }
  return 0;
}

char *obterNomePessoa(int id) {
  for (int i = 0; i < totalPessoas; i++) {
    if (pessoas[i].id == id)
      return pessoas[i].nome;
  }
  return "Nao encontrado";
}

//______FUNÇÕES DE HORAS EXTRAS________
int acumularhorasfuncao(int a, int b) {
  int horasextrascalculo;
  horasextrascalculo = abs(a - b);

  if (horasextrascalculo > 8) {
    horasextrascalculo -= 8;
    if (horasextrascalculo > 2) {
      horasextrascalculo = 2;
    }
  } else {
    horasextrascalculo = 0;
  }

  return horasextrascalculo;
}

void registrarHoras(int idPessoa, int entrada, int saida, int horasextras,
                    int negado) {
  FILE *arquivo;
  time_t agora;
  struct tm *infoTempo;

  time(&agora);
  infoTempo = localtime(&agora);

  arquivo = fopen("relatorio_horas.txt", "a");
  if (arquivo == NULL)
    return;

  fprintf(arquivo, "-------------------------------------\n");
  fprintf(arquivo, "ID: %d | Nome: %s\n", idPessoa, obterNomePessoa(idPessoa));
  fprintf(arquivo,
          "Data: %02d/%02d/%04d  |  Hora do registro: %02d:%02d:%02d\n",
          infoTempo->tm_mday, infoTempo->tm_mon + 1, infoTempo->tm_year + 1900,
          infoTempo->tm_hour, infoTempo->tm_min, infoTempo->tm_sec);

  if (negado) {
    fprintf(arquivo, "Status: Hora extra NEGADA pelo gestor.\n");
    fprintf(arquivo, "Entrada: -- | Saida: -- | Horas Extras: 0h\n");
  } else {
    fprintf(arquivo, "Status: Hora extra APROVADA.\n");
    fprintf(arquivo, "Entrada: %dh | Saida: %dh | Horas Extras: %dh\n", entrada,
            saida, horasextras);
  }

  fprintf(arquivo, "-------------------------------------\n\n");
  fclose(arquivo);
}

void solicitarHorasExtra() {
  system("clear");
  printf("=== SOLICITAR HORAS EXTRAS ===\n\n");

  if (totalPessoas == 0) {
    printf("Nenhuma pessoa cadastrada. Cadastre uma pessoa primeiro.\n");
    
    return;
  }

  printf("Pessoas cadastradas:\n");
  for (int i = 0; i < totalPessoas; i++) {
    printf("ID: %d | Nome: %s\n", pessoas[i].id, pessoas[i].nome);
  }

  int idPessoa, respostagestor, entradafuncionario, saidafuncionario,
      acumulohorasextras;

  printf("\nDigite o ID da pessoa: ");
  scanf("%d", &idPessoa);

  if (!pessoaExiste(idPessoa)) {
    printf("ID nao encontrado!\n");
        printf("\nPressione qualquer tecla para voltar...");
        getchar();
        getchar();
    return;
  }

  do {
    system("clear");
    printf("=== GESTOR === \n");
    printf("Pessoa: %s\n", obterNomePessoa(idPessoa));
    printf("Liberar hora extra diaria?\n(1) Sim    (2) Nao\n-> ");
    scanf("%d", &respostagestor);

    if (respostagestor == 1) {
      system("clear");
      printf("Pessoa: %s\n\n", obterNomePessoa(idPessoa));
      printf("Horario de Entrada (somente hora inteira): ");
      scanf("%d", &entradafuncionario);
      printf("Horario de Saida (somente hora inteira): ");
      scanf("%d", &saidafuncionario);

      acumulohorasextras =
          acumularhorasfuncao(entradafuncionario, saidafuncionario);

      printf("\nHoras extras registradas: %dh\n", acumulohorasextras);
      registrarHoras(idPessoa, entradafuncionario, saidafuncionario,
                     acumulohorasextras, 0);
          printf("\nPressione qualquer tecla para voltar...");
          getchar();
          getchar();
    } else if (respostagestor == 2) {
      printf("Horas extras negadas para %s!\n", obterNomePessoa(idPessoa));
      registrarHoras(idPessoa, 0, 0, 0, 1);
          printf("\nPressione qualquer tecla para voltar...");
          getchar();
          getchar();
    } else {
      printf("Opcao invalida! Tente novamente.\n");
          printf("\nPressione qualquer tecla para voltar...");
          getchar();
          getchar();
    }
  } while (respostagestor != 1 && respostagestor != 2);
}

//______FUNÇÕES DE RELATÓRIO________
int contarRegistrosPessoa(int idPessoa) {
  FILE *arquivo;
  char linha[200];
  int contador = 0;
  int idAtual;

  arquivo = fopen("relatorio_horas.txt", "r");
  if (arquivo == NULL)
    return 0;

  while (fgets(linha, sizeof(linha), arquivo) != NULL) {
    if (sscanf(linha, "ID: %d", &idAtual) == 1) {
      if (idAtual == idPessoa) {
        // Procura pela linha de status
        while (fgets(linha, sizeof(linha), arquivo) != NULL) {
          if (strstr(linha, "Status:")) {
            contador++;
            break;
          }
        }
      }
    }
  }

  fclose(arquivo);
  return contador;
}

int somarHorasExtrasPessoa(int idPessoa) {
  FILE *arquivo;
  char linha[200];
  int total = 0, horas;
  int idAtual;
  int dentroDoRegistro = 0;

  arquivo = fopen("relatorio_horas.txt", "r");
  if (arquivo == NULL)
    return 0;

  while (fgets(linha, sizeof(linha), arquivo) != NULL) {
    if (sscanf(linha, "ID: %d", &idAtual) == 1) {
      dentroDoRegistro = (idAtual == idPessoa);
    } else if (dentroDoRegistro &&
               sscanf(linha, "Entrada: %*dh | Saida: %*dh | Horas Extras: %dh",
                      &horas) == 1) {
      total += horas;
      dentroDoRegistro = 0;
    }
  }

  fclose(arquivo);
  return total;
}

void visualizarRelatorioIndividual(int idPessoa) {
  FILE *arquivo;
  char linha[200];
  int totalHoras = somarHorasExtrasPessoa(idPessoa);
  int qtdRegistros = contarRegistrosPessoa(idPessoa);
  int valorareceber = totalHoras * VALOR_HORA_EXTRA;

  system("clear");
  printf("\n===== RELATORIO INDIVIDUAL =====\n");
  printf("Pessoa: %s (ID: %d)\n", obterNomePessoa(idPessoa), idPessoa);
  printf("================================\n\n");

  arquivo = fopen("relatorio_horas.txt", "r");
  if (arquivo == NULL) {
    printf("Nenhum registro encontrado.\n");
        printf("\nPressione qualquer tecla para voltar...");
        getchar();
        getchar();
    return;
  }

  int mostrarRegistro = 0;
  while (fgets(linha, sizeof(linha), arquivo) != NULL) {
    int idAtual;
    if (sscanf(linha, "ID: %d", &idAtual) == 1) {
      mostrarRegistro = (idAtual == idPessoa);
    }

    if (mostrarRegistro) {
      printf("%s", linha);

      // Se chegou no final do registro, para de mostrar
      if (strstr(linha, "-------------------------------------")) {
        mostrarRegistro = 0;
      }
    }
  }
  fclose(arquivo);

  printf("\n================================\n");
  printf("Registros: %d\n", qtdRegistros);
  printf("Horas extras acumuladas: %d\n", totalHoras);
  printf("Valor acumulado: R$%d\n", valorareceber);
  printf("================================\n");

  printf("\nPressione qualquer tecla para voltar...");
  getchar();
  getchar();
}

void visualizarRelatorioGeral() {
  FILE *arquivo;
  char linha[200];
  int opcaoRelatorio;

  arquivo = fopen("relatorio_horas.txt", "r");
  if (arquivo == NULL) {
    printf("\nNenhum registro encontrado.\n");
    printf("\nPressione qualquer tecla para voltar...");
    getchar();
    getchar();
    return;
  }

  system("clear");
  printf("\n===== RELATORIO GERAL DE HORAS EXTRAS =====\n\n");
  while (fgets(linha, sizeof(linha), arquivo) != NULL) {
    printf("%s", linha);
  }
  fclose(arquivo);

  printf("\nPressione qualquer tecla para voltar...");
  getchar();
  getchar();
}

void fecharHorasExtras() {
  system("clear");
  printf("\n====== FECHAMENTO DE HORAS EXTRAS =======\n\n");

  if (totalPessoas == 0) {
    printf("Nenhuma pessoa cadastrada.\n");
    printf("\nPressione qualquer tecla para voltar...");
    getchar();
    getchar();
    return;
  }

  int totalGeralHoras = 0;
  int valorTotalGeral = 0;

  for (int i = 0; i < totalPessoas; i++) {
    int horasPessoa = somarHorasExtrasPessoa(pessoas[i].id);
    int valorPessoa = horasPessoa * VALOR_HORA_EXTRA;

    printf("Pessoa: %s\n", pessoas[i].nome);
    printf("Horas extras: %d\n", horasPessoa);
    printf("Valor a receber: R$%d\n", valorPessoa);
    printf("----------------------------------------\n");

    totalGeralHoras += horasPessoa;
    valorTotalGeral += valorPessoa;
  }

  printf("\nTOTAL GERAL:\n");
  printf("Horas extras: %d\n", totalGeralHoras);
  printf("Valor total: R$%d\n", valorTotalGeral);
  printf("\n=========================================\n");

  // Limpar arquivo de horas extras
  FILE *arquivo = fopen("relatorio_horas.txt", "w");
  if (arquivo != NULL)
    fclose(arquivo);

  // Limpar pessoas cadastradas
  FILE *arquivoPessoas = fopen("pessoas.txt", "w");
  if (arquivoPessoas != NULL)
    fclose(arquivoPessoas);

  // Zerar lista de pessoas na memória
  totalPessoas = 0;
  printf("\nPressione qualquer tecla para voltar...");
  getchar();
  getchar();
}


//______FUNÇÃO AUXILIAR________
void limparBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

//______FUNÇÃO PRINCIPAL________
int main() {
  int resposta;
  carregarPessoas();

  do {
    system("clear");
    printf("<===== SISTEMA DE HORAS EXTRAS ====>\n");
    printf("(1) Cadastrar pessoa\n");
    printf("(2) Listar pessoas\n");
    printf("(3) Solicitar hora extra\n");
    printf("(4) Relatorio individual\n");
    printf("(5) Relatorio geral\n");
    printf("(6) Fechar Horas Totais\n");
    printf("(7) Sair\n-> ");
    scanf("%d", &resposta);

    switch (resposta) {
    case 1:
      cadastrarPessoa();
      break;

    case 2:
      listarPessoas();
      break;

    case 3:
      solicitarHorasExtra();
      break;

    case 4: {
      int idPessoa;
      system("clear");
      if (totalPessoas == 0) {
        printf("Nenhuma pessoa cadastrada.\n");
        printf("\nPressione qualquer tecla para voltar...");
        getchar();
        getchar();
        break;
      }
      printf("=== RELATORIO INDIVIDUAL ===\n");
      listarPessoas();
      printf("Digite o ID da pessoa: ");
      scanf("%d", &idPessoa);
      if (pessoaExiste(idPessoa)) {
        visualizarRelatorioIndividual(idPessoa);
      } else {
        printf("ID nao encontrado!\n");
        printf("\nPressione qualquer tecla para voltar...");
        getchar();
        getchar();
      }
    } break;

    case 5:
      visualizarRelatorioGeral();
      break;

    case 6:
      fecharHorasExtras();
      break;

    case 7:
      printf("Programa finalizado.\n");
      break;

    default:
      printf("Escolha uma das opcoes.\n");
      printf("\nPressione qualquer tecla para voltar...");
      getchar();
      getchar();
      break;
    }

  } while (resposta != 7);

  return 0;
}
