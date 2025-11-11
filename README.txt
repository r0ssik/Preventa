# 🛠️ Preventa - Full MVP (SQLite)

> 💡 Sistema de gerenciamento de manutenções preventivas desenvolvido em **C**, com interface **web (HTML, CSS, JS)** e banco de dados **SQLite**.

---

## 🧩 Tecnologias Utilizadas

![C]
![HTML]
![CSS]
![JavaScript]
![SQLite](MVP)


---

## 🧠 Introdução e Objetivo

O **Preventa** foi desenvolvido como projeto integrador, com o objetivo de criar um sistema **simples, intuitivo e eficiente** para o gerenciamento de manutenções preventivas em equipamentos industriais.  

A aplicação visa:
- Aumentar a **vida útil** dos equipamentos;  
- Evitar **falhas inesperadas**;  
- Garantir a **segurança operacional** das máquinas;  
- Oferecer uma **solução acessível** para pequenas e médias indústrias.

O sistema utiliza o conceito de **CRUD (Create, Read, Update, Delete)**, com um banco de dados relacional em **SQLite**, garantindo **integridade, agilidade** e **facilidade de manutenção**.

---

## 🧱 Estrutura do Projeto

📦 preventa_full_sqlite
├── backend/
│ ├── src/ # Código-fonte em C
│ ├── Makefile
│ └── preventa.db # Banco de dados SQLite
│
├── frontend/
│ ├── index.html # Interface principal
│ ├── js/ # Scripts JavaScript
│ └── css/ # Estilos CSS
│
└── README.md

yaml
Copiar código

---

## ⚙️ Como Executar no Windows (XAMPP + MinGW)

### 1️⃣ Compile o backend:
Abra o **Prompt de Comando (CMD)** e vá até o diretório do backend:
```bash
cd C:\preventa_full_sqlite\backend
mingw32-make
Será gerado o executável:

Copiar código
preventa_cgi.exe
2️⃣ Copie o executável e o banco de dados para o CGI do Apache:
bash
Copiar código
copy preventa_cgi.exe C:\xampp\cgi-bin\
copy preventa.db C:\xampp\cgi-bin\
3️⃣ Coloque o frontend no diretório htdocs:
bash
Copiar código
xcopy /E frontend C:\xampp\htdocs\preventa
Ou copie manualmente a pasta frontend para:

makefile
Copiar código
C:\xampp\htdocs\preventa
4️⃣ Reinicie o Apache
Abra o painel do XAMPP, pare e inicie novamente o módulo Apache.

5️⃣ Acesse no navegador:
👉 http://localhost/preventa/

6️⃣ Teste as funcionalidades:
Execute e teste todas as operações de CRUD nos módulos disponíveis.

⚠️ Observações Importantes
O Makefile está configurado para utilizar:

bash
Copiar código
C:/sqlite/sqlite3.c
Caso esse caminho não exista, instale o SQLite Amalgamation e ajuste o Makefile nas variáveis CFLAGS e LDFLAGS.

🧪 Metodologia
Durante o desenvolvimento, foram aplicadas metodologias de engenharia de software, como:

Brainstorming com o grupo de desenvolvimento;

Entrevistas informais com profissionais da área de manutenção;

Modelagem de banco de dados relacional em SQL;

Prototipação visual das telas no Figma.

Essas práticas garantiram que o sistema refletisse as necessidades reais das empresas.

📊 Resultados e Discussões
O Preventa demonstrou-se uma solução eficaz para:

Otimizar o controle de manutenções;

Reduzir falhas e desperdícios;

Prover relatórios completos sobre o histórico de cada equipamento.

O sistema contribui com as ODS (Objetivos de Desenvolvimento Sustentável):

ODS 8: Trabalho decente e crescimento econômico;

ODS 9: Indústria, inovação e infraestrutura;

ODS 12: Consumo e produção responsáveis.

🚀 Planos Futuros
A visão de longo prazo do projeto inclui:

Integração com IoT (Internet das Coisas) para monitoramento em tempo real;

Análise preditiva de falhas;

Dashboards BI com indicadores de desempenho e sustentabilidade;

Parcerias com instituições e universidades para pesquisa aplicada.

🧾 Conclusão
O projeto Preventa demonstra que é possível unir tecnologia, inovação e sustentabilidade para melhorar a infraestrutura industrial.
Com base em conceitos sólidos de engenharia de software e foco em usabilidade, o sistema se mostra viável, escalável e alinhado às boas práticas da indústria moderna.

🔗 Links Importantes
📂 Repositório: https://github.com/r0ssik/Preventa

🎨 Protótipo no Figma: Clique aqui

💻 Desenvolvido com dedicação por Gabriel Rodrigues Rossik e equipe
🧡 “Prevenir é o melhor caminho para inovar.”
