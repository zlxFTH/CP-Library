struct ModifyMo {
  struct V {
  };
  struct Q {
    int l, r, t, id;
  };
  struct C {
    int p;
    V v;
  };
  vector<V> a;
  vector<Q> q;
  vector<C> c;
  void add(int p) {
  }
  void del(int p) {
  }
  void answer(int id) {
  }
  void modify(int p, V v) {
    c.push_back({p, v});
  }
  void ask(int l, int r) {
    q.push_back({l, r, SZ(c), SZ(q)});
  }
  void apply(int k, int l, int r) {
    auto& [p, v] = c[k];
    if (l <= p && p < r) del(p);
    swap(a[p], v);
    if (l <= p && p < r) add(p);
  }
  void solve() {
    int B = max(1, int(pow(SZ(a), 2.0 / 3)));
    sort(ALL(q), [&](Q x, Q y) {
      int bx = x.l / B, by = y.l / B;
      if (bx != by) return bx < by;
      bx = x.r / B, by = y.r / B;
      if (bx != by) return bx < by;
      return x.t < y.t;
    });
    int l = 0, r = 0, t = 0;
    for (auto [ql, qr, qt, id] : q) {
      while (t < qt) apply(t++, l, r);
      while (qt < t) apply(--t, l, r);
      while (ql < l) add(--l);
      while (r < qr) add(r++);
      while (l < ql) del(l++);
      while (qr < r) del(--r);
      answer(id);
    }
  }
};
