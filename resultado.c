#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUNOS 100
#define MAX_NOTAS 10
#define MAX_NOME 50
#define ARQUIVO_ENTRADA "DadosEntrada.csv"
#define ARQUIVO_SAIDA "SituacaoFinal.csv"


// estrutura de dados Aluno
typedef struct {
    char nome[MAX_NOME];
    float notas[MAX_NOTAS];
    int num_notas;
    float media;
    char situacao[20];
} Aluno;


// Calcular a média e saber se o aluno foi aprovado ou reprovado.
void media(Aluno *aluno) { 
    float soma = 0;
    for (int i = 0; i < aluno->num_notas; i++) {
        soma += aluno->notas[i];
    }
    aluno->media = soma / aluno->num_notas;
    if (aluno->media >= 7.0)
        strcpy(aluno->situacao, "APROVADO");
    else
        strcpy(aluno->situacao, "REPROVADO");
}


 // Função para ler todos os dados dos alunos do arquivo de entrada
void AqrEntrada(Aluno alunos[], int *num_alunos) {
    FILE *arquivo = fopen(ARQUIVO_ENTRADA, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        exit(1);
    }

// ler dados de cada aluno
    *num_alunos = 0; 
    while (fscanf(arquivo, "%[^,],%*[^,],%*[^,],", alunos[*num_alunos].nome) != EOF) {
        alunos[*num_alunos].num_notas = 0;
        float nota;
        while (fscanf(arquivo, "%f,", &nota) == 1) {
            alunos[*num_alunos].notas[alunos[*num_alunos].num_notas++] = nota;
        }
// calcular a media e verificar se foi aprovado ou reprovado
        media(&alunos[*num_alunos]);
        (*num_alunos)++;
    }
    fclose(arquivo);
}
 // salvar os resultados do arquivo de saida
void AqrSaida(Aluno alunos[], int num_alunos) {
    FILE *arquivo = fopen(ARQUIVO_SAIDA, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        exit(1);
    }
// listar os dados de cada aluno no arquivo de saida
    for (int i = 0; i < num_alunos; i++) { 
        fprintf(arquivo, "%s, %.2f, %s\n", alunos[i].nome, alunos[i].media, alunos[i].situacao);
    }
    fclose(arquivo);
}

int main() {
    Aluno alunos[MAX_ALUNOS];
    int num_alunos;

    AqrEntrada(alunos, &num_alunos); //ler os dados de arquivo de entrada
    AqrSaida(alunos, num_alunos); //salvar os dados do arquivo de saida

    printf("Arquivo gerado com sucesso: %s\n", ARQUIVO_SAIDA);

    return 0;
}
