//				DESENVOLVIDO POR
//				NIVALDO TARGINO

#include<stdio.h>
#include<locale.h>
#include<string.h>
#include<ctype.h>
#define MAXVENDA 5


void FormatarSTR(char *str);
void AtualizarSaldoCaixa(float valor);
void ApagarCampo();
	//////	CLIENTES   //////
typedef struct{
	char nome[101],estado[5],cidade[31],bairro[31],rua[51];
	char cpfc[13],cnpjc[16],telc[13],cepc[10],numc[7];
	int tipo;	// 1== CPF 2 == CNPJ
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
		do{
			do{
				system("cls");
				printf("Cadastro de Clientes\n\nEntre com o nome completo do cliente: (0 Para Voltar)");
				fgets(clt.nome,100,stdin);
				FormatarSTR(clt.nome);
				
				if(CampoVazio(clt.nome) && stricmp(clt.nome,"0")!=0)
				{
					printf("Campo Vazio!\n");
					system("pause");
					ApagarCampo();
				}
			}while(CampoVazio(clt.nome) && stricmp(clt.nome,"0")!=0);
			if(stricmp(clt.nome,"0")!=0)
			{
				printf("Entre com o Tipo de cliente:\n1- Pessoa Física\n2- Pessoa Jurídica\n0- Voltar\n");
				do{
					printf("Opção: ");
					scanf("%d",&clt.tipo);fflush(stdin);
					if(clt.tipo!=1 && clt.tipo!=2 && clt.tipo!=0)
					{
						printf("Opção Inválida!\n");
						system("pause");
						ApagarCampo();
					}
				}while(clt.tipo!=1 && clt.tipo!=2 && clt.tipo!=0);
			}
			else
				clt.tipo=0;
			if(clt.tipo!=0)
			{
				if(clt.tipo==1)
				{
					do{
						printf("CPF: ");
						fgets(clt.cpfc,13,stdin);
						FormatarSTR(clt.cpfc);
						
						if(!ValidarCPF(clt.cpfc))
						{
							printf("CPF Inválido!\n");
							system("pause");
							ApagarCampo();
						}
					}while(!ValidarCPF(clt.cpfc));
				}
				else
				{
					do{
						printf("CNPJ: ");
						fgets(clt.cnpjc,16,stdin);
						FormatarSTR(clt.cnpjc);
						
						if(!ValidarCNPJ(clt.cnpjc))
						{
							printf("CNPJ Inválido!\n");
							system("pause");
							ApagarCampo();
						}
					}while(!ValidarCNPJ(clt.cnpjc));
				}
				if(clt.tipo==1)
					pos = VerificarCliente(arq,clt.cpfc);
				else
					pos = VerificarClienteCNPJ(arq,clt.cnpjc);
				if(pos==-1)
				{
					do{
						printf("Telefone: ");
						fgets(clt.telc,13,stdin);
						FormatarSTR(clt.telc);
						
						if(!ValidarTel(clt.telc))
						{
							printf("Telefone Inválido!\n");
							system("pause");
							ApagarCampo();
						}
					}while(!ValidarTel(clt.telc));
					do{
						printf("CEP: ");
						fgets(clt.cepc,10,stdin);
						FormatarSTR(clt.cepc);
						
						if(!ValidarCep(clt.cepc))
						{
							printf("CEP Inválido!\n");
							system("pause");
							ApagarCampo();
						}
					}while(!ValidarCep(clt.cepc));
					
					do{
					printf("Estado(SP):");
					fgets(clt.estado,4,stdin);
					FormatarSTR(clt.estado);
					
					strupr(clt.estado);
					if(!ValidarEstado(clt.estado))
						{
							printf("Estado Inválido!\n");
							system("pause");
							ApagarCampo();
						}
					}while(!ValidarEstado(clt.estado));
					do{
						printf("Cidade: ");
						fgets(clt.cidade,30,stdin);
						if(CampoVazio(clt.cidade))
						{
							printf("Campo Vazio!\n");
							system("pause");
							ApagarCampo();
						}
					}while(CampoVazio(clt.cidade));
					
					do{
						printf("Bairro: ");
						fgets(clt.bairro,30,stdin);
						if(CampoVazio(clt.bairro))
						{
							printf("Campo Vazio!\n");
							system("pause");
							ApagarCampo();
						}
					}while(CampoVazio(clt.bairro));
					do{
						printf("Rua: ");
						fgets(clt.rua,50,stdin);
						if(CampoVazio(clt.rua))
						{
							printf("Campo Vazio!\n");
							system("pause");
							ApagarCampo();
						}
					}while(CampoVazio(clt.rua));
					do{
						printf("Número da Casa: ");
						fgets(clt.numc,7,stdin);
						FormatarSTR(clt.numc);
						
						if(!ValidarNum(clt.numc))
						{
							printf("Numero da casa inválido!\n");
							system("pause");
							ApagarCampo();
						}
					}while(!ValidarNum(clt.numc));
					fflush(stdin);
					fwrite(&clt,sizeof(DadosCliente),1,arq);
					printf("Cliente Cadastrado com Sucesso!\n");
					system("pause");
				}
				else
				{
					printf("\nCliente já cadastrado!\n\n");
					fseek(arq,pos,0);
					fread(&clt,sizeof(DadosCliente),1,arq);
					printf("Nome: %s\n",clt.nome);
					if(clt.tipo==1)
						printf("CPF: %s\n",clt.cpfc);
					else
						printf("CNPJ: %s\n",clt.cnpjc);
					printf("Telefone: %s\n",clt.telc);
					printf("CEP: %s\n",clt.cepc);
					printf("Estado: %s\n",clt.estado);
					printf("Cidade: %s",clt.cidade);
					printf("Bairro: %s",clt.bairro);
					printf("Rua: %s",clt.rua);
					printf("Número da Casa: %s\n",clt.numc);
					system("pause");
				}
			}
		}while(stricmp(clt.nome,"0")!=0);
		fclose(arq);
	}
}
void EditarCliente()
{
	DadosCliente clt;
	int pos,op,voltar=0;
	
	FILE *arq;
	arq = fopen("Clientes.bin","rb+");
	if(arq == NULL)
		printf("\nErro no arquivo");
	else
	{
		do 
		{
			do{
				voltar=0;
				system("cls");
				printf("Editar Clientes\n\nEntre com o tipo de cliente:\n1- Pessoa Física \n2- Pessoa Jurídica\n0- Voltar\n\nOpção: ");
				scanf("%d",&clt.tipo);fflush(stdin);
				if(clt.tipo<0 || clt.tipo>2)
				{
					printf("Opção Inválida!\n");
					system("pause");
					ApagarCampo();
				}
			}while(clt.tipo<0 || clt.tipo>2);
			if(clt.tipo==1)
			{
				do{
					voltar=0;
					printf("Entre com o CPF do cliente: (0 Para Voltar) ");
					fgets(clt.cpfc,13,stdin);
					FormatarSTR(clt.cpfc);
					
					if(!ValidarCPF(clt.cpfc) && stricmp(clt.cpfc,"0")!=0)
					{
						printf("CPF Inválido!\n");
						system("pause");
						ApagarCampo();
					}
					if(stricmp(clt.cpfc,"0")==0)
						voltar=1;
				}while(!ValidarCPF(clt.cpfc) && stricmp(clt.cpfc,"0")!=0);
			}
			if(clt.tipo==2)
			{
				do{
					voltar=0;
					printf("Entre com o CNPJ do cliente: (0 Para Voltar) ");
					fgets(clt.cnpjc,16,stdin);
					FormatarSTR(clt.cnpjc);
					
					if(!ValidarCNPJ(clt.cnpjc) && stricmp(clt.cnpjc,"0")!=0)
					{
						printf("CNPJ Inválido!\n");
						system("pause");
						ApagarCampo();
					}
					if(stricmp(clt.cnpjc,"0")==0)
						voltar=1;
				}while(!ValidarCNPJ(clt.cnpjc)&& stricmp(clt.cnpjc,"0")!=0);
			}
		
			if(clt.tipo!=0 && voltar==0)
			{
				if(clt.tipo==1)
					pos = VerificarCliente(arq,clt.cpfc);
				else
					pos = VerificarClienteCNPJ(arq,clt.cnpjc);
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
					
						printf("Editar Clientes\n\nNome: %s\n",clt.nome);
						if(clt.tipo==1)
							printf("CPF: %s\n",clt.cpfc);
						else
							printf("CNPJ: %s\n",clt.cnpjc);
						printf("Telefone: %s\n--Endereço:\n",clt.telc);
						printf("CEP: %s\n",clt.cepc);
						printf("Estado: %s\n",clt.estado);
						printf("Cidade: %s",clt.cidade);
						printf("Bairro: %s",clt.bairro);
						printf("Rua: %s",clt.rua);
						printf("Número: %s\n\n----\n",clt.numc);
						printf("\nDeseja alterar: \n 1- Nome \n 2- CPF/CNPJ\n 3- Telefone\n 4- Endereço\n 0- Voltar\n\n Opção: ");
						scanf("%d",&op);fflush(stdin);
						if(op == 1 || op == 2)
						{
							if (ClienteFezVenda(clt.cpfc)) {
						        printf("\nEste cliente já efetuou uma compra e não pode ter seu nome ou CPF Alterado!\n");
						        system("pause");
						        op = -1;
						    }
						    if (ClienteFezVendaCNPJ(clt.cnpjc)) {
						        printf("\nEste cliente já efetuou uma compra e não pode ter seu nome ou CNPJ Alterado!\n");
						        system("pause");
						        op = -1;
						    }
						}
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
							if(clt.tipo==1){
								do{
									printf("Novo CPF: ");
									fgets(clt.cpfc,13,stdin);
									FormatarSTR(clt.cpfc);
									
									if(!ValidarCPF(clt.cpfc))
									{
										printf("CPF Inválido!\n");
										system("pause");
										ApagarCampo();
									}
								}while(!ValidarCPF(clt.cpfc));
							}
							else{
								do{
									printf("Novo CNPJ: ");
									fgets(clt.cnpjc,16,stdin);
									FormatarSTR(clt.cnpjc);
									
									if(!ValidarCNPJ(clt.cnpjc))
									{
										printf("CNPJ Inválido!\n");
										system("pause");
										ApagarCampo();
									}
								}while(!ValidarCNPJ(clt.cnpjc)&& stricmp(clt.cnpjc,"0")!=0);
							}
							fseek(arq,pos,0);
							fwrite(&clt,sizeof(DadosCliente),1,arq);
							printf("CPF/CNPJ Alterado!\n");
							system("pause");
							system("cls");
							break;
						case 3:
							
							do{
								printf("Novo telefone: ");
								fgets(clt.telc,13,stdin);
								FormatarSTR(clt.telc);
								
								if(!ValidarTel(clt.telc))
								{
									printf("Telefone Inválido!\n");
									system("pause");
									ApagarCampo();
								}
							}while(!ValidarTel(clt.telc));
							
							fseek(arq,pos,0);
							fwrite(&clt,sizeof(DadosCliente),1,arq);
							printf("Telefone Alterado!\n");
							system("pause");
							system("cls");
							break;
						case 4:
							
							do{
								printf("CEP: ");
								fgets(clt.cepc,10,stdin);
								FormatarSTR(clt.cepc);
								
								if(!ValidarCep(clt.cepc))
								{
									printf("CEP Inválido!\n");
									system("pause");
									ApagarCampo();
								}
							}while(!ValidarCep(clt.cepc));
							do{
								printf("Estado(SP):");
								fgets(clt.estado,4,stdin);
								FormatarSTR(clt.estado);
								
							    strupr(clt.estado);
								if(!ValidarEstado(clt.estado))
								{
									printf("Estado Inválido!\n");
									system("pause");
									ApagarCampo();
								}
							}while(!ValidarEstado(clt.estado));
							
							do{
								printf("Cidade: ");
								fgets(clt.cidade,30,stdin);
								if(CampoVazio(clt.cidade))
								{
									printf("Campo Vazio!\n");
									system("pause");
									ApagarCampo();
								}
							}while(CampoVazio(clt.cidade));
							
							do{
								printf("Bairro: ");
								fgets(clt.bairro,50,stdin);
								if(CampoVazio(clt.bairro))
								{
									printf("Campo Vazio!\n");
									system("pause");
									ApagarCampo();
								}
							}while(CampoVazio(clt.bairro));
							
							do{
								printf("Rua: ");
								fgets(clt.rua,50,stdin);
								if(CampoVazio(clt.rua))
								{
									printf("Campo Vazio!\n");
									system("pause");
									ApagarCampo();
								}
							}while(CampoVazio(clt.rua));
							
							do{
								printf("Número da Casa: ");
								fgets(clt.numc,7,stdin);
								FormatarSTR(clt.numc);
								
								if(!ValidarNum(clt.numc))
								{
									printf("Numero da Casa no maximo 5 digitos!\n");
									system("pause");
									ApagarCampo();
								}
							}while(!ValidarNum(clt.numc));
							
							fseek(arq,pos,0);
							fwrite(&clt,sizeof(DadosCliente),1,arq);
							printf("Endereço Alterado!\n");
							system("pause");
							system("cls");
							break;
						default:printf("Opção Inválida");
								system("pause");
							break;
						case 0:break;
					}
				}
			}
		}while(clt.tipo!=0 || voltar!=0);
	}
	fclose(arq);
}
void ExcluirCliente()
{
	char conf;
	int pos;
	char cpfc[13],cnpjc[16];
	int voltar=0,tipo;
	
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
		do{
			do{
				voltar=0;
				system("cls");
				printf("Excluir Cliente\n\nEntre com o tipo de cliente:\n1- Pessoa Física \n2- Pessoa Jurídica\n0- Voltar\n\nOpção: ");
				scanf("%d",&tipo);fflush(stdin);
				if(tipo<0 || tipo>2)
				{
					printf("Opção Inválida!\n");
					system("pause");
				}
			}while(tipo<0 || tipo>2);
			if(tipo==1){
				do{
					voltar=0;
					printf("Entre com o CPF do cliente:(0 Para Voltar) ");
					fgets(cpfc,13,stdin);
					FormatarSTR(cpfc);
					
					if(!ValidarCPF(cpfc) && stricmp(cpfc,"0")!=0)
					{
						printf("CPF Inválido!\n");
						system("pause");
						ApagarCampo();
					}
					if(stricmp(cpfc,"0")==0)
						voltar=1;
				}while(!ValidarCPF(cpfc) && stricmp(cpfc,"0")!=0);
			}
			if(tipo==2){
				do{
					voltar=0;
					printf("Entre com o CNPJ do cliente:(0 Para Voltar) ");
					fgets(cnpjc,16,stdin);
					FormatarSTR(cnpjc);
					
					if(!ValidarCNPJ(cnpjc) && stricmp(cnpjc,"0")!=0)
					{
						printf("CNPJ Inválido!\n");
						system("pause");
						ApagarCampo();
					}
					if(stricmp(cnpjc,"0")==0)
						voltar=1;
				}while(!ValidarCNPJ(cnpjc) && stricmp(cnpjc,"0")!=0);
			}
			if(tipo!=0 && voltar==0)
			{
				if(tipo==1){
					pos = VerificarCliente(arqcliente,cpfc);
					if (ClienteFezVenda(cpfc)) {
				        printf("\nEste cliente já efetuou uma compra e não pode ser excluído!\n");
				        fclose(arqcliente);
				        system("pause");
				        return;
				    }
				}
				else{
					pos = VerificarClienteCNPJ(arqcliente,cnpjc);	
			    	if (ClienteFezVendaCNPJ(cnpjc)) {
				        printf("\nEste cliente já efetuou uma compra e não pode ser excluído!\n");
				        fclose(arqcliente);
				        system("pause");
				        return;
				    }
				}
			    
				if(pos == -1)
					printf("Cliente Inexistente!");
				else
				{
					fseek(arqcliente,pos,0);
					fread(&clt,sizeof(DadosCliente),1,arqcliente);
					
					do
					{
						system("cls");
						printf("Excluir Cliente\n\nNome: %s\n",clt.nome);
						if(clt.tipo==1)
							printf("CPF: %s\n",clt.cpfc);
						else
							printf("CNPJ: %s\n",clt.cnpjc);
						printf("Telefone: %s\n--Endereço:\n",clt.telc);
						printf("CEP: %s\n",clt.cepc);
						printf("Estado: %s\n",clt.estado);
						printf("Cidade: %s",clt.cidade);
						printf("Bairro: %s",clt.bairro);
						printf("Rua: %s",clt.rua);
						printf("Número: %s\n\n----\n",clt.numc);
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
								if(clt.tipo==1){
									if(stricmp(clt.cpfc,cpfc)!=0)
										fwrite(&clt,sizeof(DadosCliente),1,arqtemp);
									fread(&clt,sizeof(DadosCliente),1,arqcliente);
								}
								else{
									if(stricmp(clt.cnpjc,cnpjc)!=0)
										fwrite(&clt,sizeof(DadosCliente),1,arqtemp);
									fread(&clt,sizeof(DadosCliente),1,arqcliente);
								}
							}
							fclose(arqcliente);
							fclose(arqtemp);
							remove("Clientes.bin");
							rename("temp.bin","Clientes.bin");
							printf("Cliente excluido com sucesso!\n");
							system("pause");	
						}	
					}
					else
					{
						printf("Exclusão cancelada!\n");
						system("pause");
					}
				}
			}
		}while(tipo!=0);

	}
	
	fclose(arqcliente);
}
int VerificarCliente(FILE *arq, char *cpfc) //verifica se ja existe
{
	DadosCliente clt;
	rewind (arq);
	fread(&clt,sizeof(DadosCliente),1,arq);
	while(!feof(arq) && stricmp(clt.cpfc,cpfc) != 0)
	{
		fread(&clt,sizeof(DadosCliente),1,arq);
	}
	if(!feof(arq))
		return (ftell(arq)-sizeof(DadosCliente));
	else
		return -1;
}
int VerificarClienteCNPJ(FILE *arq, char *cnpj) //verifica se ja existe
{
	DadosCliente clt;
	rewind (arq);
	fread(&clt,sizeof(DadosCliente),1,arq);
	while(!feof(arq) && stricmp(clt.cnpjc,cnpj) != 0)
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
		printf("\nNenhum cliente cadastrado!");
	else
	{
		fread(&clt,sizeof(DadosCliente),1,arq);
		while(!feof(arq))
		{
			printf("Nome: %s\n",clt.nome);
			if(clt.tipo==1)
				printf("CPF: %s\n",clt.cpfc);
			else
				printf("CNPJ: %s\n",clt.cnpjc);
			printf("Telefone: %s\n",clt.telc);
			printf("CEP: %s\n",clt.cepc);
			printf("Estado: %s\n",clt.estado);
			printf("Cidade: %s",clt.cidade);
			printf("Bairro: %s",clt.bairro);
			printf("Rua: %s",clt.rua);
			printf("Número: %s\n\n----\n",clt.numc);
			fread(&clt,sizeof(DadosCliente),1,arq);
		}
		
	}
	fclose(arq);
	system("pause");
}
void BuscarCliente()
{
	DadosCliente clt;
	int pos,voltar=0;
	
	FILE *arq;
	arq = fopen("Clientes.bin","rb+");
	if(arq == NULL)
		printf("\nErro no arquivo");
	else
	{
		do{
			do{
				voltar=0;
				system("cls");
				printf("Buscar Cliente\n\nEntre com o tipo de cliente:\n1- Pessoa Física \n2- Pessoa Jurídica\n0- Voltar\n\nOpção: ");
				scanf("%d",&clt.tipo);fflush(stdin);
				if(clt.tipo<0 || clt.tipo>2)
				{
					printf("Opção Inválida!\n");
					system("pause");
				}
			}while(clt.tipo<0 || clt.tipo>2);
			if(clt.tipo==1){
				do{
					voltar=0;
					printf("Entre com o CPF do cliente:(0 Para Voltar) ");
					fgets(clt.cpfc,13,stdin);
					FormatarSTR(clt.cpfc);
					
					if(!ValidarCPF(clt.cpfc) && stricmp(clt.cpfc,"0")!=0)
					{
						printf("CPF Inválido!\n");
						system("pause");
						ApagarCampo();
					}
					if(stricmp(clt.cpfc,"0")==0)
						voltar=1;
				}while(!ValidarCPF(clt.cpfc) && stricmp(clt.cpfc,"0")!=0);
			}
			if(clt.tipo==2){
				do{
					voltar=0;
					printf("Entre com o CNPJ do cliente:(0 Para Voltar) ");
					fgets(clt.cnpjc,16,stdin);
					FormatarSTR(clt.cnpjc);
					
					if(!ValidarCNPJ(clt.cnpjc) && stricmp(clt.cnpjc,"0")!=0)
					{
						printf("CNPJ Inválido!\n");
						system("pause");
						ApagarCampo();
					}
					if(stricmp(clt.cnpjc,"0")==0)
						voltar=1;
				}while(!ValidarCNPJ(clt.cnpjc) && stricmp(clt.cnpjc,"0")!=0);
			}
			if(clt.tipo!=0 && voltar==0){
				if(clt.tipo==1)
					pos = VerificarCliente(arq,clt.cpfc);
				else
					pos = VerificarClienteCNPJ(arq,clt.cnpjc);
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
					printf("Nome: %s\n",clt.nome);
					if(clt.tipo==1)
						printf("CPF: %s\n",clt.cpfc);
					else
						printf("CNPJ: %s\n",clt.cnpjc);
					printf("Telefone: %s\n",clt.telc);
					printf("CEP: %s\n",clt.cepc);
					printf("Estado: %s\n",clt.estado);
					printf("Cidade: %s",clt.cidade);
					printf("Bairro: %s",clt.bairro);
					printf("Rua: %s",clt.rua);
					printf("Número: %s\n",clt.numc);
					system("pause");
				}
			}
		}while(clt.tipo!=0);
		fclose(arq);
	}
}
void OrdenarClientes()
{
	FILE *arq;
	DadosCliente clt,clti;
	int i,qtde=0;
	arq = fopen("Clientes.bin","rb+");
	if(arq == NULL)
	  printf("Nenhum cliente cadastrado!\n");
	else
	{
		fseek(arq,0,2);
		qtde=ftell(arq)/sizeof(DadosCliente);
		while(qtde>1)
		{
			for(i=0;i<qtde-1;i++)
			{
				fseek(arq,i*sizeof(DadosCliente),0);
				fread(&clt,sizeof(DadosCliente),1,arq);
				fseek(arq,(i+1)*sizeof(DadosCliente),0);
				fread(&clti,sizeof(DadosCliente),1,arq);
				if(stricmp(clt.nome,clti.nome)>0)
				{
					fseek(arq,i*sizeof(DadosCliente),0);
					fwrite(&clti,sizeof(DadosCliente),1,arq);
					fseek(arq,(i+1)*sizeof(DadosCliente),0);
					fwrite(&clt,sizeof(DadosCliente),1,arq);
				}
			}
			qtde--;
		}
		printf("\nArquivo ordenado\n");
	}
	fclose(arq);
	system("pause");	
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
		do{
		
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
				do{
					printf("Entre com o nome do Item:(0 Para Voltar) ");
					fgets(prod.nome,100,stdin);
					FormatarSTR(prod.nome);
					
					if(CampoVazio(prod.nome) && stricmp(prod.nome,"0")!=0)
					{
						printf("Campo Vazio!\n");
						system("pause");
						ApagarCampo();
					}
				}while(CampoVazio(prod.nome) && stricmp(prod.nome,"0")!=0);
				if(stricmp(prod.nome,"0")!=0)
				{
					printf("Código do Produto: ");
					scanf("%d",&prod.cod);fflush(stdin);
					pos = VerificarProduto(arq,prod.cod);
					if(pos==-1)
					{
						do{
							printf("Descrição do Item: ");
							fgets(prod.desc,50,stdin);
							if(CampoVazio(prod.desc))
							{
								printf("Campo Vazio!\n");
								system("pause");
								ApagarCampo();
							}
						}while(CampoVazio(prod.desc));
						
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
						printf("Nome: %s\n",prod.nome);
						printf("Descrição: %s",prod.desc);
						printf("Código: %d\n",prod.cod);
						printf("Preço: %.2fR$\n",prod.preco);
						printf("Quantidade em Estoque: %d\n",prod.qtd);
						system("pause");
					}
				}
			}
		}while(tipo!=0);
	}
	fclose(arq);
}
void EditarProduto()
{
	DadosProduto prod;
	int pos,op;
	
	FILE *arq;
	arq = fopen("Produtos.bin","rb+");
	if(arq == NULL)
	{
		printf("\nNenhum item cadastrado!\n");
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
					printf("Nome: %s\n",prod.nome);
					printf("Descrição: %s",prod.desc);
					printf("Código: %d\n",prod.cod);
					printf("Preço: %.2fR$\n----\n",prod.preco);
					printf("\nDeseja alterar: \n 1- Nome \n 2- Descrição\n 3- Código\n 4- Preço\n 0- Voltar\n\n Opção: ");
					scanf("%d",&op);fflush(stdin);
					if(ProdutoComVenda(prod.cod)&& (op==1 || op==3))
					{
						printf("O Produto: %s Possui venda cadastrada logo não pode ter seu Código ou Nome alterado!\n",prod.nome);
						system("pause");
						op=0;
					}
				}while(op<0 || op>4);
				if(op!=0)
					switch(op)
					{
						case 1:
							
							do{
								printf("Novo Nome: ");
								fgets(prod.nome,100,stdin);
								if(CampoVazio(prod.nome))
								{
									printf("Campo Vazio!\n");
									system("pause");
									ApagarCampo();
								}
							}while(CampoVazio(prod.nome));
							
							fseek(arq,pos,0);
							fwrite(&prod,sizeof(DadosProduto),1,arq);
							printf("Nome Alterado!\n");
							system("pause");
							system("cls");
							break;
						case 2:
							
							do{
								printf("Nova Descrição: ");
								fgets(prod.desc,50,stdin);
								if(CampoVazio(prod.desc))
								{
									printf("Campo Vazio!\n");
									system("pause");
									ApagarCampo();
								}
							}while(CampoVazio(prod.desc));
							
							fseek(arq,pos,0);
							fwrite(&prod,sizeof(DadosProduto),1,arq);
							printf("Descrição Alterada!\n");
							system("pause");
							system("cls");
							break;
						case 3:
							printf("Novo Código: ");
							scanf("%d",&prod.cod);fflush(stdin);
							fseek(arq,pos,0);
							fwrite(&prod,sizeof(DadosProduto),1,arq);
							printf("Código Alterado!\n");
							system("pause");
							system("cls");
							break;
						case 4:
							printf("Novo Preço: ");
							scanf("%f",&prod.preco);fflush(stdin);
							fseek(arq,pos,0);
							fwrite(&prod,sizeof(DadosProduto),1,arq);
							printf("Preço Alterado!\n");
							system("pause");
							system("cls");
							break;
						default: printf("Opção Inválida!\n");
								system("pause");
							break;
					}
			}
			system("cls");
			printf("Editar Produtos, Serviços e Insumos\n\nEntre com o cod do Produto/Serviço: (0 Para Sair)");
			scanf("%d",&prod.cod);
		}
		
	}
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
		printf("Nenhum item cadastrado!\n");
		system("pause");
	}
	else
	{
		
		do{
			system("cls");
			printf("Excluir Item\n\nTipo de Item:\n 1- Produto\n 2- Serviço\n 3- Insumo\n 0- Voltar\n\n Opção:");
			scanf("%d",&tipo);fflush(stdin);
			if(tipo<0 || tipo>3)
			{
				printf("Opção Inválida!\n");
				system("pause");
			}
		}while(tipo<0 || tipo>3);
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
					printf("Excluir Item\n\nNome: %s\n",prod.nome);
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
					
					if(ProdutoComVenda(prod.cod))
					{
						printf("O Produto: %s Possui venda cadastrada, logo não será possivel a exclusão!\n",prod.nome);
						conf='N';
					}
					else
					{
						printf("Confirma a exclusão do produto?(S/N) ");
						scanf(" %c",&conf);fflush(stdin);
						conf = toupper(conf);
					}
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
	do
	{
		system("cls");
		printf("Tipo de item:\n1- Produto\n2- Serviço\n3- Insumo\n0- Voltar\nOpção:");
		scanf("%d",&tipo);fflush(stdin);
		if(tipo<0 || tipo>3)
		{
			printf("Opção Inválida!\n");
			system("pause");
			ApagarCampo();
		}
	}while(tipo<0 || tipo>3);
	if(tipo!=0)
	{
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
			printf("\nNenhum item cadastrado!\n");
			system("pause");
		}
		else
		{
			fread(&prod,sizeof(DadosProduto),1,arq);
			while(!feof(arq))
			{
				if(tipo==prod.tipo)
				{
					printf("Nome: %s\n",prod.nome);
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
		
		do{
			system("cls");
			printf("Buscar Produtos, Serviços e Insumos\n\nEntre com o Código do Item:(0 Para Voltar) ");
			scanf("%d",&prod.cod);
			if(prod.cod!=0)
			{
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
					printf("Nome: %s\n",prod.nome);
					printf("Descrição: %s",prod.desc);
					printf("Código: %d\n",prod.cod);
					printf("Preço: %.2fR$\n",prod.preco);
					printf("Quantidade: %d\n",prod.qtd);
					system("pause");
				}
			}
		}while(prod.cod!=0);
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
void OrdenarProdutos()
{
	FILE *arq;
	DadosProduto clt,clti;
	int i,qtde=0;
	arq = fopen("Produtos.bin","rb+");
	if(arq == NULL)
	  return;
	else
	{
		fseek(arq,0,2);
		qtde=ftell(arq)/sizeof(DadosProduto);
		while(qtde>1)
		{
			for(i=0;i<qtde-1;i++)
			{
				fseek(arq,i*sizeof(DadosProduto),0);
				fread(&clt,sizeof(DadosProduto),1,arq);
				fseek(arq,(i+1)*sizeof(DadosProduto),0);
				fread(&clti,sizeof(DadosProduto),1,arq);
				if(stricmp(clt.nome,clti.nome)>0)
				{
					fseek(arq,i*sizeof(DadosProduto),0);
					fwrite(&clti,sizeof(DadosProduto),1,arq);
					fseek(arq,(i+1)*sizeof(DadosProduto),0);
					fwrite(&clt,sizeof(DadosProduto),1,arq);
				}
			}
			qtde--;
		}
	}
	fclose(arq);
}
void OrdenarProdutosQtd(int menor)
{
	FILE *arq;
	DadosProduto clt,clti;
	int i,qtde=0;
	arq = fopen("Produtos.bin","rb+");
	if(arq == NULL)
	  return;
	else
	{
		fseek(arq,0,2);
		qtde=ftell(arq)/sizeof(DadosProduto);
		while(qtde>1)
		{
			for(i=0;i<qtde-1;i++)
			{
				fseek(arq,i*sizeof(DadosProduto),0);
				fread(&clt,sizeof(DadosProduto),1,arq);
				fseek(arq,(i+1)*sizeof(DadosProduto),0);
				fread(&clti,sizeof(DadosProduto),1,arq);
				if(menor)
				{
					if(clt.qtd>clti.qtd)// Ordena menor pro maior
					{
						fseek(arq,i*sizeof(DadosProduto),0);
						fwrite(&clti,sizeof(DadosProduto),1,arq);
						fseek(arq,(i+1)*sizeof(DadosProduto),0);
						fwrite(&clt,sizeof(DadosProduto),1,arq);
					}
				}
				else
				{
					if(clt.qtd<clti.qtd) /// Ordena maior pro menor
					{
						fseek(arq,i*sizeof(DadosProduto),0);
						fwrite(&clti,sizeof(DadosProduto),1,arq);
						fseek(arq,(i+1)*sizeof(DadosProduto),0);
						fwrite(&clt,sizeof(DadosProduto),1,arq);
					}
				}
			}
			qtde--;
		}
	}
	fclose(arq);	
}

	//////  FORNECEDORES  //////
	
typedef struct{
	char nome[101],categ[51],estado[5],cidade[31],bairro[31],rua[51];
	char cnpjc[16],cepc[10],numc[7];
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
		do{
			do{
				system("cls");
				printf("Cadastro de Fornecedores\n\nEntre com o nome do Fornecedor:(0 Para Voltar) ");
				fgets(fornecedor.nome,100,stdin);
				FormatarSTR(fornecedor.nome);
				
				if(CampoVazio(fornecedor.nome) && stricmp(fornecedor.nome,"0")!=0)
				{
					printf("Campo Vazio!\n");
					system("pause");
				}
			}while(CampoVazio(fornecedor.nome) && stricmp(fornecedor.nome,"0")!=0);
			if(stricmp(fornecedor.nome,"0")!=0)
			{
				do{
					printf("CNPJ: ");
					fgets(fornecedor.cnpjc,16,stdin);
					FormatarSTR(fornecedor.cnpjc);
					
					if(!ValidarCNPJ(fornecedor.cnpjc))
					{
						printf("CNPJ Inválido!\n");
						system("pause");
						ApagarCampo();
					}
				}while(!ValidarCNPJ(fornecedor.cnpjc));
				
				pos = VerificarFornecedor(arq,fornecedor.cnpjc);
				if(pos==-1)
				{
					do{
					printf("Categoria de Produtos: ");
					fgets(fornecedor.categ,50,stdin);
					if(CampoVazio(fornecedor.categ))
					{
						printf("Campo Vazio!\n");
						system("pause");
						ApagarCampo();
					}
				}while(CampoVazio(fornecedor.categ));
					
					do{
						printf("CEP: ");
						fgets(fornecedor.cepc,10,stdin);
						FormatarSTR(fornecedor.cepc);
						
						if(!ValidarCep(fornecedor.cepc))
						{
							printf("CEP Inválido!\n");
							system("pause");
							ApagarCampo();
						}
					}while(!ValidarCep(fornecedor.cepc));
					
					do{
						printf("Estado(SP):");
						fgets(fornecedor.estado,4,stdin);
						FormatarSTR(fornecedor.estado);
						
					    strupr(fornecedor.estado);
						if(!ValidarEstado(fornecedor.estado))
						{
							printf("Estado Inválido!\n");
							system("pause");
							ApagarCampo();
						}
					}while(!ValidarEstado(fornecedor.estado));
					
					do{
						printf("Cidade: ");
						fgets(fornecedor.cidade,30,stdin);
						if(CampoVazio(fornecedor.cidade))
						{
							printf("Campo Vazio!\n");
							system("pause");
							ApagarCampo();
						}
					}while(CampoVazio(fornecedor.cidade));
					
					do{
						printf("Bairro: ");
						fgets(fornecedor.bairro,30,stdin);
						if(CampoVazio(fornecedor.bairro))
						{
							printf("Campo Vazio!\n");
							system("pause");
							ApagarCampo();
						}
					}while(CampoVazio(fornecedor.bairro));
					
					do{
						printf("Rua: ");
						fgets(fornecedor.rua,50,stdin);
						if(CampoVazio(fornecedor.rua))
						{
							printf("Campo Vazio!\n");
							system("pause");
							ApagarCampo();
						}
					}while(CampoVazio(fornecedor.rua));
					
					do{
						printf("Número: ");
						fgets(fornecedor.numc,7,stdin);
						FormatarSTR(fornecedor.numc);
						
						if(!ValidarNum(fornecedor.numc))
						{
							printf("Numero da Casa no maximo 5 digitos!\n");
							system("pause");
							ApagarCampo();
						}
					}while(!ValidarNum(fornecedor.numc));
					
					fwrite(&fornecedor,sizeof(DadosFornecedor),1,arq);
					printf("Fornecedor Cadastrado com Sucesso!\n");
					system("pause");
				}
				else
				{
					printf("\nFornecedor já cadastrado!\n\n");
					fseek(arq,pos,0);
					fread(&fornecedor,sizeof(DadosFornecedor),1,arq);
					printf("Nome: %s\n",fornecedor.nome);
					printf("CNPJ: %s\n",fornecedor.cnpjc);
					printf("Categoria: %s",fornecedor.categ);
					printf("CEP: %s\n",fornecedor.cepc);
					printf("Estado: %s\n",fornecedor.estado);
					printf("Cidade: %s",fornecedor.cidade);
					printf("Bairro: %s",fornecedor.bairro);
					printf("Rua: %s",fornecedor.rua);
					printf("Número: %s\n",fornecedor.numc);
					
					system("pause");
				}
			}
		}while(stricmp(fornecedor.nome,"0")!=0);
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
		do{
			system("cls");
			printf("Editar Fornecedor\n\nEntre com o CNPJ do Fornecedor: (0 Para Sair) ");
			fgets(fornecedor.cnpjc,16,stdin);
			FormatarSTR(fornecedor.cnpjc);
			
			if(!ValidarCNPJ(fornecedor.cnpjc) && stricmp(fornecedor.cnpjc,"0")!=0)
			{
				printf("CNPJ Inválido!\n");
				system("pause");
			}
		}while(!ValidarCNPJ(fornecedor.cnpjc) && stricmp(fornecedor.cnpjc,"0")!=0);
		
		while(stricmp(fornecedor.cnpjc,"0")!=0)
		{
			pos = VerificarFornecedor(arq,fornecedor.cnpjc);
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
					printf("Editar Fornecedor\n\nNome: %s\n",fornecedor.nome);
					printf("CNPJ: %s\n",fornecedor.cnpjc);
					printf("Categoria: %s--Endereço:\n",fornecedor.categ);
					printf("CEP: %s\n",fornecedor.cepc);
					printf("Estado: %s\n",fornecedor.estado);
					printf("Cidade: %s",fornecedor.cidade);
					printf("Bairro: %s",fornecedor.bairro);
					printf("Rua: %s",fornecedor.rua);
					printf("Número: %s\n",fornecedor.numc);
					printf("\nDeseja alterar: \n 1- Nome \n 2- CNPJ\n 3- Categoria\n 4- Endereço\n 0- Voltar\n\n Opção: ");
					scanf("%d",&op);fflush(stdin);
				}while(op<0 || op>4);
				if(op!=0)
					switch(op)
					{
						case 1:
							do{
								printf("Novo Nome: ");
								fgets(fornecedor.nome,100,stdin);
								if(CampoVazio(fornecedor.nome))
								{
									printf("Campo Vazio!\n");
									system("pause");
									ApagarCampo();
								}
							}while(CampoVazio(fornecedor.nome));
							
							fseek(arq,pos,0);
							fwrite(&fornecedor,sizeof(DadosFornecedor),1,arq);
							printf("Nome Alterado!\n");
							system("pause");
							system("cls");
							break;
						case 2:
							do{
								printf("Novo CNPJ: ");
								fgets(fornecedor.cnpjc,16,stdin);
								FormatarSTR(fornecedor.cnpjc);
								
								if(!ValidarCNPJ(fornecedor.cnpjc))
								{
									printf("CNPJ Inválido!\n");
									system("pause");
									ApagarCampo();
								}
							}while(!ValidarCNPJ(fornecedor.cnpjc));
							
							fseek(arq,pos,0);
							fwrite(&fornecedor,sizeof(DadosFornecedor),1,arq);
							printf("CNPJ Alterado!");
							system("pause");
							system("cls");
							break;
						case 3:
							do{
								printf("Nova Categoria: ");
								fgets(fornecedor.categ,100,stdin);
								if(CampoVazio(fornecedor.categ))
								{
									printf("Campo Vazio!\n");
									system("pause");
									ApagarCampo();
								}
							}while(CampoVazio(fornecedor.categ));
							
							fseek(arq,pos,0);
							fwrite(&fornecedor,sizeof(DadosFornecedor),1,arq);
							printf("Categoria Alterada!\n");
							system("pause");
							system("cls");
							break;
						case 4:
							do{
								printf("Novo CEP: ");
								fgets(fornecedor.cepc,10,stdin);
								FormatarSTR(fornecedor.cepc);
								
								if(!ValidarCep(fornecedor.cepc))
								{
									printf("CEP Inválido!\n");
									system("pause");
									ApagarCampo();
								}
							}while(!ValidarCep(fornecedor.cepc));
							
							do{
								printf("Estado(SP):");
								fgets(fornecedor.estado,4,stdin);
								FormatarSTR(fornecedor.estado);
								
							    strupr(fornecedor.estado);
								if(!ValidarEstado(fornecedor.estado))
								{
									printf("Estado Inválido!\n");
									system("pause");
									ApagarCampo();
								}
							}while(!ValidarEstado(fornecedor.estado));
							
							do{
								printf("Cidade: ");
								fgets(fornecedor.cidade,30,stdin);
								if(CampoVazio(fornecedor.cidade))
								{
									printf("Campo Vazio!\n");
									system("pause");
									ApagarCampo();
								}
							}while(CampoVazio(fornecedor.cidade));
							
							do{
								printf("Bairro: ");
								fgets(fornecedor.bairro,30,stdin);
								if(CampoVazio(fornecedor.bairro))
								{
									printf("Campo Vazio!\n");
									system("pause");
									ApagarCampo();
								}
							}while(CampoVazio(fornecedor.bairro));
							
							do{
								printf("Rua: ");
								fgets(fornecedor.rua,50,stdin);
								if(CampoVazio(fornecedor.rua))
								{
									printf("Campo Vazio!\n");
									system("pause");
									ApagarCampo();
								}
							}while(CampoVazio(fornecedor.rua));
							
							do{
								printf("Número: ");
								fgets(fornecedor.numc,7,stdin);
								FormatarSTR(fornecedor.numc);
								
								if(!ValidarNum(fornecedor.numc))
								{
									printf("Numero da Casa no maximo 5 digitos!\n");
									system("pause");
									ApagarCampo();
								}
							}while(!ValidarNum(fornecedor.numc));
							
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
			do{
				system("cls");
				printf("Editar Fornecedor\n\nEntre com o CNPJ do Fornecedor: (0 Para Sair) ");
				fgets(fornecedor.cnpjc,16,stdin);
				FormatarSTR(fornecedor.cnpjc);
				
				if(!ValidarCNPJ(fornecedor.cnpjc) && stricmp(fornecedor.cnpjc,"0")!=0)
				{
					printf("CNPJ Inválido!\n");
					system("pause");
				}
			}while(!ValidarCNPJ(fornecedor.cnpjc) && stricmp(fornecedor.cnpjc,"0")!=0);
			
		}
	}
	fclose(arq);
}
void ExcluirFornecedor()
{
	char conf;
	int pos,cnpj;
	char cnpjc[16];
	
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
		do{
			system("cls");
			printf("Excluir Fornecedor\n\nEntre com o CNPJ do Fornecedor:(0 Para Voltar) ");
			fgets(cnpjc,16,stdin);
			FormatarSTR(cnpjc);
			
			if(!ValidarCNPJ(cnpjc) && stricmp(cnpjc,"0")!=0)
			{
				printf("CNPJ Inválido!\n");
				system("pause");
			}
		}while(!ValidarCNPJ(cnpjc) && stricmp(cnpjc,"0")!=0);
		if(stricmp(cnpjc,"0")!=0)
		{
			pos = VerificarFornecedor(arqforn,cnpjc);
			if(pos == -1)
				printf("Fornecedor Inexistente!");
			else
			{
				fseek(arqforn,pos,0);
				fread(&fornecedor,sizeof(DadosFornecedor),1,arqforn);
				
				do
				{
					system("cls");
					printf("Excluir Fornecedor\n\nNome: %s\n",fornecedor.nome);
					printf("CNPJ: %s\n",fornecedor.cnpjc);
					printf("Categoria: %s--Endereço:\n",fornecedor.categ);
					printf("CEP: %s\n",fornecedor.cepc);
					printf("Estado: %s\n",fornecedor.estado);
					printf("Cidade: %s",fornecedor.cidade);
					printf("Bairro: %s",fornecedor.bairro);
					printf("Rua: %s",fornecedor.rua);
					printf("Número: %s\n",fornecedor.numc);
					
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
							if(stricmp(fornecedor.cnpjc,cnpjc)!=0)//fornecedor.cnpj != cnpj)
								fwrite(&fornecedor,sizeof(DadosFornecedor),1,arqtemp);
							fread(&fornecedor,sizeof(DadosFornecedor),1,arqforn);
						}
						fclose(arqforn);
						fclose(arqtemp);
						remove("Fornecedores.bin");
						rename("temp.bin","Fornecedores.bin");
						printf("Fornecedor excluido com sucesso!\n");	
						system("pause");
					}	
				}
				else{
					printf("Exclusão Cancelada!\n");
					system("pause");
				}
			}
		}
	}
	fclose(arqforn);
}
int VerificarFornecedor(FILE *arq, char *cnpjc)
{
	DadosFornecedor fornecedor;
	rewind (arq);
	fread(&fornecedor,sizeof(DadosFornecedor),1,arq);
	while(!feof(arq) && stricmp(fornecedor.cnpjc,cnpjc)!=0)//fornecedor.cnpj!=cnpj )
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
			printf("Nome: %s\n",fornecedor.nome);
			printf("CNPJ: %s\n",fornecedor.cnpjc);
			printf("Categoria: %s--Endereço:\n",fornecedor.categ);
			printf("CEP: %s\n",fornecedor.cepc);
			printf("Estado: %s\n",fornecedor.estado);
			printf("Cidade: %s",fornecedor.cidade);
			printf("Bairro: %s",fornecedor.bairro);
			printf("Rua: %s",fornecedor.rua);
			printf("Número: %s\n-----\n\n",fornecedor.numc);
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
		do{
			system("cls");
			printf("Buscar Fornecedor\n\nEntre com o CNPJ do Fornecedor:(0 Para Voltar) ");
			fgets(fornecedor.cnpjc,16,stdin);
			FormatarSTR(fornecedor.cnpjc);
			
			if(!ValidarCNPJ(fornecedor.cnpjc) && stricmp(fornecedor.cnpjc,"0")!=0)
			{
				printf("CNPJ Inválido!\n");
				system("pause");
			}
		}while(!ValidarCNPJ(fornecedor.cnpjc) && stricmp(fornecedor.cnpjc,"0")!=0);
		if(stricmp(fornecedor.cnpjc,"0")!=0)
		{
			pos = VerificarFornecedor(arq,fornecedor.cnpjc);
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
				printf("Nome: %s\n",fornecedor.nome);
				printf("CNPJ: %s\n",fornecedor.cnpjc);
				printf("Categoria: %s",fornecedor.categ);
				printf("CEP: %s\n",fornecedor.cepc);
				printf("Estado: %s\n",fornecedor.estado);
				printf("Cidade: %s",fornecedor.cidade);
				printf("Bairro: %s",fornecedor.bairro);
				printf("Rua: %s",fornecedor.rua);
				printf("Número: %s\n\n",fornecedor.numc);
				system("pause");
			}
		}
		fclose(arq);
	}
}
void OrdenarFornecedores()
{
	FILE *arq;
	DadosFornecedor clt,clti;
	int i,qtde=0;
	arq = fopen("Fornecedores.bin","rb+");
	if(arq == NULL)
	  printf("Nenhum Fornecedor cadastrado!\n");
	else
	{
		fseek(arq,0,2);
		qtde=ftell(arq)/sizeof(DadosFornecedor);
		while(qtde>1)
		{
			for(i=0;i<qtde-1;i++)
			{
				fseek(arq,i*sizeof(DadosFornecedor),0);
				fread(&clt,sizeof(DadosFornecedor),1,arq);
				fseek(arq,(i+1)*sizeof(DadosFornecedor),0);
				fread(&clti,sizeof(DadosFornecedor),1,arq);
				if(stricmp(clt.nome,clti.nome)>0)
				{
					fseek(arq,i*sizeof(DadosFornecedor),0);
					fwrite(&clti,sizeof(DadosFornecedor),1,arq);
					fseek(arq,(i+1)*sizeof(DadosFornecedor),0);
					fwrite(&clt,sizeof(DadosFornecedor),1,arq);
				}
			}
			qtde--;
		}
		printf("Arquivo Ordenado!\n");
	}
	fclose(arq);
	system("pause");
}

		
	//////  COMPRAS  //////
typedef struct{
	int EstaDevolvido[MAXVENDA];
	int cod[MAXVENDA];
	int qtd[MAXVENDA];
	char motivo[MAXVENDA][101];//Motivo de devolução
	int qtdCarrinho;
}ItensDevCompra;

typedef struct{
	char nomeprod[MAXVENDA][101];
	int cod[MAXVENDA];
	int qtd[MAXVENDA];
	int qtdCarrinho;		//Quantidade de itens no carrinho
	float valorUni[MAXVENDA];
	float totalProd[MAXVENDA];
	float totalCompra;
}ItensCompra;

typedef struct{
	int dia,mes,ano;
}DataCompra;
typedef struct{
	char cnpjc[16];
	char fornecedor[101],MetPag[21];
	int CodNota;
	DataCompra dma;
	ItensCompra itens;
	ItensDevCompra devolucao;
}Compra;
int ProximaNotaCompra()
{
	int maiornota = 0;
	Compra compra;
	
	FILE *arqcompra;
	arqcompra = fopen("Compras.bin","rb");
	if(arqcompra == NULL)
	{
		printf("Erro no arquivo Compras!(PROX NOTA)");
		system("pause");
		return 20250001;
	}
	else
	{
		fread(&compra,sizeof(Compra),1,arqcompra);
		while(!feof(arqcompra))
		{
			if(compra.CodNota > maiornota)
				maiornota = compra.CodNota;
			fread(&compra,sizeof(Compra),1,arqcompra);
		}
		if(maiornota < 20250000)
			maiornota += 20250000;
		fclose(arqcompra);
		return maiornota + 1;
	}
	fclose(arqcompra);
}

ItensCompra AdicionarItemCompra(ItensCompra itens)
{
	DadosProduto prod;
	
	int posprod,i;
	int voltar=0;
	
	FILE *arqprod;
	arqprod = fopen("Produtos.bin","rb");
	if(arqprod == NULL)
	{
		printf("Erro no arquivo produtos");
		system("pause");
	}
	else
	{
		do{
			voltar = 0;
			system("cls");
			printf("Efetuar Compra\n\nCódigo do Produto: (0 Para voltar)");
			scanf("%d",&itens.cod[itens.qtdCarrinho]);
			if(itens.cod[itens.qtdCarrinho]!=0){
				posprod = VerificarProduto(arqprod,itens.cod[itens.qtdCarrinho]);
				if(posprod == -1)
				{
					printf("Produto/Serviço Inexistente!\n");
					system("pause");
					ApagarCampo();
				}
			}
			for(i=0;i<itens.qtdCarrinho;i++)
			{
				if(itens.cod[itens.qtdCarrinho] == itens.cod[i]){
					printf("O item que escolheu já está no carrinho! Para editar a quantidade faça uma nova compra!\n");
					system("pause");
					itens.cod[itens.qtdCarrinho] = 0;
					voltar=1;
				}
			}
			if(itens.cod[itens.qtdCarrinho]==0)
				voltar = 1;
		}while(posprod==-1 && voltar == 0);
		if(voltar==0)
		{
			//do{
			do{
				printf("Quantidade: ");
				scanf("%d",&itens.qtd[itens.qtdCarrinho]);fflush(stdin);
				if(itens.qtd[itens.qtdCarrinho]<1)
				{
					printf("Favor inserir quantidade maior que zero!\n");
					system("pause");
					ApagarCampo();
				}
			}while(itens.qtd[itens.qtdCarrinho] < 1);
			
			fseek(arqprod,posprod,0);
			fread(&prod,sizeof(DadosProduto),1,arqprod);
			strcpy(itens.nomeprod[itens.qtdCarrinho] , prod.nome);
			itens.valorUni[itens.qtdCarrinho] = prod.preco;
			itens.totalProd[itens.qtdCarrinho] = prod.preco*itens.qtd[itens.qtdCarrinho];
			
			itens.totalCompra += itens.totalProd[itens.qtdCarrinho];
		}
		fclose(arqprod);
		return itens;
	}
}

void CadastrarCompra()
{
	DadosFornecedor fornecedor;
	DadosProduto prod;
	Compra compra;
	int posforn,posprod;
	int cnpj,cod,qtd,pag,i;				// pag = Método de pagamento:\n\n1- Pix\n2- Cartão crédito\n3- Cartão débito\n4- Dinheiro
	char conf,MetPag[21];
	
	int StatusCaixa;
	StatusCaixa = VerificarCaixa();
	if(StatusCaixa == 0)
	{
		system("cls");
		printf("Efetuar Compra\n\nCaixa está fechado! Favor abrir o caixa antes de operar!\n");
		system("pause");
	}
	else
	{
		FILE *arqcompra;
		arqcompra = fopen("Compras.bin","ab+");
		if(arqcompra == NULL){
			printf("Erro no arquivo Compras!\n");
			system("pause");
			return;
		}
		do{
			do{
				system("cls");
				printf("Efetuar Compra\n\nEntre com o CNPJ do Fornecedor: (0 Para Voltar) ");
				fgets(compra.cnpjc,16,stdin);
				FormatarSTR(compra.cnpjc);
				
				if(!ValidarCNPJ(compra.cnpjc) && stricmp(compra.cnpjc,"0")!=0)
				{
					printf("CNPJ Inválido!\n");
					system("pause");
				}
			}while(!ValidarCNPJ(compra.cnpjc) && stricmp(compra.cnpjc,"0")!=0);
			
			if(stricmp(compra.cnpjc,"0")!=0)
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
					posforn = VerificarFornecedor(arqforn,compra.cnpjc);
					if(posforn == -1){
						printf("Fornecedor Inexistente!\n");
						system("pause");
					}
					else
					{
						fseek(arqforn,posforn,0);
						fread(&fornecedor,sizeof(DadosFornecedor),1,arqforn);
						compra.itens.qtdCarrinho = 0;
						compra.itens.totalCompra = 0;
						do{	//qtdCarrinho comeca com 0
							compra.itens = AdicionarItemCompra(compra.itens);
							if(compra.itens.cod[compra.itens.qtdCarrinho]!=0)
								compra.itens.qtdCarrinho++;
							
							if(compra.itens.cod[0]!=0)
							{
								system("cls");
								printf("Efetuar Compra\n\nItens no carrinho:\n\n");
								
								for(i=0;i<compra.itens.qtdCarrinho;i++)
								{
									printf("Item: %s\n",compra.itens.nomeprod[i]);
									printf("Código: %d\n",compra.itens.cod[i]);
									printf("Quantidade: %d\n",compra.itens.qtd[i]);
									printf("Valor Unitário: %.2fR$\n",compra.itens.valorUni[i]);
									printf("Total do Produto: %.2fR$\n---\n",compra.itens.totalProd[i]);
								}
								printf("Total da Compra: %.2fR$\n",compra.itens.totalCompra);
								
							}
							do{						
								printf("Deseja adicionar outro item a compra?(S/N/ C Para cancelar) ");
								scanf(" %c",&conf);fflush(stdin);
								conf = toupper(conf);
								if(conf=='S' && compra.itens.qtdCarrinho==MAXVENDA)
								{
									printf("O carrinho está cheio! Favor finalizar compra ou cancelar!\n");
									system("pause");
									ApagarCampo();
									conf='Z';
								}
								if(compra.itens.cod[0]==0 && conf=='N')
								{
									printf("O carrinho está vazio! Favor ou cancelar a compra ou adicionar item!\n");
									system("pause");
									ApagarCampo();
									conf='Z';
								}
								if(conf!='N' && conf!='S' && conf!='C' && conf!='Z')
								{
									printf("Opção inválida!\n");
									system("pause");
									ApagarCampo();
								}
							}while(conf!='N' && conf!='S' && conf!='C');
							if(conf=='C')
								printf("saiucccccc");
								
						}while(conf=='S');
						if(conf=='N')
						{
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
							printf("Efetuar Compra\n\nData da Compra:");
							do{
								printf("Dia: ");
								scanf("%d",&compra.dma.dia);
								if(compra.dma.dia<1 || compra.dma.dia>31)
								{
									printf("Dia inválido!\n");
									system("pause");
									ApagarCampo();
								}
							}while(compra.dma.dia<1 || compra.dma.dia>31);
							do{
								printf("Mês: ");
								scanf("%d",&compra.dma.mes);
								if(compra.dma.mes<1 || compra.dma.mes>12)
								{
									printf("Mês inválido!\n");
									system("pause");
									ApagarCampo();
								}
							}while(compra.dma.mes<1 || compra.dma.mes>12);
							do{
								printf("Ano: ");
								scanf("%d",&compra.dma.ano);
								if(compra.dma.ano<2020 || compra.dma.ano>2025)
								{
									printf("Ano inválido, Por favor escolha entre 2020 e 2025!\n");
									system("pause");
									ApagarCampo();
								}
							}while(compra.dma.ano<2020 || compra.dma.ano>2025);
							
							compra.CodNota = ProximaNotaCompra();
							
							system("cls");
							printf("Dados da Compra:\n\nFornecedor: %s\nData da Venda: %d/%d/%d\nMétodo de Pagamento: %s\n\nItens no carrinho:\n\n",fornecedor.nome,compra.dma.dia,compra.dma.mes,compra.dma.ano,compra.MetPag);
							for(i=0;i<compra.itens.qtdCarrinho;i++)
							{
								printf("Item: %s\n",compra.itens.nomeprod[i]);
								printf("Quantidade: %d\n",compra.itens.qtd[i]);
								printf("Valor Unitário: %.2fR$\n",compra.itens.valorUni[i]);
								printf("Total do Produto: %.2fR$\n---\n",compra.itens.totalProd[i]);
							}
							printf("Total da Compra: %.2fR$\nNota Fiscal: %d\n\n",compra.itens.totalCompra,compra.CodNota);
							do{
								printf("Confirma a Compra? (S/N)");
								scanf(" %c",&conf);fflush(stdin);
								conf = toupper(conf);
								if(conf!='S' && conf != 'N')
								{
									printf("Opção inválida!\n");
									system("pause");
									ApagarCampo();
								}
							}while(conf!='S' && conf != 'N');
							switch(conf)
							{
								case 'S':printf(" Compra Concluida!\n");
										 strcpy(compra.fornecedor,fornecedor.nome);		
										 									 
										 fwrite(&compra,sizeof(Compra),1,arqcompra);  /// CADASTRANDO COMPRA
										 
										 for(i=0;i<compra.itens.qtdCarrinho;i++)
										 	AtualizarEstoque(compra.itens.cod[i],compra.itens.qtd[i]);	///ATUALIZANDO ESTOQUE
										 	
										 AtualizarSaldoCaixa(compra.itens.totalCompra);		//ATUALIZANDO CAIXA
									 	 
										 system("pause");
										 system("cls");
									break;
								case 'N':printf(" Compra Cancelada!\n");
									system("pause");
									break;
								default:printf(" Opção Inválida!\n");
									system("pause");
									break;
							}
						}
					}
				}
				fclose(arqforn);
			}
		}while(stricmp(compra.cnpjc,"0")!=0);
	fclose(arqcompra);
	}
}

void DevolucaoCompra()
{
	DadosFornecedor forn;
	Compra compra;
	int StatusCaixa;
	char cnpjc[16];
	int pos,poscompra,cont=0,nota,achou=0,qtd,qtdDev;
	int VcomDevolucao=0;
	int voltar=0,i,codCancel;
	char conf;
	
	FILE *arqforn;
	arqforn = fopen("Fornecedores.bin","rb");
	if(arqforn == NULL)
	{
		printf("Erro no arquivo Fornecedores!\n");
		system("pause");
		return;
	}
	StatusCaixa = VerificarCaixa();
	if(StatusCaixa == 0)
	{
		system("cls");
		printf("Devolução de Compra\n\nCaixa está fechado! Favor abrir o caixa antes de operar!\n");
		system("pause");
	}
	else
	{
		do{
			
			do{
				voltar=0;
				system("cls");
				printf("Devolução de Compra\n\nEntre com o CNPJ do fornecedor:(0 Para Voltar) ");
				fgets(compra.cnpjc,16,stdin);
				FormatarSTR(compra.cnpjc);
				
				if(!ValidarCNPJ(compra.cnpjc) && stricmp(compra.cnpjc,"0")!=0)
				{
					printf("CNPJ Inválido!\n");
					system("pause");
					ApagarCampo();
				}
				if(stricmp(compra.cnpjc,"0")==0)
					voltar=1;
			}while(!ValidarCNPJ(compra.cnpjc) && stricmp(compra.cnpjc,"0")!=0);
		
			if(stricmp(compra.cnpjc,"0")!=0 && voltar==0)
			{	
				
				pos = VerificarFornecedor(arqforn,compra.cnpjc);
				if(pos==-1)
					printf("Fornecedor Inexistente!\n");
				else
				{
					fseek(arqforn,pos,0);
					fread(&forn,sizeof(DadosFornecedor),1,arqforn);
					system("cls");
					
					FILE *arqcompra;
					arqcompra = fopen("Compras.bin","rb+");
					if(arqcompra == NULL)
						printf("Nenhuma Compra Cadastrada!\n");
					else
					{
						strcpy(cnpjc,compra.cnpjc);		//COPIANDO PARA AUXILIARES
						
						fread(&compra,sizeof(Compra),1,arqcompra);
						while(!feof(arqcompra))
						{
								if(stricmp(compra.cnpjc,cnpjc)==0)
									cont++;
							fread(&compra,sizeof(Compra),1,arqcompra);
						}
						if(cont>0)
						{
							do
							{
								VcomDevolucao=0;
								printf("Devolução de Compra\n\nCompras com o Fornecedor: %s\n\n",forn.nome);
								rewind(arqcompra);
								fread(&compra,sizeof(Compra),1,arqcompra);
								while(!feof(arqcompra))
								{
										if(stricmp(compra.cnpjc,cnpjc)==0)
										{
											
											printf("Fornecedor: %s\n",compra.fornecedor);
											printf("CNPJ: %s\n",compra.cnpjc);
											printf("Data da Compra: %d/%d/%d\n",compra.dma.dia,compra.dma.mes,compra.dma.ano);
											printf("Método de Pagamento: %s\n",compra.MetPag);
											printf("Itens no carrinho:\n\n");
											
											for(i=0;i<compra.itens.qtdCarrinho;i++)
											{
												printf("Item: %s\n",compra.itens.nomeprod[i]);
												printf("Quantidade: %d\n",compra.itens.qtd[i]);
												printf("Código: %d\n",compra.itens.cod[i]);
												printf("Valor Unitário: %.2fR$\n",compra.itens.valorUni[i]);
												printf("Total do Produto: %.2fR$\n",compra.itens.totalProd[i]);
												if(compra.devolucao.EstaDevolvido[i]==1)
												{
													printf("****\nItem com devolução de %d unidades!\n",compra.devolucao.qtd[i]);
													printf("Motivo: %s",compra.devolucao.motivo[i]);
												}
												printf("-----\n");
											}
											printf("Total da Compra: %.2fR$\nNota Fiscal: %d\n\n---------||---------\n",compra.itens.totalCompra,compra.CodNota);
										}
									fread(&compra,sizeof(Compra),1,arqcompra);
								}
								printf("Entre com o Número da Nota Fiscal à fazer devolução: (0 Para voltar)");
								scanf("%d",&nota);fflush(stdin);
								rewind(arqcompra);
								
								do
								{
									fread(&compra,sizeof(Compra),1,arqcompra);
									if(compra.CodNota == nota)
									{
										achou=1;
										poscompra = (ftell(arqcompra)-sizeof(Compra));
									}
								}while(compra.CodNota != nota && !feof(arqcompra));
								
								if(achou!=1 && nota !=0)
								{
									printf("Nenhuma compra encontrada com esta Nota Fiscal!\n");
									system("pause");
									system("cls");
								}
							}while(nota != 0 && achou == 0);
							if(nota != 0)
							{
								do{
									system("cls");
									printf("Devolução de Compra\n\n");
									printf("Fornecedor: %s\n",compra.fornecedor);
									printf("CNPJ: %s\n",compra.cnpjc);
									printf("Data da Compra: %d/%d/%d\n",compra.dma.dia,compra.dma.mes,compra.dma.ano);
									printf("Método de Pagamento: %s\n",compra.MetPag);
									printf("Itens no carrinho:\n\n");
									
									for(i=0;i<compra.itens.qtdCarrinho;i++)
									{
										printf("Item: %s\n",compra.itens.nomeprod[i]);
										printf("Código: %d\n",compra.itens.cod[i]);
										printf("Quantidade: %d\n",compra.itens.qtd[i]);
										printf("Valor Unitário: %.2fR$\n",compra.itens.valorUni[i]);
										printf("Total do Produto: %.2fR$\n",compra.itens.totalProd[i]);
										if(compra.devolucao.EstaDevolvido[i]==1)
										{
											printf("****Item com devolução de %d unidades!\n",compra.devolucao.qtd[i]);
											printf("Motivo de devolução: %s",compra.devolucao.motivo[i]);
										}
										printf("-----\n");
									}
									printf("Total da Compra: %.2fR$\nNota Fiscal: %d\n\n",compra.itens.totalCompra,compra.CodNota);
									printf("Código do produto a devolver:(0 Para cancelar)");
									scanf("%d",&codCancel);fflush(stdin);
									achou=0;
									conf='N';
									if(codCancel!=0)
									{
										for(i=0;i<compra.itens.qtdCarrinho;i++)
										{
											if(codCancel==compra.itens.cod[i])
											{
												achou=1;
												if(compra.devolucao.EstaDevolvido[i]==1)
												{
													printf("Neste item desta compra já foi realizado uma devolução! Outra não sera possivel!\n");
													system("pause");
													ApagarCampo();
												}
												else
												{
													compra.devolucao.cod[i] = codCancel;
													do{
														printf("Quantidade a devolver: ");
														scanf("%d",&compra.devolucao.qtd[i]);fflush(stdin);
														if(compra.devolucao.qtd[i]>compra.itens.qtd[i] || compra.devolucao.qtd[i]<1)
														{
															printf("Quantidade Inválida! Deve ser menor que a adquirida e maior que zero!\n");
															system("pause");
															ApagarCampo();
														}
													}while(compra.devolucao.qtd[i]>compra.itens.qtd[i] || compra.devolucao.qtd[i]<1);
													do{
														printf("Motivo de devolução:");
														fgets(compra.devolucao.motivo[i],100,stdin);
														if(CampoVazio(compra.devolucao.motivo[i]))
														{
															printf("Campo Vazio! Favor insira motivo\n");
															system("pause");
															ApagarCampo();
														}
													}while(CampoVazio(compra.devolucao.motivo[i]));
													do{
														printf("Confirma a Devolução do item?(S/N)");
														scanf(" %c",&conf);fflush(stdin);
														conf = toupper(conf);
														if(conf!='S' && conf!='N')
														{
															printf("Opção Inválida!\n");
															system("pause");
															ApagarCampo();
														}
													}while(conf!='S' && conf!='N');
													if(conf=='S')
													{
														compra.devolucao.EstaDevolvido[i] = 1;
														fseek(arqcompra,poscompra,0);
														fwrite(&compra,sizeof(Compra),1,arqcompra);
														AtualizarEstoque(compra.devolucao.cod[i],-compra.devolucao.qtd[i]);
														AtualizarSaldoCaixa((compra.itens.valorUni[i]*compra.devolucao.qtd[i]));
														printf("Devolução Concluida!\n");
														system("pause");
													}
													else
													{
														printf("Devolução Cancelada!\n");
														system("pause");
														ApagarCampo();
													}
												}
											}
										}
										if(achou==1){
											do{
												printf("\nRealizar outra devolução?(S/N)");
												scanf(" %c",&conf);fflush(stdin);
												conf=toupper(conf);
												if(conf!='N'&&conf!='S')
												{
													printf("Opção inválida!\n");
													system("pause");
													ApagarCampo();
												}
											}while(conf!='N'&&conf!='S');}
										else{
											printf("Nenhum Produto com este código na compra!\n");
											system("pause");
											conf='S';
										}
									}
								}while(conf=='S');
							}
						}
						else{
							printf("O Fornecedor: %s\nNão possui compras realizadas.\n",forn.nome);
							system("pause");
						}
					}
					fclose(arqcompra);
				}
			}
		}while(stricmp(compra.cnpjc,"0")!=0);
	}
	fclose(arqforn);
}
void OrdenarCompras()
{
	FILE *arq;
	Compra clt,clti;
	int i,qtde=0;
	arq = fopen("Compras.bin","rb+");
	if(arq == NULL)
	  return;
	else
	{
		fseek(arq,0,2);
		qtde=ftell(arq)/sizeof(Compra);
		while(qtde>1)
		{
			for(i=0;i<qtde-1;i++)
			{
				fseek(arq,i*sizeof(Compra),0);
				fread(&clt,sizeof(Compra),1,arq);
				fseek(arq,(i+1)*sizeof(Compra),0);
				fread(&clti,sizeof(Compra),1,arq);
				if(stricmp(clt.fornecedor,clti.fornecedor)>0)
				{
					fseek(arq,i*sizeof(Compra),0);
					fwrite(&clti,sizeof(Compra),1,arq);
					fseek(arq,(i+1)*sizeof(Compra),0);
					fwrite(&clt,sizeof(Compra),1,arq);
				}
			}
			qtde--;
		}
	}
	fclose(arq);	
}
void OrdenarComprasValor(int menor)
{
	FILE *arq;
	Compra clt,clti;
	int i,qtde=0;
	arq = fopen("Compras.bin","rb+");
	if(arq == NULL)
		return;
	else
	{
		fseek(arq,0,2);
		qtde=ftell(arq)/sizeof(Compra);
		while(qtde>1)
		{
			for(i=0;i<qtde-1;i++)
			{
				fseek(arq,i*sizeof(Compra),0);
				fread(&clt,sizeof(Compra),1,arq);
				fseek(arq,(i+1)*sizeof(Compra),0);
				fread(&clti,sizeof(Compra),1,arq);
				if(menor)
				{
					if(clt.itens.totalCompra>clti.itens.totalCompra) // Ordena menor pro maior
					{
						fseek(arq,i*sizeof(Compra),0);
						fwrite(&clti,sizeof(Compra),1,arq);
						fseek(arq,(i+1)*sizeof(Compra),0);
						fwrite(&clt,sizeof(Compra),1,arq);
					}
				}
				else
				{
					if(clt.itens.totalCompra<clti.itens.totalCompra) // Ordena maior pro menor
					{
						fseek(arq,i*sizeof(Compra),0);
						fwrite(&clti,sizeof(Compra),1,arq);
						fseek(arq,(i+1)*sizeof(Compra),0);
						fwrite(&clt,sizeof(Compra),1,arq);
					}
				}
			}
			qtde--;
		}
	}
	fclose(arq);	
}
void OrdenarComprasData(int menor)
{
	FILE *arq;
	Compra compra,comprai;
	int i,qtde=0;
	arq = fopen("Compras.bin","rb+");
	if(arq == NULL)
	  return;
	else
	{
		fseek(arq,0,2);
		qtde=ftell(arq)/sizeof(Compra);
		while(qtde>1)
		{
			for(i=0;i<qtde-1;i++)
			{
				fseek(arq,i*sizeof(Compra),0);
				fread(&compra,sizeof(Compra),1,arq);
				fseek(arq,(i+1)*sizeof(Compra),0);
				fread(&comprai,sizeof(Compra),1,arq);
				if(menor)
				{
					if(compra.dma.ano>comprai.dma.ano)		//Ordena menor pro maior
					{
						fseek(arq,i*sizeof(Compra),0);
						fwrite(&comprai,sizeof(Compra),1,arq);
						fseek(arq,(i+1)*sizeof(Compra),0);
						fwrite(&compra,sizeof(Compra),1,arq);
					}
					if(compra.dma.ano==comprai.dma.ano)
					{
						if(compra.dma.mes>comprai.dma.mes)
						{
							fseek(arq,i*sizeof(Compra),0);
							fwrite(&comprai,sizeof(Compra),1,arq);
							fseek(arq,(i+1)*sizeof(Compra),0);
							fwrite(&compra,sizeof(Compra),1,arq);
						}
						if(compra.dma.mes==comprai.dma.mes)
						{
							if(compra.dma.dia>comprai.dma.dia)
							{
								fseek(arq,i*sizeof(Compra),0);
								fwrite(&comprai,sizeof(Compra),1,arq);
								fseek(arq,(i+1)*sizeof(Compra),0);
								fwrite(&compra,sizeof(Compra),1,arq);
							}
						}
					}
				}
				else
				{
					if(compra.dma.ano<comprai.dma.ano)		//Ordena maior pro menor
					{
						fseek(arq,i*sizeof(Compra),0);
						fwrite(&comprai,sizeof(Compra),1,arq);
						fseek(arq,(i+1)*sizeof(Compra),0);
						fwrite(&compra,sizeof(Compra),1,arq);
					}
					if(compra.dma.ano==comprai.dma.ano)
					{
						if(compra.dma.mes<comprai.dma.mes)
						{
							fseek(arq,i*sizeof(Compra),0);
							fwrite(&comprai,sizeof(Compra),1,arq);
							fseek(arq,(i+1)*sizeof(Compra),0);
							fwrite(&compra,sizeof(Compra),1,arq);
						}
						if(compra.dma.mes==comprai.dma.mes)
						{
							if(compra.dma.dia<comprai.dma.dia)
							{
								fseek(arq,i*sizeof(Compra),0);
								fwrite(&comprai,sizeof(Compra),1,arq);
								fseek(arq,(i+1)*sizeof(Compra),0);
								fwrite(&compra,sizeof(Compra),1,arq);
							}
						}
					}
				}
			}
			qtde--;
		}
	}
	fclose(arq);
}




	//////  VENDAS  ////// 

typedef struct{
	int EstaDevolvido[MAXVENDA];
	int cod[MAXVENDA];
	int qtd[MAXVENDA];
	char motivo[MAXVENDA][101];//Motivo de devolução
	int qtdCarrinho;
}ItensDevVenda;

typedef struct{
	char nomeprod[MAXVENDA][101];
	int cod[MAXVENDA];
	int qtd[MAXVENDA];
	int qtdCarrinho;		//Quantidade de itens no carrinho
	float valorUni[MAXVENDA];
	float totalProd[MAXVENDA];
	float totalVenda;
}ItensVenda;

typedef struct{
	int dia,mes,ano;
}DataVenda;
typedef struct{
	int tipoclt;
	char cliente[101];
	char cpfc[13];		//caso comprador seja pessoa física
	char cnpjc[16];		//caso comprador seja pessoa jurídica
	char MetPag[21]; 
	int CodNota;
	DataVenda dma;
	ItensVenda itens;
	ItensDevVenda devolucao;
}Venda;
int ProximaNota()
{
	int maiornota = 0;
	Venda venda;
	
	FILE *arqvendaI;
	arqvendaI = fopen("Vendas.bin","rb");
	if(arqvendaI == NULL)
	{
		printf("Erro no arquivo Vendas!(PROX NOTA)");
		system("pause");
		return 20250001;
	}
	else
	{
		fread(&venda,sizeof(Venda),1,arqvendaI);
		while(!feof(arqvendaI))
		{
			if(venda.CodNota > maiornota)
				maiornota = venda.CodNota;
			fread(&venda,sizeof(Venda),1,arqvendaI);
		}
		if(maiornota < 20250000)
			maiornota += 20250000;
		fclose(arqvendaI);
		return maiornota + 1;
	}
	fclose(arqvendaI);
}


ItensVenda AdicionarItemVenda(ItensVenda itens)
{
	DadosProduto prod;
	
	int posprodI=0,i;
	int voltar=0;
	
	FILE *arqprodI;
	arqprodI = fopen("Produtos.bin","rb");
	if(arqprodI == NULL)
	{
		printf("Erro no arquivo produtos");
		system("pause");
	}
	else
	{
		do{
			voltar = 0;
			system("cls");
			printf("Efetuar Venda\n\nCódigo do Produto: (0 Para voltar)");
			scanf("%d",&itens.cod[itens.qtdCarrinho]);fflush(stdin);
			if(itens.cod[itens.qtdCarrinho]!=0){
				posprodI = VerificarProduto(arqprodI,itens.cod[itens.qtdCarrinho]);
				if(posprodI == -1)
				{
					printf("Produto/Serviço Inexistente!\n");
					system("pause");
					ApagarCampo();
				}
				else
				{
					fseek(arqprodI,posprodI,0);
					fread(&prod,sizeof(DadosProduto),1,arqprodI);
				}
			}
			for(i=0;i<itens.qtdCarrinho;i++)
			{
				if(itens.cod[itens.qtdCarrinho] == itens.cod[i]){
					printf("O item que escolheu já está no carrinho! Para editar a quantidade faça uma nova compra!\n");
					system("pause");
					itens.cod[itens.qtdCarrinho] = 0;
					voltar=1;
				}
			}
			if(itens.cod[itens.qtdCarrinho]==0)
				voltar = 1;
		}while(posprodI==-1 && voltar == 0);
		if(voltar==0)
		{
			do{
				do{
					printf("Quantidade: ");
					scanf("%d",&itens.qtd[itens.qtdCarrinho]);fflush(stdin);
					if(itens.qtd[itens.qtdCarrinho]<1)
					{
						printf("Favor inserir quantidade maior que zero!\n");
						system("pause");
						ApagarCampo();
					}
				}while(itens.qtd[itens.qtdCarrinho] < 1);
				
				if(itens.qtd[itens.qtdCarrinho]>prod.qtd)
				{
					printf("Quantidade em estoque insuficiente!\n\nItem: %s\nEm Estoque: %d\n",prod.nome,prod.qtd);
					system("pause");
					ApagarCampo();
				}
			}while(itens.qtd[itens.qtdCarrinho]>prod.qtd);
			strcpy(itens.nomeprod[itens.qtdCarrinho] , prod.nome);
			itens.valorUni[itens.qtdCarrinho] = prod.preco;
			itens.totalProd[itens.qtdCarrinho] = prod.preco*itens.qtd[itens.qtdCarrinho];
			itens.totalVenda += itens.totalProd[itens.qtdCarrinho];
			itens.qtdCarrinho++;

		}
		fclose(arqprodI);
		return itens;
	}
}

void CadastrarVenda()
{
	DadosCliente clt;
	DadosProduto prod;
	Venda venda;
	int i;
	//int ProxNota;
	int poscliente=0,posprod=0;
	int cod,qtd,pag;			// pag = Método de pagamento:\n\n1- Pix\n2- Cartão crédito\n3- Cartão débito\n4- Dinheiro
	int StatusCaixa;
	int voltar;
	char conf;
	StatusCaixa = VerificarCaixa();
	if(StatusCaixa == 0)
	{
		system("cls");
		printf("Efetuar Venda\n\nCaixa está fechado! Favor abrir o caixa antes de operar!\n");
		system("pause");
	}
	else{
		do{
			do{	
				voltar=0;
				system("cls");
				printf("Efetuar Venda\n\nEntre com o tipo de cliente:\n1- Pessoa Física \n2- Pessoa Jurídica\n0- Voltar\n\nOpção: ");
				scanf("%d",&clt.tipo);fflush(stdin);
				if(clt.tipo<0 || clt.tipo>2)
				{
					printf("Opção Inválida!\n");
					system("pause");
				}
			}while(clt.tipo<0 || clt.tipo>2);
			if(clt.tipo==1)
			{
				do{
					printf("Entre com o CPF do Cliente: (0 Para Voltar) ");
					fgets(venda.cpfc,13,stdin);
					FormatarSTR(venda.cpfc);
					
					if(!ValidarCPF(venda.cpfc) && stricmp(venda.cpfc,"0")!=0)
					{
						printf("CPF Inválido!\n");
						system("pause");
						ApagarCampo();
					}
					if(stricmp(venda.cpfc,"0")==0)
						voltar=1;
				}while(!ValidarCPF(venda.cpfc) && stricmp(venda.cpfc,"0")!=0);
			}					
			if(clt.tipo==2)
			{
				do{
					voltar=0;
					printf("Entre com o CNPJ do cliente:(0 Para Voltar) ");
					fgets(venda.cnpjc,16,stdin);
					FormatarSTR(venda.cnpjc);
					if(!ValidarCNPJ(venda.cnpjc) && stricmp(venda.cnpjc,"0")!=0)
					{
						printf("CNPJ Inválido!\n");
						system("pause");
						ApagarCampo();
					}
					if(stricmp(venda.cnpjc,"0")==0)
						voltar=1;
				}while(!ValidarCNPJ(venda.cnpjc) && stricmp(venda.cnpjc,"0")!=0);
			}
			if(clt.tipo!=0 && voltar==0)
			{
				FILE *arqvenda;
				arqvenda = fopen("Vendas.bin","ab+");
				if(arqvenda == NULL){
					printf("Erro no arquivo Vendas!\n");
					system("pause");
					return;
				}
				
				FILE *arqprod;
				arqprod = fopen("Produtos.bin","rb+");
				if(arqprod == NULL){
					printf("Erro no arquivo Produtos!\n");
					system("pause");
					fclose(arqvenda);
					return;
				}
				FILE *arqcliente;
				arqcliente = fopen("Clientes.bin","rb+");
				if(arqcliente == NULL){
					printf("Erro no arquivo Clientes!\n");
					system("pause");
					fclose(arqprod);
					fclose(arqvenda);
					return;
				}
				if(clt.tipo==1)
					poscliente = VerificarCliente(arqcliente,venda.cpfc);
				else
					poscliente = VerificarClienteCNPJ(arqcliente,venda.cnpjc);
				if(poscliente == -1)
				{
					printf("Cliente Inexistente!\n");
					system("pause");
				}
				else
				{
					fseek(arqcliente,poscliente,0);
					fread(&clt,sizeof(DadosCliente),1,arqcliente);
					venda.itens.totalVenda=0;
					venda.itens.qtdCarrinho = 0;
					do{	//qtdCarrinho comeca com 0
						venda.itens = AdicionarItemVenda(venda.itens);
						
						if(venda.itens.cod[0]!=0)
						{
							system("cls");
							printf("Efetuar Venda\n\nItens no carrinho:\n\n");
							
							for(i=0;i<venda.itens.qtdCarrinho;i++)
							{
								printf("Item: %s\n",venda.itens.nomeprod[i]);
								printf("Código: %d\n",venda.itens.cod[i]);
								printf("Quantidade: %d\n",venda.itens.qtd[i]);
								printf("Valor Unitário: %.2fR$\n",venda.itens.valorUni[i]);
								printf("Total do Produto: %.2fR$\n---\n",venda.itens.totalProd[i]);
							}
							printf("Total da Venda: %.2fR$\n",venda.itens.totalVenda);
							
						}
						do{
							printf("Deseja adicionar outro item a venda?(S/N/ C Para cancelar) ");
							scanf(" %c",&conf);fflush(stdin);
							conf = toupper(conf);
							if(conf=='S' && venda.itens.qtdCarrinho==MAXVENDA)
							{
								printf("O carrinho está cheio! Favor finalizar compra ou cancelar!\n");
								system("pause");
								ApagarCampo();
								conf='Z';
							}
							if(venda.itens.cod[0]==0 && conf=='N')
							{
								printf("O carrinho está vazio! Favor ou cancelar a venda ou adicionar item!\n");
								system("pause");
								ApagarCampo();
								conf='Z';
							}
							if(conf!='N' && conf!='S' && conf!='C' && conf!='Z')
							{
								printf("Opção inválida!\n");
								system("pause");
								ApagarCampo();
							}
						}while(conf!='N' && conf!='S' && conf!='C');
							
					}while(conf=='S');
					if(conf=='N')
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
						printf("Efetuar Venda\n\nData da Venda:");
						do{
							printf("Dia: ");
							scanf("%d",&venda.dma.dia);
							if(venda.dma.dia<1 || venda.dma.dia>31)
							{
								printf("Dia inválido!\n");
								system("pause");
								ApagarCampo();
							}
						}while(venda.dma.dia<1 || venda.dma.dia>31);
						do{
							printf("Mês: ");
							scanf("%d",&venda.dma.mes);
							if(venda.dma.mes<1 || venda.dma.mes>12)
							{
								printf("Mês inválido!\n");
								system("pause");
								ApagarCampo();
							}
						}while(venda.dma.mes<1 || venda.dma.mes>12);
						do{
							printf("Ano: ");
							scanf("%d",&venda.dma.ano);
							if(venda.dma.ano<2020 || venda.dma.ano>2025)
							{
								printf("Ano inválido, Por favor escolha entre 2020 e 2025!\n");
								system("pause");
								ApagarCampo();
							}
						}while(venda.dma.ano<2020 || venda.dma.ano>2025);
						
						venda.CodNota = ProximaNota();
						
						system("cls");
						printf("Dados da Venda:\n\nCliente: %s\nData da Venda: %d/%d/%d\nMétodo de Pagamento: %s\n\nItens no carrinho:\n\n",clt.nome,venda.dma.dia,venda.dma.mes,venda.dma.ano,venda.MetPag);
						for(i=0;i<venda.itens.qtdCarrinho;i++)
						{
							printf("Item: %s\n",venda.itens.nomeprod[i]);
							printf("Quantidade: %d\n",venda.itens.qtd[i]);
							printf("Valor Unitário: %.2fR$\n",venda.itens.valorUni[i]);
							printf("Total do Produto: %.2fR$\n---\n",venda.itens.totalProd[i]);
						}
						printf("Total da Venda: %.2fR$\nNota Fiscal: %d\n\n",venda.itens.totalVenda,venda.CodNota);
						do{
							printf("Confirma a Venda? (S/N)");
							scanf(" %c",&conf);fflush(stdin);
							conf = toupper(conf);
							if(conf!='S' && conf != 'N')
							{
								printf("Opção inválida!\n");
								system("pause");
								ApagarCampo();
							}
						}while(conf!='S' && conf != 'N');
						switch(conf)
						{
							case 'S':printf(" Venda Concluida!\n");
									 strcpy(venda.cliente,clt.nome);
									 
									 venda.tipoclt = clt.tipo;			
									 									 
									 fwrite(&venda,sizeof(Venda),1,arqvenda);  /// CADASTRANDO VENDA
									 
									 for(i=0;i<venda.itens.qtdCarrinho;i++)
									 	AtualizarEstoque(venda.itens.cod[i],-venda.itens.qtd[i]);	///ATUALIZANDO ESTOQUE
									 	
									 AtualizarSaldoCaixa(venda.itens.totalVenda);		//ATUALIZANDO CAIXA
								 	 
									 fclose(arqvenda);
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
					}
				}
				
				fclose(arqprod);
				fclose(arqcliente);
			}
		}while(clt.tipo!=0);
	}
	
}

void DevolucaoVenda()
{
	DadosCliente clt;
	Venda venda;
	int StatusCaixa;
	char cpfc[13];
	char cnpjc[16];
	int pos,posvenda,cont=0,nota,achou=0,qtd,qtdDev;
	int VcomDevolucao=0;
	int voltar=0,i,codCancel;
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
			system("pause");
		}
		else
		{
			do{
				do{	
					voltar=0;
					system("cls");
					printf("Devolução de Venda\n\nEntre com o tipo de cliente:\n1- Pessoa Física \n2- Pessoa Jurídica\n0- Voltar\n\nOpção: ");
					scanf("%d",&clt.tipo);fflush(stdin);
					if(clt.tipo<0 || clt.tipo>2)
					{
						printf("Opção Inválida!\n");
						system("pause");
					}
				}while(clt.tipo<0 || clt.tipo>2);
				if(clt.tipo==1)
				{
					do{
						printf("Entre com o CPF do Cliente: (0 Para Voltar) ");
						fgets(venda.cpfc,13,stdin);
						FormatarSTR(venda.cpfc);
					    
						if(!ValidarCPF(venda.cpfc) && stricmp(venda.cpfc,"0")!=0)
						{
							printf("CPF Inválido!\n");
							system("pause");
							ApagarCampo();
						}
						if(stricmp(venda.cpfc,"0")==0)
							voltar=1;
					}while(!ValidarCPF(venda.cpfc) && stricmp(venda.cpfc,"0")!=0);
				}					
				if(clt.tipo==2)
				{
					do{
						voltar=0;
						printf("Entre com o CNPJ do cliente:(0 Para Voltar) ");
						fgets(venda.cnpjc,16,stdin);
						FormatarSTR(venda.cnpjc);
						
						if(!ValidarCNPJ(venda.cnpjc) && stricmp(venda.cnpjc,"0")!=0)
						{
							printf("CNPJ Inválido!\n");
							system("pause");
							ApagarCampo();
						}
						if(stricmp(venda.cnpjc,"0")==0)
							voltar=1;
					}while(!ValidarCNPJ(venda.cnpjc) && stricmp(venda.cnpjc,"0")!=0);
				}
				if(clt.tipo!=0 && voltar==0)
				{	
					if(clt.tipo==1)
						pos = VerificarCliente(arqcliente,venda.cpfc);
					else
						pos = VerificarClienteCNPJ(arqcliente,venda.cnpjc);
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
							printf("Nenhuma Venda Cadastrada!\n");
						else
						{
							strcpy(cpfc,venda.cpfc);
							strcpy(cnpjc,venda.cnpjc);		//COPIANDO PARA AUXILIARES
							
							fread(&venda,sizeof(Venda),1,arqvenda);
							while(!feof(arqvenda))
							{
								if(clt.tipo==1)
									if(stricmp(venda.cpfc,cpfc)==0)
										cont++;
								if(clt.tipo==2)
									if(stricmp(venda.cnpjc,cnpjc)==0)
										cont++;
								fread(&venda,sizeof(Venda),1,arqvenda);
							}
							if(cont>0)
							{
								do
								{
									VcomDevolucao=0;
									printf("Devolução de Venda\n\nCompras do cliente: %s\n",clt.nome);
									rewind(arqvenda);
									fread(&venda,sizeof(Venda),1,arqvenda);
									while(!feof(arqvenda))
									{
										if(clt.tipo==1)
											if(stricmp(venda.cpfc,cpfc)==0)
											{
												printf("Cliente: %s\n",venda.cliente);
												printf("CPF: %s\n",venda.cpfc);
												printf("Data da Venda: %d/%d/%d\n",venda.dma.dia,venda.dma.mes,venda.dma.ano);
												printf("Método de Pagamento: %s\n",venda.MetPag);
												printf("Itens no carrinho:\n\n");
												
												for(i=0;i<venda.itens.qtdCarrinho;i++)
												{
													printf("Item: %s\n",venda.itens.nomeprod[i]);
													printf("Quantidade: %d\n",venda.itens.qtd[i]);
													printf("Valor Unitário: %.2fR$\n",venda.itens.valorUni[i]);
													printf("Total do Produto: %.2fR$\n",venda.itens.totalProd[i]);
													if(venda.devolucao.EstaDevolvido[i]==1)
													{
														printf("****\nItem com devolução de %d unidades!\n",venda.devolucao.qtd[i]);
														printf("Motivo: %s",venda.devolucao.motivo[i]);
													}
													printf("-----\n");
												}
												printf("Total da Venda: %.2fR$\nNota Fiscal: %d\n\n---------||---------\n",venda.itens.totalVenda,venda.CodNota);
											}
										if(clt.tipo==2)
											if(stricmp(venda.cnpjc,cnpjc)==0)
											{
												
												printf("Cliente: %s\n",venda.cliente);
												printf("CNPJ: %s\n",venda.cnpjc);
												printf("Data da Venda: %d/%d/%d\n",venda.dma.dia,venda.dma.mes,venda.dma.ano);
												printf("Método de Pagamento: %s\n",venda.MetPag);
												printf("Itens no carrinho:\n\n");
												
												for(i=0;i<venda.itens.qtdCarrinho;i++)
												{
													printf("Item: %s\n",venda.itens.nomeprod[i]);
													printf("Quantidade: %d\n",venda.itens.qtd[i]);
													printf("Código: %d\n",venda.itens.cod[i]);
													printf("Valor Unitário: %.2fR$\n",venda.itens.valorUni[i]);
													printf("Total do Produto: %.2fR$\n",venda.itens.totalProd[i]);
													if(venda.devolucao.EstaDevolvido[i]==1)
													{
														printf("****\nItem com devolução de %d unidades!\n",venda.devolucao.qtd[i]);
														printf("Motivo: %s",venda.devolucao.motivo[i]);
													}
													printf("-----\n");
												}
												printf("Total da Venda: %.2fR$\nNota Fiscal: %d\n\n---------||---------\n",venda.itens.totalVenda,venda.CodNota);
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
											posvenda = (ftell(arqvenda)-sizeof(Venda));
										}
									}while(venda.CodNota != nota && !feof(arqvenda));
									
									if(achou!=1 && nota !=0)
									{
										printf("Nenhuma venda encontrada com esta Nota Fiscal!\n");
										system("pause");
										system("cls");
									}
								}while(nota != 0 && achou == 0);
								if(nota != 0)
								{
									do{
										system("cls");
										printf("Devolução de Venda\n\n");
										printf("Cliente: %s\n",venda.cliente);
										if(clt.tipo==1)
											printf("CPF: %s\n",venda.cpfc);
										if(clt.tipo==2)
											printf("CNPJ: %s\n",venda.cnpjc);
										printf("Data da Venda: %d/%d/%d\n",venda.dma.dia,venda.dma.mes,venda.dma.ano);
										printf("Método de Pagamento: %s\n",venda.MetPag);
										printf("Itens no carrinho:\n\n");
										
										for(i=0;i<venda.itens.qtdCarrinho;i++)
										{
											printf("Item: %s\n",venda.itens.nomeprod[i]);
											printf("Código: %d\n",venda.itens.cod[i]);
											printf("Quantidade: %d\n",venda.itens.qtd[i]);
											printf("Valor Unitário: %.2fR$\n",venda.itens.valorUni[i]);
											printf("Total do Produto: %.2fR$\n",venda.itens.totalProd[i]);
											if(venda.devolucao.EstaDevolvido[i]==1)
											{
												printf("****Item com devolução de %d unidades!\n",venda.devolucao.qtd[i]);
												printf("Motivo de devolução: %s",venda.devolucao.motivo[i]);
											}
											printf("-----\n");
										}
										printf("Total da Venda: %.2fR$\nNota Fiscal: %d\n\n",venda.itens.totalVenda,venda.CodNota);
										printf("Código do produto a devolver:(0 Para cancelar)");
										scanf("%d",&codCancel);fflush(stdin);
										achou=0;
										conf='N';
										if(codCancel!=0)
										{
											for(i=0;i<venda.itens.qtdCarrinho;i++)
											{
												if(codCancel==venda.itens.cod[i])
												{
													achou=1;
													if(venda.devolucao.EstaDevolvido[i]==1)
													{
														printf("Neste item desta venda já foi realizado uma devolução! Outra não sera possivel!\n");
														system("pause");
														ApagarCampo();
													}
													else
													{
														venda.devolucao.cod[i] = codCancel;
														do{
															printf("Quantidade a devolver: ");
															scanf("%d",&venda.devolucao.qtd[i]);fflush(stdin);
															if(venda.devolucao.qtd[i]>venda.itens.qtd[i] || venda.devolucao.qtd[i]<1)
															{
																printf("Quantidade Inválida! Deve ser menor que a adquirida e maior que zero!\n");
																system("pause");
																ApagarCampo();
															}
														}while(venda.devolucao.qtd[i]>venda.itens.qtd[i] || venda.devolucao.qtd[i]<1);
														do{
															printf("Motivo de devolução:");
															fgets(venda.devolucao.motivo[i],100,stdin);
															if(CampoVazio(venda.devolucao.motivo[i]))
															{
																printf("Campo Vazio! Favor insira motivo\n");
																system("pause");
																ApagarCampo();
															}
														}while(CampoVazio(venda.devolucao.motivo[i]));
														do{
															printf("Quantos itens podem voltar ao estoque?");
															scanf("%d",&qtdDev);
															if(qtdDev > venda.devolucao.qtd[i] || qtdDev<0)
															{
																printf("Quantidade Inválida! Deve ser menor ou igual a quantidade devolvida!\n");
																system("pause");
																ApagarCampo();
															}
														}while(qtdDev > venda.devolucao.qtd[i] || qtdDev<0);
														do{
															printf("Confirma a Devolução do item?(S/N)");
															scanf(" %c",&conf);fflush(stdin);
															conf = toupper(conf);
															if(conf!='S' && conf!='N')
															{
																printf("Opção Inválida!\n");
																system("pause");
																ApagarCampo();
															}
														}while(conf!='S' && conf!='N');
														if(conf=='S')
														{
															venda.devolucao.EstaDevolvido[i] = 1;
															fseek(arqvenda,posvenda,0);
															fwrite(&venda,sizeof(Venda),1,arqvenda);
															AtualizarEstoque(venda.devolucao.cod[i],qtdDev);
															AtualizarSaldoCaixa(-(venda.itens.totalProd[i]));
															printf("Devolução Concluida!\n");
															system("pause");
														}
														else
														{
															printf("Devolução Cancelada!\n");
															system("pause");
															ApagarCampo();
														}
													}
												}
											}
											if(achou==1){
												do{
													printf("\nRealizar outra devolução?(S/N)");
													scanf(" %c",&conf);fflush(stdin);
													conf=toupper(conf);
													if(conf!='N'&&conf!='S')
													{
														printf("Opção inválida!\n");
														system("pause");
														ApagarCampo();
													}
												}while(conf!='N'&&conf!='S');}
											else{
												printf("Nenhum Produto com este código na venda!\n");
												system("pause");
												conf='S';
											}
										}
									}while(conf=='S');
								}
							}
							else{
								printf("O(A) cliente: %sNão possui compras realizadas.\n",clt.nome);
								system("pause");
							}
						}
						fclose(arqvenda);
					}
				}
			}while(clt.tipo!=0);
		}
	}
	fclose(arqcliente);
}

void OrdenarVendas()
{
	FILE *arq;
	Venda venda,vendai;
	int i,qtde=0;
	arq = fopen("Vendas.bin","rb+");
	if(arq == NULL)
		return;
	else
	{
		fseek(arq,0,2);
		qtde=ftell(arq)/sizeof(Venda);
		while(qtde>1)
		{
			for(i=0;i<qtde-1;i++)
			{
				fseek(arq,i*sizeof(Venda),0);
				fread(&venda,sizeof(Venda),1,arq);
				fseek(arq,(i+1)*sizeof(Venda),0);
				fread(&vendai,sizeof(Venda),1,arq);
				if(stricmp(venda.cliente,vendai.cliente)>0)
				{
					fseek(arq,i*sizeof(Venda),0);
					fwrite(&vendai,sizeof(Venda),1,arq);
					fseek(arq,(i+1)*sizeof(Venda),0);
					fwrite(&venda,sizeof(Venda),1,arq);
				}
			}
			qtde--;
		}
	}
	fclose(arq);	
}
void OrdenarVendasData(int menor)
{
	FILE *arq;
	Venda venda,vendai;
	int i,qtde=0;
	arq = fopen("Vendas.bin","rb+");
	if(arq == NULL)
	  return;
	else
	{
		fseek(arq,0,2);
		qtde=ftell(arq)/sizeof(Venda);
		while(qtde>1)
		{
			for(i=0;i<qtde-1;i++)
			{
				fseek(arq,i*sizeof(Venda),0);
				fread(&venda,sizeof(Venda),1,arq);
				fseek(arq,(i+1)*sizeof(Venda),0);
				fread(&vendai,sizeof(Venda),1,arq);
				if(menor)
				{
					if(venda.dma.ano>vendai.dma.ano)		//Ordena menor pro maior
					{
						fseek(arq,i*sizeof(Venda),0);
						fwrite(&vendai,sizeof(Venda),1,arq);
						fseek(arq,(i+1)*sizeof(Venda),0);
						fwrite(&venda,sizeof(Venda),1,arq);
					}
					if(venda.dma.ano==vendai.dma.ano)
					{
						if(venda.dma.mes>vendai.dma.mes)
						{
							fseek(arq,i*sizeof(Venda),0);
							fwrite(&vendai,sizeof(Venda),1,arq);
							fseek(arq,(i+1)*sizeof(Venda),0);
							fwrite(&venda,sizeof(Venda),1,arq);
						}
						if(venda.dma.mes==vendai.dma.mes)
						{
							if(venda.dma.dia>vendai.dma.dia)
							{
								fseek(arq,i*sizeof(Venda),0);
								fwrite(&vendai,sizeof(Venda),1,arq);
								fseek(arq,(i+1)*sizeof(Venda),0);
								fwrite(&venda,sizeof(Venda),1,arq);
							}
						}
					}
				}
				else
				{
					if(venda.dma.ano<vendai.dma.ano)		//Ordena maior pro menor
					{
						fseek(arq,i*sizeof(Venda),0);
						fwrite(&vendai,sizeof(Venda),1,arq);
						fseek(arq,(i+1)*sizeof(Venda),0);
						fwrite(&venda,sizeof(Venda),1,arq);
					}
					if(venda.dma.ano==vendai.dma.ano)
					{
						if(venda.dma.mes<vendai.dma.mes)
						{
							fseek(arq,i*sizeof(Venda),0);
							fwrite(&vendai,sizeof(Venda),1,arq);
							fseek(arq,(i+1)*sizeof(Venda),0);
							fwrite(&venda,sizeof(Venda),1,arq);
						}
						if(venda.dma.mes==vendai.dma.mes)
						{
							if(venda.dma.dia<vendai.dma.dia)
							{
								fseek(arq,i*sizeof(Venda),0);
								fwrite(&vendai,sizeof(Venda),1,arq);
								fseek(arq,(i+1)*sizeof(Venda),0);
								fwrite(&venda,sizeof(Venda),1,arq);
							}
						}
					}
				}
			}
			qtde--;
		}
	}
	fclose(arq);
}


void OrdenarVendasValor(int menor)
{
	FILE *arq;
	Venda venda,vendai;
	int i,qtde=0;
	arq = fopen("Vendas.bin","rb+");
	if(arq == NULL)
	  return;
	else
	{
		fseek(arq,0,2);
		qtde=ftell(arq)/sizeof(Venda);
		while(qtde>1)
		{
			for(i=0;i<qtde-1;i++)
			{
				fseek(arq,i*sizeof(Venda),0);
				fread(&venda,sizeof(Venda),1,arq);
				fseek(arq,(i+1)*sizeof(Venda),0);
				fread(&vendai,sizeof(Venda),1,arq);
				if(menor)
				{
					if(venda.itens.totalVenda>vendai.itens.totalVenda)// Ordena menor pro maior
					{
						fseek(arq,i*sizeof(Venda),0);
						fwrite(&vendai,sizeof(Venda),1,arq);
						fseek(arq,(i+1)*sizeof(Venda),0);
						fwrite(&venda,sizeof(Venda),1,arq);
					}
				}
				else
				{
					if(venda.itens.totalVenda<vendai.itens.totalVenda) /// Ordena maior pro menor
					{
						fseek(arq,i*sizeof(Venda),0);
						fwrite(&vendai,sizeof(Venda),1,arq);
						fseek(arq,(i+1)*sizeof(Venda),0);
						fwrite(&venda,sizeof(Venda),1,arq);
					}
				}
			}
			qtde--;
		}
	}
	fclose(arq);
}


	//////  RELATÓRIOS  //////
	
void RelatorioProd()
{
	int tipo=1,cont=0;
	DadosProduto prod;
	
	FILE *arq;
	arq = fopen("Produtos.bin","rb");
	if(arq == NULL)
	{
		printf("\nNão há produtos cadastrados!\n");
		system("pause");
	}
	else
	{
		fread(&prod,sizeof(DadosProduto),1,arq);
		system("cls");
		printf("Relatório Produtos\n\n");
		while(!feof(arq))
		{
			if(tipo==prod.tipo)
			{
				cont++;
				printf("Nome: %s\n",prod.nome);
				printf("Código: %d\n",prod.cod);
				printf("Preço: %.2fR$\n",prod.preco);
				printf("Quantidade: %d\n----\n",prod.qtd);
			}
			
			fread(&prod,sizeof(DadosProduto),1,arq);
		}
		if(cont==0)
			printf("Não há produtos cadastrados.\n");
		system("pause");
	}
	fclose(arq);
}
void RelatorioInsumo()
{
	int tipo=3,cont=0;
	DadosProduto prod;
	
	FILE *arq;
	arq = fopen("Produtos.bin","rb");
	if(arq == NULL)
	{
		printf("\nNão há insumos cadastrados!\n");
		system("pause");
	}
	else
	{
		fread(&prod,sizeof(DadosProduto),1,arq);
		system("cls");
		printf("Relatório Insumos\n\n");
		while(!feof(arq))
		{
			if(tipo==prod.tipo)
			{
				cont++;
				printf("Nome: %s\n",prod.nome);
				printf("Código: %d\n",prod.cod);
				printf("Preço: %.2fR$\n",prod.preco);
				printf("Quantidade: %d\n----\n",prod.qtd);
			}
			
			fread(&prod,sizeof(DadosProduto),1,arq);
		}
		if(cont==0)
			printf("Não há insumos cadastrados.\n");
		system("pause");
	}
	fclose(arq);
}
void RelatorioNotas()
{
	Venda venda;
	int ComDevolucao=0;
	int i;
	FILE *arq;
	arq = fopen("Vendas.bin","rb");
	if(arq == NULL)
	{
		printf("\nNão há vendas cadastradas!\n");
		system("pause");
	}
	else
	{
		fread(&venda,sizeof(Venda),1,arq);
		system("cls");
		printf("Relatório Notas Fiscais\n\n");
		while(!feof(arq))
		{
			
			printf("----------||----------\n\nCliente: %s\n",venda.cliente);
			if(venda.tipoclt==1)
				printf("CPF: %s\n",venda.cpfc);
			else
				printf("CNPJ: %s\n\n",venda.cnpjc);
			printf("Valor Total: %.2fR$\n",venda.itens.totalVenda);
			printf("Método de Pagamento: %s\n",venda.MetPag);
			for(i=0;i<venda.itens.qtdCarrinho;i++)
				if(venda.devolucao.EstaDevolvido[i]==1)
					ComDevolucao=1;
			if(ComDevolucao)
				printf("***Venda com Devolução de itens***\n");
			printf("Data da Venda: %d/%d/%d\n",venda.dma.dia,venda.dma.mes,venda.dma.ano);
			printf("Nota fiscal: %d\n\n",venda.CodNota);
			fread(&venda,sizeof(Venda),1,arq);
		}
		system("pause");
	}
	fclose(arq);
}
void RelatorioVendas()
{
	Venda venda;
	int i;
	FILE *arq;
	arq = fopen("Vendas.bin","rb");
	if(arq == NULL)
	{
		printf("\nNão há vendas cadastradas!\n");
		system("pause");
	}
	else
	{
		fread(&venda,sizeof(Venda),1,arq);
		system("cls");
		printf("Relatório Vendas\n\n");
		while(!feof(arq))
		{
			printf("----------||----------\n\nCliente: %s\n",venda.cliente);
			if(venda.tipoclt==1)
				printf("CPF: %s\n",venda.cpfc);
			else
				printf("CNPJ: %s\n\nCarrinho:\n",venda.cnpjc);
			for(i=0;i<venda.itens.qtdCarrinho;i++)
			{
				printf("-----\nItem: %s\n",venda.itens.nomeprod[i]);
				printf("Quantidade: %d\n",venda.itens.qtd[i]);
				printf("Valor Unitário: %.2fR$\n",venda.itens.valorUni[i]);
				printf("Total do Produto: %.2fR$\n",venda.itens.totalProd[i]);
				if(venda.devolucao.EstaDevolvido[i]==1)
				{
					printf("***Item com devolução de %d unidades.\n",venda.devolucao.qtd[i]);
					printf("Motivo: %s",venda.devolucao.motivo[i]);
				}
			}
			printf("-----\nValor Total: %.2fR$\n",venda.itens.totalVenda);
			printf("Método de Pagamento: %s\n",venda.MetPag);
			printf("Data da Venda: %d/%d/%d\n",venda.dma.dia,venda.dma.mes,venda.dma.ano);
			printf("Nota fiscal: %d\n\n",venda.CodNota);
			fread(&venda,sizeof(Venda),1,arq);
		}
		system("pause");
	}
	fclose(arq);
}
void RelatorioCompras()
{
	Compra compra;
	int i;
	FILE *arq;
	arq = fopen("Compras.bin","rb");
	if(arq == NULL)
	{
		printf("\nNão há Compras cadastradas!\n");
		system("pause");
	}
	else
	{
		fread(&compra,sizeof(Compra),1,arq);
		system("cls");
		printf("Relatório de Compras\n\n");
		while(!feof(arq))
		{
			printf("----------||----------\n\nFornecedor: %s\n",compra.fornecedor);
			printf("CNPJ: %s\n\nCarrinho:\n",compra.cnpjc);
			for(i=0;i<compra.itens.qtdCarrinho;i++)
			{
				printf("-----\nItem: %s\n",compra.itens.nomeprod[i]);
				printf("Quantidade: %d\n",compra.itens.qtd[i]);
				printf("Valor Unitário: %.2fR$\n",compra.itens.valorUni[i]);
				printf("Total do Produto: %.2fR$\n",compra.itens.totalProd[i]);
				if(compra.devolucao.EstaDevolvido[i]==1)
				{
					printf("***Item com devolução de %d unidades.\n",compra.devolucao.qtd[i]);
					printf("Motivo: %s",compra.devolucao.motivo[i]);
				}
			}
			printf("-----\nValor Total: %.2fR$\n",compra.itens.totalCompra);
			printf("Método de Pagamento: %s\n",compra.MetPag);
			printf("Data da Venda: %d/%d/%d\n",compra.dma.dia,compra.dma.mes,compra.dma.ano);
			printf("Nota fiscal: %d\n\n",compra.CodNota);
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

	//////	  FUNÇÕES AUXILIARES //////
// ===== Funções de Validação Adicionadas da V25 =====

void FormatarSTR(char *str)
{
	size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    } else {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);		// Limpa o restante do buffer se o \n não foi lido (entrada maior que o buffer)
    }
}



void ApagarCampo()
{
	printf("\033[A");    // Move o cursor 3 linhas para cima
	printf("\033[2K");	// Apaga
	printf("\033[A");    
	printf("\033[2K");
	printf("\033[A");    
	printf("\033[2K");
}

int ProdutoComVenda(int cod)
{
	int i;
	FILE *arqvenda;
	arqvenda = fopen("Vendas.bin", "rb");
    if (arqvenda == NULL) {
        printf("Erro ao abrir o arquivo de vendas!\n");
        return 0;
    }
    Venda venda;
    fread(&venda, sizeof(Venda), 1, arqvenda);
    while (!feof(arqvenda)) 
	{
		for(i=0;i<venda.itens.qtdCarrinho;i++)
		    if (venda.itens.cod[i]==cod)
			{
		        fclose(arqvenda);
		        return 1; // Produto já teve venda
		    }
		fread(&venda, sizeof(Venda), 1, arqvenda);
    }

    fclose(arqvenda);
    return 0; // Cliente não fez compra
}

int ClienteFezVenda(char *cpfc) 
{
    FILE *arqvenda;
	arqvenda = fopen("Vendas.bin", "rb");
    if (arqvenda == NULL) {
        printf("Erro ao abrir o arquivo de vendas!\n");
        return 0;
    }

    Venda venda;
    while (fread(&venda, sizeof(Venda), 1, arqvenda)) {
        if (stricmp(venda.cpfc,cpfc)==0)//venda.cpf == cpf) 
		{
            fclose(arqvenda);
            return 1; // Cliente já fez compra
        }
    }

    fclose(arqvenda);
    return 0; // Cliente não fez compra
}
int ClienteFezVendaCNPJ(char *cnpjc) 
{
    FILE *arqvenda;
	arqvenda = fopen("Vendas.bin", "rb");
    if (arqvenda == NULL) {
        printf("Erro ao abrir o arquivo de vendas!\n");
        return 0;
    }

    Venda venda;
    while (fread(&venda, sizeof(Venda), 1, arqvenda)) {
        if (stricmp(venda.cnpjc,cnpjc)==0)//venda.cpf == cpf) 
		{
            fclose(arqvenda);
            return 1; // Cliente já fez compra
        }
    }

    fclose(arqvenda);
    return 0; // Cliente não fez compra
}

int ValidarEstado(char *estado) 
{
    const char *estados[] = {
        "AC","AL","AP","AM","BA","CE","DF","ES","GO","MA","MT","MS","MG","PA","PB",
        "PR","PE","PI","RJ","RN","RS","RO","RR","SC","SP","SE","TO"
    };
    int i; //Gambiarra
    for (i = 0; i < 27; i++) {
        if (strcmp(estado, estados[i]) == 0) return 1;
    }
    return 0;
}
int ValidarCPF(char *cpfc) 
{
	int CPF[11],i,j,Psoma=0;
	if(stricmp(cpfc,"11111111111")==0)
		return 0;
	if(stricmp(cpfc,"22222222222")==0)
			return 0;
	if(stricmp(cpfc,"33333333333")==0)
			return 0;
	if(stricmp(cpfc,"44444444444")==0)
			return 0;
	if(stricmp(cpfc,"55555555555")==0)
			return 0;
	if(stricmp(cpfc,"66666666666")==0)
			return 0;
	if(stricmp(cpfc,"77777777777")==0)
			return 0;
	if(stricmp(cpfc,"88888888888")==0)
			return 0;		
	if(stricmp(cpfc,"99999999999")==0)
			return 0;
	if(stricmp(cpfc,"00000000000")==0)
			return 0;
	for(i=0;i<11;i++)
		CPF[i] = cpfc[i]-'0';
	j=10;
	for(i=0;i<9;i++)
	{
		Psoma = Psoma+(CPF[i]*j);
		j--;
	}
	if((Psoma*10)%11==CPF[9] || (Psoma*10)%11==10 )
	{
		j=11;
		Psoma=0;
		for(i=0;i<10;i++)
		{
			Psoma = Psoma + (CPF[i]*j);
			j--;
		}
		if((Psoma*10)%11==CPF[10])
			return 1;
		else
			return 0;
	}
	else
		return 0;
}
int ValidarCNPJ(char *cnpjc)
{	
	int cnpj[14],i,j,Psoma=0;
	int Resto1;
	int PDigito;
	int Ssoma;
	int Resto2;
	int SDigito;
	
	if(stricmp(cnpjc,"11111111111111")==0)
		return 0;
	if(stricmp(cnpjc,"22222222222222")==0)
		return 0;
	if(stricmp(cnpjc,"33333333333333")==0)
		return 0;
	if(stricmp(cnpjc,"44444444444444")==0)
		return 0;
	if(stricmp(cnpjc,"55555555555555")==0)
		return 0;
	if(stricmp(cnpjc,"66666666666666")==0)
		return 0;
	if(stricmp(cnpjc,"77777777777777")==0)
		return 0;
	if(stricmp(cnpjc,"88888888888888")==0)
		return 0;		
	if(stricmp(cnpjc,"99999999999999")==0)
		return 0;
	if(stricmp(cnpjc,"00000000000000")==0)
		return 0;
	for(i=0;i<14;i++)
		cnpj[i] = cnpjc[i]-'0';
	Psoma=(cnpj[0]*5)+(cnpj[1]*4)+(cnpj[2]*3)+(cnpj[3]*2)+(cnpj[4]*9)+(cnpj[5]*8)+(cnpj[6]*7)+(cnpj[7]*6)+
	(cnpj[8]*5)+(cnpj[9]*4)+(cnpj[10]*3)+(cnpj[11]*2);
	Resto1=Psoma%11;
	if(Resto1<2)
		PDigito = 0;
	else
		PDigito = 11 - Resto1;
	if(PDigito==cnpj[12])
	{
		Ssoma = (cnpj[0]*6)+(cnpj[1]*5)+(cnpj[2]*4)+(cnpj[3]*3)+(cnpj[4]*2)+(cnpj[5]*9)+(cnpj[6]*8)+(cnpj[7]*7)+
		(cnpj[8]*6)+(cnpj[9]*5)+(cnpj[10]*4)+(cnpj[11]*3)+(cnpj[12]*2);
		Resto2 = Ssoma%11;
		if(Resto2<2)
			SDigito = 0;
		else
			SDigito = 11 - Resto2;
		if(SDigito==cnpj[13])
			return 1;
		else
			return 0;
	}
	else
		return 0;
}
int ValidarTel(char *telefone) {
	if(strlen(telefone) == 11)
		return 1;
	else
		return 0;}
int ValidarCep(char *cep) {
    return strlen(cep) == 8;
}
int ValidarNum(char *num) {
    return strlen(num)>0 && strlen(num) <6;
}
int CampoVazio(char *str) {
	if(strlen(str)<4)
		return 1;
	else
		return 0;
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
	printf("\n4- Gerenciar Compras");
	printf("\n5- Gerenciar Vendas");
	printf("\n6- Gerar Relatórios");
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
	printf("\n6- Ordenar Clientes");

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
	printf("\n6- Ordenar Itens");

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
	printf("\n6- Ordenar Fornecedores");

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
	printf("\n0- Voltar\n\nOpção: ");
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
	
	int op,op2,filtro,menor; // OPCÃO DO MENU
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
						case 6: OrdenarClientes();
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
						case 6: OrdenarProdutos();
								printf("Produtos Ordenados!\n");
								system("pause");
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
						case 6: OrdenarFornecedores();
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
						case 1: do{
								system("cls");
								printf("Relatório Produtos\n\nFiltrar relatório por:\n1- Nome\n2- Menor Quantidade\n3- Maior Quantidade\n0- Voltar\n\nOpção: ");
								scanf("%d",&filtro);
								if(filtro<0 || filtro>3)
								{
									printf("Opção Inválida!\n");
									system("pause");
									ApagarCampo();
								}
								}while(filtro<0 || filtro>3);
								switch(filtro)
								{
									case 1: OrdenarProdutos();
											RelatorioProd();
										break;
									case 2: menor = 1;
											OrdenarProdutosQtd(menor);
											RelatorioProd();
										break;
									case 3: menor = 0;
											OrdenarProdutosQtd(menor);
											RelatorioProd();
										break;
								}
								
								
							break;
						case 2: do{
								system("cls");
								printf("Relatório Insumos\n\nFiltrar relatório por:\n1- Nome\n2- Menor Quantidade\n3- Maior Quantidade\n0- Voltar\n\nOpção: ");
								scanf("%d",&filtro);
								if(filtro<0 || filtro>3)
								{
									printf("Opção Inválida!\n");
									system("pause");
									ApagarCampo();
								}
								}while(filtro<0 || filtro>3);
								switch(filtro)
								{
									case 1: OrdenarProdutos();
											RelatorioInsumo();
										break;
									case 2: menor = 1;
											OrdenarProdutosQtd(menor);
											RelatorioInsumo();
										break;
									case 3: menor = 0;
											OrdenarProdutosQtd(menor);
											RelatorioInsumo();
										break;
								}
								
								
							break;
						case 3:	do{
								system("cls");
								printf("Relatório Notas\n\nFiltrar relatório por:\n1- Cliente\n2- Menor Valor\n3- Maior Valor\n4- Data mais antiga\n5- Data mais recente\n0- Voltar\n\nOpção: ");
								scanf("%d",&filtro);
								if(filtro<0 || filtro>5)
								{
									printf("Opção Inválida!\n");
									system("pause");
									ApagarCampo();
								}
								}while(filtro<0 || filtro>5);
								switch(filtro)
								{
									case 1: OrdenarVendas();
											RelatorioNotas();
										break;
									case 2: menor = 1;
											OrdenarVendasValor(menor);
											RelatorioNotas();
										break;
									case 3: menor = 0;
											OrdenarVendasValor(menor);
											RelatorioNotas();
										break;
									case 4: menor = 1;
											OrdenarVendasData(menor);
											RelatorioNotas();
										break;
									case 5: menor = 0;
											OrdenarVendasData(menor);
											RelatorioNotas();
										break;
								}
								
								
							break;
						case 4: do{
								system("cls");
								printf("Relatório Vendas\n\nFiltrar relatório por:\n1- Cliente\n2- Menor Valor\n3- Maior Valor\n4- Data mais antiga\n5- Data mais recente\n0- Voltar\n\nOpção: ");
								scanf("%d",&filtro);
								if(filtro<0 || filtro>5)
								{
									printf("Opção Inválida!\n");
									system("pause");
									ApagarCampo();
								}
								}while(filtro<0 || filtro>5);
								switch(filtro)
								{
									case 1: OrdenarVendas();
											RelatorioVendas();
										break;
									case 2: menor = 1;
											OrdenarVendasValor(menor);
											RelatorioVendas();
										break;
									case 3: menor = 0;
											OrdenarVendasValor(menor);
											RelatorioVendas();
										break;
									case 4: menor = 1;
											OrdenarVendasData(menor);
											RelatorioVendas();
										break;
									case 5: menor = 0;
											OrdenarVendasData(menor);
											RelatorioVendas();
										break;
								}
								
								
							break;
						case 5: do{
								system("cls");
								printf("Relatório Compras\n\nFiltrar relatório por:\n1- Fornecedor\n2- Menor Valor\n3- Maior Valor\n4- Data mais antiga\n5- Data mais recente\n0- Voltar\n\nOpção: ");
								scanf("%d",&filtro);
								if(filtro<0 || filtro>5)
								{
									printf("Opção Inválida!\n");
									system("pause");
									ApagarCampo();
								}
								}while(filtro<0 || filtro>5);
								switch(filtro)
								{
									case 1: OrdenarCompras();
											RelatorioCompras();
										break;
									case 2: menor = 1;
											OrdenarComprasValor(menor);
											RelatorioCompras();
										break;
									case 3: menor = 0;
											OrdenarComprasValor(menor);
											RelatorioCompras();
										break;
									case 4: menor = 1;
											OrdenarComprasData(menor);
											RelatorioCompras();
										break;
									case 5: menor = 0;
											OrdenarComprasData(menor);
											RelatorioCompras();
										break;
								}
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
//THE END
