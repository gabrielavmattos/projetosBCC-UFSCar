#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct disc {
    char s[10];
    int c;
    int f;
    int ind;
} Disc;


int horario[16][7];
int sumM=0;
int quantM=0;

/*
	Função: defineDia
	Objetivo: numerar os dias da semana para acesso ao vetor.
*/

int defineDia (char *dia)
{
	if (!strcmp(dia, "seg"))
		return 0;
	if (!strcmp(dia, "ter"))
		return 1;
	if (!strcmp(dia, "qua"))
		return 2;
	if (!strcmp(dia, "qui"))
		return 3;
	if (!strcmp(dia, "sex"))
		return 4;
	if (!strcmp(dia, "sab"))
		return 5;
	if (!strcmp(dia, "dom"))
		return 6;
}

/*
	Funcao: horariodisponivel()
	Objetivo: verificar na matriz de horarios se existe algum ocupado mais de uma vez, ou seja, com valor maior que 1. Quando 0 o horario esta livre.

*/
int horariodisponivel ()
{
	int i,j;

	for (i=0; i<16; i++)
		for(j=0; j<7; j++)
			if(horario[i][j]>1)
				return 0;

	return 1;
}

/*
	Funcao: indiceCM()
	Objetivo: testar todas as possibilidades de combinacoes de turmas informadas pelo usuario e encontrar a com maior indice de CM e com maior numero de turmas selecionadas.

*/

void indiceCM (int tam, int i, Disc sol, Disc *vet, int sum, int disc)
{
 	int j;
	int dia_atual;
	int horaI, horaF;

	if(i>=tam)
	{
		if(horariodisponivel() && sumM <= sum)
			if (disc >= quantM)
			{
			    quantM = disc; //salva o maior numero de disciplinas
			    sumM = sum;    //salva o maior numero do somatorio dos indices que passam pelas condicoes
			}
	}
	else
	{
		indiceCM(tam, i+1, sol, vet, sum, disc); //chamada da funcao sem contar uma opcao
		sol = vet[i];
		horaI = sol.c - 8;
		horaF = sol.f - 8;
		dia_atual=defineDia(sol.s);

		for (j=horaI; j<horaF; j++)
			horario[j][dia_atual]++; //soma 1 a cada vez que o horario foi ocupado

		indiceCM(tam, i+1, sol, vet, sum + vet[i].ind, disc+1); //chamada da funcao contando uma opcao

		for (j=horaI; j<horaF; j++)
			horario[j][dia_atual]--; //subtrai 1 para eliminar o horario que nao esta mais ocupado

		sum -= vet[i].ind;	//subtrai o indice do disciplina que nao sera mais escolhida na proxima chamada
	}
}

int main()
{

	Disc *x, sol;
	int j, tam, i;

	for(i=0; i<16; i++)
        	for(j=0; j<7;j++)
            		horario[i][j]=0;

	scanf("%d", &tam);
	x = malloc(tam*sizeof(Disc));

	for (i=0; i<tam; i++)
		scanf ("%s %d %d %d", &x[i].s, &x[i].c, &x[i].f, &x[i].ind);

	indiceCM(tam, 0, sol, x, 0, 0);

	free(x);
	printf ("%d", sumM);

	return (0);
}
