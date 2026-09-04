LL primitive_root(LL p) {
  assert(prime(p));
  if (p == 2) return 1;
  vector<LL> f = factor(p - 1);
  f.erase(unique(ALL(f)), f.end());
  for (LL g = 2; g < p; g++) {
    bool ok = true;
    for (LL q : f) {
      if (qp(g, (p - 1) / q, p) == 1) {
        ok = false;
        break;
      }
    }
    if (ok) return g;
  }
  return 0;
}
