\
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "equipamento.h"
#include "db.h"

int equipamento_create(const Equipamento *e) {
    sqlite3 *db = db_open(); if(!db) return 0;
    const char *sql = "INSERT INTO equipamentos (nome, modelo, setor, data_aquisicao) VALUES (?,?,?,?);";
    sqlite3_stmt *stmt; sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt,1,e->nome,-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,2,e->modelo,-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,3,e->setor,-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,4,e->data_aquisicao,-1,SQLITE_STATIC);
    int rc = sqlite3_step(stmt); sqlite3_finalize(stmt); sqlite3_close(db);
    return rc == SQLITE_DONE;
}

char *equipamento_list_json() {
    sqlite3 *db = db_open(); if(!db) return NULL;
    const char *sql = "SELECT id_equipamento, nome, modelo, setor, data_aquisicao FROM equipamentos;";
    sqlite3_stmt *stmt; sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    size_t size = 4096; char *buf = malloc(size); buf[0]='\0'; strcat(buf,"[");
    int first = 1;
    while(sqlite3_step(stmt) == SQLITE_ROW) {
        if(!first) strcat(buf,",");
        first = 0;
        char item[512];
        snprintf(item,sizeof(item),"{\"id\":%d,\"nome\":\"%s\",\"modelo\":\"%s\",\"setor\":\"%s\",\"data_aquisicao\":\"%s\"}",
                 sqlite3_column_int(stmt,0),
                 sqlite3_column_text(stmt,1)?(char*)sqlite3_column_text(stmt,1):"",
                 sqlite3_column_text(stmt,2)?(char*)sqlite3_column_text(stmt,2):"",
                 sqlite3_column_text(stmt,3)?(char*)sqlite3_column_text(stmt,3):"",
                 sqlite3_column_text(stmt,4)?(char*)sqlite3_column_text(stmt,4):"");
        if(strlen(buf)+strlen(item)+10>size){ size*=2; buf=realloc(buf,size); }
        strcat(buf,item);
    }
    strcat(buf,"]");
    sqlite3_finalize(stmt); sqlite3_close(db); return buf;
}

int equipamento_update(const Equipamento *e) {
    sqlite3 *db = db_open(); if(!db) return 0;
    const char *sql = "UPDATE equipamentos SET nome=?, modelo=?, setor=?, data_aquisicao=? WHERE id_equipamento=?;";
    sqlite3_stmt *stmt; sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt,1,e->nome,-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,2,e->modelo,-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,3,e->setor,-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,4,e->data_aquisicao,-1,SQLITE_STATIC);
    sqlite3_bind_int(stmt,5,e->id);
    int rc = sqlite3_step(stmt); sqlite3_finalize(stmt); sqlite3_close(db);
    return rc == SQLITE_DONE;
}

int equipamento_delete(int id) {
    sqlite3 *db = db_open(); if(!db) return 0;
    const char *sql = "DELETE FROM equipamentos WHERE id_equipamento=?;";
    sqlite3_stmt *stmt; sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt,1,id);
    int rc = sqlite3_step(stmt); sqlite3_finalize(stmt); sqlite3_close(db);
    return rc == SQLITE_DONE;
}
