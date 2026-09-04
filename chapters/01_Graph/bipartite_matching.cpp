// 左部 0...n-1，右部 0...m-1，G 为左到右的边。
vector<int> mt(m, -1), vis(n);
auto aug = [&](auto self, int u) -> bool {
  if (vis[u]) return 0;
  vis[u] = 1;
  for (int v : G[u]) {
    if (mt[v] == -1 || self(self, mt[v])) {
      mt[v] = u;
      return 1;
    }
  }
  return 0;
};
int matching = 0;
for (int u = 0; u < n; u++) {
  fill(ALL(vis), 0);
  matching += aug(aug, u);
}
