pair<LL, LL> excrt(vector<LL> r, vector<LL> m) {
  assert(SZ(r) == SZ(m));
  LL R = 0, M = 1;
  for (int i = 0; i < SZ(r); i++) {
    assert(m[i] > 0);
    auto z = linear_congruence(M, LL((I(r[i]) - R) % m[i]), m[i]);
    if (!z) return {0, 0};
    auto [x, p] = *z;
    I nm = I(M) * p;
    assert(nm <= LLONG_MAX);
    R = LL(I(R) + I(M) * x), M = LL(nm);
  }
  return {R, M};
}
