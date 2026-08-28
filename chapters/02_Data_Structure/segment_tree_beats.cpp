struct Beats {
  static constexpr LL INF = (LL)4e18;
  struct Node {
    LL sum = 0, add = 0;
    LL mx = -INF, smx = -INF;
    LL mn = INF, smn = INF;
    int cmx = 0, cmn = 0;
  };
  int n;
  vector<Node> t;
  Beats(const vector<LL>& a) : n(a.size()), t(4 * n) {
    assert(n > 0);
    build(1, 0, n, a);
  }
  Node merge(Node a, Node b) {
    Node c;
    c.sum = a.sum + b.sum;
    if (a.mx == b.mx) {
      c.mx = a.mx;
      c.smx = max(a.smx, b.smx);
      c.cmx = a.cmx + b.cmx;
    } else if (a.mx > b.mx) {
      c.mx = a.mx;
      c.smx = max(a.smx, b.mx);
      c.cmx = a.cmx;
    } else {
      c.mx = b.mx;
      c.smx = max(a.mx, b.smx);
      c.cmx = b.cmx;
    }
    if (a.mn == b.mn) {
      c.mn = a.mn;
      c.smn = min(a.smn, b.smn);
      c.cmn = a.cmn + b.cmn;
    } else if (a.mn < b.mn) {
      c.mn = a.mn;
      c.smn = min(a.smn, b.mn);
      c.cmn = a.cmn;
    } else {
      c.mn = b.mn;
      c.smn = min(a.mn, b.smn);
      c.cmn = b.cmn;
    }
    return c;
  }
  void build(int p, int l, int r, const vector<LL>& a) {
    if (r - l == 1) {
      t[p].sum = t[p].mx = t[p].mn = a[l];
      t[p].cmx = t[p].cmn = 1;
      return;
    }
    int m = (l + r) / 2;
    build(2 * p, l, m, a);
    build(2 * p + 1, m, r, a);
    t[p] = merge(t[2 * p], t[2 * p + 1]);
  }
  void apply_add(int p, int len, LL x) {
    t[p].sum += x * len;
    t[p].mx += x;
    t[p].mn += x;
    if (t[p].smx != -INF) t[p].smx += x;
    if (t[p].smn != INF) t[p].smn += x;
    t[p].add += x;
  }
  void apply_chmin(int p, LL x) {
    if (t[p].mx <= x) return;
    t[p].sum += (x - t[p].mx) * t[p].cmx;
    if (t[p].mn == t[p].mx) t[p].mn = x;
    else if (t[p].smn == t[p].mx) t[p].smn = x;
    t[p].mx = x;
  }
  void apply_chmax(int p, LL x) {
    if (t[p].mn >= x) return;
    t[p].sum += (x - t[p].mn) * t[p].cmn;
    if (t[p].mx == t[p].mn) t[p].mx = x;
    else if (t[p].smx == t[p].mn) t[p].smx = x;
    t[p].mn = x;
  }
  void down(int p, int l, int r) {
    int m = (l + r) / 2;
    if (t[p].add) {
      apply_add(2 * p, m - l, t[p].add);
      apply_add(2 * p + 1, r - m, t[p].add);
      t[p].add = 0;
    }
    if (t[2 * p].mx > t[p].mx) apply_chmin(2 * p, t[p].mx);
    if (t[2 * p + 1].mx > t[p].mx) apply_chmin(2 * p + 1, t[p].mx);
    if (t[2 * p].mn < t[p].mn) apply_chmax(2 * p, t[p].mn);
    if (t[2 * p + 1].mn < t[p].mn) apply_chmax(2 * p + 1, t[p].mn);
  }
  void up(int p) {
    t[p] = merge(t[2 * p], t[2 * p + 1]);
  }
  void add(int ql, int qr, LL x, int p, int l, int r) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) return apply_add(p, r - l, x);
    down(p, l, r);
    int m = (l + r) / 2;
    add(ql, qr, x, 2 * p, l, m);
    add(ql, qr, x, 2 * p + 1, m, r);
    up(p);
  }
  void chmin(int ql, int qr, LL x, int p, int l, int r) {
    if (qr <= l || r <= ql || t[p].mx <= x) return;
    if (ql <= l && r <= qr && t[p].smx < x) {
      return apply_chmin(p, x);
    }
    down(p, l, r);
    int m = (l + r) / 2;
    chmin(ql, qr, x, 2 * p, l, m);
    chmin(ql, qr, x, 2 * p + 1, m, r);
    up(p);
  }
  void chmax(int ql, int qr, LL x, int p, int l, int r) {
    if (qr <= l || r <= ql || t[p].mn >= x) return;
    if (ql <= l && r <= qr && t[p].smn > x) {
      return apply_chmax(p, x);
    }
    down(p, l, r);
    int m = (l + r) / 2;
    chmax(ql, qr, x, 2 * p, l, m);
    chmax(ql, qr, x, 2 * p + 1, m, r);
    up(p);
  }
  LL qsum(int ql, int qr, int p, int l, int r) {
    if (qr <= l || r <= ql) return 0;
    if (ql <= l && r <= qr) return t[p].sum;
    down(p, l, r);
    int m = (l + r) / 2;
    return qsum(ql, qr, 2 * p, l, m)
        + qsum(ql, qr, 2 * p + 1, m, r);
  }
  LL qmax(int ql, int qr, int p, int l, int r) {
    if (qr <= l || r <= ql) return -INF;
    if (ql <= l && r <= qr) return t[p].mx;
    down(p, l, r);
    int m = (l + r) / 2;
    return max(qmax(ql, qr, 2 * p, l, m),
        qmax(ql, qr, 2 * p + 1, m, r));
  }
  LL qmin(int ql, int qr, int p, int l, int r) {
    if (qr <= l || r <= ql) return INF;
    if (ql <= l && r <= qr) return t[p].mn;
    down(p, l, r);
    int m = (l + r) / 2;
    return min(qmin(ql, qr, 2 * p, l, m),
        qmin(ql, qr, 2 * p + 1, m, r));
  }
  void add(int l, int r, LL x) {
    assert(0 <= l && l <= r && r <= n);
    if (l < r) add(l, r, x, 1, 0, n);
  }
  void chmin(int l, int r, LL x) {
    assert(0 <= l && l <= r && r <= n);
    if (l < r) chmin(l, r, x, 1, 0, n);
  }
  void chmax(int l, int r, LL x) {
    assert(0 <= l && l <= r && r <= n);
    if (l < r) chmax(l, r, x, 1, 0, n);
  }
  LL qsum(int l, int r) {
    assert(0 <= l && l < r && r <= n);
    return qsum(l, r, 1, 0, n);
  }
  LL qmax(int l, int r) {
    assert(0 <= l && l < r && r <= n);
    return qmax(l, r, 1, 0, n);
  }
  LL qmin(int l, int r) {
    assert(0 <= l && l < r && r <= n);
    return qmin(l, r, 1, 0, n);
  }
};
