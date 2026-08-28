template <class S, S (*op)(S, S), S (*e)(),
    class F, S (*FS)(F, S), F (*FF)(F, F), F (*id)()>
struct LazySGT {
  int n, sz, lg = 0;
  vector<S> t;
  vector<F> lz;
  LazySGT(int n = 0) : LazySGT(vector<S>(n, e())) {}
  LazySGT(const vector<S>& a) : n(a.size()) {
    while ((1 << lg) < n) lg++;
    sz = 1 << lg;
    t.assign(2 * sz, e());
    lz.assign(sz, id());
    for (int i = 0; i < n; i++) t[sz + i] = a[i];
    for (int p = sz - 1; p; p--) upd(p);
  }
  void upd(int p) {
    t[p] = op(t[2 * p], t[2 * p + 1]);
  }
  void push(int p, F f) {
    t[p] = FS(f, t[p]);
    if (p < sz) lz[p] = FF(f, lz[p]);
  }
  void down(int p) {
    push(2 * p, lz[p]);
    push(2 * p + 1, lz[p]);
    lz[p] = id();
  }
  void set(int p, S x) {
    assert(0 <= p && p < n);
    p += sz;
    for (int i = lg; i; i--) down(p >> i);
    t[p] = x;
    for (int i = 1; i <= lg; i++) upd(p >> i);
  }
  S get(int p) {
    assert(0 <= p && p < n);
    p += sz;
    for (int i = lg; i; i--) down(p >> i);
    return t[p];
  }
  S prod(int l, int r) {
    assert(0 <= l && l <= r && r <= n);
    if (l == r) return e();
    l += sz;
    r += sz;
    for (int i = lg; i; i--) {
      if (((l >> i) << i) != l) down(l >> i);
      if (((r >> i) << i) != r) down((r - 1) >> i);
    }
    S x = e(), y = e();
    while (l < r) {
      if (l & 1) x = op(x, t[l++]);
      if (r & 1) y = op(t[--r], y);
      l >>= 1;
      r >>= 1;
    }
    return op(x, y);
  }
  S all_prod() { return t[1]; }
  void apply(int p, F f) {
    assert(0 <= p && p < n);
    p += sz;
    for (int i = lg; i; i--) down(p >> i);
    t[p] = FS(f, t[p]);
    for (int i = 1; i <= lg; i++) upd(p >> i);
  }
  void apply(int l, int r, F f) {
    assert(0 <= l && l <= r && r <= n);
    if (l == r) return;
    l += sz;
    r += sz;
    for (int i = lg; i; i--) {
      if (((l >> i) << i) != l) down(l >> i);
      if (((r >> i) << i) != r) down((r - 1) >> i);
    }
    int a = l, b = r;
    while (l < r) {
      if (l & 1) push(l++, f);
      if (r & 1) push(--r, f);
      l >>= 1;
      r >>= 1;
    }
    l = a;
    r = b;
    for (int i = 1; i <= lg; i++) {
      if (((l >> i) << i) != l) upd(l >> i);
      if (((r >> i) << i) != r) upd((r - 1) >> i);
    }
  }
  template <class G> int max_right(int l, G&& g) {
    assert(0 <= l && l <= n && g(e()));
    if (l == n) return n;
    l += sz;
    for (int i = lg; i; i--) down(l >> i);
    S x = e();
    do {
      while (!(l & 1)) l >>= 1;
      if (!g(op(x, t[l]))) {
        while (l < sz) {
          down(l);
          l *= 2;
          if (g(op(x, t[l]))) x = op(x, t[l++]);
        }
        return l - sz;
      }
      x = op(x, t[l++]);
    } while ((l & -l) != l);
    return n;
  }
  template <class G> int min_left(int r, G&& g) {
    assert(0 <= r && r <= n && g(e()));
    if (!r) return 0;
    r += sz;
    for (int i = lg; i; i--) down((r - 1) >> i);
    S x = e();
    do {
      r--;
      while (r > 1 && (r & 1)) r >>= 1;
      if (!g(op(t[r], x))) {
        while (r < sz) {
          down(r);
          r = 2 * r + 1;
          if (g(op(t[r], x))) x = op(t[r--], x);
        }
        return r + 1 - sz;
      }
      x = op(t[r], x);
    } while ((r & -r) != r);
    return 0;
  }
};
