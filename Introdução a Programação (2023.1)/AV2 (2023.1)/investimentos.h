#define TAM 100
#define TAM_STR 255

enum menu_investimentos {
    INSERIR_INVO = 1,
    ALTERAR_INVO = 2,
    REMOVER_INVO = 3,
    BUSCAR_INVO = 4,
    BUSCAR_INVOS = 5,
    LISTAR_INVO = 6,
    LISTAR_ALF_INVO = 7,
    RETORNAR_INVO = 8
};

struct investimentos {
    char codigo_invo[6];
    char codigo_inver_invo[5];
    char tipo[10];
    double valor_apli;
    char descricao[TAM_STR];
    int prazo;
    double rentabilidade;
    char data_apli[15];
    double valorizacao;
};

extern struct investimentos *invos[TAM];

void iniciar_invos();
int inserir_codigo_invo();
void inserir_tipo(int index);
void inserir_aplic(int index);
void inserir_descricao(int index);
void inserir_prazo(int index);
void inserir_rentabilidade(int index);
void perguntar_data(int index);
void inserir_data(int index);
int verificar_data_apli(char data[]);
void valorizacao(int index);
void inserir_invo();
int buscar_codigo_invo();
void alterar_invo();
void listar_invos();
void listar_alfabetico();
void buscar_invo();
void buscar_invos_inver();
void remover_invo();
void liberar_invos();
void salvar_arquivo_invo();
void carregar_arquivo_invo();
void menu_invos();