\
#ifndef EXECUCAO_H
#define EXECUCAO_H
typedef struct {
    int id_execucao;
    int id_os;
    char data_execucao[20];
    char tecnico_responsavel[128];
    char observacoes[512];
} Execucao;
int exec_create(const Execucao *e);
char *exec_list_json();
#endif
