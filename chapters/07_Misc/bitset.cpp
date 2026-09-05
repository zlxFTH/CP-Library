struct BS {
  int n;
  vector<ULL> a;
  BS(int n = 0) : n(n), a((n + 63LL) / 64) {}
  void trim() { if (n % 64) a.back() &= (1ULL << (n % 64)) - 1; }
  bool operator[](int i) const { return a[i / 64] >> (i % 64) & 1; }
  void set(int i, bool v = 1) {
    ULL m = 1ULL << (i % 64);
    if (v) a[i / 64] |= m; else a[i / 64] &= ~m;
  }
  void flip(int i) { a[i / 64] ^= 1ULL << (i % 64); }
  void clear() { fill(ALL(a), 0); }
  int count() const { int s = 0; for (ULL x : a) s += __builtin_popcountll(x); return s; }
  bool any() const { for (ULL x : a) if (x) return 1; return 0; }
  bool operator==(const BS& b) const { return n == b.n && a == b.a; }
  bool operator!=(const BS& b) const { return !(*this == b); }
  BS& operator&=(const BS& b) { for (int i = 0; i < SZ(a); i++) a[i] &= b.a[i]; return *this; }
  BS& operator|=(const BS& b) { for (int i = 0; i < SZ(a); i++) a[i] |= b.a[i]; return *this; }
  BS& operator^=(const BS& b) { for (int i = 0; i < SZ(a); i++) a[i] ^= b.a[i]; return *this; }
  friend BS operator&(BS a, const BS& b) { a &= b; return a; }
  friend BS operator|(BS a, const BS& b) { a |= b; return a; }
  friend BS operator^(BS a, const BS& b) { a ^= b; return a; }
  BS operator~() const {
    BS b = *this;
    for (ULL& x : b.a) x = ~x;
    b.trim(); return b;
  }
  BS shift(int k, int d) const {
    BS b(n);
    int q = k / 64, r = k % 64;
    for (int i = 0; i < SZ(a); i++) {
      int j = i + d * q;
      if (j >= 0 && j < SZ(a)) b.a[j] |= d > 0 ? a[i] << r : a[i] >> r;
      j += d;
      if (r && j >= 0 && j < SZ(a))
        b.a[j] |= d > 0 ? a[i] >> (64 - r) : a[i] << (64 - r);
    }
    b.trim(); return b;
  }
  BS operator<<(int k) const { return shift(k, 1); }
  BS operator>>(int k) const { return shift(k, -1); }
  BS& operator<<=(int k) { *this = *this << k; return *this; }
  BS& operator>>=(int k) { *this = *this >> k; return *this; }
  int next(int i = 0) const {
    if (i >= n) return n;
    int j = i / 64; ULL x = a[j] & (~0ULL << (i % 64));
    while (!x && ++j < SZ(a)) x = a[j];
    return x ? j * 64 + __builtin_ctzll(x) : n;
  }
};
