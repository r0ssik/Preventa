\
#include "db.h"
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

sqlite3 *db_open() {
    sqlite3 *db;
    int rc = sqlite3_open("preventa.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return NULL;
    }
    const char *sql = "PRAGMA foreign_keys = ON;"
                      "CREATE TABLE IF NOT EXISTS equipamentos ("
                      "id_equipamento INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "nome TEXT NOT NULL, modelo TEXT, setor TEXT, data_aquisicao TEXT);"
                      "CREATE TABLE IF NOT EXISTS tipos_manutencao ("
                      "id_tipo INTEGER PRIMARY KEY AUTOINCREMENT, descricao TEXT NOT NULL, periodicidade_dias INTEGER);"
                      "CREATE TABLE IF NOT EXISTS ordens_servico ("
                      "id_os INTEGER PRIMARY KEY AUTOINCREMENT, id_equipamento INTEGER NOT NULL, id_tipo INTEGER, data_abertura TEXT DEFAULT (date('now')), descricao_problema TEXT, status TEXT DEFAULT 'ABERTA', FOREIGN KEY (id_equipamento) REFERENCES equipamentos(id_equipamento) ON DELETE CASCADE, FOREIGN KEY (id_tipo) REFERENCES tipos_manutencao(id_tipo));"
                      "CREATE TABLE IF NOT EXISTS execucoes_manutencao ("
                      "id_execucao INTEGER PRIMARY KEY AUTOINCREMENT, id_os INTEGER NOT NULL, data_execucao TEXT DEFAULT (date('now')), tecnico_responsavel TEXT, observacoes TEXT, FOREIGN KEY (id_os) REFERENCES ordens_servico(id_os) ON DELETE CASCADE);";
    sqlite3_exec(db, sql, 0, 0, 0);
    return db;
}
