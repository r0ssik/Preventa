const CGI_BASE = "/cgi-bin/preventa_cgi.exe";

// EQUIPAMENTOS
async function listEquipamentos() {
  const res = await fetch(CGI_BASE + "?action=list_equipamentos");
  return await res.json();
}
async function createEquipamento(e) {
  const form = new URLSearchParams(e).toString();
  await fetch(CGI_BASE + "?action=create_equipamento", { method: "POST", headers: { "Content-Type": "application/x-www-form-urlencoded" }, body: form });
}
async function updateEquipamento(e) {
  const form = new URLSearchParams(e).toString();
  await fetch(CGI_BASE + "?action=update_equipamento", { method: "POST", headers: { "Content-Type": "application/x-www-form-urlencoded" }, body: form });
}
async function deleteEquipamento(id) {
  await fetch(CGI_BASE + "?action=delete_equipamento&id=" + id);
}

// TIPOS
async function listTipos() {
  const res = await fetch(CGI_BASE + "?action=list_tipos");
  return await res.json();
}
async function createTipo(t) {
  const form = new URLSearchParams(t).toString();
  await fetch(CGI_BASE + "?action=create_tipo", { method: "POST", headers: { "Content-Type": "application/x-www-form-urlencoded" }, body: form });
}
async function deleteTipo(id) {
  await fetch(CGI_BASE + "?action=delete_tipo&id=" + id);
}

// ORDENS
async function listOS() {
  const res = await fetch(CGI_BASE + "?action=list_os");
  return await res.json();
}
async function createOS(o) {
  const form = new URLSearchParams(o).toString();
  await fetch(CGI_BASE + "?action=create_os", { method: "POST", headers: { "Content-Type": "application/x-www-form-urlencoded" }, body: form });
}
async function deleteOS(id) {
  await fetch(CGI_BASE + "?action=delete_os&id=" + id);
}

// EXECUÇÕES
async function listExecucoes() {
  const res = await fetch(CGI_BASE + "?action=list_execucoes");
  return await res.json();
}
async function createExecucao(ex) {
  const form = new URLSearchParams(ex).toString();
  await fetch(CGI_BASE + "?action=create_execucao", { method: "POST", headers: { "Content-Type": "application/x-www-form-urlencoded" }, body: form });
}
