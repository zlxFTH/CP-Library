LL merge(LL a, LL b) {
  return a + b;
}
LL e() {
  return 0;
}
void apply(int p, int l, int r, LL x) {
  t[p] += x * (r - l);
  lz[p] += x;
}
build(a);
mdf(l, r, x);
LL ans = qry(l, r);
