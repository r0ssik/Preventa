\
CC = gcc
CFLAGS = -Wall -O2 -IC:/sqlite
LDFLAGS = C:/sqlite/sqlite3.c
SRC = src/main.c src/db.c src/equipamento.c src/tipo.c src/os.c src/execucao.c
OBJ = $(SRC:.c=.o)
TARGET = preventa_cgi.exe

all: $(TARGET)
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

clean:
	del /Q $(OBJ) $(TARGET) 2>nul || rm -f $(OBJ) $(TARGET)
