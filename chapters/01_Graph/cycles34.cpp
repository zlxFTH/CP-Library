// 简单无向图，O(m sqrt(m)) 统计三元环 c3、四元环 c4。
auto lt = [&](int u, int v) {
  return pair(SZ(G[u]), u) < pair(SZ(G[v]), v);
};
vector<vector<int>> D(n);
for (int u = 0; u < n; u++)
  for (int v : G[u]) if (lt(u, v)) D[u].pb(v);
LL c3 = 0, c4 = 0;
vector<int> vis(n, -1), cnt(n);
for (int u = 0; u < n; u++) {
  for (int v : D[u]) vis[v] = u;
  for (int v : D[u])
    for (int w : D[v]) if (vis[w] == u) c3++;
  for (int v : D[u])
    for (int w : G[v]) if (lt(u, w)) c4 += cnt[w]++;
  for (int v : D[u])
    for (int w : G[v]) if (lt(u, w)) cnt[w] = 0;
}
