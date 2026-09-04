using Poly = vector<LL>;
void ntt(Poly &a) {
  int n = SZ(a);
  for (int i = 1, j = 0; i < n; i++) {
    int k = n >> 1;
    for (; j & k; k >>= 1) j ^= k;
    j ^= k;
    if (i < j) swap(a[i], a[j]);
  }
  for (int k = 1; k < n; k <<= 1) {
    LL z = qp(3, (P - 1) / (k << 1));
    for (int i = 0; i < n; i += k << 1) {
      LL w = 1;
      for (int j = 0; j < k; j++, w = Mul(w, z)) {
        LL x = a[i + j], y = Mul(a[i + j + k], w);
        a[i + j] = Add(x, y);
        a[i + j + k] = x >= y ? x - y : x - y + P;
      }
    }
  }
}
void intt(Poly &a) {
  reverse(a.begin() + 1, a.end()), ntt(a);
  LL z = qp(SZ(a));
  for (LL &x : a) x = Mul(x, z);
}
Poly conv(Poly a, Poly b) {
  if (!SZ(a) || !SZ(b)) return {};
  int m = SZ(a) + SZ(b) - 1, n = 1;
  while (n < m) n <<= 1;
  a.resize(n), b.resize(n), ntt(a), ntt(b);
  for (int i = 0; i < n; i++) a[i] = Mul(a[i], b[i]);
  intt(a), a.resize(m);
  return a;
}
Poly pre(Poly a, int n) { a.resize(n); return a; }
Poly der(Poly a) {
  if (!SZ(a)) return {};
  for (int i = 1; i < SZ(a); i++) a[i - 1] = Mul(a[i], i);
  return a.pop_back(), a;
}
Poly integ(Poly a) {
  static Poly iv{0, 1};
  for (int i = SZ(iv); i <= SZ(a); i++) iv.pb(P - Mul(P / i, iv[P % i]));
  a.pb(0);
  for (int i = SZ(a) - 1; i; i--) a[i] = Mul(a[i - 1], iv[i]);
  return a[0] = 0, a;
}
Poly inv(Poly a, int n) {
  assert(!n || (SZ(a) && a[0]));
  if (!n) return {};
  Poly b{qp(a[0])};
  for (int m = 2; m < 2 * n; m <<= 1) {
    int k = min(m, n);
    Poly c = pre(conv(pre(a, k), b), k);
    for (LL &x : c) x = x ? P - x : 0;
    c[0] = Add(c[0], 2);
    b = pre(conv(b, c), k);
  }
  return b;
}
Poly ln(Poly a, int n) {
  assert(!n || (SZ(a) && a[0] == 1));
  if (!n) return {};
  return pre(integ(conv(der(a), inv(a, n))), n);
}
Poly exp(Poly a, int n) {
  assert(!SZ(a) || !a[0]);
  if (!n) return {};
  Poly b{1};
  for (int m = 2; m < 2 * n; m <<= 1) {
    int k = min(m, n);
    Poly c = pre(a, k), d = ln(b, k);
    for (int i = 0; i < k; i++) c[i] = c[i] >= d[i] ? c[i] - d[i] : c[i] - d[i] + P;
    c[0] = Add(c[0], 1);
    b = pre(conv(b, c), k);
  }
  return b;
}
Poly cdq_ntt(Poly g, Poly h) {
  int n = SZ(g); h.resize(n); Poly f(n);
  auto cdq = [&](auto&& self, int l, int r) -> void {
    if (r - l == 1) return f[l] = Add(f[l], g[l]), void();
    int m = (l + r) / 2; self(self, l, m);
    Poly a(f.begin() + l, f.begin() + m), b(h.begin(), h.begin() + r - l);
    a = conv(a, b);
    for (int i = m; i < r; i++) f[i] = Add(f[i], a[i - l]);
    self(self, m, r);
  };
  if (n) cdq(cdq, 0, n);
  return f;
}
