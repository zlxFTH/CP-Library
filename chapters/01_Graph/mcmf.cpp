// 残量网络无负环时使用。
struct MCMF {
  struct E {
    int u, v;
    LL w, c;
  };
  static constexpr LL inf = LLONG_MAX / 4;
  vector<E> e;
  vector<vector<int>> G;
  vector<LL> d, in;
  vector<int> p, vis;
  MCMF(int n) : G(n), d(n), in(n), p(n), vis(n) {}
  void add(int u, int v, LL w, LL c) {
    G[u].pb(SZ(e)), e.pb({u, v, w, c});
    G[v].pb(SZ(e)), e.pb({v, u, 0, -c});
  }
  bool spfa(int s, int t) {
    fill(ALL(d), inf), fill(ALL(vis), 0), d[s] = 0, in[s] = inf;
    queue<int> q;
    q.push(s), vis[s] = 1;
    while (SZ(q)) {
      int u = q.front();
      q.pop(), vis[u] = 0;
      for (int id : G[u]) {
        auto &x = e[id];
        if (x.w && d[x.v] > d[u] + x.c) {
          d[x.v] = d[u] + x.c, p[x.v] = id;
          in[x.v] = min(in[u], x.w);
          if (!vis[x.v]) q.push(x.v), vis[x.v] = 1;
        }
      }
    }
    return d[t] != inf;
  }
  pair<LL, LL> flow(int s, int t, LL lim = inf) {
    LL f = 0, c = 0;
    while (f < lim && spfa(s, t)) {
      LL x = min(in[t], lim - f);
      f += x, c += x * d[t];
      for (int v = t; v != s; v = e[p[v]].u) {
        int id = p[v];
        e[id].w -= x, e[id ^ 1].w += x;
      }
    }
    return {f, c};
  }
};
