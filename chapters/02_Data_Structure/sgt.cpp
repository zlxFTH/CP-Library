template <class S, S (*op)(S, S), S (*e)()> struct SGT {
  int n, sz = 1;
  vector<S> t;
  SGT(int n = 0) : SGT(vector<S>(n, e())) {}
  SGT(const vector<S>& a) : n(a.size()) {
    while (sz < n) sz <<= 1;
    t.assign(2 * sz, e());
    for (int i = 0; i < n; i++) t[sz + i] = a[i];
    for (int p = sz - 1; p; p--) upd(p);
  }
  void upd(int p) {
    t[p] = op(t[2 * p], t[2 * p + 1]);
  }
  void set(int p, S x) {
    assert(0 <= p && p < n);
    t[p += sz] = x;
    while (p >>= 1) upd(p);
  }
  S get(int p) {
    assert(0 <= p && p < n);
    return t[p + sz];
  }
  S prod(int l, int r) {
    assert(0 <= l && l <= r && r <= n);
    S x = e(), y = e();
    for (l += sz, r += sz; l < r; l >>= 1, r >>= 1) {
      if (l & 1) x = op(x, t[l++]);
      if (r & 1) y = op(t[--r], y);
    }
    return op(x, y);
  }
  S all_prod() { return t[1]; }
  template <class F> int max_right(int l, F&& f) {
    assert(0 <= l && l <= n && f(e()));
    if (l == n) return n;
    l += sz;
    S x = e();
    do {
      while (!(l & 1)) l >>= 1;
      if (!f(op(x, t[l]))) {
        while (l < sz) {
          l *= 2;
          if (f(op(x, t[l]))) x = op(x, t[l++]);
        }
        return l - sz;
      }
      x = op(x, t[l++]);
    } while ((l & -l) != l);
    return n;
  }
  template <class F> int min_left(int r, F&& f) {
    assert(0 <= r && r <= n && f(e()));
    if (!r) return 0;
    r += sz;
    S x = e();
    do {
      r--;
      while (r > 1 && (r & 1)) r >>= 1;
      if (!f(op(t[r], x))) {
        while (r < sz) {
          r = 2 * r + 1;
          if (f(op(t[r], x))) x = op(t[r--], x);
        }
        return r + 1 - sz;
      }
      x = op(t[r], x);
    } while ((r & -r) != r);
    return 0;
  }
};
