// tipos.js - criação/listagem/exclusão (compatível com id_tipo ou id)
document.addEventListener("DOMContentLoaded", async () => {
  await carregarTipos();
  document.getElementById("formTipo").addEventListener("submit", async (e) => {
    e.preventDefault();
    await salvarTipo();
  });
});

async function carregarTipos() {
  const data = await listTipos();
  const tbody = document.querySelector("#tableTipo tbody");
  tbody.innerHTML = "";
  data.forEach(t => {
    const id = t.id_tipo || t.id || t.ID || 0;
    const descricao = t.descricao || t.nome || "";
    // periodicidade pode vir com nomes diferentes
    const periodicidade = (t.periodicidade_dias != null) ? t.periodicidade_dias : (t.periodicidade != null ? t.periodicidade : "");
    const tr = document.createElement("tr");
    tr.innerHTML = `
      <td>${id}</td>
      <td>${escapeHtml(descricao)}</td>
      <td>${periodicidade}</td>
      <td>
        <button class="btn btn-sm btn-danger" onclick="excluirTipo(${id})">Excluir</button>
      </td>
    `;
    tbody.appendChild(tr);
  });
}

async function salvarTipo() {
  const descricao = document.getElementById("descricao").value.trim();
  const periodicidade = document.getElementById("periodicidade").value.trim();
  if (!descricao) { alert("Descrição é obrigatória"); return; }
  await createTipo({ descricao, periodicidade });
  document.getElementById("formTipo").reset();
  await carregarTipos();
  // Atualiza OS selects caso estejam sendo usados
  if (typeof preencherCombosOS === "function") await preencherCombosOS();
}

async function excluirTipo(id) {
  if (!confirm("Excluir este tipo de manutenção?")) return;
  await deleteTipo(id);
  await carregarTipos();
  if (typeof preencherCombosOS === "function") await preencherCombosOS();
}

// small helper (same as in equipamentos.js)
function escapeHtml(text) {
  if (!text) return "";
  return String(text)
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;")
    .replace(/"/g, "&quot;")
    .replace(/'/g, "&#039;");
}
