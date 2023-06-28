#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include "investidores.h"
#include "investimentos.h"
#include "readers.h"

#define TAM 100
#define TAM_STR 255

const int SUCCESS = 0;
const int ERROR = -1;
const int ERROR_INSERTED = -2;

struct investimentos *invos[TAM];

char codigo_invo_temp[6];

void iniciar_invos()
{
    for(int i = 0; i < TAM; i++) {
        invos[i] = NULL;
    }
}

int inserir_codigo_invo()
{
    char str[TAM_STR];

    printf("\nDigite o codigo do investimento (Ex: 1762): ");
    ler_codigo(str, 4);

    for(int i = 0; i < TAM; i++) {
        if(invos[i] != NULL && strcmp(invos[i]->codigo_invo, str) == 0) {
            return ERROR_INSERTED;
        }
    }

    strcpy(codigo_invo_temp, str);
    printf("Codigo cadastrado com sucesso!\n");
    return SUCCESS;
}

void inserir_tipo(int index)
{
    printf("\nQual tipo de investimmento deseja cadastrar?\n");
    printf("1- CDB | ");
    printf("2- CRI | ");
    printf("3- CRA | ");
    printf("4- LCA | ");
    printf("5- LCI | ");
    printf("6- Acao\n");

    printf("Opcao: ");
    int op = ler_opcao(6);

    if(op == 1) {
        strcpy(invos[index]->tipo, "CDB");
    } else if(op == 2) {
        strcpy(invos[index]->tipo, "CRI");
    } else if(op == 3) {
        strcpy(invos[index]->tipo, "CRA");
    } else if(op == 4) {
        strcpy(invos[index]->tipo, "LCA");
    } else if(op == 5) {
        strcpy(invos[index]->tipo, "LCI");
    } else if(op == 6) {
        strcpy(invos[index]->tipo, "Acao");
    }

    printf("Tipo de investimento cadastrado com sucesso!\n");
}

void inserir_aplic(int index)
{
    printf("\nDigite o valor da aplicacao (RS): ");

    invos[index]->valor_apli = ler_valor();
    printf("Valor da aplicacao cadastrado com sucesso!\n");
}

void inserir_descricao(int index)
{
    char str[TAM_STR], carac;
    int verif = 1, cont = 0;

    printf("\nDigite a descricao do investimento: ");
    ler_string(str);

    while(verif == 1) {
        for(int i = 0; i < (int)strlen(str); i++) {
            carac = str[i];

            if(isdigit(carac)) {
                cont++;
            }
        }

        if(cont == (int)strlen(str)) {
            printf("Digite uma descricao melhor: ");
            ler_string(str);
        } else {
            verif = -1;
        }

        cont = 0;
    }

    maiusculo(str);

    strcpy(invos[index]->descricao, str);
    printf("Descricao cadastrada com sucesso!\n");
}

void inserir_prazo(int index)
{
    char str[TAM_STR], carac;
    int verif = 1, cont = 0;

    printf("\nDigite o prazo do investimento (em dias): ");
    ler_string(str);

    while(verif == 1) {
        for(int i = 0; i < (int)strlen(str); i++) {
            carac = str[i];
            if(!isdigit(carac)) {
                verif = -1;
                break;
            }

            if(carac == ' ') {
                cont++;
            }
        }

        if(verif == -1 || cont == (int)strlen(str)) {
            printf("Digite um prazo valido: ");
            ler_string(str);
            verif = 1;
        } else {
            verif = -1;
        }
    }

    int prazo = atoi(str);

    invos[index]->prazo = prazo;
    printf("Prazo cadastrado com sucesso!\n");
}

void inserir_rentabilidade(int index)
{
    printf("\nDigite o valor da rentabilidade anual (Em %%): ");

    invos[index]->rentabilidade = ler_valor();
    printf("Rentabilidade anual cadastrada com sucesso!\n");
}

void perguntar_data(int index)
{
    printf("\nDeseja digitar a data do investimento? Digite 1 para SiM ou 2 para NAO: ");
    int op = ler_opcao(2);

    if(op == 1) {
        inserir_data(index);
    } else {
        printf("A data da aplicacao sera definida como a atual!\n");
        time_t tempo_atual;
        struct tm *tempo_local;
        char data_atual[15];

        time(&tempo_atual);
        tempo_local = localtime(&tempo_atual);

        strftime(data_atual, sizeof(data_atual), "%d/%m/%Y", tempo_local);
        strcpy(invos[index]->data_apli, data_atual);
    }
}

void inserir_data(int index)
{
    char str[TAM_STR];
    int resp = -1;

    printf("Digite a data da aplicacao do investimento (DD/MM/YYYY): ");
    while(resp == -1) {
        ler_data(str);

        resp = verificar_data_apli(str);
    }

    strcpy(invos[index]->data_apli, str);
    printf("Data da aplicacao cadastrada com sucesso!\n");
}

int verificar_data_apli(char data[])
{
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

    if(dia > 31 || dia < 1) {
        printf("Digite uma data valida: ");
        return ERROR;
    } else if(mes > 12 || mes < 1) {
        printf("Digite uma data valida: ");
        return ERROR;
    } else if(dia > 29 && mes == 2) {
        printf("Digite uma data valida: ");
        return ERROR;
    } else if((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) {
        printf("Digite uma data valida: ");
        return ERROR;
    } else if(ano < 1900 || ano > anoAtual) {
        printf("Digite uma data valida: ");
        return ERROR;
    } else {
        struct tm tempo_inicial = {0};
        tempo_inicial.tm_year = ano - 1900;
        tempo_inicial.tm_mon = mes - 1;
        tempo_inicial.tm_mday = dia;

        time_t tempo_atual;
        time(&tempo_atual);

        time_t diferenca = difftime(tempo_atual, mktime(&tempo_inicial));
        int dias = diferenca / (60 * 60 * 24);

        if(dias < 0) {
            printf("Digite uma data menor que a atual: ");
            return ERROR;
        } else {
            return SUCCESS;
        }
    }
}

void valorizacao(int index)
{
    char str_dia[3], str_mes[3], str_ano[5];

    strncpy(str_dia, invos[index]->data_apli, 2);
    str_dia[sizeof(str_dia) - 1] = '\0';

    strncpy(str_mes, invos[index]->data_apli + 3, 2);
    str_mes[sizeof(str_mes) - 1] = '\0';

    strncpy(str_ano, invos[index]->data_apli + 6, 4);
    str_ano[sizeof(str_ano) - 1] = '\0';

    int dia = atoi(str_dia), mes = atoi(str_mes), ano = atoi(str_ano);

    struct tm tempo_inicial = {0};
    tempo_inicial.tm_year = ano - 1900;
    tempo_inicial.tm_mon = mes - 1;
    tempo_inicial.tm_mday = dia;

    time_t tempo_atual;
    time(&tempo_atual);

    time_t diferenca = difftime(tempo_atual, mktime(&tempo_inicial));

    int dias = diferenca / (60 * 60 * 24);

    double rent_anual, tx_d, calc, valorizacao;
    rent_anual = (invos[index]->rentabilidade / 100.0) + 1;
    tx_d = pow(rent_anual, 1.0 / 365.0);

    if(dias > invos[index]->prazo) {
        calc = invos[index]->valor_apli * pow(tx_d, invos[index]->prazo);
    } else {
        calc = invos[index]->valor_apli * pow(tx_d, dias);
    }

    valorizacao = calc - invos[index]->valor_apli;
    invos[index]->valorizacao = valorizacao;
}

void inserir_invo()
{
    int index = -1, index_inver, resp;

    for(int i = 0; i < TAM; i++) {
        if(invos[i] == NULL) {
            index = i;
            break;
        }
    }

    if(index == -1) {
        printf("Limite de cadastros excedido!!!\n");
    } else {
        printf("                 CADASTRO DO INVESTIMENTO              \n");
        printf("\nDigite o codigo do investidor que deseja cadastrar um investimento: ");
        index_inver = buscar_codigo_inver();
        if(index_inver == -1) {
            printf("\nNao ha investidor cadastrado com esse codigo\n");
        } else {
            printf("Investidor encontrado!\n");
            resp = inserir_codigo_invo();
            if(resp == ERROR_INSERTED) {
                printf("Codigo ja cadastrado!\n");
            } else {
                invos[index] = malloc(sizeof(struct investimentos));
                strcpy(invos[index]->codigo_inver_invo, invers[index_inver]->codigo_inver);
                strcpy(invos[index]->codigo_invo, codigo_invo_temp);
                inserir_tipo(index);
                inserir_aplic(index);
                inserir_descricao(index);
                inserir_prazo(index);
                inserir_rentabilidade(index);
                perguntar_data(index);
            }
        }
        printf("---------------------------------------------------------\n");
    }
}

int buscar_codigo_invo()
{
    char str[TAM_STR];

    ler_codigo(str, 4);

    int index = -1;
    for(int i = 0; i < TAM; i++) {
        if(invos[i] != NULL && strcmp(str, invos[i]->codigo_invo) == 0) {
            index = i;
            break;
        }
    }

    return index;
}

void alterar_invo()
{
    printf("                   ALTERAR INVESTIMENTO                  \n");
    printf("\nDigite o codigo do investimento que deseja alterar: ");
    int index = buscar_codigo_invo();

    if(index >= 0) {
        printf("\n- Qual o dado que voce deseja alterar?\n");
        printf("1 - Tipo de investimento\n");
        printf("2 - Valor aplicado\n");
        printf("3 - Descricao\n");
        printf("4 - Prazo da aplicacao\n");
        printf("5 - Rentabilidade anual\n");
        printf("6 - Data da aplicacao\n");
        printf("7 - RETORNAR\n");

        printf("Opcao: ");
        int op = ler_opcao(7);

        if(op == 1) {
            inserir_tipo(index);
        } else if(op == 2) {
            inserir_aplic(index);
        } else if(op == 3) {
            inserir_descricao(index);
        } else if(op == 4) {
            inserir_prazo(index);
        } else if(op == 5) {
            inserir_rentabilidade(index);
        } else if(op == 6) {
            printf("\n");
            inserir_data(index);
        }
    } else {
        printf("Nao ha investimento cadastrado com esse codigo\n");
    }
    printf("---------------------------------------------------------\n");
}

void printar_info_invo(int index)
{
    printf("\nCodigo do investimento: %s\n", invos[index]->codigo_invo);
    printf("- Cod. investidor: %s\n", invos[index]->codigo_inver_invo);
    printf("- Tipo de investimento: %s\n", invos[index]->tipo);
    printf("- Descricao: %s\n", invos[index]->descricao);
    printf("- Prazo da aplicacao: %d dias\n", invos[index]->prazo);
    printf("- Rentabilidade anual: %.2lf%%\n", invos[index]->rentabilidade);
    printf("- Data da aplicacao: %s\n", invos[index]->data_apli);
    printf("- Valor aplicado: %.2lf reais\n", invos[index]->valor_apli);
    valorizacao(index);
    printf("- Valorizacao: %.2lf reais\n", invos[index]->valorizacao);
}

void listar_invos()
{
    printf("                INVESTIMENTOS CADASTRADOS            \n");
    for(int i = 0; i < TAM; i++) {
        if(invos[i] != NULL) {
            printar_info_invo(i);
        }
    }
    printf("---------------------------------------------------------\n");
}

void listar_alfabetico()
{
    printf("               LISTA ALFABETICA POR TIPO            \n");
    char tipo_alf[6][6];
    strcpy(tipo_alf[0], "Acao");
    strcpy(tipo_alf[1], "CDB");
    strcpy(tipo_alf[2], "CRA");
    strcpy(tipo_alf[3], "CRI");
    strcpy(tipo_alf[4], "LCA");
    strcpy(tipo_alf[5], "LCI");

    for(int j = 0; j < 6; j++) {
        for(int i = 0; i < TAM; i++) {
            if(invos[i] != NULL && strcmp(invos[i]->tipo, tipo_alf[j]) == 0) {
                printar_info_invo(i);
            }
        }
    }
    printf("---------------------------------------------------------\n");
}

void buscar_invo()
{
    printf("                  BUSCAR INVESTIMENTO            \n");
    printf("\nDigite o codigo do investimento que deseja buscar: ");
    int index = buscar_codigo_invo();

    if(index >= 0) {
        printar_info_invo(index);
    } else {
        printf("Investimento nao encontrado!\n");
    }
    printf("---------------------------------------------------------\n");
}

void buscar_invos_inver()
{
    printf("               INVESTIMENTOS DE UM INVESTIDOR          \n");
    printf("\nDigite o codigo do investidor que deseja buscar os investimentos: ");
    int index = buscar_codigo_inver();

    if(index == -1) {
        printf("Investidor nao encontrado\n");
    } else {
        int index_invo = -1;
        for(int i = 0; i < TAM; i++) {
            if(invos[i] != NULL && strcmp(invers[index]->codigo_inver, invos[i]->codigo_inver_invo) == 0) {
                index_invo = i;
                break;
            }
        }

        if(index_invo == -1) {
            printf("Nao ha investimentos cadastrados para esse investidor!\n");
        } else {
            for(int i = 0; i < TAM; i++) {
                if(invos[i] != NULL && strcmp(invers[index]->codigo_inver, invos[i]->codigo_inver_invo) == 0) {
                    printar_info_invo(i);
                }
            }
        }
    }
    printf("---------------------------------------------------------\n");
}

void remover_invo()
{
    printf("                  REMOVER INVESTIMENTO            \n");
    printf("\nDigite o codigo do investimento que voce deseja remover: ");
    int index = buscar_codigo_invo();

    if(index >= 0) {
        printf("Voce deseja realmente remover esse investimento? Digite 1 para SiM ou 2 para NAO: ");
        int op = ler_opcao(2);

        if(op == 1) {
            free(invos[index]);
            invos[index] = NULL;
            printf("Investimento removido com sucesso!\n");
        } else {
            printf("Remocao cancelada!\n");
        }
    } else {
        printf("Investimento nao encontrado!\n");
    }
    printf("---------------------------------------------------------\n");
}

void liberar_invos()
{
    for(int i = 0; i < TAM; ++i) {
        if(invos[i] != NULL) {
            free(invos[i]);
        }
    }
}

void salvar_arquivo_invo()
{
    FILE *f2 = fopen("investimentos.bin","wb+");
    if(f2 == NULL) {
        printf("Não foi possivel recriar o arquivo!\n");
        exit(1);
    }

    fseek(f2, 0, SEEK_SET);
    for(int i = 0; i < TAM; i++) {
        if(invos[i] != NULL) {
            fwrite(invos[i], sizeof(struct investimentos), 1, f2);
        }
    }

    fclose(f2);
}

void carregar_arquivo_invo()
{
    FILE *f2 = fopen("investimentos.bin","rb+");
    if(f2 == NULL) {
        printf("Criando arquivo dos investimentos!\n");
        f2 = fopen("investimentos.bin", "wb+");
        if(f2 == NULL) {
            printf("Não foi possivel criar o arquivo!\n");
            exit(1);
        }
    }

    fseek(f2, 0, SEEK_SET);
    for(int i = 0; i < TAM; i++) {
        if(invos[i] == NULL) {
            invos[i] = malloc(sizeof(struct investimentos));
            if(fread(invos[i], sizeof(struct investimentos), 1, f2) != 1) {
                free(invos[i]);
                invos[i] = NULL;
                break;
            }
        }
    }

    fclose(f2);
}

void menu_invos()
{
    int op;

    do {
        printf("\n================== MENU INVESTIMENTOS ===================\n");
        printf("---------------------------------------------------------\n");
        printf("1 - Inserir investimento\n");
        printf("2 - Alterar investimento\n");
        printf("3 - Remover investimento\n");
        printf("4 - Buscar investimento\n");
        printf("5 - Buscar investimentos de um investidor\n");
        printf("6 - Listar todos os investimentos\n");
        printf("7 - Listar em ordem alfabetica\n");
        printf("8 - Retornar ao menu principal\n");

        printf("Opcao: ");
        op = ler_opcao(8);

        printf("---------------------------------------------------------\n");

        switch(op) {
            case INSERIR_INVO:
                inserir_invo();
                break;

            case ALTERAR_INVO:
                alterar_invo();
                break;

            case REMOVER_INVO:
                remover_invo();
                break;

            case BUSCAR_INVO:
                buscar_invo();
                break;

            case BUSCAR_INVOS:
                buscar_invos_inver();
                break;

            case LISTAR_INVO:
                listar_invos();
                break;

            case LISTAR_ALF_INVO:
                listar_alfabetico();
                break;
        }

    } while(op != RETORNAR_INVO);
}