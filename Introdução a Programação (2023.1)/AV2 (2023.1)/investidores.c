#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "investidores.h"
#include "investimentos.h"
#include "readers.h"

#define TAM 100
#define TAM_STR 255

const int SUCESSO = 0;
const int ERRO = -1;
const int JA_INSERIDO = -2;

struct investidores *invers[TAM];

char codigo_temp[TAM_STR];
char nome_temp[TAM_STR];
char cpf_temp[TAM_STR];

void iniciar_invers()
{
    for(int i = 0; i < TAM; i++) {
        invers[i] = NULL;
    }
}

int inserir_codigo_inver()
{
    char str[TAM_STR];

    printf("\nDigite o codigo do investidor (Ex: 027): ");
    ler_codigo(str, 3);

    for(int i = 0; i < TAM; i++) {
        if(invers[i] != NULL && strcmp(invers[i]->codigo_inver, str) == 0) {
            return JA_INSERIDO;
        }
    }

    strcpy(codigo_temp, str);
    printf("Codigo cadastrado com sucesso!\n");
    return SUCESSO;
}

void inserir_nome()
{
    char str[TAM_STR], carac;
    int verif = 1, cont = 0;

    printf("\nDigite o nome do investidor: ");
    ler_string(str);

    while(verif == 1) {
        for(int i = 0; i < (int)strlen(str); i++) {
            carac = str[i];
            if(!isalpha(carac) && !isspace(carac)) {
                verif = -1;
                break;
            }

            if(carac == ' ') {
                cont++;
            }
        }

        if(verif == -1 || cont == (int)strlen(str)) {
            printf("Digite um nome valido: ");
            ler_string(str);
            verif = 1;
        } else {
            verif = -1;
        }

        cont = 0;
    }

    maiusculo(str);

    strcpy(nome_temp, str);
    printf("Nome cadastrado com sucesso!\n");
}

int inserir_cpf()
{
    char str[TAM_STR];

    printf("\nDigite o CPF do investidor (Somente numeros): ");
    ler_codigo(str, 11);

    for(int i = 0; i < TAM; i++) {
        if(invers[i] != NULL && strcmp(invers[i]->cpf, str) == 0) {
            return JA_INSERIDO;
        }
    }

    strcpy(cpf_temp, str);
    printf("Cpf cadastrado com sucesso!\n");
    return SUCESSO;
}

void inserir_nasc(int index)
{
    char str[TAM_STR];
    int resp = -1;

    printf("\nDigite a data de nascimento do investidor (DD/MM/YYYY): ");
    while(resp == -1) {
        ler_data(str);

        resp = verificar_data(str);
    }

    strcpy(invers[index]->nasc, str);
    printf("Data de nascimento cadastrada com sucesso!\n");
}

int verificar_data(char data[]) {
    char str_dia[3], str_mes[3], str_ano[5];

    strncpy(str_dia, data, 2);
    str_dia[sizeof(str_dia) - 1] = '\0';

    strncpy(str_mes, data + 3, 2);
    str_mes[sizeof(str_mes) - 1] = '\0';

    strncpy(str_ano, data + 6, 4);
    str_ano[sizeof(str_ano) - 1] = '\0';

    int dia = atoi(str_dia), mes = atoi(str_mes), ano = atoi(str_ano);

    time_t t = time(NULL);
    struct tm *dataHora = localtime(&t);
    int anoAtual = dataHora->tm_year + 1900;

    int resp;

    if(dia > 31 || dia < 1) {
        printf("Digite uma data valida: ");
        return ERRO;
    } else if(mes > 12 || mes < 1) {
        printf("Digite uma data valida: ");
        return ERRO;
    } else if(dia > 29 && mes == 2) {
        printf("Digite uma data valida: ");
        return ERRO;
    } else if((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) {
        printf("Digite uma data valida: ");
        return ERRO;
    } else if(ano < 1900 || ano > anoAtual) {
        printf("Digite uma data valida: ");
        return ERRO;
    } else {
        resp = verificar_adulto(dia, mes, ano);
        return resp;
    }
}

int verificar_adulto(int dia, int mes, int ano)
{
    time_t t = time(NULL);
    struct tm atual = *localtime(&t);
    int anoAtual = atual.tm_year + 1900;
    int mesAtual = atual.tm_mon + 1;
    int diaAtual = atual.tm_mday;

    int idade = anoAtual - ano;

    if(mes > mesAtual || (mes == mesAtual && dia > diaAtual)) {
        idade--;
    }

    if(idade < 18) {
        printf("O investidor deve ter mais de 18 anos: ");
        return ERRO;
    } else {
        return SUCESSO;
    }
}

void perguntar_endereco(int index)
{
    printf("\nDeseja cadastrar o endereco do investidor? Digite 1 para SiM ou 2 para NAO: ");
    int op = ler_opcao(2);

    if(op == 2) {
        printf("Endereco nao informado!\n");
        strcpy(invers[index]->endereco, "NAO CADASTRADO");
    } else if(op == 1) {
        inserir_endereco(index);
    }
}

void inserir_endereco(int index)
{
    char str[TAM_STR], carac;
    int verif = 1, cont = 0;

    printf("Digite o endereco do investidor: ");
    ler_string(str);

    while(verif == 1) {
        for(int i = 0; i < (int)strlen(str); i++) {
            carac = str[i];

            if(isdigit(carac)) {
                cont++;
            }
        }

        if(cont == (int)strlen(str)) {
            printf("O endereco deve possuir letras e numeros, digite novamente: ");
            ler_string(str);
        } else if(cont == 0) {
            printf("O endereco deve possuir letras e numeros, digite novamente: ");
            ler_string(str);
        } else {
            verif = -1;
        }

        cont = 0;
    }

    maiusculo(str);

    strcpy(invers[index]->endereco, str);
    printf("Endereco cadastrado com sucesso!\n");
}

void inserir_salario(int index)
{
    printf("\nDigite o salario do investidor (RS): ");

    invers[index]->salario = ler_valor();
    printf("Salario cadastrado com sucesso!\n");
}

void inserir_inver()
{
    int index = -1, resp;

    for(int i = 0; i < TAM; i++) {
        if(invers[i] == NULL) {
            index = i;
            break;
        }
    }

    if(index == -1) {
        printf("Limite de cadastros excedido!!!\n");
    } else {
        printf("                  CADASTRO DO INVESTIDOR               \n");
        resp = inserir_codigo_inver();
        if(resp == JA_INSERIDO) {
            printf("Codigo ja cadastrado!\n");
        } else {
            inserir_nome();
            resp = inserir_cpf();
            if(resp == JA_INSERIDO) {
                printf("CPF ja cadastrado!\n");
            } else {
                invers[index] = malloc(sizeof(struct investidores));
                strcpy(invers[index]->codigo_inver, codigo_temp);
                strcpy(invers[index]->nome, nome_temp);
                strcpy(invers[index]->cpf, cpf_temp);

                inserir_nasc(index);
                perguntar_endereco(index);
                inserir_salario(index);
            }
        }
        printf("---------------------------------------------------------\n");
    }
}

int buscar_codigo_inver()
{
    char str[TAM_STR];

    ler_codigo(str, 3);

    int index = -1;
    for(int i = 0; i < TAM; i++) {
        if(invers[i] != NULL && strcmp(str, invers[i]->codigo_inver) == 0) {
            index = i;
            break;
        }
    }

    return index;
}

void alterar_inver()
{
    printf("                    ALTERAR INVESTIDOR                  \n");
    printf("\nDigite o codigo do investidor que deseja alterar: ");
    int index = buscar_codigo_inver();

    if(index >= 0) {
        printf("\n- Qual o dado que deseja alterar?\n");
        printf("1 - Nome\n");
        printf("2 - Cpf\n");
        printf("3 - Data de nascimento\n");
        printf("4 - Endereco\n");
        printf("5 - Salario\n");
        printf("6 - RETORNAR\n");

        printf("Opcao: ");
        int op = ler_opcao(6);

        if(op == 1) {
            inserir_nome();
            strcpy(invers[index]->nome, nome_temp);
        } else if(op == 2) {
            int resp = inserir_cpf();
            if(resp == SUCESSO) {
                strcpy(invers[index]->cpf, cpf_temp);
            } else {
                printf("CPF ja cadastrado!\n");
            }
        } else if(op == 3) {
            inserir_nasc(index);
        } else if(op == 4) {
            printf("\n");
            inserir_endereco(index);
        } else if(op == 5) {
            inserir_salario(index);
        }
    } else {
        printf("Investidor nao encontrado!\n");
    }
    printf("---------------------------------------------------------\n");
}

void printar_info_inver(int index)
{
    printf("\nCodigo do investidor: %s\n", invers[index]->codigo_inver);
    printf("- Nome: %s\n", invers[index]->nome);
    printf("- CPF: %s\n", invers[index]->cpf);
    printf("- Endereco: %s\n", invers[index]->endereco);
    printf("- Data de Nascimento: %s\n", invers[index]->nasc);
    printf("- Salario: RS %.2lf\n", invers[index]->salario);
    patrimonio(index);
    printf("- Patrimonio: RS %.2lf\n", invers[index]->patrimonio);
}

void listar_invers()
{
    printf("                  INVESTIDORES CADASTRADOS              \n");
    for(int i = 0; i < TAM; i++) {
        if(invers[i] != NULL) {
            printar_info_inver(i);
        }
    }
    printf("---------------------------------------------------------\n");
}

void buscar_inver()
{
    printf("                    BUSCAR INVESTIDOR             \n");
    printf("\nDigite o codigo do investidor que deseja buscar: ");
    int index = buscar_codigo_inver();

    if(index >= 0) {
        printar_info_inver(index);
    } else {
        printf("Investidor nao encontrado!\n");
    }
    printf("---------------------------------------------------------\n");
}

void remover_inver()
{
    printf("                    REMOVER INVESTIDOR             \n");
    printf("\nDigite o codigo do investidor que voce deseja remover: ");
    int index = buscar_codigo_inver();

    if(index == -1) {
        printf("Investidor nao encontrado!\n");
    } else {
        printf("\nDeseja realmente remover esse investidor e todos os seus investimentos?\n");
        printf("Digite 1 para SiM ou 2 para NAO: ");
        int op = ler_opcao(2);

        if(op == 1) {
            for(int i = 0; i < TAM; i++) {
                if(invos[i] != NULL && strcmp(invers[index]->codigo_inver, invos[i]->codigo_inver_invo) == 0) {
                    free(invos[i]);
                    invos[i] = NULL;
                }
            }

            printf("\nInvestidor %s removido com sucesso!\n", invers[index]->nome);
            free(invers[index]);
            invers[index] = NULL;
        } else {
            printf("\nRemocao cancelada!\n");
        }
    }
    printf("---------------------------------------------------------\n");
}

void listar_tipo()
{
    printf("              LISTA POR TIPO DE INVESTIMENTO            \n");
    char str[TAM_STR];

    printf("\n- Qual tipo de investimmento deseja buscar os investidores?\n");
    printf("1 - CDB\n");
    printf("2 - CRI\n");
    printf("3 - CRA\n");
    printf("4 - LCA\n");
    printf("5 - LCI\n");
    printf("6 - Acao\n");

    printf("Opcao: ");
    int op = ler_opcao(6);

    if(op == 1) {
        strcpy(str, "CDB");
    } else if(op == 2) {
        strcpy(str, "CRI");
    } else if(op == 3) {
        strcpy(str, "CRA");
    } else if(op == 4) {
        strcpy(str, "LCA");
    } else if(op == 5) {
        strcpy(str, "LCI");
    } else if(op == 6) {
        strcpy(str, "Acao");
    }

    int cont = 0;
    for(int i = 0; i < TAM; i++) {
        if(invos[i] != NULL && strcmp(str, invos[i]->tipo) == 0) {
            cont++;
        }
    }

    if(cont > 0) {
        char codigo_tipo[cont][10];
        int k = 0;
        for(int i = 0; i < TAM; i++) {
            if(invos[i] != NULL && strcmp(str, invos[i]->tipo) == 0) {
                strcpy(codigo_tipo[k++], invos[i]->codigo_inver_invo);
            }
        }

        for(int i = 0; i < cont; i++) {
            for(int j = i + 1; j < cont; j++) {
                if(strcmp(codigo_tipo[j], codigo_tipo[i]) == 0) {
                    strcpy(codigo_tipo[j], "NOT");
                }
            }
        }

        printf("\nOs investidores que possuem investimento em %s sao:\n", str);
        for(int i = 0; i < cont; i++) {
            for(int j = 0; j < TAM; j++) {
                if(invers[j] != NULL && (strcmp(invers[j]->codigo_inver, codigo_tipo[i]) == 0)) {
                    printar_info_inver(j);
                }
            }
        }
    } else {
        printf("\nNao ha investimentos cadastrados desse tipo!\n");
    }
    printf("---------------------------------------------------------\n");
}

void patrimonio(int index)
{
    double soma = 0;

    for(int i = 0; i < TAM; i++) {
        if(invos[i] != NULL && strcmp(invers[index]->codigo_inver, invos[i]->codigo_inver_invo) == 0) {
            valorizacao(i);
            soma = soma + invos[i]->valor_apli + invos[i]->valorizacao;
        }
    }

    invers[index]->patrimonio = soma;
}

void listar_patrimonio()
{
    printf("                 LISTA POR PATRIMONIO            \n");
    int cont_inv = 0;
    for(int i = 0; i < TAM; i++) {
        if(invers[i] != NULL) {
            cont_inv++;
        }
    }

    double patrimonios[cont_inv];
    int k = 0;
    for(int i = 0; i < TAM; i++) {
        if(invers[i] != NULL) {
            patrimonio(i);
            patrimonios[k++] = invers[i]->patrimonio;
        }
    }

    for(int i = 0; i < cont_inv; i++) {
        for(int j = i + 1; j < cont_inv; j++) {
            if(patrimonios[j] == patrimonios[i]) {
                patrimonios[j] = -1;
            }
        }
    }

    double aux;
    for(int i = 0; i < cont_inv; i++) {
        for(int j = i + 1; j < cont_inv; j++) {
            if(patrimonios[j] < patrimonios[i]) {
                aux = patrimonios[i];
                patrimonios[i] = patrimonios[j];
                patrimonios[j] = aux;
            }
        }
    }

    for(int i = 0; i < cont_inv; i++) {
        for(int j = 0; j < TAM; j++) {
            if(invers[j] != NULL && patrimonios[i] == invers[j]->patrimonio) {
                printf("\nCodigo do investidor: %s\n", invers[j]->codigo_inver);
                printf("- Nome: %s\n", invers[j]->nome);
                printf("- Patrimonio: RS %.2lf\n", invers[j]->patrimonio);
            }
        }
    }
    printf("---------------------------------------------------------\n");
}

void liberar_invers()
{
    for(int i = 0; i < TAM; ++i) {
        if(invers[i] != NULL) {
            free(invers[i]);
        }
    }
}

void salvar_arquivo_inver()
{
    FILE *f1 = fopen("investidores.bin","wb+");
    if(f1 == NULL) {
        printf("Não foi possivel recriar o arquivo!\n");
        exit(1);
    }

    fseek(f1, 0, SEEK_SET);
    for(int i = 0; i < TAM; i++) {
        if(invers[i] != NULL) {
            fwrite(invers[i], sizeof(struct investidores), 1, f1);
        }
    }

    fclose(f1);
}

void carregar_arquivo_inver()
{
    FILE *f1 = fopen("investidores.bin","rb+");
    if(f1 == NULL) {
        printf("Criando arquivo dos investidores!\n");
        f1 = fopen("investidores.bin", "wb+");
        if(f1 == NULL) {
            printf("Não foi possivel criar o arquivo!\n");
            exit(1);
        }
    }

    fseek(f1, 0, SEEK_SET);
    for(int i = 0; i < TAM; i++) {
        if(invers[i] == NULL) {
            invers[i] = malloc(sizeof(struct investidores));
            if(fread(invers[i], sizeof(struct investidores), 1, f1) != 1) {
               free(invers[i]);
               invers[i] = NULL;
               break;
            }
        }
    }

    fclose(f1);
}

void menu_invers()
{
    int op;

    do {
        printf("\n================== MENU INVESTIDORES ====================\n");
        printf("---------------------------------------------------------\n");
        printf("1 - Inserir investidor\n");
        printf("2 - Alterar investidor\n");
        printf("3 - Remover investidor\n");
        printf("4 - Buscar Investidor\n");
        printf("5 - Listar todos os investidores\n");
        printf("6 - Listar por tipo de investimento\n");
        printf("7 - Listar por ordem crescente de patrimonio\n");
        printf("8 - Retornar ao menu principal\n");

        printf("Opcao: ");
        op = ler_opcao(8);

        printf("---------------------------------------------------------\n");

        switch(op) {
            case INSERIR_INVER:
                inserir_inver();
                break;

            case ALTERAR_INVER:
                alterar_inver();
                break;

            case REMOVER_INVER:
                remover_inver();
                break;

            case BUSCAR_INVER:
                buscar_inver();
                break;

            case LISTAR_INVER:
                listar_invers();
                break;

            case TIPO_INVER:
                listar_tipo();
                break;

            case PATRIM_INVER:
                listar_patrimonio();
                break;
        }

    } while(op != RETORNAR_INVER);
}