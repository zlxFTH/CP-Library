struct LiChao {
  static constexpr LL INF = (LL)4e18;
  struct Line {
    LL k, b;
    Line(LL k = 0, LL b = INF) : k(k), b(b) {}
    LL get(LL x) {
      I y = (I)k * x + b;
      if (y > INF) return INF;
      if (y < -INF) return -INF;
      return y;
    }
  };
  struct Node {
    Line f;
    int ls = 0, rs = 0;
  };
  int L, R;
  vector<Node> t = {Node(), Node()};
  LiChao(int L, int R) : L(L), R(R) { assert(L < R); }
  int node() {
    t.emplace_back();
    return SZ(t) - 1;
  }
  void add(Line f, int p, int l, int r) {
    int m = l + (r - l) / 2;
    bool x = f.get(l) < t[p].f.get(l);
    bool y = f.get(m) < t[p].f.get(m);
    if (y) swap(f, t[p].f);
    if (r - l == 1) return;
    if (x != y) {
      if (!t[p].ls) t[p].ls = node();
      add(f, t[p].ls, l, m);
    } else {
      if (!t[p].rs) t[p].rs = node();
      add(f, t[p].rs, m, r);
    }
  }
  void add(Line f) { add(f, 1, L, R); }
  void add(int ql, int qr, Line f, int p, int l, int r) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) return add(f, p, l, r);
    int m = l + (r - l) / 2;
    if (ql < m) {
      if (!t[p].ls) t[p].ls = node();
      add(ql, qr, f, t[p].ls, l, m);
    }
    if (m < qr) {
      if (!t[p].rs) t[p].rs = node();
      add(ql, qr, f, t[p].rs, m, r);
    }
  }
  void add(int l, int r, Line f) {
    assert(L <= l && l <= r && r <= R);
    if (l < r) add(l, r, f, 1, L, R);
  }
  LL qry(int x, int p, int l, int r) {
    if (!p) return INF;
    LL ans = t[p].f.get(x);
    if (r - l == 1) return ans;
    int m = l + (r - l) / 2;
    if (x < m) return min(ans, qry(x, t[p].ls, l, m));
    return min(ans, qry(x, t[p].rs, m, r));
  }
  LL qry(int x) {
    assert(L <= x && x < R);
    return qry(x, 1, L, R);
  }
};
