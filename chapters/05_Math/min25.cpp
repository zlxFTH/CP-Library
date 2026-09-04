array<LL, 3> coef{P - 1, 1, 0};
LL fpk(LL p, int e) {
  return Mul(qp(p % P, e - 1), (p - 1) % P);
}
LL min25(LL n) {
  int B = sqrtl(n);
  while (I(B + 1) * (B + 1) <= n) B++;
  while (I(B) * B > n) B--;
  int pc = upper_bound(ALL(pr), B) - pr.begin();
  vector<LL> w;
  vector<int> id1(B + 1), id2(B + 1);
  vector<array<LL, 3>> g;
  LL iv2 = qp(2), iv6 = qp(6);
  auto sums = [&](LL n) {
    LL x = n % P;
    LL s1 = Mul(Mul(x, (x + 1) % P), iv2);
    LL s2 = Mul(Mul(Mul(x, (x + 1) % P),
        (2 * x + 1) % P), iv6);
    return array<LL, 3>{(n - 1) % P,
        (s1 - 1 + P) % P, (s2 - 1 + P) % P};
  };
  for (LL l = 1, r; l <= n; l = r + 1) {
    LL x = n / l;
    r = n / x;
    int k = SZ(w);
    w.pb(x), g.pb(sums(x));
    if (x <= B) id1[x] = k;
    else id2[n / x] = k;
  }
  auto id = [&](LL x) { return x <= B ? id1[x] : id2[n / x]; };
  array<LL, 3> sp{};
  vector<LL> pre(pc + 1);
  for (int j = 0; j < pc; j++) {
    LL p = pr[j], x = p % P;
    array<LL, 3> pk{1, x, Mul(x, x)};
    for (int i = 0; i < SZ(w) && I(p) * p <= w[i]; i++) {
      int k = id(w[i] / p);
      for (int d = 0; d < 3; d++) {
        LL z = (g[k][d] - sp[d] + P) % P;
        g[i][d] = (g[i][d] - Mul(pk[d], z) + P) % P;
      }
    }
    for (int d = 0; d < 3; d++) {
      sp[d] = Add(sp[d], pk[d]);
      pre[j + 1] = Add(pre[j + 1], Mul(coef[d], sp[d]));
    }
  }
  auto ps = [&](LL x) {
    LL ans = 0;
    int k = id(x);
    for (int d = 0; d < 3; d++)
      ans = Add(ans, Mul(coef[d], g[k][d]));
    return ans;
  };
  auto S = [&](auto&& self, LL x, int y) -> LL {
    if (y && pr[y - 1] >= x) return 0;
    LL ans = (ps(x) - pre[y] + P) % P;
    for (int i = y; i < pc && I(pr[i]) * pr[i] <= x; i++) {
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
