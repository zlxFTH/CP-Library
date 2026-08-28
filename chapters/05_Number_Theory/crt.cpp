LL safe_mod(LL x, LL m) {
  x %= m;
  return x < 0 ? x + m : x;
}
pair<LL, LL> inv_gcd(LL a, LL b) {
  a = safe_mod(a, b);
  if (!a) return {b, 0};
  LL s = b, t = a;
  I x = 0, y = 1;
  while (t) {
    LL q = s / t;
    s -= q * t;
    swap(s, t);
    x -= I(q) * y;
    swap(x, y);
  }
  LL m = b / s;
  x %= m;
  if (x < 0) x += m;
  return {s, LL(x)};
}
pair<LL, LL> crt(const vector<LL>& r, const vector<LL>& m) {
  assert(r.size() == m.size());
  LL r0 = 0, m0 = 1;
  for (int i = 0; i < SZ(r); i++) {
    assert(m[i] > 0);
    LL r1 = safe_mod(r[i], m[i]), m1 = m[i];
    if (m0 < m1) swap(r0, r1), swap(m0, m1);
    if (m0 % m1 == 0) {
      if (r0 % m1 != r1) return {0, 0};
      continue;
    }
    auto [g, im] = inv_gcd(m0, m1);
    LL u = m1 / g;
    if ((r1 - r0) % g) return {0, 0};
    LL x = LL(I((r1 - r0) / g) * im % u);
    I nm = I(m0) * u;
    assert(nm <= numeric_limits<LL>::max());
    I nr = r0 + I(x) * m0;
    m0 = LL(nm);
    r0 = LL(nr % m0);
    if (r0 < 0) r0 += m0;
  }
  return {r0, m0};
}
