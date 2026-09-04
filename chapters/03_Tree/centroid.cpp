int sz[N], cfa[N];
bool ban[N];
vector<int> CT[N];
int getsz(int u, int f) {
  sz[u] = 1;
  for (int v : G[u]) if (v != f && !ban[v]) sz[u] += getsz(v, u);
  return sz[u];
}
int getcen(int u, int f, int n) {
  for (int v : G[u])
    if (v != f && !ban[v] && sz[v] > n / 2) return getcen(v, u, n);
  return u;
}
int divide(int u, int f = -1) {
  int c = getcen(u, -1, getsz(u, -1));
  cfa[c] = f;
  if (f != -1) CT[f].pb(c);
  work(c), ban[c] = 1;
  for (int v : G[c]) if (!ban[v]) divide(v, c);
  return c;
}
