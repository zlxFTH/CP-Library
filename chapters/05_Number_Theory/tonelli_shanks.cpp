LL sqrt_mul(LL a, LL b, LL p) { return LL(I(a) * b % p); }
LL sqrt_pow(LL a, LL b, LL p) {
  LL r = 1 % p;
  for (; b; b >>= 1, a = sqrt_mul(a, a, p))
    if (b & 1) r = sqrt_mul(r, a, p);
  return r;
}
LL mod_sqrt(LL a, LL p) {
  assert(p >= 2);
  a %= p;
  if (a < 0) a += p;
  if (!a || p == 2) return a;
  if (sqrt_pow(a, (p - 1) / 2, p) != 1) return -1;
  if (p % 4 == 3) {
    LL x = sqrt_pow(a, (p + 1) / 4, p);
    return min(x, p - x);
  }
  LL q = p - 1; int s = 0;
  while (!(q & 1)) q >>= 1, s++;
  LL z = 2; while (sqrt_pow(z, (p - 1) / 2, p) != p - 1) z++;
  LL c = sqrt_pow(z, q, p), x = sqrt_pow(a, (q + 1) / 2, p);
  LL t = sqrt_pow(a, q, p); int m = s;
  while (t != 1) {
    int i = 0; LL y = t;
    while (y != 1 && i < m) y = sqrt_mul(y, y, p), i++;
    assert(i < m);
    LL b = c;
    for (int j = 0; j < m - i - 1; j++) b = sqrt_mul(b, b, p);
    x = sqrt_mul(x, b, p);
    c = sqrt_mul(b, b, p);
    t = sqrt_mul(t, c, p);
    m = i;
  }
  return min(x, p - x);
}
