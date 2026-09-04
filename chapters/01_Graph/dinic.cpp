struct Dinic {
  struct E {
    int v;
    LL w;
  };
  static constexpr LL inf = LLONG_MAX / 4;
  vector<E> e;
  vector<vector<int>> G;
  vector<int> d, cur;
  Dinic(int n) : G(n), d(n), cur(n) {}
  void add(int u, int v, LL w) {
    G[u].pb(SZ(e)), e.pb({v, w});
    G[v].pb(SZ(e)), e.pb({u, 0});
  }
  bool bfs(int s, int t) {
    fill(ALL(d), -1), d[s] = 0;
    queue<int> q;
    q.push(s);
    while (SZ(q)) {
      int u = q.front();
      q.pop();
      for (int id : G[u]) {
        auto [v, w] = e[id];
        if (w && d[v] == -1) d[v] = d[u] + 1, q.push(v);
      }
    }
    return d[t] != -1;
  }
  LL dfs(int u, int t, LL f) {
    if (u == t) return f;
    for (int &i = cur[u]; i < SZ(G[u]); i++) {
      int id = G[u][i];
      auto &[v, w] = e[id];
      if (w && d[v] == d[u] + 1) {
        LL x = dfs(v, t, min(f, w));
        if (x) {
          w -= x, e[id ^ 1].w += x;
          return x;
        }
      }
    }
    return 0;
  }
  LL flow(int s, int t) {
    LL ans = 0, f;
    while (bfs(s, t)) {
      fill(ALL(cur), 0);
      while ((f = dfs(s, t, inf))) ans += f;
    }
    return ans;
  }
};
