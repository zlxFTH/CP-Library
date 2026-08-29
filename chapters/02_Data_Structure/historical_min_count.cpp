struct V {
  LL mn = INF, cmn = 0, hmn = INF, chmn = 0;
};
struct L {
  LL add = 0, pre = INF, cpre = 0;
  bool operator==(L x) {
    return add == x.add && pre == x.pre && cpre == x.cpre;
  }
};
V merge(V x, V y) {
  V z{min(x.mn, y.mn), 0, min(x.hmn, y.hmn), 0};
  if (x.mn == z.mn) z.cmn += x.cmn;
  if (y.mn == z.mn) z.cmn += y.cmn;
  if (x.hmn == z.hmn) z.chmn += x.chmn;
  if (y.hmn == z.hmn) z.chmn += y.chmn;
  return z;
}
L merge(L x, L y) {
  if (x.pre == INF) return y;
  if (y.pre == INF) return x;
  L z{x.add + y.add, min(x.pre, x.add + y.pre), 0};
  if (x.pre == z.pre) z.cpre += x.cpre;
  if (x.add + y.pre == z.pre) z.cpre += y.cpre;
  return z;
}
void apply(int p, int, int, L x) {
  LL hmn = t[p].mn + x.pre, chmn = t[p].cmn * x.cpre;
  if (hmn < t[p].hmn) t[p].hmn = hmn, t[p].chmn = chmn;
  else if (hmn == t[p].hmn) t[p].chmn += chmn;
  t[p].mn += x.add;
  lz[p] = merge(lz[p], x);
}
