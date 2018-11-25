#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
//PROJETO LOCADORA DE DVD

typedef struct{ long long int cpf;
				int tel;
				char nome[20],endereco[20],depend1[20],depend2[20];
}Cliente; Cliente cliente, clienteNulo;

typedef struct{ int cod;
	char nomef[15], genero[10];
	
}Filme; Filme filme, filmeNulo;

FILE*pcliente;
FILE*pfilme;

void linha(){
	int i;
	for (i=1; i<=60; i++)
	printf("_"); 
}

   
void cabec(){
	system("cls");
	printf("LOCADORA DVD\n");
	linha();
}


void abreArquivo(){
	pcliente = fopen("locadora.bin", "r+b");
	if(pcliente == NULL)
	pcliente = fopen("locadora.bin", "w+b");
}


void abreArquivo1(){
	pfilme = fopen("locadoraf.bin", "r+b");
	if(pfilme == NULL)
	pfilme = fopen("locadoraf.bin", "w+b");
}

void inserir(){
int resp;
do { 
cabec();	
	printf("\n\nCADASTRAR CLIENTE\n\n");
	printf("\nNOME: ");
	fflush(stdin);
		gets(cliente.nome);
	printf("\nCPF: ");
	fflush(stdin);
		scanf("%lld", &cliente.cpf);
	printf("\nTELEFONE: ");
	fflush(stdin);
		scanf("%d",&cliente.tel);
	printf("\nENDERECO: ");
	fflush(stdin);
		gets(cliente.endereco);
	printf("\nDEPENDENTE 01: ");
	fflush(stdin);
		gets(cliente.depend1);
	printf("\nDEPENDENTE 02: ");
	fflush(stdin);
		gets(cliente.depend2);
		fseek(pcliente, 0, SEEK_END);
	fwrite(&cliente, sizeof(Cliente), 1, pcliente);		
	printf("\n\nCLIENTE CADASTRADO COM SUCESSO!\n\n");	
	printf("\n\nCADASTRAR OUTRO CLIENTE? 1-SIM   /  2-NAO\n");
		scanf("%d", &resp);
}while (resp == 1);
}

 
void inserir1(){
int resp;
do { 
cabec();
	printf("\n\nCADASTRAR FILME\n\n");
	printf("\nNOME: ");
	fflush(stdin);
	gets(filme.nomef);
	fflush(stdin);
	printf("\nCODIGO DO FILME:");
	fflush(stdin);
	scanf("%d", &filme.cod);
	printf("\nGENERO: ");
	fflush(stdin);
		gets(filme.genero);
	fseek(pfilme, 0,SEEK_END);
	fwrite(&filme, sizeof(Filme), 1, pfilme);		
	printf("\n\nFILME CADASTRADO COM SUCESSO!\n\n");	
	printf("\n\nCADASTRAR OUTRO FILME? 1-SIM   /  2-NAO\n");
		scanf("%d",&resp);
} while (resp==1);
}


long long int procura(long long int Pcpf){
int p;
p = 0; 
rewind(pcliente);
fread(&cliente, sizeof(Cliente), 1, pcliente);

while(feof(pcliente)==0){ 
if (cliente.cpf==Pcpf)   
return p;
else{
 fread(&cliente, sizeof(Cliente), 1, pcliente);
  p++;
  } 
} 
return -1; 
}


int procura1(int codP){
 int p;
 p = 0; 
rewind(pfilme);
fread(&filme, sizeof(Filme), 1, pfilme); 

while (feof(pfilme)==0){
if (filme.cod==codP)   
return p;
else  { fread(&filme,sizeof(Filme), 1,pfilme);
  p++;
  } 
} 
return -1; }


void mostre(int pos){
fseek(pcliente, pos*sizeof(Cliente), SEEK_SET); 
fread(&cliente, sizeof(Cliente), 1, pcliente); 
printf("\n\n");
printf("\n__________________________________________________________________");
printf("\nNOME                   CPF           TELEFONE        ENDERECO            ");
printf("\n__________________________________________________________________");
printf("\n%-20s   %-11lld   %-13d   %-20s", cliente.nome, cliente.cpf, cliente.tel, cliente.endereco);

}


void mostre1(int pos){
fseek(pfilme, pos*sizeof(Filme), SEEK_SET);
fread(&filme, sizeof(Filme), 1, pfilme);	
printf("\n\n");
printf("\n_____________________________________");
printf("\nCODIGO   NOME              GENERO    ");
printf("\n_____________________________________");
printf("\n%-6d   %-15s   %-10s",filme.cod, filme.nomef, filme.genero);

}


void consultar(){
int resp; long long int cpfP,posicao;
do{ cabec();
printf("\n\nCONSULTAR CLIENTE\n\n\n");
printf("CPF CLIENTE: ");
scanf("%lld", &cpfP);
posicao = procura(cpfP);
if (posicao == -1)   
printf("\n\nCPF NAO CADASTRADO!!! \n\n");
else mostre(posicao);
printf("\n\nDESEJA CONSULTAR OUTRO CPF: (1-sim/0-nao)? ");
fflush(stdin);
scanf("%d", &resp);
 } 
while (resp==1);
}


void consultar1(){
 int resp, posic, Pcod;
do{ cabec();
printf("\n\nCONSULTAR FILME\n\n\n");
printf("CODIGO FILME: ");
	scanf("%d", &Pcod);
posic = procura1(Pcod);
if (posic == -1)   
printf("\n\nCODIGO NAO CADASTRADO!!! \n\n");
else mostre1(posic);
printf("\n\nDESEJA CONSULTAR OUTRO FILME: (1-sim/0-nao)? ");
	scanf("%d", &resp);
} 
while (resp == 1);
}


void listar(){
	system("cls");	
	cabec();
	printf("\n\nLISTAGEM DE CLIENTES\n\n"); 
	printf("\n__________________________________________________________________");
	printf("\nNOME              CPF           TELEFONE        ENDERECO          ");
	printf("\n==================================================================\n");
	rewind(pcliente);
	fread(&cliente, sizeof(Cliente), 1, pcliente);
	while (feof(pcliente) == 0)
{   	if (cliente.cpf != 0)
	printf("\n%-15s   %11lld   %-13d   %-15s\n", cliente.nome, cliente.cpf, cliente.tel, cliente.endereco);
 	fread(&cliente, sizeof(Cliente), 1, pcliente);
	}
	printf("\n__________________________________________________________________");
	printf("\nTECLE ENTER PARA VOLTAR AO MENU...");
	getch();
}


void listar1(){
	system("cls");
	cabec();
	printf("\n\nLISTAGEM DE FILMES\n\n"); 
	printf("\n_____________________________________");
	printf("\nCODIGO   NOME              GENERO    ");
	printf("\n=====================================");
	rewind(pfilme);
	fread(&filme, sizeof(Filme), 1, pfilme);
	while (feof(pfilme) == 0)
{   	if (filme.cod != 0)		
	printf("\n%6d   %-15s   %-10s",filme.cod,filme.nomef,filme.genero);
 	fread(&filme, sizeof(Filme), 1,pfilme);
	}
	printf("\n_____________________________________");
    printf("\nTECLE ENTER PARA VOLTAR AO MENU...");
	getch();
}


void removercli(){
long long int cpfR;
int conf, resp, posicao;
	clienteNulo.cpf = 0;
do{
cabec();	
printf("\n\nEXCLUIR CLIENTE\n\n\n");
printf("CPF: ");
	scanf("%lld", &cpfR);
posicao = procura(cpfR);
if (posicao == -1)
	printf("\nCLIENTE NAO ENCONTRADO!!\a");
else  { 
mostre(posicao);
printf("\n\nDESEJA REMOVER CLIENTE (1-sim/0-nao)? ");
scanf("%d", &conf);
if(conf==1)
{ fseek(pcliente, posicao*sizeof(Cliente), SEEK_SET);
fwrite(&clienteNulo, sizeof(Cliente), 1, pcliente);
printf("\n\nCLIENTE REMOVIDO COM SUSSESSO!\n");
}
else
printf("\nCANCELAR EXCLUSAO!!!");
}
printf("\n\n\nDeseja remover outro (1-sim/0-nao)? ");
scanf("%d", &resp);
}
while (resp==1);
}


void removerfilme(){
int codR; int conf, resp, posicao;
filmeNulo.cod = 0;
do{
cabec();
printf("\n\nEXCLUIR FILME\n\n\n");
printf("CODIGO: ");
	scanf("%d", &codR);
posicao=procura1(codR);
if(posicao == -1)
	printf("\nFILME NAO ENCONTRADO!!\a");
else  { 
mostre(posicao);
printf("\n\nDESEJA REMOVER FILME (1-sim/0-nao)? ");
scanf("%d", &conf);
if (conf == 1)
{ fseek(pfilme, posicao*sizeof(Filme), SEEK_SET);
fwrite(&filmeNulo, sizeof(Filme), 1, pfilme);
printf("\n\nFILME REMOVIDO COM SUSSESSO!\n");
}
else
printf("\nCANCELAR EXCLUSAO!!!");
}
printf("\n\n\nDeseja remover outro (1-sim/0-nao)? ");
scanf("%d", &resp);
}
while (resp == 1);
}



void alterar() { long long int cpfalt, posicao; int conf, resp;
do { 
cabec();
printf("\n\nALTERAR DADOS DO CLIENTE\n\n");
printf("BUSCAR POR CPF: ");
	scanf("%d", &cpfalt);
posicao = procura(cpfalt);
if (posicao == -1)   
printf("\nAluno,nao encontrado!!\n");
else  { 
mostre(posicao);
printf("\n\nALTERAR NOME(1-sim/0-nao)? ");
	scanf("%d", &conf);
if (conf == 1){
printf("\nNOVO NOME: ");
fflush(stdin);
	gets(cliente.nome);
printf("\nNome alterado com sucesso! \n\n");
fseek(pcliente, posicao*sizeof(Cliente), SEEK_SET);
fwrite(&cliente, sizeof(Cliente), 1, pcliente);
mostre(posicao);
printf("\nNome alterado com sucesso!\n");  } 
else
printf("\n\nAlteracao cancelada! \n\n");
}
printf("\n\nDeseja alterar outro (1-sim/0-nao)? ");
	scanf("%d", &resp);
}
while (resp ==1); 
}


main(){
 int op;
 abreArquivo(), abreArquivo1(); 
do{ cabec(); 

printf ("\n\nOpcoes: \n\n\n");
printf ("1- CADASTRAR NOVO CLIENTE\n\n");
printf ("2- CADASTRAR NOVO FILME\n\n");
printf ("3- CONSULTAR CLIENTE\n\n");
printf ("4- CONSULTAR FILME\n\n");
printf ("5- LISTAR CLIENTES\n\n");
printf ("6- LISTAR FILMES\n\n");
printf ("7- REMOVER CLIENTE\n\n");
printf ("8- REMOVER FILME\n\n");
printf ("9- EDITAR CLIENTE\n\n");
printf ("0- Sair\n\n"); 
printf ("\nInforme a opcao desejada: \n");
fflush(stdin);
	scanf("%d", &op);

switch(op){ 

case 1: inserir(); break;

case 2: inserir1(); break;

case 3: consultar(); break;

case 4: consultar1(); break;

case 5: listar(); break;

case 6: listar1(); break;

case 7: removercli(); break;

case 8: removerfilme(); break;

case 9: alterar(); break;

case 0: fclose(pcliente) && fclose(pfilme), printf("\nPROGRAMA ENCERRADO!"); break;
default: printf("\n\nOPCAO INVALIDA!\n\n"); break;
 }
 }
while (op != 0);	
}
