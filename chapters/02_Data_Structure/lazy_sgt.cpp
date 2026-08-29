#define ls (p << 1)
#define rs (p << 1 | 1)
int n;
LL t[N << 2], lz[N << 2];
LL merge(LL a, LL b);
LL e();
void apply(int p, int l, int r, LL x);
void up(int p) {
  t[p] = merge(t[ls], t[rs]);
}
void down(int p, int l, int r) {
  if (!lz[p]) return;
  int m = (l + r) / 2;
  apply(ls, l, m, lz[p]);
  apply(rs, m, r, lz[p]);
  lz[p] = 0;
}
void build(const vector<LL>& a, int p = 1, int l = 0, int r = n) {
  if (r - l == 1) {
    t[p] = a[l];
    return;
  }
  int m = (l + r) / 2;
  build(a, ls, l, m);
  build(a, rs, m, r);
  up(p);
}
void mdf(int ql, int qr, LL x, int p = 1, int l = 0, int r = n) {
  if (qr <= l || r <= ql) return;
  if (ql <= l && r <= qr) return apply(p, l, r, x);
  down(p, l, r);
  int m = (l + r) / 2;
  mdf(ql, qr, x, ls, l, m);
  mdf(ql, qr, x, rs, m, r);
  up(p);
}
LL qry(int ql, int qr, int p = 1, int l = 0, int r = n) {
  if (ql <= l && r <= qr) return t[p];
  down(p, l, r);
  int m = (l + r) / 2;
  if (qr <= m) return qry(ql, qr, ls, l, m);
  if (m <= ql) return qry(ql, qr, rs, m, r);
  return merge(qry(ql, qr, ls, l, m), qry(ql, qr, rs, m, r));
}
#undef ls
#undef rs
