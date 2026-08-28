ULL primitive_root(ULL p) {
  assert(Factor::prime(p));
  if (p == 2) return 1;
  vector<ULL> f = Factor::factor(p - 1);
  f.erase(unique(f.begin(), f.end()), f.end());
  for (ULL g = 2; g < p; g++) {
    bool ok = true;
    for (ULL q : f) {
      if (Factor::pow_mod(g, (p - 1) / q, p) == 1) {
        ok = false;
        break;
      }
    }
    if (ok) return g;
  }
  return 0;
}
