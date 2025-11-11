// execucoes.js - registro/listagem de execuções (compatível)
document.addEventListener("DOMContentLoaded", async () => {
  await preencherCombosExec();
  await carregarExecucoes();

  document.getElementById("formExec").addEventListener("submit", async (e) => {
    e.preventDefault();
    await salvarExecucao();
  });
});

async function carregarExecucoes() {
  const data = await listExecucoes();
  const tbody = document.querySelector("#tableExec tbody");
  tbody.innerHTML = "";

  data.forEach(ex => {
    const id_execucao = ex.id_execucao || ex.id || ex.ID || 0;
    const id_os = ex.id_os || ex.idOS || ex.os_id || "";
    const data_exec = ex.data_execucao || ex.data || "";
    const tecnico = ex.tecnico_responsavel || ex.tecnico || "";
    const obs = ex.observacoes || ex.observacao || "";

    const tr = document.createElement("tr");
    tr.innerHTML = `
      <td>${id_execucao}</td>
      <td>${id_os}</td>
      <td>${data_exec}</td>
      <td>${escapeHtml(tecnico)}</td>
      <td>${escapeHtml(obs)}</td>
    `;
    tbody.appendChild(tr);
  });
}

async function preencherCombosExec() {
  const osList = await listOS();
  const sel = document.getElementById("exec_os");
  if (!sel) return;
  sel.innerHTML = osList.map(o => {
    const id_os = o.id_os || o.id || 0;
    const equip = o.equipamento_nome || o.equipamento || o.equip || "";
    return `<option value="${id_os}">OS ${id_os} - ${escapeHtml(equip)}</option>`;
  }).join("");
}

async function salvarExecucao() {
  const payload = {
    id_os: document.getElementById("exec_os").value,
    data_execucao: document.getElementById("data_execucao").value,
    tecnico_responsavel: document.getElementById("tecnico_responsavel").value.trim(),
    observacoes: document.getElementById("observacoes").value.trim()
  };
  if (!payload.id_os) { alert("Selecione uma OS"); return; }
  await createExecucao(payload);
  document.getElementById("formExec").reset();
  await carregarExecucoes();
  await preencherCombosExec();
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
