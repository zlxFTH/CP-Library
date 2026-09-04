vector<LL> fac, ifac;
void initComb(int n) {
  fac.resize(n + 1), ifac.resize(n + 1);
  fac[0] = 1;
  for (int i = 1; i <= n; i++) fac[i] = Mul(fac[i - 1], i);
  ifac[n] = qp(fac[n]);
  for (int i = n; i; i--) ifac[i - 1] = Mul(ifac[i], i);
}
LL binom(int n, int m) {
  if (n < m || m < 0) return 0;
  return Mul(fac[n], Mul(ifac[m], ifac[n - m]));
}
