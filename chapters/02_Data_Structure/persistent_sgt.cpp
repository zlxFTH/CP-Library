#define ls(p) t[p].ls
#define rs(p) t[p].rs
struct SGT {
  struct V {};
  struct Node {
    int ls, rs;
    V v;
  };
  int n;
  vector<Node> t = {{}};
  V merge(V a, V b) {}
  void up(int p) {
    t[p].v = merge(t[ls(p)].v, t[rs(p)].v);
  }
  int mdf(int x, V v, int p = 0, int l = 0, int r = -1) {
    if (r < 0) r = n;
    t.push_back(t[p]);
    p = SZ(t) - 1;
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
  V qry(int ql, int qr, int p = 0, int l = 0, int r = -1) {
    if (r < 0) r = n;
    if (ql <= l && r <= qr) return t[p].v;
    int m = (l + r) / 2;
    if (qr <= m) return qry(ql, qr, ls(p), l, m);
    if (m <= ql) return qry(ql, qr, rs(p), m, r);
    return merge(qry(ql, qr, ls(p), l, m), qry(ql, qr, rs(p), m, r));
  }
};
#undef ls
#undef rs
