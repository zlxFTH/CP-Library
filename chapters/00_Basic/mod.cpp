constexpr LL P = 998244353;
LL Add(LL x, LL y) { return (x += y) >= P ? x - P : x; }
LL Mul(LL x, LL y) { return x * y % P; }
LL qp(LL a, LL b = P - 2) {
  LL r = 1;
  for (; b; b >>= 1, a = Mul(a, a)) if (b & 1) r = Mul(r, a);
  return r;
}
