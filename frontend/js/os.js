// os.js - ordens de serviço (compatível com diferentes keys)
document.addEventListener("DOMContentLoaded", async () => {
  await preencherCombosOS();
  await carregarOS();

  document.getElementById("formOS").addEventListener("submit", async (e) => {
    e.preventDefault();
    await salvarOS();
  });
});

async function carregarOS() {
  const data = await listOS();
  const tbody = document.querySelector("#tableOS tbody");
  tbody.innerHTML = "";

  data.forEach(o => {
    const id_os = o.id_os || o.id || o.ID || 0;
    // equipamento pode vir em campos diferentes
    const equipNome = o.equipamento_nome || o.equipamento || o.nome_equipamento || o.equip || "";
    const id_tipo = o.id_tipo || o.tipo || "";
    const data_ab = o.data_abertura || o.data || "";
    const status = o.status || "";
    const descricao = o.descricao_problema || o.descricao || "";

    const tr = document.createElement("tr");
    tr.innerHTML = `
      <td>${id_os}</td>
      <td>${escapeHtml(equipNome)}</td>
      <td>${id_tipo}</td>
      <td>${data_ab}</td>
      <td>${escapeHtml(status)}</td>
      <td>${escapeHtml(descricao)}</td>
      <td>
        <button class="btn btn-sm btn-danger" onclick="excluirOS(${id_os})">Excluir</button>
      </td>
    `;
    tbody.appendChild(tr);
  });
}

async function preencherCombosOS() {
  // popula selects de equipamentos e tipos (compatível com ambos os formatos)
  const equips = await listEquipamentos();
  const tipos = await listTipos();
  const selEquip = document.getElementById("os_equip");
  const selTipo = document.getElementById("os_tipo");
  if (!selEquip || !selTipo) return;

  selEquip.innerHTML = equips.map(e => {
    const id = e.id || e.id_equipamento || 0;
    const nome = e.nome || e.nome_equipamento || "";
    return `<option value="${id}">${escapeHtml(nome)}</option>`;
  }).join("");

  selTipo.innerHTML = tipos.map(t => {
    const id = t.id_tipo || t.id || 0;
    const descricao = t.descricao || t.nome || "";
    return `<option value="${id}">${escapeHtml(descricao)}</option>`;
  }).join("");
}

async function salvarOS() {
  const payload = {
    id_equipamento: document.getElementById("os_equip").value,
    id_tipo: document.getElementById("os_tipo").value,
    descricao_problema: document.getElementById("descricao_problema").value.trim()
  };
  if (!payload.id_equipamento) { alert("Selecione um equipamento"); return; }
  await createOS(payload);
  document.getElementById("formOS").reset();
  await preencherCombosOS();
  await carregarOS();
}

async function excluirOS(id) {
  if (!confirm("Excluir esta Ordem de Serviço?")) return;
  await deleteOS(id);
  await carregarOS();
}

// helper
function escapeHtml(text) {
  if (!text) return "";
  return String(text)
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;")
    .replace(/"/g, "&quot;")
    .replace(/'/g, "&#039;");
}
