#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "readers.h"

#define TAM_STR 255

void ler_string(char string[])
{
    fflush(stdin);
    fgets(string, TAM_STR, stdin);
    string[strcspn(string, "\n")] = '\0';
}

int ler_opcao(int quant)
{
    char str[TAM_STR], carac;
    int verif = 1, cont = 0, op;

    ler_string(str);

    while(verif == 1) {
        for(int i = 0; i < (int)strlen(str); i++) {
            carac = str[i];

            if(isdigit(carac)) {
                cont++;
            }
        }

        if(cont != (int)strlen(str)) {
            printf("Digite um numero: ");
            ler_string(str);
        } else {
            op = atoi(str);

            if(op < 1 || op > quant) {
                printf("Digite uma opcao valida: ");
                ler_string(str);
            } else {
                verif = -1;
            }
        }

        cont = 0;
    }

    return op;
}

double ler_valor()
{
    char str[TAM_STR], carac;
    int verif = 1, cont = 0, cont2 = 0, resp = 1;

    ler_string(str);

    while(verif == 1) {
        for(int i = 0; i < (int)strlen(str); i++) {
            carac = str[i];

            if(isdigit(carac)) {
                cont++;
            }

            if(carac == ' ') {
                cont2++;
            }
        }

        if((cont != ((int)strlen(str) - 1) && cont != (int)strlen(str)) || cont2 == (int)strlen(str)) {
            printf("Digite em um formato valido: ");
            ler_string(str);
        } else {
            for(int i = 0; i < (int)strlen(str); i++) {
                carac = str[i];

                if(!isdigit(carac) && (carac != ',' && carac != '.')) {
                    resp = -1;
                    break;
                }
            }

            if(resp == -1) {
                printf("Digite em um formato valido: ");
                ler_string(str);
                resp = 1;
            } else {
                verif = -1;
            }
        }

        cont = 0;
        cont2 = 0;
    }

    char *ptr = strchr(str, ',');
    if(ptr != NULL) {
        *ptr = '.';
    }
    double valor = atof(str);

    return valor;
}

void ler_codigo(char string[], int quant)
{
    char carac;

    ler_string(string);

    int verif = 1;
    while(verif == 1) {
        while(strlen(string) != quant) {
            printf("Digite na quantidade ou formato valido: ");
            ler_string(string);
        }

        for(int i = 0; i < (int)strlen(string); i++) {
            carac = string[i];
            if(!isdigit(carac)) {
                verif = -1;
                break;
            }
        }

        if(verif == -1) {
            printf("Digite na quantidade ou formato valido: ");
            ler_string(string);
            verif = 1;
        } else {
            verif = -1;
        }
    }
}

void maiusculo(char string[])
{
    for(int i = 0; i < (int)strlen(string); i++) {
        string[i] = (char)toupper(string[i]);
    }

    int naoespaco = 0, j = 0;
    for(int i = 0; i < (int)strlen(string); i++) {
        if(!isspace(string[i])) {
            naoespaco = 1;
        }

        if(naoespaco || !isspace(string[i])) {
            string[j++] = string[i];
        }
    }
    string[j] = '\0';
}

void ler_data(char string[])
{
    char carac;

    ler_string(string);

    int verif = 1;
    while(verif == 1) {
        while(strlen(string) != 10) {
            printf("Digite no formato correto: ");
            ler_string(string);
        }

        for(int i = 0; i < (int)strlen(string); i++) {
            if(!(i == 2 || i == 5))
                carac = string[i];

            if(!isdigit(carac)) {
                verif = -1;
                break;
            }
        }

        if(string[2] != '/' || string[5] != '/') {
            verif = -1;
        }

        if(verif == -1) {
            printf("Digite no formato correto: ");
            ler_string(string);
            verif = 1;
        } else {
            verif = -1;
        }
    }
}