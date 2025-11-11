\
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "os.h"
#include "db.h"

int os_create(const OS *o) {
    sqlite3 *db = db_open(); if(!db) return 0;
    const char *sql = "INSERT INTO ordens_servico (id_equipamento, id_tipo, descricao_problema, status) VALUES (?,?,?,?);";
    sqlite3_stmt *stmt; sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt,1,o->id_equipamento);
    if(o->id_tipo>0) sqlite3_bind_int(stmt,2,o->id_tipo); else sqlite3_bind_null(stmt,2);
    sqlite3_bind_text(stmt,3,o->descricao_problema,-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,4,o->status,-1,SQLITE_STATIC);
    int rc = sqlite3_step(stmt); sqlite3_finalize(stmt); sqlite3_close(db);
    return rc==SQLITE_DONE;
}

char *os_list_json() {
    sqlite3 *db = db_open(); if(!db) return NULL;
    const char *sql = "SELECT o.id_os, o.id_equipamento, o.id_tipo, o.data_abertura, o.descricao_problema, o.status, e.nome FROM ordens_servico o LEFT JOIN equipamentos e ON o.id_equipamento=e.id_equipamento ORDER BY o.id_os DESC;";
    sqlite3_stmt *stmt; sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    size_t size=4096; char *buf=malloc(size); buf[0]='\0'; strcat(buf,"[");
    int first=1;
    while(sqlite3_step(stmt)==SQLITE_ROW) {
        if(!first) strcat(buf,",");
        first=0;
        char item[1024];
        snprintf(item,sizeof(item),"{\"id_os\":%d,\"id_equipamento\":%d,\"id_tipo\":%d,\"data_abertura\":\"%s\",\"descricao_problema\":\"%s\",\"status\":\"%s\",\"equipamento_nome\":\"%s\"}",
                 sqlite3_column_int(stmt,0),
                 sqlite3_column_int(stmt,1),
                 sqlite3_column_int(stmt,2),
                 sqlite3_column_text(stmt,3)?(char*)sqlite3_column_text(stmt,3):"",
                 sqlite3_column_text(stmt,4)?(char*)sqlite3_column_text(stmt,4):"",
                 sqlite3_column_text(stmt,5)?(char*)sqlite3_column_text(stmt,5):"",
                 sqlite3_column_text(stmt,6)?(char*)sqlite3_column_text(stmt,6):"");
        if(strlen(buf)+strlen(item)+10>size){size*=2;buf=realloc(buf,size);}
        strcat(buf,item);
    }
    strcat(buf,"]"); sqlite3_finalize(stmt); sqlite3_close(db); return buf;
}

int os_delete(int id) {
    sqlite3 *db = db_open(); if(!db) return 0;
    const char *sql = "DELETE FROM ordens_servico WHERE id_os=?;";
    sqlite3_stmt *stmt; sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt,1,id); int rc=sqlite3_step(stmt); sqlite3_finalize(stmt); sqlite3_close(db);
    return rc==SQLITE_DONE;
}
