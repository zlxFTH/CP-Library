struct Q {
  int l, r, id;
};
vector<Q> q;
void solve(int n) {
  int B = max(1, int(sqrt(n)));
  sort(ALL(q), [&](Q a, Q b) {
    int x = a.l / B, y = b.l / B;
    if (x != y) return x < y;
    return x & 1 ? a.r > b.r : a.r < b.r;
  });
  int l = 0, r = 0;
  for (auto [ql, qr, id] : q) {
    while (ql < l) add(--l);
    while (r < qr) add(r++);
    while (l < ql) del(l++);
    while (qr < r) del(--r);
    answer(id);
  }
}
