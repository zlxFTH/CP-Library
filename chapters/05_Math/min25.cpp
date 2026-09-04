using A = array<LL, 3>;
A c{P - 1, 1, 0};
LL fpk(LL p, int e) { return Mul(qp(p % P, e - 1), (p - 1) % P); }
LL min25(LL n) {
  int B = sqrtl(n), m = upper_bound(ALL(pr), B) - pr.begin();
  vector<LL> w; vector<A> g;
  LL iv2 = qp(2), iv6 = qp(6);
  auto sum = [&](LL n) {
    LL x = n % P;
    return A{(n - 1) % P,
        (Mul(Mul(x, (x + 1) % P), iv2) - 1 + P) % P,
        (Mul(Mul(Mul(x, (x + 1) % P), (2 * x + 1) % P), iv6) - 1 + P) % P};
  };
  for (LL l = 1, r; l <= n; l = r + 1) {
    LL x = n / l; r = n / x;
    w.pb(x), g.pb(sum(x));
  }
  auto id = [&](LL x) { return x <= B ? SZ(w) - x : n / x - 1; };
  for (int j = 0; j < m; j++) {
    LL p = pr[j], x = p % P;
    A pk{1, x, Mul(x, x)};
    int t = id(p - 1);
    for (int i = 0; I(p) * p <= w[i]; i++) {
      int k = id(w[i] / p);
      for (int d = 0; d < 3; d++) {
        LL &v = g[i][d], z = (g[k][d] - g[t][d] + P) % P;
        v = (v - Mul(pk[d], z) + P) % P;
      }
    }
  }
  auto S = [&](auto&& self, LL x, int y) -> LL {
    if (y && pr[y - 1] >= x) return 0;
    int k = id(x), t = id(y ? pr[y - 1] : 1); LL ans = 0;
    for (int d = 0; d < 3; d++)
      ans = Add(ans, Mul(c[d], (g[k][d] - g[t][d] + P) % P));
    for (int i = y; i < m && I(pr[i]) * pr[i] <= x; i++) {
      LL pe = pr[i];
      for (int e = 1;; e++) {
        LL z = self(self, x / pe, i + 1);
        if (e > 1) z = Add(z, 1);
        ans = Add(ans, Mul(fpk(pr[i], e), z));
        if (pe > x / pr[i]) break;
        pe *= pr[i];
      }
    }
    return ans;
  };
  return Add(S(S, n, 0), 1);
}
