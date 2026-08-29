int node() {
  t.push_back({});
  return SZ(t) - 1;
}
int mdf(int x, V v, int p, int l = 0, int r = -1) {
  if (r < 0) r = n;
  if (!p) p = node();
  if (r - l == 1) {
    t[p].v = v;
    return p;
  }
  int m = (l + r) / 2;
  if (x < m) ls(p) = mdf(x, v, ls(p), l, m);
  else rs(p) = mdf(x, v, rs(p), m, r);
  up(p);
  return p;
}
