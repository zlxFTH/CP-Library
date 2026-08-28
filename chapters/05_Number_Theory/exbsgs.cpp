namespace DiscreteLog {
LL norm(LL x, LL m) {
  x %= m;
  return x < 0 ? x + m : x;
}
LL mul_mod(LL a, LL b, LL m) { return LL(I(a) * b % m); }
LL inv_mod(LL a, LL m) {
  LL b = m;
  I x = 1, y = 0;
  while (b) {
    LL q = a / b;
    a -= q * b;
    swap(a, b);
    x -= I(q) * y;
    swap(x, y);
  }
  assert(a == 1);
  x %= m;
  if (x < 0) x += m;
  return LL(x);
}
LL bsgs(LL a, LL b, LL m) {
  assert(m > 1 && gcd(a, m) == 1);
  LL n = LL(sqrtl((long double)m)) + 1;
  unordered_map<LL, LL> baby;
  baby.reserve(size_t(2 * n + 1));
  LL cur = 1 % m;
  for (LL j = 0; j < n; j++) {
    baby.emplace(cur, j);
    cur = mul_mod(cur, a, m);
  }
  LL step = inv_mod(cur, m);
  cur = b;
  for (LL i = 0; i <= n; i++) {
    auto it = baby.find(cur);
    if (it != baby.end()) {
      I x = I(i) * n + it->second;
      if (x <= numeric_limits<LL>::max()) return LL(x);
      return -1;
    }
    cur = mul_mod(cur, step, m);
  }
  return -1;
}
LL exbsgs(LL a, LL b, LL m) {
  assert(m > 0);
  if (m == 1) return 0;
  a = norm(a, m);
  b = norm(b, m);
  if (b == 1) return 0;
  LL k = 1, add = 0;
  while (true) {
    LL g = gcd(a, m);
    if (g == 1) break;
    if (b % g) return -1;
    b /= g;
    m /= g;
    k = mul_mod(k, a / g, m);
    add++;
    if (k == b) return add;
  }
  b = mul_mod(b, inv_mod(k, m), m);
  LL x = bsgs(a, b, m);
  return x < 0 ? -1 : x + add;
}
}
using DiscreteLog::exbsgs;
