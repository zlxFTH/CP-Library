// G[u] 存 {v,id}，bcc 为点双点集，cut 标记割点。
int tim = 0;
vector<int> dfn(n), low(n), stk;
vector<char> cut(n);
vector<vector<int>> bcc;
auto tarj = [&](auto self, int u, int pe) -> void {
  dfn[u] = low[u] = ++tim;
  stk.pb(u);
  int son = 0;
  for (auto [v, id] : G[u]) {
    if (id == pe) continue;
    if (!dfn[v]) {
      son++, self(self, v, id);
      low[u] = min(low[u], low[v]);
      if (low[v] >= dfn[u]) {
        if (pe != -1 || son > 1) cut[u] = 1;
        bcc.pb({u});
        while (bcc.back().back() != v) {
          bcc.back().pb(stk.back());
          stk.pop_back();
        }
      }
    } else {
      low[u] = min(low[u], dfn[v]);
    }
  }
};
for (int u = 0; u < n; u++) if (!dfn[u]) {
  if (!SZ(G[u])) dfn[u] = low[u] = ++tim, bcc.pb({u});
  else tarj(tarj, u, -1), stk.clear();
}
