// ======================================
// CRUD DE EQUIPAMENTOS (versão ajustada)
// ======================================

document.addEventListener("DOMContentLoaded", async () => {
  await carregarEquipamentos();

  // Salvar ou atualizar equipamento
  document.getElementById("formEquip").addEventListener("submit", async (e) => {
    e.preventDefault();
    await salvarEquipamento();
  });

  // Limpar formulário
  document.getElementById("clearEquip").addEventListener("click", limparFormulario);
});

// -----------------------------
// LISTAR
// -----------------------------
async function carregarEquipamentos() {
  const data = await listEquipamentos();
  const tbody = document.querySelector("#tableEquip tbody");
  tbody.innerHTML = "";

  data.forEach((e) => {
    const tr = document.createElement("tr");
    tr.innerHTML = `
      <td>${e.id}</td>
      <td>${e.nome}</td>
      <td>${e.modelo}</td>
      <td>${e.setor}</td>
      <td>${e.data_aquisicao || ""}</td>
      <td>
        <button class="btn btn-sm btn-warning me-1" onclick="editarEquip(${e.id}, '${escapeHtml(e.nome)}', '${escapeHtml(e.modelo)}', '${escapeHtml(e.setor)}', '${e.data_aquisicao || ""}')">Editar</button>
        <button class="btn btn-sm btn-danger" onclick="excluirEquip(${e.id})">Excluir</button>
      </td>
    `;
    tbody.appendChild(tr);
  });
}

// -----------------------------
// SALVAR / ATUALIZAR
// -----------------------------
async function salvarEquipamento() {
  const e = {
    id: document.getElementById("equip_id").value,
    nome: document.getElementById("nome").value.trim(),
    modelo: document.getElementById("modelo").value.trim(),
    setor: document.getElementById("setor").value.trim(),
    data_aquisicao: document.getElementById("data_aquisicao").value
  };

  if (!e.nome) {
    alert("O nome é obrigatório!");
    return;
  }

  if (e.id && e.id !== "0") {
    await updateEquipamento(e);
  } else {
    await createEquipamento(e);
  }

  limparFormulario();
  await carregarEquipamentos();
}

// -----------------------------
// EDITAR
// -----------------------------
function editarEquip(id, nome, modelo, setor, data) {
  document.getElementById("equip_id").value = id;
  document.getElementById("nome").value = nome;
  document.getElementById("modelo").value = modelo;
  document.getElementById("setor").value = setor;
  document.getElementById("data_aquisicao").value = data;
}

// -----------------------------
// EXCLUIR
// -----------------------------
async function excluirEquip(id) {
  if (confirm("Excluir este equipamento?")) {
    await deleteEquipamento(id);
    await carregarEquipamentos();
  }
}

// -----------------------------
// LIMPAR FORMULÁRIO
// -----------------------------
function limparFormulario() {
  document.getElementById("equip_id").value = 0;
  document.getElementById("formEquip").reset();
}

// -----------------------------
// FUNÇÃO DE SEGURANÇA (escapa aspas e HTML)
// -----------------------------
function escapeHtml(text) {
  return text
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;")
    .replace(/"/g, "&quot;")
    .replace(/'/g, "&#039;");
}
