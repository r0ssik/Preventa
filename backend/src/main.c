\
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db.h"
#include "equipamento.h"
#include "tipo.h"
#include "os.h"
#include "execucao.h"

void print_json_header() { printf("Content-Type: application/json\r\n\r\n"); }
void print_text_header() { printf("Content-Type: text/plain\r\n\r\n"); }

char *get_qs_param(const char *qs, const char *key) {
    if(!qs || !key) return NULL;
    char *dup = strdup(qs);
    char *token = strtok(dup, "&");
    while(token) {
        char *eq = strchr(token, '=');
        if(eq) {
            *eq = '\0';
            if(strcmp(token, key) == 0) {
                char *res = strdup(eq + 1);
                free(dup);
                return res;
            }
        }
        token = strtok(NULL, "&");
    }
    free(dup);
    return NULL;
}

char *read_stdin_all() {
    char *lenstr = getenv("CONTENT_LENGTH");
    if(!lenstr) return NULL;
    int len = atoi(lenstr);
    if(len <= 0) return NULL;
    char *buf = malloc(len + 1);
    fread(buf, 1, len, stdin);
    buf[len] = '\0';
    return buf;
}

char *form_get_field(const char *form, const char *key, char *dest, size_t size) {
    if(!form || !key) { if(dest) dest[0]='\0'; return NULL; }
    char pattern[128];
    snprintf(pattern, sizeof(pattern), "%s=", key);
    char *start = strstr(form, pattern);
    if(!start) { if(dest) dest[0]='\0'; return NULL; }
    start += strlen(pattern);
    char *end = strchr(start, '&');
    size_t len = end ? (size_t)(end - start) : strlen(start);
    if(len >= size) len = size - 1;
    // URL decode percent-encoding and '+' to space
    size_t di = 0;
    for(size_t i=0; i<len && di < size-1; ++i) {
        char ch = start[i];
        if(ch == '+') dest[di++] = ' ';
        else if(ch == '%' && i+2 < len) {
            char hex[3] = { start[i+1], start[i+2], 0 };
            dest[di++] = (char) strtol(hex, NULL, 16);
            i += 2;
        } else dest[di++] = ch;
    }
    dest[di] = '\0';
    return dest;
}

int main(void) {
    char *qs = getenv("QUERY_STRING");
    char *action = get_qs_param(qs, "action");

    // Equipamentos
    if(action && strcmp(action, "list_equipamentos") == 0) {
        print_json_header();
        char *json = equipamento_list_json();
        printf("%s", json?json:"[]");
        free(json);
    } else if(action && strcmp(action, "create_equipamento") == 0) {
        char *body = read_stdin_all();
        if(body) {
            Equipamento e; memset(&e,0,sizeof(e));
            form_get_field(body,"nome",e.nome,sizeof(e.nome));
            form_get_field(body,"modelo",e.modelo,sizeof(e.modelo));
            form_get_field(body,"setor",e.setor,sizeof(e.setor));
            form_get_field(body,"data_aquisicao",e.data_aquisicao,sizeof(e.data_aquisicao));
            equipamento_create(&e);
            free(body);
        }
        print_text_header(); printf("OK");
    } else if(action && strcmp(action, "update_equipamento") == 0) {
        char *body = read_stdin_all();
        if(body) {
            Equipamento e; memset(&e,0,sizeof(e));
            char idbuf[16]; form_get_field(body,"id",idbuf,sizeof(idbuf)); e.id = atoi(idbuf);
            form_get_field(body,"nome",e.nome,sizeof(e.nome));
            form_get_field(body,"modelo",e.modelo,sizeof(e.modelo));
            form_get_field(body,"setor",e.setor,sizeof(e.setor));
            form_get_field(body,"data_aquisicao",e.data_aquisicao,sizeof(e.data_aquisicao));
            equipamento_update(&e);
            free(body);
        }
        print_text_header(); printf("OK");
    } else if(action && strcmp(action, "delete_equipamento") == 0) {
        char *id = get_qs_param(qs,"id");
        if(id) { equipamento_delete(atoi(id)); free(id); }
        print_text_header(); printf("OK");
    }

    // Tipos de manutenção
    else if(action && strcmp(action, "list_tipos") == 0) {
        print_json_header();
        char *json = tipo_list_json();
        printf("%s", json?json:"[]"); free(json);
    } else if(action && strcmp(action, "create_tipo") == 0) {
        char *body = read_stdin_all();
        if(body) {
            Tipo t; memset(&t,0,sizeof(t));
            form_get_field(body,"descricao",t.descricao,sizeof(t.descricao));
            char per[16]; form_get_field(body,"periodicidade",per,sizeof(per));
            t.periodicidade_dias = per[0]?atoi(per):0;
            tipo_create(&t); free(body);
        }
        print_text_header(); printf("OK");
    } else if(action && strcmp(action, "delete_tipo") == 0) {
        char *id = get_qs_param(qs,"id"); if(id){ tipo_delete(atoi(id)); free(id); }
        print_text_header(); printf("OK");
    }

    // Ordens de Servico (OS)
    else if(action && strcmp(action, "list_os") == 0) {
        print_json_header(); char *json = os_list_json(); printf("%s", json?json:"[]"); free(json);
    } else if(action && strcmp(action, "create_os") == 0) {
        char *body = read_stdin_all();
        if(body) {
            OS osr; memset(&osr,0,sizeof(osr));
            char ideq[16], idt[16];
            form_get_field(body,"id_equipamento",ideq,sizeof(ideq)); osr.id_equipamento = atoi(ideq);
            form_get_field(body,"id_tipo",idt,sizeof(idt)); osr.id_tipo = atoi(idt);
            form_get_field(body,"descricao_problema",osr.descricao_problema,sizeof(osr.descricao_problema));
            os_create(&osr); free(body);
        }
        print_text_header(); printf("OK");
    } else if(action && strcmp(action, "delete_os") == 0) {
        char *id = get_qs_param(qs,"id"); if(id){ os_delete(atoi(id)); free(id); }
        print_text_header(); printf("OK");
    }

    // Execuções
    else if(action && strcmp(action, "list_execucoes") == 0) {
        print_json_header(); char *json = exec_list_json(); printf("%s", json?json:"[]"); free(json);
    } else if(action && strcmp(action, "create_exec") == 0) {
        char *body = read_stdin_all();
        if(body) {
            Execucao ex; memset(&ex,0,sizeof(ex));
            char idos[16]; form_get_field(body,"id_os",idos,sizeof(idos)); ex.id_os = atoi(idos);
            form_get_field(body,"data_execucao",ex.data_execucao,sizeof(ex.data_execucao));
            form_get_field(body,"tecnico_responsavel",ex.tecnico_responsavel,sizeof(ex.tecnico_responsavel));
            form_get_field(body,"observacoes",ex.observacoes,sizeof(ex.observacoes));
            exec_create(&ex); free(body);
        }
        print_text_header(); printf("OK");
    } else {
        print_text_header();
        printf("Preventa CGI (SQLite) - ready\n");
    }

    if(action) free(action);
    return 0;
}
