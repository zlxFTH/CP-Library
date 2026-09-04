LL mulm(LL a, LL b, LL m) { return LL(I(a) * b % m); }
LL qpm(LL a, LL b, LL m) {
  LL r = 1;
  for (; b; b >>= 1, a = mulm(a, a, m)) if (b & 1) r = mulm(r, a, m);
  return r;
}
LL binomPk(LL n, LL k, LL p, LL pk) {
  vector<LL> f(pk + 1, 1);
  for (LL i = 1; i <= pk; i++) f[i] = mulm(f[i - 1], i % p ? i : 1, pk);
  auto F = [&](auto&& self, LL x) -> LL {
    if (!x) return 1;
    return mulm(qpm(f[pk], x / pk, pk),
        mulm(f[x % pk], self(self, x / p), pk), pk);
  };
  auto vp = [&](LL x) {
    LL s = 0;
    while (x) s += x /= p;
    return s;
  };
  LL e = vp(n) - vp(k) - vp(n - k);
  LL a = F(F, n), b = mulm(F(F, k), F(F, n - k), pk);
  LL ib = linear_congruence(b, 1, pk)->first;
  return mulm(mulm(a, ib, pk), qpm(p, e, pk), pk);
}
LL exlucas(LL n, LL k, LL mod) {
  assert(n >= 0 && mod > 0);
  if (k < 0 || k > n || mod == 1) return 0;
  vector<LL> r, m;
  LL x = mod;
  for (LL p = 2; p <= x / p; p++) if (x % p == 0) {
    LL pk = 1;
    while (x % p == 0) x /= p, pk *= p;
    r.pb(binomPk(n, k, p, pk)), m.pb(pk);
  }
  if (x > 1) r.pb(binomPk(n, k, x, x)), m.pb(x);
  return excrt(r, m).first;
}
