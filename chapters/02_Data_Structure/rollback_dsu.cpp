struct DSU {
  vector<int> f, sz;
  vector<array<int, 2>> his;
  DSU(int n = 0) { init(n); }
  void init(int n) {
    f.resize(n), iota(ALL(f), 0);
    sz.assign(n, 1), his.clear();
  }
  int find(int x) {
    while (x != f[x]) x = f[x];
    return x;
  }
  bool same(int x, int y) {
    return find(x) == find(y);
  }
  bool merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    if (sz[x] < sz[y]) swap(x, y);
    his.push_back({x, y});
    sz[x] += sz[y], f[y] = x;
    return true;
  }
  int size(int x) {
    return sz[find(x)];
  }
  int time() {
    return SZ(his);
  }
  void rollback(int t) {
    while (SZ(his) > t) {
      auto [x, y] = his.back();
      his.pop_back();
      f[y] = y, sz[x] -= sz[y];
    }
  }
};
