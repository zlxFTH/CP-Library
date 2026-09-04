vector<LL> sf;
unordered_map<LL, LL> mem;
LL G(LL n) { return n; }
LL H(LL) { return 1; }
void initDu(int n) {
  sf.assign(n + 1, 0), mem.clear();
  for (int i = 1; i <= n; i++) sf[i] = sf[i - 1] + mu[i];
}
LL du(LL n) {
  if (n < SZ(sf)) return sf[n];
  if (auto it = mem.find(n); it != mem.end()) return it->second;
  LL ans = H(n);
  for (LL l = 2, r; l <= n; l = r + 1) {
    LL q = n / l;
    r = n / q;
    ans -= (G(r) - G(l - 1)) * du(q);
  }
  return mem[n] = ans;
}
