#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int cod;
	char nome[100];
	float preco;
	int estoque;
} Produto;

Produto * abrirArquivo(int *numeroProdutos, int *capacidade);
void cadastrarProduto(Produto *lista, int *numeroProdutos, int *capacidade);
void exibirProdutos(Produto *lista, int numeroProdutos);
void apagarProduto(Produto *lista, int *numeroProdutos);
void salvar(Produto *lista, int numeroProdutos);
void consultarProduto(Produto *lista, int numeroProdutos);
void editarProduto(Produto *lista, int numeroProdutos);

int main(){

	Produto *lista;
	int capacidade, numeroProdutos, opcao;

	lista = abrirArquivo(&numeroProdutos, &capacidade);

	do{

		printf("1. CADASTRAR PRODUTO\n");
		printf("2. EXIBIR PRODUTOS\n");
		printf("3. APAGAR PRODUTO\n");
		printf("4. CONSULTAR PRODUTO\n");
		printf("5. EDITAR PRODUTO\n");
		printf("6. SAIR\n\n");
		scanf("%i", &opcao);

		switch(opcao){
			case 1:
				cadastrarProduto(lista, &numeroProdutos, &capacidade);
				break;
			case 2:
				exibirProdutos(lista, numeroProdutos);
				break;
			case 3:
				apagarProduto(lista, &numeroProdutos);
				break;
			case 4:
				consultarProduto(lista, numeroProdutos);
				break;
			case 5:
				editarProduto(lista, numeroProdutos);
				break;
		}

	}while(opcao != 6);

	salvar(lista, numeroProdutos);

	free(lista);

	return 0;
}

Produto * abrirArquivo(int *numeroProdutos, int *capacidade){

	Produto *lista;

	FILE *file = fopen("lista.txt", "r");

	if(file == NULL){
		*numeroProdutos = 0;
		*capacidade = 10;

		lista = (Produto *) malloc(sizeof(Produto) * (*capacidade));
	}else{
		fread(numeroProdutos, sizeof(int), 1, file);

		*capacidade = (*numeroProdutos) * 2;

		lista = (Produto *) malloc(sizeof(Produto) * (*capacidade));

		fread(lista, sizeof(Produto), *numeroProdutos, file);

		fclose(file);
	}

	return lista;

}

void cadastrarProduto(Produto *lista, int *numeroProdutos, int *capacidade){

	if(*numeroProdutos == *capacidade){
		*capacidade = *capacidade * 2;
		lista = (Produto*)realloc(lista, sizeof(Produto)*(*capacidade));
	}

	__fpurge(stdin);

	int cod = *numeroProdutos;
	lista[*numeroProdutos].cod = cod;

	printf("Nome: ");
	gets(lista[*numeroProdutos].nome);

	printf("Preco: ");
	scanf("%f", &lista[*numeroProdutos].preco);

	printf("Estoque: ");
	scanf("%i", &lista[*numeroProdutos].estoque);

	(*numeroProdutos)++;
}

void exibirProdutos(Produto *lista, int numeroProdutos){

	int i;

	for(i=0; i<numeroProdutos;i++){
		printf("\n\n--- PRODUTO %i ------ \n", i+1);
		printf(" CODIGO: %i\n", lista[i].cod);
		printf(" NOME:	%s\n", lista[i].nome);
		printf(" PRECO:	%.2f\n", lista[i].preco);
		printf(" ESTOQUE: %i\n", lista[i].estoque);
		printf("-------------------- \n\n");
	}

}

void apagarProduto(Produto *lista, int *numeroProdutos){

	char nome[100];
	int i, j;

	__fpurge(stdin);
	printf("Produto a ser removido: ");
	gets(nome);

	for(i=0; i< *numeroProdutos; i++){
		if(strcmp(lista[i].nome, nome)==0){
			for(j=i; j< *numeroProdutos; j++)
				lista[j] = lista[j+1];

			(*numeroProdutos)--;
			i = *numeroProdutos;
		}
	}

}

void salvar(Produto *lista, int numeroProdutos){

	if(numeroProdutos > 0){

		FILE *file = fopen("lista.txt", "w");

		fwrite(&numeroProdutos, sizeof(int), 1, file);

		fwrite(lista, sizeof(Produto), numeroProdutos, file);

		fclose(file);

	}

}

void consultarProduto(Produto *lista, int numeroProdutos){

	char nome[100];
	int i;

	__fpurge(stdin);
	printf("\nProduto a ser pesquisado: ");
	gets(nome);

	for(i=0; i<numeroProdutos; i++){
		if(strcmp(lista[i].nome, nome)==0){
			printf("\n\n--- PRODUTO %i ------ \n", i+1);
			printf(" CODIGO: %i\n", lista[i].cod);
			printf(" NOME:	%s\n", lista[i].nome);
			printf(" PRECO:	%.2f\n", lista[i].preco);
			printf(" ESTOQUE: %i\n", lista[i].estoque);
			printf("-------------------- \n\n");
		}
	}

}

void editarProduto(Produto *lista, int numeroProdutos){

	int i, cod;

	printf("Codigo do produto a ser editado: ");
	scanf("%i", &cod);

	for(i=0; i<numeroProdutos; i++){
		if(lista[i].cod == cod){

			__fpurge(stdin);
			printf("Nome: ");
			gets(lista[i].nome);

			printf("Preco: ");
			scanf("%f", &lista[i].preco);

			printf("Estoque: ");
			scanf("%i", &lista[i].estoque);

		}
	}

}
