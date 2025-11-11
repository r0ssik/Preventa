\
#ifndef EQUIPAMENTO_H
#define EQUIPAMENTO_H
typedef struct {
    int id;
    char nome[128];
    char modelo[64];
    char setor[64];
    char data_aquisicao[20];
} Equipamento;
int equipamento_create(const Equipamento *e);
char *equipamento_list_json();
int equipamento_update(const Equipamento *e);
int equipamento_delete(int id);
#endif
