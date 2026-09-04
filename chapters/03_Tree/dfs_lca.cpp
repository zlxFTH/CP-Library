int dn, dfn[N], out[N], fa[N], dep[N], mi[__lg(N) + 1][N];
vector<int> ch[N];
int mn(int u, int v) {
  return dfn[u] < dfn[v] ? u : v;
}
void dfs_lca(int u, int f) {
  fa[u] = f, dep[u] = u == f ? 0 : dep[f] + 1;
  mi[0][dfn[u] = dn++] = f;
  for (int v : G[u]) if (v != f) ch[u].pb(v), dfs_lca(v, u);
  out[u] = dn;
}
void init_lca(int r) {
  dn = 0, dfs_lca(r, r);
  for (int j = 1; (1 << j) <= dn; j++)
    for (int i = 0; i + (1 << j) <= dn; i++)
      mi[j][i] = mn(mi[j - 1][i], mi[j - 1][i + (1 << (j - 1))]);
}
int lca(int u, int v) {
  if (u == v) return u;
  if ((u = dfn[u]) > (v = dfn[v])) swap(u, v);
  int k = __lg(v - u++);
  return mn(mi[k][u], mi[k][v - (1 << k) + 1]);
}
bool anc(int u, int v) {
  return dfn[u] <= dfn[v] && dfn[v] < out[u];
}
int findchild(int u, int v) {
  assert(u != v);
  if (!anc(u, v)) return fa[u];
  return *prev(upper_bound(ALL(ch[u]), v, [](int x, int y) {
    return dfn[x] < dfn[y];
  }));
}
