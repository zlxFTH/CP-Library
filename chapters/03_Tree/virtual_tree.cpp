vector<int> VT[N];
vector<int> virtual_tree(vector<int> a) {
  auto cmp = [](int u, int v) { return dfn[u] < dfn[v]; };
  sort(ALL(a), cmp);
  int k = SZ(a);
  for (int i = 1; i < k; i++) a.pb(lca(a[i - 1], a[i]));
  sort(ALL(a), cmp), a.erase(unique(ALL(a)), a.end());
  for (int u : a) VT[u].clear();
  for (int i = 1; i < SZ(a); i++) VT[lca(a[i - 1], a[i])].pb(a[i]);
  return a;
}
