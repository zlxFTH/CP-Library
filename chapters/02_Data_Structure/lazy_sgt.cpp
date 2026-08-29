#define ls (p << 1)
#define rs (p << 1 | 1)
struct SGT {
  struct V {
  };
  struct L {
  };
  int n;
  V t[N << 2];
  L lz[N << 2];
  V merge(V a, V b) {}
  void apply(int p, int l, int r, L x) {}
  void up(int p) {
    t[p] = merge(t[ls], t[rs]);
  }
  void down(int p, int l, int r) {
    int m = (l + r) / 2;
    apply(ls, l, m, lz[p]);
    apply(rs, m, r, lz[p]);
    lz[p] = {};
  }
  void build(const vector<V>& a, int p = 1, int l = 0, int r = -1) {
    if (r < 0) n = r = SZ(a);
    if (r - l == 1) {
      t[p] = a[l];
      return;
    }
    int m = (l + r) / 2;
    build(a, ls, l, m);
    build(a, rs, m, r);
    up(p);
  }
  void mdf(int ql, int qr, L x, int p = 1, int l = 0, int r = -1) {
    if (r < 0) r = n;
    if (ql <= l && r <= qr) return apply(p, l, r, x);
    down(p, l, r);
    int m = (l + r) / 2;
    if (ql < m) mdf(ql, qr, x, ls, l, m);
    if (m < qr) mdf(ql, qr, x, rs, m, r);
    up(p);
  }
  V qry(int ql, int qr, int p = 1, int l = 0, int r = -1) {
    if (r < 0) r = n;
    if (ql <= l && r <= qr) return t[p];
    down(p, l, r);
    int m = (l + r) / 2;
    if (qr <= m) return qry(ql, qr, ls, l, m);
    if (m <= ql) return qry(ql, qr, rs, m, r);
    return merge(qry(ql, qr, ls, l, m), qry(ql, qr, rs, m, r));
  }
};
#undef ls
#undef rs
