LL lag(vector<LL> y, LL x) {
  int n = SZ(y); if (!n) return 0;
  x %= P; if (x < 0) x += P;
  if (x < n) return y[x];
  vector<LL> pre(n + 1, 1), suf(n + 1, 1);
  for (int i = 0; i < n; i++) pre[i + 1] = Mul(pre[i], x - i);
  for (int i = n; i--;) suf[i] = Mul(suf[i + 1], x - i);
  LL ans = 0;
  for (int i = 0; i < n; i++) {
    LL v = Mul(y[i], Mul(pre[i], suf[i + 1]));
    v = Mul(v, Mul(ifac[i], ifac[n - 1 - i]));
    if ((n - 1 - i) & 1) v = v ? P - v : 0;
    ans = Add(ans, v);
  }
  return ans;
}
vector<LL> coef(vector<LL> x, vector<LL> y) {
  int n = SZ(x); if (!n) return {};
  vector<LL> q(n + 1), b(n), a(n); q[0] = 1;
  for (int i = 0; i < n; i++) {
    LL z = x[i] ? P - x[i] : 0;
    for (int j = i + 1; j; j--) q[j] = Add(q[j - 1], Mul(q[j], z));
    q[0] = Mul(q[0], z);
  }
  for (int i = 0; i < n; i++) {
    b[n - 1] = 1;
    for (int j = n - 1; j--;) b[j] = Add(q[j + 1], Mul(x[i], b[j + 1]));
    LL d = 0;
    for (int j = n; j--;) d = Add(Mul(d, x[i]), b[j]);
    LL w = Mul(y[i], qp(d));
    for (int j = 0; j < n; j++) a[j] = Add(a[j], Mul(w, b[j]));
  }
  return a;
}
