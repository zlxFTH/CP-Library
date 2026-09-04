LL floor_sum(LL n, LL m, LL a, LL b) {
  LL ans = 0;
  for (;;) {
    if (a >= m) ans += LL(I(n) * (n - 1) / 2 * (a / m)), a %= m;
    if (b >= m) ans += LL(I(n) * (b / m)), b %= m;
    I y = I(a) * n + b;
    if (y < m) return ans;
    n = LL(y / m), b = LL(y % m), swap(a, m);
  }
}
