int S = 1;
while (S < n) S <<= 1;
int sn = 2 * S - 1;
int tot = n + 2 * sn;
vector<vector<pair<int, LL>>> G(tot + 1);
auto id = [&](int p, int up) {
  return n + p + up * sn;
};
auto add = [&](int u, int v, LL w) {
  G[u].push_back({v, w});
};
auto link = [&](int u, int v, LL w, int up) {
  if (up) swap(u, v);
  add(u, v, w);
};
auto Node = [&]() {
  G.emplace_back();
  return ++tot;
};
for (int up = 0; up < 2; up++) {
  for (int p = 1; p < S; p++) {
    link(id(p, up), id(p * 2, up), 0, up);
    link(id(p, up), id(p * 2 + 1, up), 0, up);
  }
  for (int i = 1; i <= n; i++) {
    link(id(S + i - 1, up), i, 0, up);
  }
}
auto mdf = [&](int l, int r, int x, LL w, int up) {
  for (l += S - 1, r += S; l < r; l >>= 1, r >>= 1) {
    if (l & 1) link(x, id(l++, up), w, up);
    if (r & 1) link(x, id(--r, up), w, up);
  }
};
