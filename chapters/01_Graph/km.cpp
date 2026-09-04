// n*n 完备二分图最大权完美匹配；补 0 点可求非完美匹配。
LL km(vector<vector<LL>> a) {
  int n = SZ(a);
  vector<LL> lx(n), ly(n), slack(n);
  vector<int> mt(n, -1);
  vector<char> vx(n), vy(n);
  for (int u = 0; u < n; u++) lx[u] = *max_element(ALL(a[u]));
  auto aug = [&](auto self, int u) -> bool {
    if (vx[u]) return 0;
    vx[u] = 1;
    for (int v = 0; v < n; v++) if (!vy[v]) {
      LL d = lx[u] + ly[v] - a[u][v];
      if (d) {
        slack[v] = min(slack[v], d);
      } else {
        vy[v] = 1;
        if (mt[v] == -1 || self(self, mt[v])) {
          mt[v] = u;
          return 1;
        }
      }
    }
    return 0;
  };
  for (int s = 0; s < n; s++) {
    fill(ALL(slack), LLONG_MAX / 4);
    while (1) {
      fill(ALL(vx), 0), fill(ALL(vy), 0);
      if (aug(aug, s)) break;
      LL d = LLONG_MAX / 4;
      for (int v = 0; v < n; v++) if (!vy[v]) d = min(d, slack[v]);
      for (int u = 0; u < n; u++) if (vx[u]) lx[u] -= d;
      for (int v = 0; v < n; v++) {
        if (vy[v]) ly[v] += d;
        else slack[v] -= d;
      }
    }
  }
  LL ans = 0;
  for (int v = 0; v < n; v++) ans += a[mt[v]][v];
  return ans;
}
