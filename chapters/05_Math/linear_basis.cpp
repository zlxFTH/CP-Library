struct LB {
  ULL a[64]{};
  int rk = 0;
  bool ins(ULL x) {
    for (int i = 63; i >= 0; i--) x = min(x, x ^ a[i]);
    if (!x) return 0;
    a[63 - __builtin_clzll(x)] = x, rk++;
    return 1;
  }
  bool has(ULL x) {
    for (int i = 63; i >= 0; i--) x = min(x, x ^ a[i]);
    return !x;
  }
  ULL mx(ULL x = 0) {
    for (int i = 63; i >= 0; i--) x = max(x, x ^ a[i]);
    return x;
  }
  ULL mn() {
    for (ULL x : a) if (x) return x;
    return 0;
  }
  void merge(LB b) { for (ULL x : b.a) ins(x); }
  vector<ULL> reduce() {
    for (int i = 0; i < 64; i++) for (int j = i + 1; j < 64; j++)
      a[j] = min(a[j], a[j] ^ a[i]);
    vector<ULL> b;
    for (ULL x : a) if (x) b.pb(x);
    return b;
  }
  ULL kth(ULL k) {
    auto b = reduce(); ULL x = 0;
    for (int i = 0; i < SZ(b); i++) if (k >> i & 1) x ^= b[i];
    return x;
  }
};
