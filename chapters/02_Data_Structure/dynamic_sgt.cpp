vector<Node> t = {{}, {}};
int node() {
  t.push_back({});
  return SZ(t) - 1;
}
void mdf(int x, V v, int p = 1, int l = 0, int r = -1) {
  if (r < 0) r = n;
  if (r - l == 1) {
    t[p].v = v;
    return;
  }
  int m = (l + r) / 2;
  if (x < m) {
    if (!ls(p)) ls(p) = node();
    mdf(x, v, ls(p), l, m);
  } else {
    if (!rs(p)) rs(p) = node();
    mdf(x, v, rs(p), m, r);
  }
  up(p);
}
