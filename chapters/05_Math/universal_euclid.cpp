template<class T>
T pw(T a, LL n) {
  T r{};
  for (; n; n >>= 1, a = a + a) if (n & 1) r = r + a;
  return r;
}
template<class T>
T euclid(LL a, LL b, LL c, LL n, T U, T R) {
  if (b >= c) return pw(U, b / c) + euclid(a, b % c, c, n, U, R);
  if (a >= c) return euclid(a % c, b, c, n, U, pw(U, a / c) + R);
  LL m = LL((I(a) * n + b) / c);
  if (!m) return pw(R, n);
  return pw(R, (c - b - 1) / a) + U
      + euclid(c, (c - b - 1) % a, a, m - 1, R, U)
      + pw(R, n - LL((I(c) * m - b - 1) / a));
}
