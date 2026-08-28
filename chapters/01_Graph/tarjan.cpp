int tim = 0, scc = 0;
vector<int> dfn(n), low(n), bel(n, -1), stk;
auto tarjan = [&](auto self, int u) -> void {
  dfn[u] = low[u] = ++tim;
  stk.push_back(u);
  for (int v : G[u]) {
    if (!dfn[v]) {
      self(self, v);
      low[u] = min(low[u], low[v]);
    } else if (bel[v] == -1) {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if (dfn[u] != low[u]) return;
  while (1) {
    int v = stk.back();
    stk.pop_back();
    bel[v] = scc;
    if (v == u) break;
  }
  scc++;
};
for (int u = 0; u < n; u++) {
  if (!dfn[u]) tarjan(tarjan, u);
}
