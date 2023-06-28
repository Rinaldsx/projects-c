#define TAM 100
#define TAM_STR 255

enum menu_investidores {
    INSERIR_INVER = 1,
    ALTERAR_INVER = 2,
    REMOVER_INVER = 3,
    BUSCAR_INVER = 4,
    LISTAR_INVER = 5,
    TIPO_INVER = 6,
    PATRIM_INVER = 7,
    RETORNAR_INVER = 8
};

struct investidores {
    char codigo_inver[5];
    char nome[TAM_STR];
    char cpf[15];
    char endereco[TAM_STR];
    char nasc[15];
    double salario;
    double patrimonio;
};

extern struct investidores *invers[TAM];

void iniciar_invers();
int inserir_codigo_inver();
void inserir_nome();
int inserir_cpf();
void inserir_nasc(int index);
int verificar_data(char data[]);
int verificar_adulto(int dia, int mes, int ano);
void perguntar_endereco(int index);
void inserir_endereco(int index);
void inserir_salario(int index);
void inserir_inver();
int buscar_codigo_inver();
void alterar_inver();
void printar_info_inver(int index);
void listar_invers();
void buscar_inver();
void remover_inver();
void listar_tipo();
void patrimonio(int index);
void listar_patrimonio();
void liberar_invers();
void salvar_arquivo_inver();
void carregar_arquivo_inver();
void menu_invers();