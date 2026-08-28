LL exgcd(LL a, LL b, LL& x, LL& y) {
  assert(a >= 0 && b >= 0 && (a || b));
  if (!b) return x = 1, y = 0, a;
  LL g = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return g;
}
optional<pair<LL, LL>> linear_congruence(LL a, LL b, LL m) {
  assert(m > 0);
  a %= m;
  b %= m;
  if (a < 0) a += m;
  if (b < 0) b += m;
  LL x, y, g = exgcd(a, m, x, y);
  if (b % g) return nullopt;
  LL p = m / g;
  I r = I(x) * (b / g) % p;
  if (r < 0) r += p;
  return pair<LL, LL>{LL(r), p};
}
