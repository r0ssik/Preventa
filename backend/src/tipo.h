\
#ifndef TIPO_H
#define TIPO_H
typedef struct {
    int id;
    char descricao[128];
    int periodicidade_dias;
} Tipo;
int tipo_create(const Tipo *t);
char *tipo_list_json();
int tipo_delete(int id);
#endif
