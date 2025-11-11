Preventa - Full MVP (SQLite) - Como executar

Estrutura do pacote:
- backend/: código C (src/) e banco SQLite (preventa.db)
- frontend/: arquivos web (index.html, js/, css/)

Passos para rodar no Windows (XAMPP + MinGW):

1) Compile o backend:
   - Abra CMD e vá para: C:\preventa_full_sqlite\backend
   - Execute: mingw32-make
   - Será criado: preventa_cgi.exe
2) Copie o executável e o banco para o Apache CGI:
   - copy preventa_cgi.exe C:\xampp\cgi-bin\
   - copy preventa.db C:\xampp\cgi-bin\
3) Coloque o frontend em htdocs:
   - copy /E frontend C:\xampp\htdocs\preventa
   - (ou copie manualmente a pasta 'frontend' para C:\xampp\htdocs\preventa)
4) Reinicie o Apache no painel do XAMPP.
5) Acesse: http://localhost/preventa/
6) Teste as operações de CRUD em todos os módulos.

Observações:
- O Makefile está configurado para usar C:/sqlite/sqlite3.c durante a linkedição. Se você não tem sqlite3.c nesse caminho, instale o pacote "sqlite amalgamation" e ajuste o Makefile (CFLAGS/LDFLAGS).

