#include<stdio.h>
#include<locale.h>
#include<string.h>
#include<ctype.h>
void AtualizarSaldoCaixa(float valor);

	//////	CLIENTES   //////
typedef struct{
	int cpf,tel,cep,num;
	char nome[101],estado[5],cidade[31],bairro[31],rua[51];
	
}DadosCliente;
void CadastrarCliente()
{
	DadosCliente clt;
	int pos;
	
	FILE *arq;
	arq = fopen("Clientes.bin","ab+");
	if(arq == NULL)
		printf("\nErro no arquivo");
	else
	{
		system("cls");
		fflush(stdin);
		printf("Cadastro de Clientes\n\nEntre com o nome do cliente: ");
		fgets(clt.nome,100,stdin);
		printf("CPF: ");
		scanf("%d",&clt.cpf);
		pos = VerificarCliente(arq,clt.cpf);
		if(pos==-1)
		{
			printf("Telefone: ");
			scanf("%d",&clt.tel);
			printf("CEP: ");
			scanf("%d",&clt.cep);fflush(stdin);
			printf("Estado(SP):");
			fgets(clt.estado,4,stdin);
			printf("Cidade: ");
			fgets(clt.cidade,30,stdin);
			printf("Bairro: ");
			fgets(clt.bairro,30,stdin);
			printf("Rua: ");
			fgets(clt.rua,50,stdin);
			printf("Número da Casa:");
			scanf("%d",&clt.num);fflush(stdin);
			fwrite(&clt,sizeof(DadosCliente),1,arq);
			printf("Cliente Cadastrado com Sucesso!\n");
			system("pause");
		}
		else
		{
			printf("\nCliente já cadastrado!\n\n");
			fseek(arq,pos,0);
			fread(&clt,sizeof(DadosCliente),1,arq);
			printf("Nome: %s",clt.nome);
			printf("CPF: %d\n",clt.cpf);
			printf("Telefone: %d\n",clt.tel);
			printf("CEP: %d\n",clt.cep);
			printf("Estado: %s",clt.estado);
			printf("Cidade: %s",clt.cidade);
			printf("Bairro: %s",clt.bairro);
			printf("Rua: %s",clt.rua);
			printf("Número da Casa: %d",clt.num);
			system("pause");
		}
		fclose(arq);
	}
}
void EditarCliente()
{
	DadosCliente clt;
	int pos,op;
	
	FILE *arq;
	arq = fopen("Clientes.bin","rb+");
	if(arq == NULL)
		printf("\nErro no arquivo");
	else
	{
		system("cls");
		
		printf("Editar Clientes\n\nEntre com o CPF do cliente: (0 Para Voltar)");
		scanf("%d",&clt.cpf);
		while(clt.cpf!=0)
		{
			pos = VerificarCliente(arq,clt.cpf);
			if(pos==-1)
			{
				printf("Cliente Inexistente.");
				system("pause");
			}
			else
			{
				fseek(arq,pos,0);
				fread(&clt,sizeof(DadosCliente),1,arq);
				do
				{
					system("cls");
				
					printf("Editar Clientes\n\nNome: %s",clt.nome);
					printf("CPF: %d\n",clt.cpf);
					printf("Telefone: %d\n--Endereço:\n",clt.tel);
					printf("CEP: %d\n",clt.cep);
					printf("Estado: %s",clt.estado);
					printf("Cidade: %s",clt.cidade);
					printf("Bairro: %s",clt.bairro);
					printf("Rua: %s",clt.rua);
					printf("Número: %d\n----\n",clt.num);
					printf("\nDeseja alterar: \n 1- Nome \n 2- CPF\n 3- Telefone\n 4- Endereço\n 0- Voltar\n\n Opção: ");
					scanf("%d",&op);fflush(stdin);
				}while(op<0 || op>4);
				switch(op)
				{
					case 1:
						printf("Novo Nome: ");
						fgets(clt.nome,100,stdin);
						fseek(arq,pos,0);
						fwrite(&clt,sizeof(DadosCliente),1,arq);
						printf("Nome Alterado!");
						system("pause");
						system("cls");
						break;
					case 2:
						printf("Novo CPF: ");
						scanf("%d",&clt.cpf);fflush(stdin);
						fseek(arq,pos,0);
						fwrite(&clt,sizeof(DadosCliente),1,arq);
						printf("CPF Alterado!");
						system("pause");
						system("cls");
						break;
					case 3:
						printf("Novo Telefone: ");
						scanf("%d",&clt.tel);fflush(stdin);
						fseek(arq,pos,0);
						fwrite(&clt,sizeof(DadosCliente),1,arq);
						printf("Telefone Alterado!");
						system("pause");
						system("cls");
						break;
					case 4:
						printf("CEP: ");
						scanf("%d",&clt.cep);fflush(stdin);
						printf("Estado(SP): ");
						fgets(clt.estado,4,stdin);
						printf("Cidade: ");
						fgets(clt.cidade,30,stdin);
						printf("Bairro: ");
						fgets(clt.bairro,30,stdin);
						printf("Rua: ");
						fgets(clt.rua,50,stdin);
						printf("Número da Casa:");
						scanf("%d",&clt.num);fflush(stdin);
						fseek(arq,pos,0);
						fwrite(&clt,sizeof(DadosCliente),1,arq);
						printf("Endereço Alterado!");
						system("pause");
						system("cls");
						break;
					default:printf("Opção Inválida");
							system("pause");
						break;
					case 0:break;
				}
			}
			system("cls");
			printf("Editar Clientes\n\nEntre com o CPF do cliente: (0 Para Voltar)");
			scanf("%d",&clt.cpf);
		}
		
	}
	fclose(arq);
}
void ExcluirCliente()
{
	char conf;
	int pos,cpf;
	
	DadosCliente clt;
	FILE *arqcliente;
	arqcliente = fopen("Clientes.bin","rb");
	if(arqcliente == NULL)
	{
		printf("Erro no arquivo Clientes!\n");
		system("pause");
	}
	else
	{
		system("cls");
		printf("Excluir Cliente\n\nEntre com o CPF do cliente: ");
		scanf("%d",&cpf);fflush(stdin);
		
		pos = VerificarCliente(arqcliente,cpf);
		if(pos == -1)
			printf("Cliente Inexistente!");
		else
		{
			fseek(arqcliente,pos,0);
			fread(&clt,sizeof(DadosCliente),1,arqcliente);
			
			do
			{
				system("cls");
				printf("Excluir Cliente\n\nNome: %s",clt.nome);
				printf("CPF: %d\n",clt.cpf);
				printf("Telefone: %d\n--Endereço:\n",clt.tel);
				printf("CEP: %d\n",clt.cep);
				printf("Estado: %s",clt.estado);
				printf("Cidade: %s",clt.cidade);
				printf("Bairro: %s",clt.bairro);
				printf("Rua: %s",clt.rua);
				printf("Número: %d\n----\n",clt.num);
				printf("Confirma a exclusão do cliente?(S/N) ");
				scanf(" %c",&conf);fflush(stdin);
				conf = toupper(conf);
			}while(conf != 'S' && conf != 'N');
			if(conf=='S')
			{
				FILE *arqtemp;
				arqtemp = fopen("temp.bin","wb");
				if(arqtemp == NULL)
				{
					printf("Erro no arquivo temporário!\n");
					system("pause");
				}
				else
				{
					rewind(arqcliente);
					fread(&clt,sizeof(DadosCliente),1,arqcliente);
					while(!feof(arqcliente))
					{
						if(clt.cpf != cpf)
							fwrite(&clt,sizeof(DadosCliente),1,arqtemp);
						fread(&clt,sizeof(DadosCliente),1,arqcliente);
					}
					fclose(arqcliente);
					fclose(arqtemp);
					remove("Clientes.bin");
					rename("temp.bin","Clientes.bin");
					printf("Cliente excluido com sucesso!\n");	
				}	
			}
		}
	}
	system("pause");
	fclose(arqcliente);
}
int VerificarCliente(FILE *arq, int cpf) //verifica se ja existe
{
	DadosCliente clt;
	rewind (arq);
	fread(&clt,sizeof(DadosCliente),1,arq);
	while(!feof(arq) && clt.cpf!=cpf)//stricmp(clt.cpf,cpf) != 0)
	{
		fread(&clt,sizeof(DadosCliente),1,arq);
	}
	if(!feof(arq))
		return (ftell(arq)-sizeof(DadosCliente));
	else
		return -1;
}
void ListarClientes()
{
	system("cls");
	printf("Listar Clientes\n\n");
	DadosCliente clt;
	
	FILE *arq;
	arq = fopen("Clientes.bin","rb");
	if(arq == NULL)
		printf("\nErro no arquivo!");
	else
	{
		fread(&clt,sizeof(DadosCliente),1,arq);
		if(feof(arq))
			printf("Não há clientes cadastrados!\n");
		while(!feof(arq))
		{
			printf("Nome: %s",clt.nome);
			printf("CPF: %d\n",clt.cpf);
			printf("Telefone: %d\n",clt.tel);
			printf("CEP: %d\n",clt.cep);
			printf("Estado: %s",clt.estado);
			printf("Cidade: %s",clt.cidade);
			printf("Bairro: %s",clt.bairro);
			printf("Rua: %s",clt.rua);
			printf("Número: %d\n----\n",clt.num);
			fread(&clt,sizeof(DadosCliente),1,arq);
		}
		
	}
	fclose(arq);
	system("pause");
}
void BuscarCliente()
{
	DadosCliente clt;
	int pos;
	
	FILE *arq;
	arq = fopen("Clientes.bin","rb+");
	if(arq == NULL)
		printf("\nErro no arquivo");
	else
	{
		system("cls");
		
		printf("Buscar Cliente\n\nEntre com o CPF do cliente: ");
		scanf("%d",&clt.cpf);
		pos = VerificarCliente(arq,clt.cpf);
		if(pos==-1)
		{
			printf("Cliente Inexistente!\n");
			system("pause");
		}
		else
		{
			system("cls");
			printf("Buscar Cliente\n\nDados do Cliente:\n\n");
			fseek(arq,pos,0);
			fread(&clt,sizeof(DadosCliente),1,arq);
			printf("Nome: %s",clt.nome);
			printf("CPF: %d\n",clt.cpf);
			printf("Telefone: %d\n",clt.tel);
			printf("CEP: %d\n",clt.cep);
			printf("Estado: %s",clt.estado);
			printf("Cidade: %s",clt.cidade);
			printf("Bairro: %s",clt.bairro);
			printf("Rua: %s",clt.rua);
			printf("Número: %d\n",clt.num);
			system("pause");
		}
		fclose(arq);
	}
}

	//////	PRODUTOS  //////
typedef struct{
	float preco;
	int qtd,cod,tipo;
	char nome[101], desc[51];
}DadosProduto;

void CadastrarProduto()
{
	DadosProduto prod;
	int pos,tipo;
	
	FILE *arq;
	arq = fopen("Produtos.bin","ab+");
	if(arq == NULL)
		printf("\nErro no arquivo");
	else
	{
		system("cls");
		printf("Cadastro de Produtos, Serviços e Insumos\n\n");
		printf("Tipo de Item:\n1- Produto\n2- Serviço\n3- Insumo\n0- Voltar\n\nOpção:");
		scanf("%d",&tipo);fflush(stdin);
		while(tipo<0 || tipo>3)
		{
			system("cls");
			printf("Cadastro de Produtos, Serviços e Insumos\n\nTipo de item:\n1- Produto\n2- Serviço\n3- Insumo\n0- Voltar\n\nOpção:");
			scanf("%d",&tipo);fflush(stdin);
		}
		if(tipo!=0)
		{
			prod.tipo = tipo;
			printf("Entre com o nome do Item: ");
			fgets(prod.nome,100,stdin);
			printf("Código do Produto: ");
			scanf("%d",&prod.cod);fflush(stdin);
			pos = VerificarProduto(arq,prod.cod);
			if(pos==-1)
			{
				
				printf("Descrição do Item: ");
				fgets(prod.desc,50,stdin);
				printf("Preço: ");
				scanf("%f",&prod.preco);
				prod.qtd = 0;
				fwrite(&prod,sizeof(DadosProduto),1,arq);
				printf("Item Cadastrado com Sucesso!\n");
				system("pause");
			}
			else
			{
				printf("\nItem já cadastrado!\n\n");
				fseek(arq,pos,0);
				fread(&prod,sizeof(DadosProduto),1,arq);
				if(prod.tipo==1)
					printf("Tipo: Produto\n");
				if(prod.tipo==2)
					printf("Tipo: Serviço\n");
				if(prod.tipo==3)
					printf("Tipo: Insumo\n");
				printf("Nome: %s",prod.nome);
				printf("Descrição: %s",prod.desc);
				printf("Código: %d\n",prod.cod);
				printf("Preço: %.2fR$\n",prod.preco);
				printf("Quantidade em Estoque: %d\n",prod.qtd);
				system("pause");
			}
		}
		fclose(arq);
	}
}
void EditarProduto()
{
	DadosProduto prod;
	int pos,op;
	
	FILE *arq;
	arq = fopen("Produtos.bin","rb+");
	if(arq == NULL)
	{
		printf("\nErro no arquivo Produtos!\n");
		system("pause");
	}
	else
	{
		system("cls");
		
		printf("Editar Produtos, Serviços e Insumos\n\nEntre com o cod do Item: (0 Para Sair)");
		scanf("%d",&prod.cod);
		while(prod.cod!=0)
		{
			pos = VerificarProduto(arq,prod.cod);
			if(pos==-1)
			{
				printf("Item Inexistente.\n");
				system("pause");	
			}
			else
			{
				fseek(arq,pos,0);
				fread(&prod,sizeof(DadosProduto),1,arq);
				do
				{
					system("cls");
					printf("Editar Produtos, Serviços e Insumos\n\n");
					if(prod.tipo==1)
						printf("Tipo: Produto\n");
					if(prod.tipo==2)
						printf("Tipo: Serviço\n");
					if(prod.tipo==3)
						printf("Tipo: Insumo\n");
					printf("Nome: %s",prod.nome);
					printf("Descrição: %s",prod.desc);
					printf("Código: %d\n",prod.cod);
					printf("Preço: %.2fR$\n----\n",prod.preco);
					printf("\nDeseja alterar: \n 1- Nome \n 2- Descrição\n 3- Código\n 4- Preço\n 0- Voltar\n\n Opção: ");
					scanf("%d",&op);fflush(stdin);
				}while(op<0 || op>4);
				if(op!=0)
					switch(op)
					{
						case 1:
							printf("Novo Nome: ");
							fgets(prod.nome,100,stdin);
							fseek(arq,pos,0);
							fwrite(&prod,sizeof(DadosProduto),1,arq);
							printf("Nome Alterado!");
							system("pause");
							system("cls");
							break;
						case 2:
							printf("Nova Descrição: ");
							fgets(prod.desc,50,stdin);
							fseek(arq,pos,0);
							fwrite(&prod,sizeof(DadosProduto),1,arq);
							printf("Descrição Alterada!");
							system("pause");
							system("cls");
							break;
						case 3:
							printf("Novo Código: ");
							scanf("%d",&prod.cod);fflush(stdin);
							fseek(arq,pos,0);
							fwrite(&prod,sizeof(DadosProduto),1,arq);
							printf("Código Alterado!");
							system("pause");
							system("cls");
							break;
						case 4:
							printf("Novo Preço: ");
							scanf("%f",&prod.preco);fflush(stdin);
							fseek(arq,pos,0);
							fwrite(&prod,sizeof(DadosProduto),1,arq);
							printf("Preço Alterado!");
							system("pause");
							system("cls");
							break;
						default: printf("Opção Inválida!");
								system("pause");
							break;
					}
			}
			system("cls");
			printf("Editar Produtos, Serviços e Insumos\n\nEntre com o cod do Produto/Serviço: (0 Para Sair)");
			scanf("%d",&prod.cod);
		}
		
	}
	system("pause");
	fclose(arq);
}
void ExcluirProduto()
{
	char conf;
	int pos,cod,tipo;
	
	DadosProduto prod;
	FILE *arqprod;
	arqprod = fopen("Produtos.bin","rb");
	if(arqprod == NULL)
	{
		printf("Erro no arquivo Produtos!\n");
		system("pause");
	}
	else
	{
		system("cls");
		printf("Excluir Item\n\nTipo de Item:\n 1- Produto\n 2- Serviço\n 3- Insumo\n 0- Voltar\n\n Opção:");
		scanf("%d",&tipo);fflush(stdin);
		if(tipo!=0)
		{
			printf("Entre com o código do Item: ");
			scanf("%d",&cod);fflush(stdin);
			
			pos = VerificarProduto(arqprod,cod);
			fseek(arqprod,pos,0);
			fread(&prod,sizeof(DadosProduto),1,arqprod);
			if(pos == -1 || tipo!=prod.tipo)
				printf("Item Inexistente!");
			else
			{
				do
				{
					system("cls");
					printf("Excluir Item\n\nNome: %s",prod.nome);
					if(prod.tipo==1)
					printf("Tipo: Produto\n");
					if(prod.tipo==2)
						printf("Tipo: Serviço\n");
					if(prod.tipo==3)
						printf("Tipo: Insumo\n");
					printf("Descrição: %s",prod.desc);
					printf("Código: %d\n",prod.cod);
					printf("Preço: %.2fR$\n",prod.preco);
					printf("Quantidade em Estoque: %d\n----\n\n",prod.qtd);
					
					printf("Confirma a exclusão do produto?(S/N) ");
					scanf(" %c",&conf);fflush(stdin);
					conf = toupper(conf);
				}while(conf != 'S' && conf != 'N');
				if(conf=='S')
				{
					FILE *arqtemp;
					arqtemp = fopen("temp.bin","wb");
					if(arqtemp == NULL)
					{
						printf("Erro no arquivo temporário!\n");
						system("pause");
					}
					else
					{
						rewind(arqprod);
						fread(&prod,sizeof(DadosProduto),1,arqprod);
						while(!feof(arqprod))
						{
							if(prod.cod != cod)
								fwrite(&prod,sizeof(DadosProduto),1,arqtemp);
							fread(&prod,sizeof(DadosProduto),1,arqprod);
						}
						fclose(arqprod);
						fclose(arqtemp);
						remove("Produtos.bin");
						rename("temp.bin","Produtos.bin");
						printf("Produto excluido com sucesso!\n");	
					}	
				}
				else
					printf("Exclusão cancelada!\n");
			}
			system("pause");
		}
	}
	
	fclose(arqprod);
}
int VerificarProduto(FILE *arq, int cod)
{
	DadosProduto prod;
	rewind (arq);
	fread(&prod,sizeof(DadosProduto),1,arq);
	while(!feof(arq) && prod.cod!=cod )//stricmp(prod.nome,nome) != 0)
	{
		fread(&prod,sizeof(DadosProduto),1,arq);
	}
	if(!feof(arq))
		return (ftell(arq)-sizeof(DadosProduto));
	else
		return -1;
}
void ListarProdutos()
{
	system("cls");
	int tipo;
	printf("Tipo de Item a Listar:\n 1- Produto\n 2- Serviço\n 3- Insumo\n Opção:");
	scanf("%d",&tipo);fflush(stdin);
	while(tipo!=1 && tipo!=2 && tipo!=3)
	{
		system("cls");
		printf("Tipo de item:\n 1- Produto\n 2- Serviço\n 3- Insumo\n Opção:");
		scanf("%d",&tipo);fflush(stdin);
	}
	system("cls");
	if(tipo==1)
		printf("Listar Produtos\n\n");
	if(tipo==2)
		printf("Listar Serviços\n\n");
	if(tipo==3)
		printf("Listar Insumos\n\n");
	
	DadosProduto prod;
	
	FILE *arq;
	arq = fopen("Produtos.bin","rb");
	if(arq == NULL)
	{
		printf("\nErro no arquivo!\n");
		system("pause");
	}
	else
	{
		fread(&prod,sizeof(DadosProduto),1,arq);
		if(feof(arq))
		{
			printf("Não há produtos cadastrados!\n");
			system("pause");
		}
		while(!feof(arq))
		{
			if(tipo==prod.tipo)
			{
				printf("Nome: %s",prod.nome);
				printf("Descrição: %s",prod.desc);
				printf("Código: %d\n",prod.cod);
				printf("Preço: %.2fR$\n",prod.preco);
				printf("Quantidade: %d\n----\n",prod.qtd);
			}
			
			fread(&prod,sizeof(DadosProduto),1,arq);
		}
		system("pause");
	}
	fclose(arq);
}
void BuscarProduto()
{
	DadosProduto prod;
	int pos;
	
	FILE *arq;
	arq = fopen("Produtos.bin","rb+");
	if(arq == NULL)
		printf("\nErro no arquivo");
	else
	{
		system("cls");
		
		printf("Buscar Produtos, Serviços e Insumos\n\nEntre com o Código do Item: ");
		scanf("%d",&prod.cod);
		pos = VerificarProduto(arq,prod.cod);
		if(pos==-1)
		{
			printf("Item Inexistente!");
			system("pause");
		}
		else
		{
			system("cls");
			printf("Buscar Produtos, Serviços e Insumos\n\nDados do Item:\n\n");
			fseek(arq,pos,0);
			fread(&prod,sizeof(DadosProduto),1,arq);
			if(prod.tipo==1)
				printf("Tipo: Produto\n");
			if(prod.tipo==2)
				printf("Tipo: Serviço\n");
			if(prod.tipo==3)
				printf("Tipo: Insumo\n");
			printf("Nome: %s",prod.nome);
			printf("Descrição: %s",prod.desc);
			printf("Código: %d\n",prod.cod);
			printf("Preço: %.2fR$\n",prod.preco);
			printf("Quantidade: %d\n",prod.qtd);
			system("pause");
		}
		fclose(arq);
	}
}
void AtualizarEstoque(int cod,int qtddev)
{
	DadosProduto prod;
	int pos;
	FILE *arqprod;
	arqprod = fopen("Produtos.bin","rb+");
	if(arqprod == NULL)
	{
		printf("Erro no arquivo Produtos!");
		system("pause");		
	}
	else
	{
		pos = VerificarProduto(arqprod,cod);
		fseek(arqprod,pos,0);
		fread(&prod,sizeof(DadosProduto),1,arqprod);
		prod.qtd = prod.qtd+qtddev;
		fseek(arqprod,pos,0);
		fwrite(&prod,sizeof(DadosProduto),1,arqprod);
	}
	fclose(arqprod);
}

	//////  FORNECEDORES  //////
	
typedef struct{
	char nome[101],categ[51],estado[5],cidade[31],bairro[31],rua[51];
	int cnpj,cep,num;
}DadosFornecedor;
void CadastrarFornecedor()
{
	DadosFornecedor fornecedor;
	int pos;
	
	FILE *arq;
	arq = fopen("Fornecedores.bin","ab+");
	if(arq == NULL)
		printf("\nErro no arquivo");
	else
	{
		system("cls");
		
		printf("Cadastro de Fornecedores\n\nEntre com o nome do Fornecedor: ");
		fgets(fornecedor.nome,100,stdin);
		printf("CNPJ : ");
		scanf("%d",&fornecedor.cnpj);fflush(stdin);
		pos = VerificarFornecedor(arq,fornecedor.cnpj);
		if(pos==-1)
		{
			printf("Categoria de Produtos: ");
			fgets(fornecedor.categ,50,stdin);
			printf("CEP: ");
			scanf("%d",&fornecedor.cep);fflush(stdin);
			printf("Estado(SP): ");
			fgets(fornecedor.estado,4,stdin);
			printf("Cidade: ");
			fgets(fornecedor.cidade,30,stdin);
			printf("Bairro: ");
			fgets(fornecedor.bairro,30,stdin);
			printf("Rua: ");
			fgets(fornecedor.rua,50,stdin);
			printf("Número: ");
			scanf("%d",&fornecedor.num);fflush(stdin);
			
			fwrite(&fornecedor,sizeof(DadosFornecedor),1,arq);
			printf("Fornecedor Cadastrado com Sucesso!\n");
			system("pause");
		}
		else
		{
			printf("\nFornecedor já cadastrado!\n\n");
			fseek(arq,pos,0);
			fread(&fornecedor,sizeof(DadosFornecedor),1,arq);
			printf("Nome: %s",fornecedor.nome);
			printf("CNPJ: %d\n",fornecedor.cnpj);
			printf("Categoria: %s",fornecedor.categ);
			printf("CEP: %d\n",fornecedor.cep);
			printf("Estado: %s",fornecedor.estado);
			printf("Cidade: %s",fornecedor.cidade);
			printf("Bairro: %s",fornecedor.bairro);
			printf("Rua: %s",fornecedor.rua);
			printf("Número da Casa: %d",fornecedor.num);
			
			system("pause");
		}
		fclose(arq);
	}
}
void EditarFornecedor()
{
	DadosFornecedor fornecedor;
	int pos,op;
	
	FILE *arq;
	arq = fopen("Fornecedores.bin","rb+");
	if(arq == NULL)
		printf("\nErro no arquivo");
	else
	{
		system("cls");
		
		printf("Editar Fornecedor\n\nEntre com o CNPJ do Fornecedor: (0 Para Sair) ");
		scanf("%d",&fornecedor.cnpj);
		while(fornecedor.cnpj!=0)
		{
			pos = VerificarFornecedor(arq,fornecedor.cnpj);
			if(pos==-1)
			{
				printf("Fornecedor Inexistente.\n");
				system("pause");
			}
			else
			{
				fseek(arq,pos,0);
				fread(&fornecedor,sizeof(DadosFornecedor),1,arq);
				do
				{
					system("cls");
					printf("Editar Fornecedor\n\nNome: %s",fornecedor.nome);
					printf("CNPJ: %d\n",fornecedor.cnpj);
					printf("Categoria: %s--Endereço:\n",fornecedor.categ);
					printf("CEP: %d\n",fornecedor.cep);
					printf("Estado: %s",fornecedor.estado);
					printf("Cidade: %s",fornecedor.cidade);
					printf("Bairro: %s",fornecedor.bairro);
					printf("Rua: %s",fornecedor.rua);
					printf("Número: %d\n",fornecedor.num);
					printf("\nDeseja alterar: \n 1- Nome \n 2- CNPJ\n 3- Categoria\n 4- Endereço\n 0- Voltar\n\n Opção: ");
					scanf("%d",&op);fflush(stdin);
				}while(op<0 || op>4);
				if(op!=0)
					switch(op)
					{
						case 1:
							printf("Novo Nome: ");
							fgets(fornecedor.nome,100,stdin);
							fseek(arq,pos,0);
							fwrite(&fornecedor,sizeof(DadosFornecedor),1,arq);
							printf("Nome Alterado!");
							system("pause");
							system("cls");
							break;
						case 2:
							printf("Novo CNPJ: ");
							scanf("%d",&fornecedor.cnpj);
							fseek(arq,pos,0);
							fwrite(&fornecedor,sizeof(DadosFornecedor),1,arq);
							printf("CNPJ Alterado!");
							system("pause");
							system("cls");
							break;
						case 3:
							printf("Nova Categoria: ");
							fgets(fornecedor.categ,50,stdin);
							fseek(arq,pos,0);
							fwrite(&fornecedor,sizeof(DadosFornecedor),1,arq);
							printf("Nome Alterado!");
							system("pause");
							system("cls");
							break;
						case 4:
							printf("CEP: ");
							scanf("%d",&fornecedor.cep);fflush(stdin);
							printf("Estado(SP): ");
							fgets(fornecedor.estado,4,stdin);
							printf("Cidade: ");
							fgets(fornecedor.cidade,30,stdin);
							printf("Bairro: ");
							fgets(fornecedor.bairro,30,stdin);
							printf("Rua: ");
							fgets(fornecedor.rua,50,stdin);
							printf("Número: ");
							scanf("%d",&fornecedor.num);fflush(stdin);
							fseek(arq,pos,0);
							fwrite(&fornecedor,sizeof(DadosFornecedor),1,arq);
							printf("Endereço Alterado!");
							system("pause");
							system("cls");
							break;
						default:printf("Opção Inválida");
						system("pause");
							break;
					}
			}
			system("cls");
			printf("Editar Fornecedor\n\nEntre com o CNPJ do Fornecedor: (0 Para Sair)");
			scanf("%d",&fornecedor.cnpj);
		}
	}
	fclose(arq);
}
void ExcluirFornecedor()
{
	char conf;
	int pos,cnpj;
	
	DadosFornecedor fornecedor;
	FILE *arqforn;
	arqforn = fopen("Fornecedores.bin","rb");
	if(arqforn == NULL)
	{
		printf("Erro no arquivo Fornecedores!\n");
		system("pause");
	}
	else
	{
		system("cls");
		printf("Excluir Fornecedor\n\nEntre com o CNPJ do Fornecedor: ");
		scanf("%d",&cnpj);fflush(stdin);
		
		pos = VerificarFornecedor(arqforn,cnpj);
		if(pos == -1)
			printf("Fornecedor Inexistente!");
		else
		{
			fseek(arqforn,pos,0);
			fread(&fornecedor,sizeof(DadosFornecedor),1,arqforn);
			
			do
			{
				system("cls");
				printf("Excluir Fornecedor\n\nNome: %s",fornecedor.nome);
				printf("CNPJ: %d\n",fornecedor.cnpj);
				printf("Categoria: %s--Endereço:\n",fornecedor.categ);
				printf("CEP: %d\n",fornecedor.cep);
				printf("Estado: %s",fornecedor.estado);
				printf("Cidade: %s",fornecedor.cidade);
				printf("Bairro: %s",fornecedor.bairro);
				printf("Rua: %s",fornecedor.rua);
				printf("Número: %d\n",fornecedor.num);
				
				printf("Confirma a exclusão do Fornecedor?(S/N) ");
				scanf(" %c",&conf);fflush(stdin);
				conf = toupper(conf);
			}while(conf != 'S' && conf != 'N');
			if(conf=='S')
			{
				FILE *arqtemp;
				arqtemp = fopen("temp.bin","wb");
				if(arqtemp == NULL)
				{
					printf("Erro no arquivo temporário!\n");
					system("pause");
				}
				else
				{
					rewind(arqforn);
					fread(&fornecedor,sizeof(DadosFornecedor),1,arqforn);
					while(!feof(arqforn))
					{
						if(fornecedor.cnpj != cnpj)
							fwrite(&fornecedor,sizeof(DadosFornecedor),1,arqtemp);
						fread(&fornecedor,sizeof(DadosFornecedor),1,arqforn);
					}
					fclose(arqforn);
					fclose(arqtemp);
					remove("Fornecedores.bin");
					rename("temp.bin","Fornecedores.bin");
					printf("Fornecedor excluido com sucesso!\n");	
				}	
			}
			else
				printf("Exclusão Cancelada!\n");
		}
	}
	system("pause");
	fclose(arqforn);
}
int VerificarFornecedor(FILE *arq, int cnpj)
{
	DadosFornecedor fornecedor;
	rewind (arq);
	fread(&fornecedor,sizeof(DadosFornecedor),1,arq);
	while(!feof(arq) && fornecedor.cnpj!=cnpj )//stricmp(prod.nome,nome) != 0)
	{
		fread(&fornecedor,sizeof(DadosFornecedor),1,arq);
	}
	if(!feof(arq))
		return (ftell(arq)-sizeof(DadosFornecedor));
	else
		return -1;
}
void ListarFornecedores()
{
	system("cls");
	printf("Listar Fornecedor:\n\n");
	DadosFornecedor fornecedor;
	
	FILE *arq;
	arq = fopen("Fornecedores.bin","rb");
	if(arq == NULL)
		printf("\nErro no arquivo!");
	else
	{
		fread(&fornecedor,sizeof(DadosFornecedor),1,arq);
		if(feof(arq))
			printf("Não há Fornecedores cadastrados!\n");
		while(!feof(arq))
		{
			printf("Nome: %s",fornecedor.nome);
			printf("CNPJ: %d\n",fornecedor.cnpj);
			printf("Categoria: %s--Endereço:\n",fornecedor.categ);
			printf("CEP: %d\n",fornecedor.cep);
			printf("Estado: %s",fornecedor.estado);
			printf("Cidade: %s",fornecedor.cidade);
			printf("Bairro: %s",fornecedor.bairro);
			printf("Rua: %s",fornecedor.rua);
			printf("Número: %d\n-----\n\n",fornecedor.num);
			fread(&fornecedor,sizeof(DadosFornecedor),1,arq);
		}
	}
	system("pause");
	fclose(arq);
}
void BuscarFornecedor()
{
	DadosFornecedor fornecedor;
	int pos;
	
	FILE *arq;
	arq = fopen("Fornecedores.bin","rb+");
	if(arq == NULL)
		printf("\nErro no arquivo");
	else
	{
		system("cls");
		
		printf("Buscar Fornecedor\n\nEntre com o CNPJ do Fornecedor: ");
		scanf("%d",&fornecedor.cnpj);
		pos = VerificarFornecedor(arq,fornecedor.cnpj);
		if(pos==-1)
		{
			printf("Fornecedor Inexistente!\n");
			system("pause");
		}
		else
		{
			system("cls");
			printf("Buscar Fornecedor\n\nDados do Fornecedor:\n\n");
			fseek(arq,pos,0);
			fread(&fornecedor,sizeof(DadosFornecedor),1,arq);
			printf("Nome: %s",fornecedor.nome);
			printf("CNPJ: %d\n",fornecedor.cnpj);
			printf("Categoria: %s",fornecedor.categ);
			printf("CEP: %d\n",fornecedor.cep);
			printf("Estado: %s",fornecedor.estado);
			printf("Cidade: %s",fornecedor.cidade);
			printf("Bairro: %s",fornecedor.bairro);
			printf("Rua: %s",fornecedor.rua);
			printf("Número: %d\n\n",fornecedor.num);
			system("pause");
		}
		fclose(arq);
	}
}
		
	//////  COMPRAS  //////

	
typedef struct{
	int cnpj;
	int cod,qtd;  
	float valortot,precoUni;
	char fornecedor[101],nomeprod[101],MetPag[21];
	int CodNota;
	int devolucao;         //devolução mostra a quantidade que foi devolvida
	char motivo[101];	   //Motivo de devolução
}Compra;
void CadastrarCompra()
{
	DadosFornecedor fornecedor;
	DadosProduto prod;
	Compra compra;
	int posforn,posprod;
	int cnpj,cod,qtd,pag;				// pag = Método de pagamento:\n\n1- Pix\n2- Cartão crédito\n3- Cartão débito\n4- Dinheiro
	char conf,MetPag[21];
	
	int StatusCaixa;
	StatusCaixa = VerificarCaixa();
	if(StatusCaixa == 0)
	{
		printf("Caixa está fechado! Favor abrir o caixa antes de operar!\n");
		system("pause");
	}
	else
	{
		system("cls");
		printf("Efetuar Compra\n\nEntre com o CNPJ do Fornecedor: (0 Para Voltar)");
		scanf("%d",&compra.cnpj);fflush(stdin);
		while(compra.cnpj!=0)
		{
			FILE *arqforn;
			arqforn = fopen("Fornecedores.bin","rb+");
			if(arqforn == NULL)
			{
				printf("Erro no arquivo Fornecedores!\n");
				system("pause");			
			}
			else
			{
				posforn = VerificarFornecedor(arqforn,compra.cnpj);
				if(posforn == -1){
					printf("Fornecedor Inexistente!\n");
					system("pause");
				}
				else
				{
					printf("Código do Item: ");
					scanf("%d",&compra.cod);
					FILE *arqprod;
					arqprod = fopen("Produtos.bin","rb+");
					if(arqprod == NULL)
					{
						printf("Erro no arquivo Produtos!\n");
						system("pause");			
					}
					else
					{
						FILE *arqcompra;
						arqcompra = fopen("Compras.bin","ab+");
						if(arqcompra == NULL)
						{
							printf("Erro no arquivo Compras!\n");
							system("pause");			
						}
						else
						{
							posprod = VerificarProduto(arqprod,compra.cod);
							if(posprod == -1)
							{
								printf("Item Inexistente!\n");
								system("pause");
							}
							else
							{
								printf("Quantidade: ");
								scanf("%d",&compra.qtd);fflush(stdin);
								
								printf("Valor Unitário: ");
								scanf("%f",&compra.precoUni);fflush(stdin);
								do
								{
									system("cls");
									printf("Efetuar Compra\n\nMétodo de pagamento:\n\n1- Pix\n2- Cartão crédito\n3- Cartão débito\n4- Dinheiro\n\nOpção: ");
									scanf("%d",&pag);fflush(stdin);										
								}while(pag!=1 && pag!=2 && pag!=3 && pag!=4 );
								switch(pag)
								{
									case 1: strcpy(compra.MetPag,"Pix");		
									break;
									case 2: strcpy(compra.MetPag,"Cartão de Crédito");
									break;
									case 3: strcpy(compra.MetPag,"Cartão de Débito");
									break;
									case 4: strcpy(compra.MetPag,"Dinheiro");
									break;
								}
								system("cls");
								fseek(arqforn,posforn,0);
								fread(&fornecedor,sizeof(DadosFornecedor),1,arqforn);
								fseek(arqprod,posprod,0);
								fread(&prod,sizeof(DadosProduto),1,arqprod);
								printf(" Dados da Compra:\n\n Fornecedor: %s Produto: %s Descrição: %s Quantidade: %d\n Valor Unitário: %.2fR$\n\n Valor Total: %.2fR$\n Método de Pagamento: %s\n"
								,fornecedor.nome,prod.nome,prod.desc,compra.qtd,compra.precoUni,compra.precoUni*compra.qtd,compra.MetPag);	
								conf = toupper(conf);
								do
								{
									printf(" Confirma a Compra? (S/N)");
									scanf(" %c",&conf);fflush(stdin);
									conf = toupper(conf);
									switch(conf)
									{
										case 'S':printf(" Compra Concluida!\n");
												 strcpy(compra.fornecedor,fornecedor.nome);
												 strcpy(compra.nomeprod,prod.nome);
												 compra.valortot = compra.precoUni*compra.qtd;
												 compra.devolucao = 0;
												  
												 fwrite(&compra,sizeof(Compra),1,arqcompra);  ///CADASTRANDO COMPRA
												 
												 AtualizarEstoque(compra.cod,compra.qtd);	///ATUALIZANDO ESTOQUE
												 AtualizarSaldoCaixa(-compra.valortot);		///ATUALIZANDO CAIXA
											 	 printf("Quantidade em Estoque Atualizada! QTD: %d\n",prod.qtd+compra.qtd);
												 system("pause");
												 system("cls");
												 
										break;
										case 'N':printf(" Compra Cancelada!\n");
												 system("pause");
										break;
										default: printf(" Opção Inválida!\n");
												 system("pause");
										break;
									}
									if(conf!='S' && conf!='N')
									{
										system("cls");
										printf(" Dados da Compra:\n\n Fornecedor: %s Produto: %s Descrição: %s Quantidade: %d\n Valor Unitário: %.2fR$\n\n Valor Total: %.2fR$\n Método de Pagamento: %s\n"
										,fornecedor.nome,prod.nome,prod.desc,compra.qtd,compra.precoUni,compra.precoUni*compra.qtd,compra.MetPag);	
										
									}
								}while(conf!='S' && conf != 'N');
							}
						fclose(arqcompra);
						}
					fclose(arqprod);
					}
				}
			fclose(arqforn);
			}
			system("cls");
			printf("Efetuar Compra\n\nEntre com o CNPJ do Fornecedor: (0 Para Voltar)");
			scanf("%d",&compra.cnpj);fflush(stdin);
		}
	}
	
	
}
void DevolucaoCompra()
{
	printf("Função Em Desenvolvimento..");
	system("pause");
}

	//////  VENDAS  ////// 
	
typedef struct{
	int cpf,cod,qtd;
	float valortot,valorUni;
	char cliente[101],nomeprod[101];
	char MetPag[21]; 
	int CodNota;
	int devolucao;         //devolução mostra a quantidade que foi devolvida
	char motivo[101];	   //Motivo de devolução
}Venda;
int ProximaNota()
{
	int maiornota = 0;
	Venda venda;
	
	FILE *arqvenda;
	arqvenda = fopen("Vendas.bin","rb");
	if(arqvenda == NULL)
	{
		printf("Erro no arquivo Vendas!(PROX NOTA)");
		system("pause");
		return 20250001;
	}
	else
	{
		fread(&venda,sizeof(Venda),1,arqvenda);
		while(!feof(arqvenda))
		{
			if(venda.CodNota > maiornota)
				maiornota = venda.CodNota;
			fread(&venda,sizeof(Venda),1,arqvenda);
		}
		if(maiornota < 20250000)
			maiornota += 20250000;
		return maiornota + 1;
	}
	fclose(arqvenda);
}
void CadastrarVenda()
{
	DadosCliente clt;
	DadosProduto prod;
	Venda venda;
	int ProxNota;
	int poscliente,posprod;
	int cpf,cod,qtd,pag;			// pag = Método de pagamento:\n\n1- Pix\n2- Cartão crédito\n3- Cartão débito\n4- Dinheiro
	int StatusCaixa;
	char conf;
	StatusCaixa = VerificarCaixa();
	if(StatusCaixa == 0)
	{
		printf("Caixa está fechado! Favor abrir o caixa antes de operar!\n");
		system("pause");
	}
	else
	{	
		system("cls");
		printf("Efetuar Venda\n\nEntre com o CPF do Cliente: (0 Para Voltar)");
		scanf("%d",&venda.cpf);fflush(stdin);
		while(venda.cpf!=0)
		{
			FILE *arqcliente;
			arqcliente = fopen("Clientes.bin","rb+");
			if(arqcliente == NULL)
				printf("Erro no arquivo Clientes!\n");
			else
			{
				poscliente = VerificarCliente(arqcliente,venda.cpf);
				if(poscliente == -1)
				{
					printf("Cliente Inexistente!\n");
					system("pause");
				}
				else
				{
					printf("Código do Produto: ");
					scanf("%d",&venda.cod);
					FILE *arqprod;
					arqprod = fopen("Produtos.bin","rb+");
					if(arqprod == NULL)
						printf("Erro no arquivo Produtos!");
					else
					{
						FILE *arqvenda;
						arqvenda = fopen("Vendas.bin","ab+");
						if(arqvenda == NULL)
						 	printf("Erro no arquivo Vendas!\n");
						else
						{
							posprod = VerificarProduto(arqprod,venda.cod);
							if(posprod == -1)
							{
								printf("Produto/Serviço Inexistente!\n");
								system("pause");
							}
							else
							{
								do
								{
									system("cls");
									printf("Efetuar Venda\n\nQuantidade: ");
									scanf("%d",&venda.qtd);fflush(stdin);
									if(venda.qtd==0)
									{
										printf("Quantidade Inválida!\n");
										system("pause");
									}
								}while(venda.qtd==0);
								
								system("cls");
								fseek(arqcliente,poscliente,0);
								fread(&clt,sizeof(DadosCliente),1,arqcliente);
								fseek(arqprod,posprod,0);
								fread(&prod,sizeof(DadosProduto),1,arqprod);
								if(venda.qtd>prod.qtd)
								{
									printf("Efetuar Venda\n\nQuantidade em estoque insuficiente!\n\nItem: %sEm Estoque: %d\n",prod.nome,prod.qtd);
									system("pause");
								}
								else
								{
									do
									{
										system("cls");
										printf("Efetuar Venda\n\nMétodo de pagamento:\n\n1- Pix\n2- Cartão crédito\n3- Cartão débito\n4- Dinheiro\n\nOpção: ");
										scanf("%d",&pag);fflush(stdin);										
									}while(pag!=1 && pag!=2 && pag!=3 && pag!=4 );
									switch(pag)
									{
										case 1: strcpy(venda.MetPag,"Pix");		
										break;
										case 2: strcpy(venda.MetPag,"Cartão de Crédito");
										break;
										case 3: strcpy(venda.MetPag,"Cartão de Débito");
										break;
										case 4: strcpy(venda.MetPag,"Dinheiro");
										break;
									}
									
									system("cls");
									printf(" Dados da Venda:\n\n Cliente: %s Produto: %s Descrição: %s Quantidade: %d\n Valor Unitário: %.2fR$\n\n Valor Total: %.2fR$\n Método de Pagamento: %s\n"
									,clt.nome,prod.nome,prod.desc,venda.qtd,prod.preco,prod.preco*venda.qtd,venda.MetPag);
									do
									{
										printf(" Confirma a Venda? (S/N)");
										scanf(" %c",&conf);fflush(stdin);
										conf = toupper(conf);
										switch(conf)
										{
											case 'S':printf(" Venda Concluida!\n");
													 strcpy(venda.cliente,clt.nome);
													 strcpy(venda.nomeprod,prod.nome);
													 venda.valorUni = prod.preco;
													 venda.valortot = prod.preco*venda.qtd;
													 venda.devolucao = 0;
													 venda.CodNota = ProximaNota();				
													 									 
													 fwrite(&venda,sizeof(Venda),1,arqvenda);  /// CADASTRANDO VENDA
													 
													 AtualizarEstoque(venda.cod,-venda.qtd);	///ATUALIZANDO ESTOQUE
													 
													 AtualizarSaldoCaixa(venda.valortot);		//ATUALIZANDO CAIXA
												 	 printf("Quantidade em Estoque Atualizada! QTD: %d\n",prod.qtd-venda.qtd);
												 	 
													 system("pause");
													 system("cls");
												break;
											case 'N':printf(" Venda Cancelada!\n");
												system("pause");
												break;
											default:printf(" Opção Inválida!\n");
												system("pause");
												break;
										}
										if(conf!='S' && conf!='N')
										{
											system("cls");
											printf(" Dados da Venda:\n\n Cliente: %s Produto: %s Descrição: %s Quantidade: %d\n Valor Unitário: %.2fR$\n\n Valor Total: %.2fR$\n Método de Pagamento: %s\n"
											,clt.nome,prod.nome,prod.desc,venda.qtd,prod.preco,prod.preco*venda.qtd,venda.MetPag);	
											
										}
									}while(conf!='S' && conf != 'N');
								}
								
							}
							fclose(arqvenda);
						}
						fclose(arqprod);
					}
				}
				fclose(arqcliente);
			}
			system("cls");
			printf("Efetuar Venda\n\nEntre com o CPF do Cliente: (0 Para Voltar)");
			scanf("%d",&venda.cpf);fflush(stdin);
		}	
	}
}
void DevolucaoVenda()
{
	DadosCliente clt;
	Venda venda;
	int StatusCaixa;
	int cpf,pos,posvenda,cont=0,nota,achou=0,qtd,qtddev;
	int VendaCDevolucao=0;
	char conf;
	
	FILE *arqcliente;
	arqcliente = fopen("Clientes.bin","rb");
	if(arqcliente == NULL)
		printf("Erro no arquivo Clientes!\n");
	else
	{
		StatusCaixa = VerificarCaixa();
		if(StatusCaixa == 0)
		{
			system("cls");
			printf("Devolução de Venda\n\nCaixa está fechado! Favor abrir o caixa antes de operar!\n");
		}
		else
		{
			system("cls");
			printf("Devolução de Venda\n\nEntre com o CPF do cliente: ");
			scanf("%d",&cpf);fflush(stdin);
			pos = VerificarCliente(arqcliente,cpf);
			if(pos==-1)
				printf("Cliente Inexistente!\n");
			else
			{
				fseek(arqcliente,pos,0);
				fread(&clt,sizeof(DadosCliente),1,arqcliente);
				system("cls");
				
				FILE *arqvenda;
				arqvenda = fopen("Vendas.bin","rb+");
				if(arqvenda == NULL)
					printf("Erro no arquivo Vendas!\n");
				else
				{
					fread(&venda,sizeof(Venda),1,arqvenda);
					while(!feof(arqvenda))
					{
						if(venda.cpf == cpf)
							cont++;
						fread(&venda,sizeof(Venda),1,arqvenda);
					}
					if(cont>0)
					{
						do
						{
							printf("Devolução de Venda\n\nCompras do cliente: %s\n",clt.nome);
							rewind(arqvenda);
							fread(&venda,sizeof(Venda),1,arqvenda);
							while(!feof(arqvenda))
							{
								if(venda.cpf == cpf)
								{
									
									printf("Cliente: %s",venda.cliente);
									printf("CPF: %d\n",venda.cpf);
									printf("Produto: %s",venda.nomeprod);
									printf("Codigo Produto: %d\n",venda.cod);
									printf("Quantidade: %d\n",venda.qtd);
									printf("Valor Unitário: %.2fR$\n",venda.valorUni);
									printf("Valor Total: %.2fR$\n",venda.valortot);
									printf("Método de Pagamento: %s\n",venda.MetPag);
									if(venda.devolucao>0)
									{
										printf("***Venda com Devolução de %d itens***\n",venda.devolucao);
										printf("***Motivo: %s",venda.motivo);
									}
									
									printf("Nota fiscal: %d\n----\n\n",venda.CodNota);
								}
								fread(&venda,sizeof(Venda),1,arqvenda);
							}
							printf("Entre com o Número da Nota Fiscal à fazer devolução: (0 Para voltar)");
							scanf("%d",&nota);fflush(stdin);
							rewind(arqvenda);
							
							do
							{
								fread(&venda,sizeof(Venda),1,arqvenda);
								if(venda.CodNota == nota)
								{
									achou=1;
									if(venda.devolucao>0)
									{
										system("cls");
										printf("Devolução de Venda\n\nCliente: %s",venda.cliente);
										printf("CPF: %d\n",venda.cpf);
										printf("Produto: %s",venda.nomeprod);
										printf("Codigo Produto: %d\n",venda.cod);
										printf("Quantidade: %d\n",venda.qtd);
										printf("Valor Unitário: %.2fR$\n",venda.valorUni);
										printf("Valor Total: %.2fR$\n",venda.valortot);
										printf("Método de Pagamento: %s\n",venda.MetPag);
										printf("***Venda com Devolução de %d itens***\n",venda.devolucao);
										printf("***Motivo: %s",venda.motivo);
										
										printf("Nota fiscal: %d\n----\n\n",venda.CodNota);
										printf("Venda Já com devolução! Não será possivel nova devolução!\n");
										VendaCDevolucao = 1;
									}
								
									posvenda = (ftell(arqvenda)-sizeof(Venda));
								}
							}while(venda.CodNota != nota && !feof(arqvenda));
							
							if(achou!=1 && nota !=0)
							{
								printf("Nenhuma venda encontrada com esta Nota Fiscal!\n");
								system("pause");
								system("cls");
							}
						}while(achou!=1 && nota !=0);
						
						if(!VendaCDevolucao)
							if(nota != 0)
							{
								do
								{
									system("cls");
									printf("Devolução de Venda\n\nCliente: %s",venda.cliente);
									printf("CPF: %d\n",venda.cpf);
									printf("Produto: %s",venda.nomeprod);
									printf("Codigo Produto: %d\n",venda.cod);
									printf("Quantidade: %d\n",venda.qtd);
									printf("Valor Unitário: %.2fR$\n",venda.valorUni);
									printf("Valor Total: %.2fR$\n",venda.valortot);
									printf("Método de Pagamento: %s\n",venda.MetPag);
									
									printf("Nota fiscal: %d\n----\n\n",venda.CodNota);
									printf("Quantidade à fazer devolução: ");
									scanf("%d",&qtd);fflush(stdin);
									if(qtd>venda.qtd || qtd<1)
									{
										printf("Quantidade Inválida! Deve ser menor ou igual a quantidade da venda e maior que zero!\n");
										system("pause");
									}
								}while(qtd>venda.qtd || qtd<1);
								
								do
								{
									system("cls");
									system("cls");
									printf("Devolução de Venda\n\nCliente: %s",venda.cliente);
									printf("CPF: %d\n",venda.cpf);
									printf("Produto: %s",venda.nomeprod);
									printf("Codigo Produto: %d\n",venda.cod);
									printf("Quantidade: %d\n",venda.qtd);
									printf("Valor Unitário: %.2fR$\n",venda.valorUni);
									printf("Valor Total: %.2fR$\n",venda.valortot);
									printf("Método de Pagamento: %s\n",venda.MetPag);
									printf("Nota fiscal: %d\n----\n\n",venda.CodNota);
									
									printf("Motivo de devolução: ");
									fgets(venda.motivo,100,stdin);
									if(strlen(venda.motivo)<6)
									{
										printf("Motivo deve ser preenchido com no mínimo 5 caracteres para ser considerado válido!\n");
										system("pause");
									}
								}while(strlen(venda.motivo)<6);
								
								venda.devolucao = qtd;
								do{
									system("cls");
									printf("Devolução de Venda\n\nCliente: %s",venda.cliente);
									printf("CPF: %d\n",venda.cpf);
									printf("Produto: %s",venda.nomeprod);
									printf("Codigo Produto: %d\n",venda.cod);
									printf("Quantidade: %d\n",venda.qtd);
									printf("Valor Unitário: %.2fR$\n",venda.valorUni);
									printf("Valor Total: %.2fR$\n",venda.valortot);
									printf("Método de Pagamento: %s\n",venda.MetPag);
									printf("Nota fiscal: %d\n----\n\n",venda.CodNota);
									
									printf("Motivo: %s\n",venda.motivo);
									printf("Quantidade a devolver: %d\n\n",qtd);
									printf("Quantos itens podem ser devolvidos ao estoque? ");
									scanf("%d",&qtddev);fflush(stdin);
									if(qtddev < 0 || qtddev > qtd)
									{
										printf("Quantidade inválida! Deve ser menor ou igual a quantidade em devolução!\n");
										system("pause");
									}
								}while(qtddev < 0 || qtddev > qtd);
								
								do
								{
									system("cls");
									printf("Devolução de Venda\n\nCliente: %s",venda.cliente);
									printf("CPF: %d\n",venda.cpf);
									printf("Produto: %s",venda.nomeprod);
									printf("Codigo Produto: %d\n",venda.cod);
									printf("Quantidade: %d\n",venda.qtd);
									printf("Valor Unitário: %.2fR$\n",venda.valorUni);
									printf("Valor Total: %.2fR$\n",venda.valortot);
									printf("Método de Pagamento: %s\n",venda.MetPag);
									printf("Nota fiscal: %d\n----\n\n",venda.CodNota);
									
									printf("Motivo: %s\n",venda.motivo);
									printf("Quantidade a devolver: %d\n\n",qtd);
									printf("Quantidade a devolver ao estoque: %d\n\n",qtddev);
									printf("Confirma o pedido de devolução?(S/N) ");
									scanf(" %c",&conf);fflush(stdin);
									conf = toupper(conf);
								}while(conf !='S' && conf!='N');
								if(conf == 'S')
								{
									fseek(arqvenda,posvenda,0);
									fwrite(&venda,sizeof(Venda),1,arqvenda);
									if(qtddev>0)
										AtualizarEstoque(venda.cod,qtddev);
									AtualizarSaldoCaixa(-(venda.valorUni*qtd));
									printf("Devolução concluida!\n");
								}
								else
									printf("Devolução cancelada!\n");
							}
					}
					else
						printf("O(A) cliente: %sNão possui compras realizadas.\n",clt.nome);
				}
				fclose(arqvenda);
			}
		}
	}
	fclose(arqcliente);
	system("pause");
}

	//////  RELATÓRIOS  //////
	
void RelatorioProd()
{
	int tipo=1;
	DadosProduto prod;
	
	FILE *arq;
	arq = fopen("Produtos.bin","rb");
	if(arq == NULL)
	{
		printf("\nErro no arquivo Produtos!\n");
		system("pause");
	}
	else
	{
		fread(&prod,sizeof(DadosProduto),1,arq);
		if(feof(arq))
		{
			printf("Não há produtos cadastrados!\n");
			system("pause");
		}
		system("cls");
		printf("Relatório Produtos\n\n");
		while(!feof(arq))
		{
			if(tipo==prod.tipo)
			{
				printf("Nome: %s",prod.nome);
				printf("Código: %d\n",prod.cod);
				printf("Preço: %.2fR$\n",prod.preco);
				printf("Quantidade: %d\n----\n",prod.qtd);
			}
			
			fread(&prod,sizeof(DadosProduto),1,arq);
		}
		system("pause");
	}
	fclose(arq);
}
void RelatorioInsumo()
{
	int tipo=3;
	DadosProduto prod;
	
	FILE *arq;
	arq = fopen("Produtos.bin","rb");
	if(arq == NULL)
	{
		printf("\nErro no arquivo Produtos!\n");
		system("pause");
	}
	else
	{
		fread(&prod,sizeof(DadosProduto),1,arq);
		if(feof(arq))
		{
			printf("Não há Insumos cadastrados!\n");
			system("pause");
		}
		system("cls");
		printf("Relatório Insumos\n\n");
		while(!feof(arq))
		{
			if(tipo==prod.tipo)
			{
				printf("Nome: %s",prod.nome);
				printf("Código: %d\n",prod.cod);
				printf("Preço: %.2fR$\n",prod.preco);
				printf("Quantidade: %d\n----\n",prod.qtd);
			}
			
			fread(&prod,sizeof(DadosProduto),1,arq);
		}
		system("pause");
	}
	fclose(arq);
}
void RelatorioNotas()
{
	Venda venda;
	
	FILE *arq;
	arq = fopen("Vendas.bin","rb");
	if(arq == NULL)
	{
		printf("\nErro no arquivo Venda!\n");
		system("pause");
	}
	else
	{
		fread(&venda,sizeof(Venda),1,arq);
		if(feof(arq))
		{
			printf("Não há Notas registradas!\n");
			system("pause");
		}
		system("cls");
		printf("Relatório Notas\n\n");
		while(!feof(arq))
		{
			printf("Cliente: %s",venda.cliente);
			printf("CPF: %d\n",venda.cpf);
			printf("Produto: %s",venda.nomeprod);
			printf("Quantidade: %d\n",venda.qtd);
			printf("Valor Total: %.2fR$\n",venda.valortot);
			printf("Método de Pagamento: %s\n",venda.MetPag);
			if(venda.devolucao>0)
			{
				printf("***Venda com Devolução de %d itens***\n",venda.devolucao);
				printf("***Motivo: %s",venda.motivo);
			}
			printf("Nota fiscal: %d\n----\n\n",venda.CodNota);
			fread(&venda,sizeof(Venda),1,arq);
		}
		system("pause");
	}
	fclose(arq);
}
void RelatorioVendas()
{
	Venda venda;
	
	FILE *arq;
	arq = fopen("Vendas.bin","rb");
	if(arq == NULL)
	{
		printf("\nErro no arquivo Venda!\n");
		system("pause");
	}
	else
	{
		fread(&venda,sizeof(Venda),1,arq);
		if(feof(arq))
		{
			printf("Não há Vendas cadastrados!\n");
			system("pause");
		}
		system("cls");
		printf("Relatório Vendas\n\n");
		while(!feof(arq))
		{
			printf("Cliente: %s",venda.cliente);
			printf("CPF: %d\n",venda.cpf);
			printf("Produto: %s",venda.nomeprod);
			printf("Codigo Produto: %d\n",venda.cod);
			printf("Quantidade: %d\n",venda.qtd);
			printf("Valor Unitário: %.2fR$\n",venda.valorUni);
			printf("Valor Total: %.2fR$\n",venda.valortot);
			printf("Método de Pagamento: %s\n",venda.MetPag);
			if(venda.devolucao>0)
			{
				printf("***Venda com Devolução de %d itens***\n",venda.devolucao);
				printf("***Motivo: %s",venda.motivo);
			}
			printf("Nota fiscal: %d\n----\n\n",venda.CodNota);
			fread(&venda,sizeof(Venda),1,arq);
		}
		system("pause");
	}
	fclose(arq);
}
void RelatorioCompras()
{
	Compra compra;
	
	FILE *arq;
	arq = fopen("Compras.bin","rb");
	if(arq == NULL)
	{
		printf("\nErro no arquivo Compra!\n");
		system("pause");
	}
	else
	{
		fread(&compra,sizeof(Compra),1,arq);
		if(feof(arq))
		{
			printf("Não há Comrpas cadastrados!\n");
			system("pause");
		}
		system("cls");
		printf("Relatório Compras\n\n");
		while(!feof(arq))
		{
			printf("Fornecedor: %s",compra.fornecedor);
			printf("CNPJ: %d\n",compra.cnpj);
			printf("Produto: %s",compra.nomeprod);
			printf("Codigo Produto: %d\n",compra.cod);
			printf("Quantidade: %d\n",compra.qtd);
			printf("Valor Unitário: %.2fR$\n",compra.precoUni);
			printf("Valor Total: %.2fR$\n",compra.valortot);
			printf("Método de Pagamento: %s\n----\n",compra.MetPag);
			
			//printf("Nota fiscal: %%d\n----\n\n");
			fread(&compra,sizeof(Compra),1,arq);
		}
		system("pause");
	}
	fclose(arq);
}

	//////  CAIXA  //////
	
typedef struct{
	int status; // 0 = FECHADO && 1 = ABERTO 
	float valcaixa;
}Caixa;
void InicializarCaixa()
{
	Caixa caixa;
	FILE *arq;
	arq = fopen("Caixa.bin","wb+");
	if(arq == NULL)
	{
		printf("Erro no arquivo Caixa\n");
	}
	else
	{
		fread(&caixa,sizeof(Caixa),1,arq);
		rewind(arq);
		caixa.valcaixa = 0; 
		caixa.status = 0;
		fwrite(&caixa,sizeof(Caixa),1,arq);
	}
	fclose(arq);
}
void AbrirCaixa()
{
	int valcaixa;
	Caixa caixa;
	FILE *arq;
	arq = fopen("Caixa.bin","rb+");
	if(arq == NULL)
	{
		printf("Erro no arquivo Caixa\n");
	}
	else
	{
		do
		{
			system("cls");
			printf("Gerenciar Caixa\n\nQual valor em caixa? ");
			scanf("%f",&caixa.valcaixa);
			if(caixa.valcaixa<0)
			{
				printf("Valor inválido! Deve ser zero ou mais!\n");
				system("pause");
			}
		}while(caixa.valcaixa<0);
		
		caixa.status = 1;
		fwrite(&caixa,sizeof(Caixa),1,arq);
		printf("Caixa Aberto com Sucesso!\n");
	}
	fclose(arq);
	system("pause");
	system("cls");
}
void FecharCaixa()
{
	Caixa caixa;
	FILE *arq;
	arq = fopen("Caixa.bin","rb+");
	if(arq == NULL)
	{
		printf("Erro no arquivo Caixa\n");
	}
	else
	{
		fread(&caixa,sizeof(Caixa),1,arq);
		caixa.status = 0;
		caixa.valcaixa = 0; 
		rewind(arq);
		fwrite(&caixa,sizeof(Caixa),1,arq);
		printf("Caixa Fechado!\n");
	}
	fclose(arq);
	system("pause");
	system("cls");
}
int VerificarCaixa()
{
	Caixa caixa;
	FILE *arq;
	arq = fopen("Caixa.bin","rb+");
	if(arq == NULL)
	{
		printf("Erro no arquivo Caixa\n");
	}
	else
	{
		fread(&caixa,sizeof(Caixa),1,arq);
		if(caixa.status == 0)
			return 0;
		else
			return 1;
	}
	system("pause");
	system("cls");
	fclose(arq);
}
void AtualizarSaldoCaixa(float valor)
{
	Caixa caixa;
	FILE *arq;
	arq = fopen("Caixa.bin","rb+");
	if(arq == NULL)
	{
		printf("Erro no arquivo Caixa\n");
		system("pause");
	}
	else
	{
		fread(&caixa,sizeof(Caixa),1,arq);
		caixa.valcaixa = caixa.valcaixa + valor;
		rewind(arq);
		fwrite(&caixa,sizeof(Caixa),1,arq);
	}
	fclose(arq);
}

	//////    MENUS   //////

int MenuPrincipal()
{
	int op,CaixaStatus;
	printf("Menu SEMEAR, Seja Bem Vindo! \n");
	printf("\nEscolha a opção desejada:");
	printf("\n1- Gerenciar Clientes");    
	printf("\n2- Gerenciar Produtos, Serviços e Insumos");  
	printf("\n3- Gerenciar Fornecedores");		
	printf("\n4- Gerenciar Compras");		//Falta Devolução
	printf("\n5- Gerenciar Vendas");
	printf("\n6- Gerar Relatórios\n"); //FALTANDO notas
	printf("\n7- Gerenciar Caixa\n");
	CaixaStatus = VerificarCaixa();
	if(CaixaStatus ==1)
		printf("\n   CAIXA ABERTO!");
	else
		printf("\n   CAIXA FECHADO!");
	printf("\n\n0- Sair\n\nOpção: ");
	scanf("%d",&op);fflush(stdin);
	return op;
}
int MenuGCliente()
{
	int op2;
	system("cls"); // limpa a tela.
	printf("Gerenciamento de Clientes:\n");
	printf("\n1- Cadastrar Clientes");
	printf("\n2- Editar Clientes");
	printf("\n3- Excluir Clientes");
	printf("\n4- Listar Clientes");
	printf("\n5- Buscar Clientes");

	printf("\n0- Voltar\n\n");
	scanf("%d",&op2);fflush(stdin);
	return op2;
}
int MenuGProdutos()
{
	int op2;
	system("cls"); // limpa a tela.
	printf("Gerenciamento de Produtos, Serviços e Insumos:\n");
	printf("\n1- Cadastrar Itens");
	printf("\n2- Editar Itens");
	printf("\n3- Excluir Itens");
	printf("\n4- Listar Itens");
	printf("\n5- Buscar Itens");

	printf("\n0- Voltar\n\n");
	scanf("%d",&op2);fflush(stdin);
	return op2;
}
int MenuGFornecedores()
{
	int op2;
	system("cls"); // limpa a tela.
	printf("Gerenciamento de Fornecedores:\n");
	printf("\n1- Cadastrar Fornecedores");
	printf("\n2- Editar Fornecedores");
	printf("\n3- Excluir Fornecedores");
	printf("\n4- Listar Fornecedores");
	printf("\n5- Buscar Fornecedores");
	printf("\n0- Voltar\n\n");
	scanf("%d",&op2);fflush(stdin);
	return op2;
}
int MenuGCompras()
{
	int op2;
	system("cls"); // limpa a tela.
	printf("Gerenciamento de Compras:\n");
	printf("\n1- Efetuar Compra");
	printf("\n2- Efetuar Devolução de Compra");
	printf("\n0- Voltar\n\n");
	scanf("%d",&op2);fflush(stdin);
	return op2;
}
int MenuGVendas()
{
	int op2;
	system("cls"); // limpa a tela.
	printf("Gerenciamento de Vendas:\n");
	printf("\n1- Efetuar Venda");
	printf("\n2- Efetuar Devolução de Vendas");
	printf("\n0- Voltar\n\n");
	scanf("%d",&op2);fflush(stdin);
	return op2;
}
int MenuGRelatorios()
{
	int op2;
	system("cls"); // limpa a tela.
	printf("Gerar Relatórios:\n");
	printf("\n1- Saldo de Produtos");
	printf("\n2- Saldo de Insumos");
	printf("\n3- Notas Emitidas");
	printf("\n4- Vendas Realizadas");
	printf("\n5- Compras Realizadas");
	printf("\n0- Voltar\n\n");
	scanf("%d",&op2);fflush(stdin);
	return op2;
}
int MenuCaixa()
{
	int op2;
	int CaixaStatus;
	system("cls");
	
	Caixa caixa;
	FILE *arq;
	arq = fopen("Caixa.bin","rb+");
	if(arq == NULL)
	{
		printf("Erro no arquivo Caixa\n");
	}
	else
	{
		fread(&caixa,sizeof(Caixa),1,arq);
		printf("Gerenciar Caixa\n\nDinheiro em caixa: %.2fR$\n",caixa.valcaixa);
		
	}
	fclose(arq);
	
	printf("1- Efetuar abertura de caixa\n2- Efetuar fechamento de caixa\n0- Voltar\n");
	CaixaStatus = VerificarCaixa();
	if(CaixaStatus ==1)
		printf("\nCAIXA ABERTO!");
	else
		printf("\nCAIXA FECHADO!");
	printf("\n\nOpção: ");
	scanf("%d",&op2);
	return op2;
}

main()
{
	setlocale(LC_ALL,"Portuguese");
	
	int op,op2; // OPCÃO DO MENU
	int CaixaStatus;
	
	InicializarCaixa();
	
	op = MenuPrincipal();
	while(op!=0)
	{
		switch (op)
		{
			case 1:
				op2 = MenuGCliente();
				while(op2 != 0)
				{
					switch(op2)
					{
						case 1: CadastrarCliente();
							break;
						case 2: EditarCliente();
							break;
						case 3: ExcluirCliente();
							break;
						case 4: ListarClientes();
							break;
						case 5: BuscarCliente();
							break;
							
						default: printf("Opção inválida!");
								 system("pause");
							break;
						case 0:break;
					}
					op2 = MenuGCliente();
				}
				break;
			case 2:
				op2 = MenuGProdutos();
				while(op2 != 0)
				{
					switch(op2)
					{
						case 1: CadastrarProduto();
							break;
						case 2: EditarProduto();
							break;
						case 3: ExcluirProduto();
							break;
						case 4: ListarProdutos();
							break;
						case 5: BuscarProduto();
							break;
						default: printf("Opção inválida!");
								 system("pause");
							break;
						case 0:break;
					}
					op2 = MenuGProdutos();
				}
				break;
			case 3:
				op2 = MenuGFornecedores();
				while(op2 != 0)
				{
					switch(op2)
					{
						case 1: CadastrarFornecedor();
							break;
						case 2: EditarFornecedor();
							break;
						case 3: ExcluirFornecedor();
							break;
						case 4: ListarFornecedores();
							break;
						case 5: BuscarFornecedor();
							break;
						default: printf("Opção inválida!");
								 system("pause");
							break;
						case 0:break;
					}
					op2 = MenuGFornecedores();
				}
				break;
			case 4:
				op2 = MenuGCompras();
				while(op2 != 0)
				{
					switch(op2)
					{
						case 1: CadastrarCompra();
							break;
						case 2: DevolucaoCompra();
							break;
						default: printf("Opção inválida!");
								 system("pause");
							break;
						case 0:break;
					}
					op2 = MenuGCompras();
				}
				break;
			case 5:
				op2 = MenuGVendas();
				while(op2 != 0)
				{
					switch(op2)
					{
						case 1: CadastrarVenda();
							break;
						case 2: DevolucaoVenda();
							break;
						default: printf("Opção inválida!");
								 system("pause");
							break;
						case 0:break;
					}
					op2 = MenuGVendas();
				}
			break;
			case 6:
				op2 = MenuGRelatorios();
				while(op2 != 0)
				{
					switch(op2)
					{
						case 1: RelatorioProd();
							break;
						case 2: RelatorioInsumo();
							break;
						case 3:	RelatorioNotas();
							break;
						case 4: RelatorioVendas();
							break;
						case 5: RelatorioCompras();
							break;
						default: printf("Opção inválida!");
								 system("pause");
								 break;
						case 0:break;
					}
					op2 = MenuGRelatorios();
				}
				break;
			case 7:
				op2 = MenuCaixa();
				
				while(op2!=0)
				{
					switch(op2)
					{
						case 1: AbrirCaixa();
							break;
						case 2: FecharCaixa();
							break;
						default: printf("Opção inválida!");
								 system("pause");
							break;
						case 0:break;
					}
					op2 = MenuCaixa();
				}
				break;
			default:printf("\nOpção Inválida\n");
					system("pause");
				break;
			case 0:break;
		}
   		system("cls");
		op = MenuPrincipal();
	}
	printf("Obrigado por usar nosso sistema! :D");
}
