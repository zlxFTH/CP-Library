struct OfflineMo {
  struct Q {
    int l, r, id;
  };
  struct E {
  };
  vector<Q> q;
  vector<E> e;
  vector<LL> d, ans;
  void move_l(int l, int ql, int r, int id) {
  }
  void move_r(int r, int qr, int l, int id) {
  }
  void calc() {
  }
  void ask(int l, int r) {
    q.push_back({l, r, SZ(q)});
  }
  void solve(int n) {
    int B = max(1, int(sqrt(n)));
    sort(ALL(q), [&](Q a, Q b) {
      int x = a.l / B, y = b.l / B;
      if (x != y) return x < y;
      return x & 1 ? a.r > b.r : a.r < b.r;
    });
    e.clear(), d.assign(SZ(q), 0), ans.resize(SZ(q));
    vector<int> ord;
    int l = 0, r = 0;
    for (auto [ql, qr, id] : q) {
      if (l != ql) move_l(l, ql, r, id);
      if (r != qr) move_r(r, qr, ql, id);
      l = ql, r = qr, ord.push_back(id);
    }
    calc();
    LL cur = 0;
    for (int id : ord) cur += d[id], ans[id] = cur;
  }
};
