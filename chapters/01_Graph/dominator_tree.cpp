vector<int> dom(vector<vector<int>> &G, int s) {
  int n = SZ(G), t = 0;
  vector<int> dfn(n, -1), rk(n), fa(n, -1);
  auto dfs = [&](auto self, int u) -> void {
    dfn[u] = t, rk[t++] = u;
    for (int v : G[u]) if (dfn[v] == -1) {
      self(self, v), fa[dfn[v]] = dfn[u];
    }
  };
  dfs(dfs, s);
  vector<vector<int>> rg(t), b(t);
  for (int u = 0; u < n; u++) if (dfn[u] != -1)
    for (int v : G[u]) rg[dfn[v]].pb(dfn[u]);
  vector<int> sd(t), id(t, -1), uf(t, -1), mn(t);
  iota(ALL(sd), 0), iota(ALL(mn), 0);
  auto up = [&](auto self, int x) -> void {
    int y = uf[x];
    if (y != -1 && uf[y] != -1) {
      self(self, y);
      if (sd[mn[y]] < sd[mn[x]]) mn[x] = mn[y];
      uf[x] = uf[y];
    }
  };
  auto get = [&](int x) {
    if (uf[x] == -1) return mn[x];
    up(up, x);
    int y = uf[x];
    return sd[mn[y]] < sd[mn[x]] ? mn[y] : mn[x];
  };
  for (int w = t - 1; w; w--) {
    for (int v : rg[w]) sd[w] = min(sd[w], sd[get(v)]);
    b[sd[w]].pb(w), uf[w] = fa[w];
    for (int v : b[fa[w]]) {
      int u = get(v);
      id[v] = sd[u] < sd[v] ? u : fa[w];
    }
    b[fa[w]].clear();
  }
  for (int u = 1; u < t; u++) if (id[u] != sd[u]) id[u] = id[id[u]];
  vector<int> res(n, -1);
  res[s] = s;
  for (int u = 1; u < t; u++) res[rk[u]] = rk[id[u]];
  return res;
}
