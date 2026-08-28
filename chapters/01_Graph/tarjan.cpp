struct SCC {
  int n, tim = 0, scc = 0;
  vector<vector<int>> G;
  vector<int> dfn, low, bel, stk;
  SCC(int N) : n(N), G(N), dfn(N), low(N), bel(N, -1) {}
  void add(int u, int v) { G[u].push_back(v); }
  void dfs(int u) {
    dfn[u] = low[u] = ++tim;
    stk.push_back(u);
    for (int v : G[u]) {
      if (!dfn[v]) {
        dfs(v);
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
  }
  void run() {
    for (int u = 0; u < n; u++) {
      if (!dfn[u]) dfs(u);
    }
  }
};
