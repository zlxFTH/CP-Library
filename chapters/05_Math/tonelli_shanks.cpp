LL mod_sqrt(LL a, LL p) {
  assert(p >= 2);
  a %= p;
  if (a < 0) a += p;
  if (!a || p == 2) return a;
  if (qp(a, (p - 1) / 2, p) != 1) return -1;
  int s = __builtin_ctzll(p - 1); LL q = (p - 1) >> s, z = 2;
  while (qp(z, (p - 1) / 2, p) != p - 1) z++;
  LL c = qp(z, q, p), x = qp(a, (q + 1) / 2, p), t = qp(a, q, p);
  for (int m = s; t != 1;) {
    int i = 0;
    for (LL y = t; y != 1; i++) y = LL(I(y) * y % p);
    LL b = qp(c, 1LL << (m - i - 1), p);
    x = LL(I(x) * b % p), c = LL(I(b) * b % p);
    t = LL(I(t) * c % p), m = i;
  }
  return min(x, p - x);
}
