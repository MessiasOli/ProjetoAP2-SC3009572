#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define Q_ALUNOS 50
#define N_CHAR 40
#define EMPTY "empty"
#define NOT_FOUND "notfound"

typedef struct {
    char id[N_CHAR];
    float provaPratic;
    float projeto;
    float listaExercicio;
}Notas;

typedef struct {
    char prontuario[N_CHAR];
    char nome[N_CHAR];
    char dataNasc[N_CHAR];
    char eMail[N_CHAR];
}Aluno;

int solicitarOpcao(){
    char opc[5] = "-1";

    printf("\n");
    printf("Sua escolha: ");
    scanf("%s", opc);
    fflush(stdin);
    printf("\n");

    int result = atoi(opc);
    return result;
}

void EntradaEscrita(char *string)
{
    fgets(string, N_CHAR, stdin);
    string[strcspn(string, "\n")] = 0;
	fflush(stdin);
}

void inicializaListaAluno(Aluno *lista) {
	int i;
	for (i = 0; i < Q_ALUNOS; i++) {
		strcpy(lista[i].prontuario,"");
		strcpy(lista[i].nome,"");
		strcpy(lista[i].dataNasc,"");
		strcpy(lista[i].eMail,"");
	}
}

void inicializaListaNotas (Notas *lista)
{
    int i;
	for (i = 0; i < Q_ALUNOS; i++) {
		strcpy(lista[i].id, "");
        lista[i].provaPratic = 0;
        lista[i].projeto = 0;
        lista[i].listaExercicio = 0;
	}
}

void insereAluno(Aluno *lista) {
	int i;
	char prontuario[N_CHAR];
    char nome[N_CHAR];
    char dataNasc[20];
    char eMail[N_CHAR];

    printf("Digite o prontuário: ");
	EntradaEscrita(prontuario);

	for (i = 0; i < Q_ALUNOS; i++) {

		if (strcmp(lista[i].prontuario, prontuario) == 0) {
			printf("Prontuário já cadastrada. Voltando para menu\n\n");
			break;
		}

		if (strcmp(lista[i].prontuario, "") == 0) {
			printf("Aluno sera inserido na posicao %d.\n\n", i);

			strcpy(lista[i].prontuario, prontuario);

            printf("Digite o nome do aluno: ");
            EntradaEscrita(nome);

            strcpy(lista[i].nome, nome);

            printf("Digite a data de nascimento: ");
            EntradaEscrita(dataNasc);

            strcpy(lista[i].dataNasc, dataNasc);

            printf("Digite o email: ");
            EntradaEscrita(eMail);

            strcpy(lista[i].eMail, eMail);

			printf("Aluno cadastrado com sucesso!\n\n");

			break;
		}
	}

	if (i == Q_ALUNOS) printf("Lista cheia!\n");
}

void ImprimeStatusRetornoAluno(Aluno a)
{
    if (strcmp(a.prontuario, EMPTY) == 0) {
        printf("Não há alunos cadastrados ainda...\n\n");
        return;
    }

    if (strcmp(a.prontuario, NOT_FOUND) == 0) {
        printf("Aluno não encontrado!\n\n");
        return;
    }

    if(strcmp(a.prontuario, "") != 0)
    {
        printf("Aluno encontrado!\n\n");
        return;
    }
}

void imprimirAluno(Aluno a)
{
    printf("Prontuário: %s\n", a.prontuario);
    printf("Nome: %s\n", a.nome);
    printf("Aniversário: %s\n", a.dataNasc);
    printf("E-mail: %s\n", a.eMail);
    printf("--------------------------------------\n");
}

void listarAlunos(Aluno *lista)
{
	int i;

	for (i = 0; i < Q_ALUNOS; i++) {
        if (strcmp(lista[i].prontuario,"") == 0 && i == 0) {
            printf("Não há alunos ainda...\n");
			break;
		}
		if (strcmp(lista[i].prontuario,"") == 0) {
			break;
		}
        imprimirAluno(lista[i]);
	}

	printf("\n");
}

Aluno PegarAluno(Aluno *lista) {
	int i;
	char prontuario[N_CHAR];
	Aluno alunoEncontrado;
	strcpy(alunoEncontrado.prontuario, "");

    printf("Digite o prontuário do aluno: ");
    EntradaEscrita(prontuario);

	for (i = 0; i < Q_ALUNOS; i++) {
        if (strcmp(lista[i].prontuario,"") == 0 && i == 0) {
            strcpy(alunoEncontrado.prontuario, EMPTY);
			break;
		}

		if (strcmp(lista[i].prontuario,"") == 0) {
            strcpy(alunoEncontrado.prontuario, NOT_FOUND);
			break;
		}

		if(strcmp(lista[i].prontuario, prontuario) == 0)
        {
            alunoEncontrado = lista[i];
            break;
		}
	}
	return alunoEncontrado;
}

int PegarIndiceAlunoPorProntuario(Aluno a, Aluno *lista )
{
    int i;
    for (i = 0; i < Q_ALUNOS; i++) {
        if(strcmp(lista[i].prontuario, a.prontuario) == 0)
            return i;
    }
    return i;
}

int PegarIndiceNotaPorProntuario(Aluno a, Notas *listaNotas)
{
    int i;
    for (i = 0; i < Q_ALUNOS; i++) {
        if(strcmp(listaNotas[i].id, a.prontuario) == 0)
            return i;
    }
    return i;
}

int PegarProximoIndiceNota(Notas *listaNotas)
{
    int i;
    for (i = 0; i < Q_ALUNOS; i++) {
        if(strcmp(listaNotas[i].id, "") == 0)
            break;
    }
    return i;
}

void MostrarNotas(Notas n)
{
    printf("Notas:\n");
    printf("Lista de Exercícios: %.2f\n", n.listaExercicio);
    printf("Projeto: %.2f\n", n.projeto);
    printf("Prova Prática: %.2f\n", n.provaPratic);
    printf("--------------------------------------\n\n");
}

void atribuirNotas(Aluno a, Notas *listaNotas)
{
    int opc = 0;
    int i;
    Notas nota;
    bool running = true;

    strcpy(nota.id, "");
    nota.listaExercicio = 0;
    nota.projeto = 0;
    nota.provaPratic = 0;

    i = PegarIndiceNotaPorProntuario(a, listaNotas);
    if(i == Q_ALUNOS)
        i = PegarProximoIndiceNota(listaNotas);
    else
        nota = listaNotas[i];

    printf("Index encontrado para a o aluno %s nota:%d \n\n", a.nome,i);

    do {
        printf("Opção Notas: \n");
        printf("1- Mostrar Notas: \n");
        printf("2- Alterar Notas: \n");
        printf("3- Sair e Salvar\n");

        opc = solicitarOpcao();

        printf("\n");

        if(opc == 1)
        {
            printf("Aluno: %s\n", a.nome);
            MostrarNotas(nota);
        }
        else if(opc == 2)
        {
            printf("Digite a nota dos Exercícios: ");
            scanf("%f", &nota.listaExercicio);
            fflush(stdin);

            printf("Digite a nota do Projeto: ");
            scanf("%f", &nota.projeto);
            fflush(stdin);

            printf("Digite a nota da Prova Prática: ");
            scanf("%f", &nota.provaPratic);
            fflush(stdin);

            printf("\n");
        }
        else if(opc == 3)
        {
            strcpy(nota.id, a.prontuario);
            listaNotas[i] = nota;
            running = false;
        }
        else
        {
            printf("Erro: Opção Inválida, insira um número válido.\n\n");
        }
    }while(running);
}

void alterarUmAluno(Aluno a, Aluno *lista, Notas *notas)
{
    int i;
    int opc = -1;

    i = PegarIndiceAlunoPorProntuario(a, lista);

    printf("Editar Aluno: \n");
    printf("1- Alterar prontuário: \n");
    printf("2- Alterar nome: \n");
    printf("3- Alterar data de nascimento: \n");
    printf("4- Alterar E-mail: \n");
    printf("5- Atribuir notas: \n");
    printf("6- Sair: \n");

    opc = solicitarOpcao();

    printf("\n");

    if(opc == 1)
    {
        char prontuario[N_CHAR];
        printf("Digite o prontuário: ");
        EntradaEscrita(prontuario);
        strcpy(a.prontuario, prontuario);
    }
    else if(opc == 2)
    {
        char nome[N_CHAR];
        printf("Digite um nome: ");
        EntradaEscrita(nome);
        strcpy(a.nome, nome);
    }
    else if(opc == 3)
    {
        char dataNasc[N_CHAR];
        printf("Digite a data de nascimento: ");
        EntradaEscrita(dataNasc);
        strcpy(a.dataNasc, dataNasc);
    }
    else if(opc == 4)
    {
        char eMail[N_CHAR];
        printf("Digite um novo e-mail: ");
        EntradaEscrita(eMail);
        strcpy(a.eMail, eMail);
    }
    else if(opc == 5)
    {
        atribuirNotas(a, notas);
    }
    else if(opc == 6)
    {
        printf("Saindo e salvando...\n\n");
    }
    else
    {
        printf("Erro: Opção Inválida, insira um número válido.\n\n");
    }

    lista[i] = a;
}

void ExcluirAluno (Aluno a, Aluno *lista, Notas *notas)
{
    int i;
    i = PegarIndiceAlunoPorProntuario(a, lista);
    int k;
    k = PegarIndiceNotaPorProntuario(a, notas);

    Aluno AlunoEmBranco;
    strcpy(AlunoEmBranco.prontuario, "");
    strcpy(AlunoEmBranco.nome, "");
    strcpy(AlunoEmBranco.dataNasc, "");
    strcpy(AlunoEmBranco.eMail, "");

    Notas NotasEmBranco;
    strcpy(NotasEmBranco.id, "");
    NotasEmBranco.listaExercicio = 0;
    NotasEmBranco.projeto = 0;
    NotasEmBranco.provaPratic = 0;

    int j;
    for (j = i + 1; j < Q_ALUNOS; j++) {
        if(strcmp(lista[j].prontuario, "") == 0)
        {
            printf("Aluno excluído com sucesso!\n\n");
            lista[i] = AlunoEmBranco;
            break;
        }
        else
        {
            lista[i] = lista[j];
            i++;
        }
    }

    if(k == Q_ALUNOS)
        return;

    for (j = i + 1; j < Q_ALUNOS; j++) {
        if(strcmp(notas[j].id, "") == 0)
        {
            printf("Notas excluído com sucesso!\n\n");
            notas[i] = NotasEmBranco;
            break;
        }
        else
        {
            notas[i] = notas[j];
            i++;
        }
    }
}

bool checkAlunoOk(Aluno a)
{
    return !(strcmp(a.prontuario, NOT_FOUND) == 0 || strcmp(a.prontuario, EMPTY) == 0);
}

int PegarProximoIndiceAluno(Aluno *lista){
    int i;
    for (i = 0; i < Q_ALUNOS; i++) {
        if(strcmp(lista[i].prontuario, "") == 0)
            return i;
    }
    return i;
}

void MostrarMenuAluno(Aluno *lista, Aluno *listaExcluidos, Notas *listaNotas) {
    int opc = 0;
    bool running = true;

    do {
        printf("Opção Aluno: \n");
        printf("1- Listar todos os alunos: \n");
        printf("2- Listar um aluno: \n");
        printf("3- Cadastrar aluno: \n");
        printf("4- Alterar aluno: \n");
        printf("5- Excluir aluno \n");
        printf("6- Voltar\n");

        opc = solicitarOpcao();

        printf("\n");

        if(opc == 1)
        {
            listarAlunos(lista);
        }
        else if(opc == 2)
        {
            Aluno a = PegarAluno(lista);
            ImprimeStatusRetornoAluno(a);
            if(checkAlunoOk(a))
                imprimirAluno(a);
        }
        else if(opc == 3)
        {
            insereAluno(lista);
        }
        else if(opc == 4)
        {
            Aluno a = PegarAluno(lista);
            ImprimeStatusRetornoAluno(a);
            if(checkAlunoOk(a))
                alterarUmAluno(a, lista, listaNotas);
        }
        else if(opc == 5)
        {
            Aluno a = PegarAluno(lista);
            if(checkAlunoOk(a)){
                ExcluirAluno(a, lista, listaNotas);
                int i = PegarProximoIndiceAluno(listaExcluidos);
                listaExcluidos[i] = a;
            }
        }
        else if(opc == 6)
        {
            running = false;
        }
        else
        {
            printf("Erro: Opção Inválida, insira um número válido.\n\n");
        }
    }while(running);
}

float CalcularMediaNota(Notas n)
{
    return (n.listaExercicio + n.projeto + n.provaPratic) / 3;
}

void MostrarAlunosAprovados(Aluno *listaAlunos, Notas *listaNotas)
{
    int i;
    bool AoMenosUmAprovado = false;

    for (i = 0; i < Q_ALUNOS; i++) {
        if(strcmp(listaAlunos[i].prontuario, "") == 0 && i == 0){
            printf("Não há alunos matriculados.\n\n");
            break;
        }


        if(strcmp(listaAlunos[i].prontuario, "") == 0 && AoMenosUmAprovado){
            printf("------------------------------------\n\n");
            break;
        }

        if(strcmp(listaAlunos[i].prontuario, "") == 0){
            printf("Não há alunos aprovados.\n\n");
            break;
        }

        int indiceNota = PegarIndiceNotaPorProntuario(listaAlunos[i], listaNotas);

        if(indiceNota != Q_ALUNOS){
            if(i == 0)
                printf("STATUS\t\tALUNO\t\t\t\tNOTA\n");

            float notaFinal = CalcularMediaNota(listaNotas[indiceNota]);
            if(notaFinal >= 7){
                printf("APROVADO!\tAluno: %s\t\tNota: %.2f\n", listaAlunos[i].nome, notaFinal);
                AoMenosUmAprovado = true;
            }
        }
    }
}

void MostrarAlunosReprovados(Aluno *listaAlunos, Notas *listaNotas)
{
    int i;
    bool AoMenosUmAprovado = false;

    for (i = 0; i < Q_ALUNOS; i++) {
        if(strcmp(listaAlunos[i].prontuario, "") == 0 && i == 0){
            printf("Não há alunos matriculados.\n\n");
            break;
        }


        if(strcmp(listaAlunos[i].prontuario, "") == 0 && AoMenosUmAprovado){
            printf("------------------------------------\n\n");
            break;
        }

        if(strcmp(listaAlunos[i].prontuario, "") == 0){
            printf("Não há alunos reprovados.\n\n");
            break;
        }

        int indiceNota = PegarIndiceNotaPorProntuario(listaAlunos[i], listaNotas);

        if(indiceNota != Q_ALUNOS){
            if(i == 0)
                printf("STATUS\t\tALUNO\t\tNOTA\n");

            float notaFinal = CalcularMediaNota(listaNotas[indiceNota]);
            if(notaFinal < 7){
                printf("REPROVADO\tAluno: %s\tNota: %.2f\n", listaAlunos[i].nome, notaFinal);
                AoMenosUmAprovado = true;
            }
        }
    }
}

void MostrarMenuRelatorio(Aluno* lista, Aluno *listaAlunosExcluidos, Notas *listaNotas) {
    int opc = 0;
    bool running = true;

    do {
        printf("Opção Relatórios: \n");
        printf("1- Mostrar todos os alunos aprovados na disciplina AP2: \n");
        printf("2- Mostrar todos os alunos reprovados: \n");
        printf("3- Mostrar alunos excluídos: \n");
        printf("4- Voltar: \n");

        opc = solicitarOpcao();

        printf("\n");

        if(opc == 1)
        {
            MostrarAlunosAprovados(lista, listaNotas);
        }
        else if(opc == 2)
        {
            MostrarAlunosReprovados(lista, listaNotas);
        }
        else if(opc == 3)
        {
            listarAlunos(listaAlunosExcluidos);
        }
        else if(opc == 4)
        {
            running = false;
        }
        else
        {
            printf("Erro: Opção Inválida, insira um número válido.\n\n");
        }
    }while(running);
}

void CarregarAluno(FILE *coletor, Aluno *lista)
{
    char c;
    int i = 0;
    int ichar = 0;
    int iAlunoProperty = 0;
    char buffer[N_CHAR];
    Aluno a;
    do{
        c = fgetc(coletor);

        if(c != '|' && c != '\n' && c != '\0')
            buffer[ichar++] = c;

        if(c == '|'){
            buffer[ichar] = '\0';

            if(iAlunoProperty == 0 )
            {
                strcpy(a.prontuario, buffer);
            }
            else if(iAlunoProperty == 1)
            {
                strcpy(a.nome, buffer);
            }
            else if(iAlunoProperty == 2)
            {
                strcpy(a.dataNasc, buffer);
            }
            else if(iAlunoProperty == 3)
            {
                strcpy(a.eMail, buffer);
                lista[i] = a;
                i++;
                iAlunoProperty = -1;
            }

            if(c == '|'){
                strcpy(buffer, "");
                ichar = 0;
            }

            iAlunoProperty++;
        }

    }while (c != EOF);
}

void CarregarNotas(FILE *coletor, Notas *lista)
{
    char c;
    int i = 0;
    int ichar = 0;
    int iAlunoProperty = 0;
    char buffer[N_CHAR];
    Notas n;
    do{
        c = fgetc(coletor);

        if(c != '|' && c != '\n' && c != '\0')
            buffer[ichar++] = c;

        if(c == '|'){
            buffer[ichar] = '\0';

            if(iAlunoProperty == 0 )
            {
                strcpy(n.id, buffer);
            }
            else if(iAlunoProperty == 1)
            {
                n.listaExercicio =  atoi(buffer);
            }
            else if(iAlunoProperty == 2)
            {
                n.projeto =  atoi(buffer);
            }
            else if(iAlunoProperty == 3)
            {
                n.provaPratic =  atoi(buffer);
                lista[i] = n;
                i++;
                iAlunoProperty = -1;
            }

            if(c == '|'){
                strcpy(buffer, "");
                ichar = 0;
            }

            iAlunoProperty++;
        }

    }while (c != EOF);
}

void LerDadosDosArquivos(Aluno *listaAlunos, Aluno *listaAlunosExcluidos, Notas *listaNotas)
{
    FILE *lerAlunos = fopen("DadosAlunos.txt","r");
    FILE *lerAlunosExcluidos = fopen("DadosAlunosExcluidos.txt","r");
    FILE *lerNotas = fopen("DadosNotas.txt","r");

    printf("Carregando dados do aluno...\n");
    if (lerAlunos == NULL && lerAlunosExcluidos == NULL){
        printf("Falha ao ler o arquivos de recuperação!\n\n");
        return;
    }

    CarregarAluno(lerAlunos, listaAlunos);
    CarregarAluno(lerAlunosExcluidos, listaAlunosExcluidos);
    CarregarNotas(lerNotas, listaNotas);

    printf("Dados carregados!\n\n");

    fclose(lerAlunos);
    fclose(lerAlunosExcluidos);
    fclose(lerNotas);
}

void SalvaDadosNoArquivo(Aluno *listaAlunos, Aluno *listaExcluidos, Notas *listaNotas) {
	int i;
	FILE *registrador = fopen("RegistrosAlunos.txt","a");
	FILE *salvaAlunos = fopen("DadosAlunos.txt","w");
	FILE *salvaAlunosExcluidos = fopen("DadosAlunosExcluidos.txt","w");
	FILE *salvaNotas = fopen("DadosNotas.txt","w");

    struct tm *data_hora_atual;
	time_t segundos;
	time(&segundos);
	data_hora_atual = localtime(&segundos);

	fprintf(registrador, "INICIO\n************ Registro %d/%d/%d %d:%d:%d ************\n",
        data_hora_atual->tm_mday,
        data_hora_atual->tm_mon+1,
        data_hora_atual->tm_year+1900,
        data_hora_atual->tm_hour,
        data_hora_atual->tm_min,
        data_hora_atual->tm_sec);

	fflush(registrador);

	for (i = 0; i < Q_ALUNOS; i++) {

		if (strcmp(listaAlunos[i].prontuario,"") == 0) {
			break;
		}

		fprintf(registrador, "\nALUNO %d: \n", i+1);
		fprintf(registrador, "\tProntuário: %s", listaAlunos[i].prontuario);
		fprintf(registrador, "\tNome: %s\n", listaAlunos[i].nome);
		fprintf(registrador, "\tData Nascimento: %s\n", listaAlunos[i].dataNasc);
		fprintf(registrador, "\tE-Mail: %s\n\n", listaAlunos[i].eMail);

		fprintf(salvaAlunos, "%s|", listaAlunos[i].prontuario);
		fprintf(salvaAlunos, "%s|", listaAlunos[i].nome);
		fprintf(salvaAlunos, "%s|", listaAlunos[i].dataNasc);
		fprintf(salvaAlunos, "%s|\n", listaAlunos[i].eMail);

		int j = PegarIndiceNotaPorProntuario(listaAlunos[i], listaNotas);

		fprintf(registrador, "NOTAS:\n");
		fprintf(registrador, "\tExercícios: %.2f\n", listaNotas[j].listaExercicio);
		fprintf(registrador, "\tProjeto: %.2f\n", listaNotas[j].projeto);
		fprintf(registrador, "\tProva Prática: %.2f\n\n", listaNotas[j].provaPratic);

		fprintf(salvaNotas, "%s|", listaNotas[j].id);
		fprintf(salvaNotas, "%f|", listaNotas[j].listaExercicio);
		fprintf(salvaNotas, "%f|", listaNotas[j].projeto);
		fprintf(salvaNotas, "%f|\n", listaNotas[j].provaPratic);

		float media = CalcularMediaNota(listaNotas[j]);
		fprintf(registrador, "SITUAÇÃO:\n");
		fprintf(registrador, "\tMédia: %.2f\n", media);

		if(media >= 7)
            fprintf(registrador, "\tAPROVADO\n");
        else
            fprintf(registrador, "\tREPROVADO\n");

		fprintf(registrador, "\n------------------------------------\n");

		fflush(registrador);
		fflush(salvaAlunos);
		fflush(salvaNotas);
	}

    for (i = 0; i < Q_ALUNOS; i++) {

		if (strcmp(listaExcluidos[i].prontuario,"") == 0) {
			break;
		}

		fprintf(registrador, "\nALUNO CANCELADOS %d: \n", i-1);
		fprintf(registrador, "\tProntuário: %s", listaExcluidos[i].prontuario);
		fprintf(registrador, "\tNome: %s\n", listaExcluidos[i].nome);
		fprintf(registrador, "\tData Nascimento: %s\n", listaExcluidos[i].dataNasc);
		fprintf(registrador, "\tE-Mail: %s\n\n", listaExcluidos[i].eMail);

		fprintf(salvaAlunosExcluidos, "%s|", listaExcluidos[i].prontuario);
		fprintf(salvaAlunosExcluidos, "%s|", listaExcluidos[i].nome);
		fprintf(salvaAlunosExcluidos, "%s|", listaExcluidos[i].dataNasc);
		fprintf(salvaAlunosExcluidos, "%s|\n", listaExcluidos[i].eMail);

		fprintf(registrador, "\n------------------------------------\n");

		fflush(registrador);
		fflush(salvaAlunosExcluidos);
	}

    fprintf(registrador, "********************************\nFIM\n\n");
    fflush(registrador);

	fclose(registrador);
	fclose(salvaAlunos);
	fclose(salvaNotas);
	fclose(salvaAlunosExcluidos);
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int opc = 0;
    bool running = true;

    Aluno *listaAlunos;
    Aluno *listaAlunosExcluidos;
    Notas *listaNotas;

    listaAlunos = malloc (Q_ALUNOS * sizeof(Aluno));
    listaAlunosExcluidos = malloc (Q_ALUNOS * sizeof(Aluno));
    listaNotas = malloc (Q_ALUNOS * sizeof(Notas));

    inicializaListaAluno(listaAlunos);
    inicializaListaAluno(listaAlunosExcluidos);
    inicializaListaNotas(listaNotas);

    printf("PROJETO AP2\n\n");
    LerDadosDosArquivos(listaAlunos, listaAlunosExcluidos, listaNotas);

    do
    {
        printf("Escolha uma opção: \n");
        printf("1- Alunos \n");
        printf("2- Relatórios \n");
        printf("3- Sair \n");

        opc = solicitarOpcao();

        printf("\n");

        if(opc == 1)
        {
            MostrarMenuAluno(listaAlunos, listaAlunosExcluidos, listaNotas);
        }
        else if(opc == 2)
        {
            MostrarMenuRelatorio(listaAlunos, listaAlunosExcluidos, listaNotas);
        }
        else if(opc == 3)
        {
            running = false;
        }
        else
        {
            printf("Erro: Opção Inválida, insira um número válido.\n\n");
        }

    }while(running);

    SalvaDadosNoArquivo(listaAlunos, listaAlunosExcluidos, listaNotas);

    free(listaAlunos);
    free(listaAlunosExcluidos);
    free(listaNotas);

    return 0;
}
