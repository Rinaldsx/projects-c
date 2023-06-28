#include <stdio.h>
#include "investidores.h"
#include "investimentos.h"
#include "readers.h"

#define TAM_STR 255

enum menu_principal {
    m_investidores = 1,
    m_investimentos = 2,
    encerrar = 3
};

int main()
{
    iniciar_invers();
    iniciar_invos();

    carregar_arquivo_inver();
    carregar_arquivo_invo();

    int op;

    do {
        printf("\n==================== MENU PRINCIPAL =====================\n");
        printf("---------------------------------------------------------\n");
        printf("1 - Menu Investidores\n");
        printf("2 - Menu investimentos\n");
        printf("3 - Encerrar programa\n");

        printf("Opcao: ");
        op = ler_opcao(3);

        printf("---------------------------------------------------------\n");

        switch(op) {
            case m_investidores:
                menu_invers();
                break;

            case m_investimentos:
                menu_invos();
                break;

            case encerrar:
                printf("Programa encerrado e dados salvos!\n");
                break;
        }

    } while(op != encerrar);

    salvar_arquivo_inver();
    salvar_arquivo_invo();

    liberar_invers();
    liberar_invos();

    return 0;
}