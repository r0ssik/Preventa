\
#ifndef OS_H
#define OS_H
typedef struct {
    int id_os;
    int id_equipamento;
    int id_tipo;
    char data_abertura[20];
    char descricao_problema[256];
    char status[32];
} OS;
int os_create(const OS *o);
char *os_list_json();
int os_delete(int id);
#endif
