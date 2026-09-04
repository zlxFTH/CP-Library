// G[u] 存 {v,id}，无向边 id 为 0...m-1。
int tim = 0, ebcc = 0;
vector<int> dfn(n), low(n), bel(n, -1);
vector<char> bridge(m);
auto tarj = [&](auto self, int u, int pe) -> void {
  dfn[u] = low[u] = ++tim;
  for (auto [v, id] : G[u]) {
    if (!dfn[v]) {
      self(self, v, id);
      low[u] = min(low[u], low[v]);
      if (low[v] > dfn[u]) bridge[id] = 1;
    } else if (id != pe) {
      low[u] = min(low[u], dfn[v]);
    }
  }
};
for (int u = 0; u < n; u++) if (!dfn[u]) tarj(tarj, u, -1);
auto paint = [&](auto self, int u) -> void {
  bel[u] = ebcc;
  for (auto [v, id] : G[u])
    if (bel[v] == -1 && !bridge[id]) self(self, v);
};
for (int u = 0; u < n; u++) if (bel[u] == -1) paint(paint, u), ebcc++;
