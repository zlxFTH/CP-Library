struct Q {
  int l, r, id;
};
vector<Q> q;
void ask(int l, int r) {
  q.push_back({l, r, SZ(q)});
}
void solve(int n) {
  int B = max(1, int(sqrt(n)));
  sort(ALL(q), [&](Q a, Q b) {
    int x = a.l / B, y = b.l / B;
    if (x != y) return x < y;
    return a.r < b.r;
  });
  for (int i = 0; i < SZ(q);) {
    int b = q[i].l / B, j = i;
    while (j < SZ(q) && q[j].l / B == b) j++;
    int R = min(n, (b + 1) * B), r = R;
    int base = snapshot();
    for (int k = i; k < j; k++) {
      auto [ql, qr, id] = q[k];
      if (qr <= R) {
        int t = snapshot();
        for (int p = ql; p < qr; p++) add(p);
        answer(id), rollback(t);
        continue;
      }
      while (r < qr) add(r++);
      int t = snapshot();
      for (int p = R - 1; p >= ql; p--) add(p);
      answer(id), rollback(t);
    }
    rollback(base), i = j;
  }
}
