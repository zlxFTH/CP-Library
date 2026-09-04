bool prime(LL n) {
  if (n < 4) return n > 1;
  if (n % 2 == 0) return false;
  int s = __builtin_ctzll(n - 1);
  LL d = (n - 1) >> s;
  for (LL a : {2LL, 325LL, 9375LL, 28178LL,
      450775LL, 9780504LL, 1795265022LL}) {
    if (a % n == 0) continue;
    LL x = qp(a, d, n);
    if (x == 1 || x == n - 1) continue;
    for (int r = 1; r < s && x != n - 1; r++) x = LL(I(x) * x % n);
    if (x != n - 1) return false;
  }
  return true;
}
LL rho(LL n) {
  if (n % 2 == 0) return 2;
  while (true) {
    LL c = rnd() % (n - 1) + 1, x = rnd() % n, y = x, d = 1;
    auto f = [&](LL x) { return LL((I(x) * x + c) % n); };
    while (d == 1) x = f(x), y = f(f(y)), d = gcd(abs(x - y), n);
    if (d < n) return d;
  }
}
void fac(LL n, vector<LL>& a) {
  if (n == 1) return;
  if (prime(n)) return a.pb(n);
  LL d = rho(n);
  fac(d, a), fac(n / d, a);
}
vector<LL> factor(LL n) {
  assert(n > 0);
  vector<LL> a;
  fac(n, a), sort(ALL(a));
  return a;
}
