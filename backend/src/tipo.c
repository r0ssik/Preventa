\
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "tipo.h"
#include "db.h"

int tipo_create(const Tipo *t) {
    sqlite3 *db = db_open(); if(!db) return 0;
    const char *sql = "INSERT INTO tipos_manutencao (descricao, periodicidade_dias) VALUES (?,?);";
    sqlite3_stmt *stmt; sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt,1,t->descricao,-1,SQLITE_STATIC);
    if(t->periodicidade_dias>0) sqlite3_bind_int(stmt,2,t->periodicidade_dias);
    else sqlite3_bind_null(stmt,2);
    int rc = sqlite3_step(stmt); sqlite3_finalize(stmt); sqlite3_close(db);
    return rc == SQLITE_DONE;
}

char *tipo_list_json() {
    sqlite3 *db = db_open(); if(!db) return NULL;
    const char *sql = "SELECT id_tipo, descricao, periodicidade_dias FROM tipos_manutencao;";
    sqlite3_stmt *stmt; sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    size_t size=1024; char *buf=malloc(size); buf[0]='\0'; strcat(buf,"[");
    int first=1;
    while(sqlite3_step(stmt)==SQLITE_ROW) {
        if(!first) strcat(buf,",");
        first=0;
        char item[256];
        snprintf(item,sizeof(item),"{\"id\":%d,\"descricao\":\"%s\",\"periodicidade\":%s}",
                 sqlite3_column_int(stmt,0),
                 sqlite3_column_text(stmt,1)?(char*)sqlite3_column_text(stmt,1):"",
                 sqlite3_column_text(stmt,2)?(char*)sqlite3_column_text(stmt,2):"null");
        if(strlen(buf)+strlen(item)+10>size){size*=2;buf=realloc(buf,size);}
        strcat(buf,item);
    }
    strcat(buf,"]"); sqlite3_finalize(stmt); sqlite3_close(db); return buf;
}

int tipo_delete(int id) {
    sqlite3 *db = db_open(); if(!db) return 0;
    const char *sql = "DELETE FROM tipos_manutencao WHERE id_tipo=?;";
    sqlite3_stmt *stmt; sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt,1,id); int rc=sqlite3_step(stmt); sqlite3_finalize(stmt); sqlite3_close(db);
    return rc==SQLITE_DONE;
}
