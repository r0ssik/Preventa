\
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "execucao.h"
#include "db.h"

int exec_create(const Execucao *e) {
    sqlite3 *db = db_open(); if(!db) return 0;
    const char *sql = "INSERT INTO execucoes_manutencao (id_os, data_execucao, tecnico_responsavel, observacoes) VALUES (?,?,?,?);";
    sqlite3_stmt *stmt; sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt,1,e->id_os);
    sqlite3_bind_text(stmt,2,e->data_execucao,-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,3,e->tecnico_responsavel,-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,4,e->observacoes,-1,SQLITE_STATIC);
    int rc = sqlite3_step(stmt); sqlite3_finalize(stmt); sqlite3_close(db);
    return rc==SQLITE_DONE;
}

char *exec_list_json() {
    sqlite3 *db = db_open(); if(!db) return NULL;
    const char *sql = "SELECT ex.id_execucao, ex.id_os, ex.data_execucao, ex.tecnico_responsavel, ex.observacoes, o.descricao_problema FROM execucoes_manutencao ex LEFT JOIN ordens_servico o ON ex.id_os=o.id_os ORDER BY ex.id_execucao DESC;";
    sqlite3_stmt *stmt; sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    size_t size=4096; char *buf=malloc(size); buf[0]='\0'; strcat(buf,"[");
    int first=1;
    while(sqlite3_step(stmt)==SQLITE_ROW) {
        if(!first) strcat(buf,",");
        first=0;
        char item[1024];
        snprintf(item,sizeof(item),"{\"id_execucao\":%d,\"id_os\":%d,\"data_execucao\":\"%s\",\"tecnico_responsavel\":\"%s\",\"observacoes\":\"%s\",\"descricao_problema\":\"%s\"}",
                 sqlite3_column_int(stmt,0),
                 sqlite3_column_int(stmt,1),
                 sqlite3_column_text(stmt,2)?(char*)sqlite3_column_text(stmt,2):"",
                 sqlite3_column_text(stmt,3)?(char*)sqlite3_column_text(stmt,3):"",
                 sqlite3_column_text(stmt,4)?(char*)sqlite3_column_text(stmt,4):"",
                 sqlite3_column_text(stmt,5)?(char*)sqlite3_column_text(stmt,5):"");
        if(strlen(buf)+strlen(item)+10>size){size*=2;buf=realloc(buf,size);}
        strcat(buf,item);
    }
    strcat(buf,"]"); sqlite3_finalize(stmt); sqlite3_close(db); return buf;
}
