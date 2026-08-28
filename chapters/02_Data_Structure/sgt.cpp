template <class S> struct SGT {
  int n;
  vector<S> t;
  SGT(int n) : n(n), t(2 * n) {}
  SGT(vector<S> a) : SGT(SZ(a)) {
    copy(ALL(a), t.begin() + n);
    for (int p = n - 1; p; p--) t[p] = t[2 * p] + t[2 * p + 1];
  }
  void set(int p, S x) {
    t[p += n] = x;
    while (p >>= 1) t[p] = t[2 * p] + t[2 * p + 1];
  }
  S prod(int l, int r) {
    S x{}, y{};
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) x = x + t[l++];
      if (r & 1) y = t[--r] + y;
    }
    return x + y;
  }
};
