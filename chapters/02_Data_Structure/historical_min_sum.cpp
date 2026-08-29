struct V {
  LL a = 0, c = 0, mn = INF, se = INF;
  int cmn = 0;
};
struct L {
  LL add = 0, low = -INF;
  bool operator==(L x) { return add == x.add && low == x.low; }
};
V merge(V x, V y) {
  V z{x.a + y.a, x.c + y.c};
  z.mn = min(x.mn, y.mn);
  z.cmn = (x.mn == z.mn ? x.cmn : 0) + (y.mn == z.mn ? y.cmn : 0);
  z.se = min(x.mn == z.mn ? x.se : x.mn, y.mn == z.mn ? y.se : y.mn);
  return z;
}
L merge(L x, L y) {
  return {x.add + y.add, max(x.low + y.add, y.low)};
}
void apply(int p, int l, int r, L x) {
  t[p].a += x.add * (r - l);
  t[p].c += x.add * (r - l);
  t[p].mn += x.add;
  if (t[p].se != INF) t[p].se += x.add;
  if (x.low > t[p].mn) {
    t[p].c += (x.low - t[p].mn) * t[p].cmn;
    t[p].mn = x.low;
  }
  lz[p] = merge(lz[p], x);
}
void mdf(int ql, int qr, L x, int p = 1, int l = 0, int r = -1) {
  if (r < 0) r = n;
  if (ql <= l && r <= qr &&
      (x.low <= t[p].mn + x.add || t[p].se == INF || x.low < t[p].se + x.add))
    return apply(p, l, r, x);
  down(p, l, r);
  int m = (l + r) / 2;
  if (ql < m) mdf(ql, qr, x, ls, l, m);
  if (m < qr) mdf(ql, qr, x, rs, m, r);
  up(p);
}

vector<SGT::V> b(n);
for (int i = 0; i < n; i++) b[i] = {a[i], 0, 0, INF, 1};
seg.build(b);
seg.mdf(l, r, {x, 0});
auto v = seg.qry(l, r);
LL ans = v.a - v.c;
