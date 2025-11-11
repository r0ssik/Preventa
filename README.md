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


---

## ⚙️ Como Executar no Windows (XAMPP + MinGW)

### 1️⃣ Compile o backend:
Abra o **Prompt de Comando (CMD)** e vá até o diretório do backend:
```bash
cd C:\preventa_full_sqlite\backend
mingw32-make
Será gerado o executável:



2️⃣ Copie o executável e o banco de dados para o CGI do Apache:

copy preventa_cgi.exe C:\xampp\cgi-bin\
copy preventa.db C:\xampp\cgi-bin\

3️⃣ Coloque o frontend no diretório htdocs:
xcopy /E frontend C:\xampp\htdocs\preventa

Ou copie manualmente a pasta frontend para:
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

🗃️ Estrutura do Banco de Dados

O sistema Preventa utiliza o banco de dados SQLite, contendo quatro tabelas principais que se relacionam por chaves estrangeiras (FOREIGN KEYS), garantindo integridade referencial entre os dados.

🧩 Diagrama Simplificado
equipamentos (1) ───< ordens_servico (N) ───< execucoes_manutencao (N)
        │
        └──< tipos_manutencao (N)

🧱 Tabelas
🧰 equipamentos
Campo	Tipo	Descrição
id_equipamento	INTEGER (PK)	Identificador único do equipamento
nome	TEXT	Nome do equipamento
modelo	TEXT	Modelo do equipamento
setor	TEXT	Setor onde está alocado
data_aquisicao	TEXT	Data de aquisição
🧾 tipos_manutencao
Campo	Tipo	Descrição
id_tipo	INTEGER (PK)	Identificador do tipo de manutenção
descricao	TEXT	Descrição da manutenção
periodicidade_dias	INTEGER	Frequência (em dias) da manutenção
🧮 ordens_servico
Campo	Tipo	Descrição
id_os	INTEGER (PK)	Identificador da ordem de serviço
id_equipamento	INTEGER (FK)	Equipamento vinculado
id_tipo	INTEGER (FK)	Tipo de manutenção
data_abertura	TEXT	Data de abertura da OS
descricao_problema	TEXT	Descrição do problema
status	TEXT	Status da OS (ABERTA, CONCLUÍDA, etc.)
🔧 execucoes_manutencao
Campo	Tipo	Descrição
id_execucao	INTEGER (PK)	Identificador da execução
id_os	INTEGER (FK)	Ordem de serviço vinculada
data_execucao	TEXT	Data da execução da manutenção
tecnico_responsavel	TEXT	Nome do técnico
observacoes	TEXT	Observações gerais
⚙️ Comandos CRUD
➕ CREATE
-- Inserir novo equipamento
INSERT INTO equipamentos (nome, modelo, setor, data_aquisicao)
VALUES ('Compressor X', 'Model 3000', 'Produção', '2023-05-10');

-- Inserir tipo de manutenção
INSERT INTO tipos_manutencao (descricao, periodicidade_dias)
VALUES ('Lubrificação preventiva', 30);

-- Criar ordem de serviço
INSERT INTO ordens_servico (id_equipamento, id_tipo, descricao_problema)
VALUES (1, 1, 'Ruído excessivo detectado');

-- Registrar execução de manutenção
INSERT INTO execucoes_manutencao (id_os, tecnico_responsavel, observacoes)
VALUES (1, 'Carlos Silva', 'Troca de rolamentos concluída com sucesso');

📖 READ
-- Listar todos os equipamentos
SELECT * FROM equipamentos;

-- Ver ordens de serviço com nome do equipamento e tipo de manutenção
SELECT os.id_os, e.nome AS equipamento, t.descricao AS tipo, os.status
FROM ordens_servico os
JOIN equipamentos e ON os.id_equipamento = e.id_equipamento
LEFT JOIN tipos_manutencao t ON os.id_tipo = t.id_tipo;

✏️ UPDATE
-- Atualizar status da ordem de serviço
UPDATE ordens_servico
SET status = 'CONCLUÍDA'
WHERE id_os = 1;

-- Atualizar periodicidade de um tipo de manutenção
UPDATE tipos_manutencao
SET periodicidade_dias = 60
WHERE id_tipo = 1;

❌ DELETE
-- Remover um equipamento (remove também ordens e execuções relacionadas)
DELETE FROM equipamentos WHERE id_equipamento = 1;

-- Remover uma execução específica
DELETE FROM execucoes_manutencao WHERE id_execucao = 1;

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
