LL qp(LL a, LL b, LL m) {
  LL r = 1 % m;
  for (; b; b >>= 1, a = LL(I(a) * a % m))
    if (b & 1) r = LL(I(r) * a % m);
  return r;
}
LL bsgs(LL a, LL b, LL m, LL k = 1) {
  assert(m > 1 && gcd(a, m) == 1);
  if (k == b) return 0;
  LL n = LL(sqrtl((long double)m)) + 1, e = b;
  unordered_map<LL, LL> mp;
  for (LL j = 0; j < n; j++, e = LL(I(e) * a % m)) mp[e] = j;
  a = qp(a, n, m), e = k;
  for (LL i = 1; i <= n; i++) {
    e = LL(I(e) * a % m);
    auto it = mp.find(e);
    if (it != mp.end()) return LL(I(i) * n - it->second);
  }
  return -1;
}
LL exbsgs(LL a, LL b, LL m) {
  assert(m > 0);
  if (m == 1) return 0;
  a %= m, b %= m;
  if (a < 0) a += m;
  if (b < 0) b += m;
  if (b == 1) return 0;
  LL k = 1, c = 0, g;
  while ((g = gcd(a, m)) > 1) {
    if (b % g) return -1;
    b /= g, m /= g, k = LL(I(k) * (a / g) % m), c++;
    if (k == b) return c;
  }
  LL x = bsgs(a, b, m, k);
  return x < 0 ? -1 : x + c;
}
