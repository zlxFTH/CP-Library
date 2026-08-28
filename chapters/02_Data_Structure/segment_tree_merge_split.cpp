struct SplitSGT {
  struct Node {
    int ls = 0, rs = 0;
    LL sum = 0;
  };
  int n;
  vector<Node> t = {Node()};
  SplitSGT(int n) : n(n) { assert(n > 0); }
  int node() {
    t.emplace_back();
    return SZ(t) - 1;
  }
  void up(int p) {
    t[p].sum = t[t[p].ls].sum + t[t[p].rs].sum;
  }
  int add(int p, int l, int r, int x, LL v) {
    if (!p) p = node();
    if (r - l == 1) {
      t[p].sum += v;
      return p;
    }
    int m = (l + r) / 2;
    if (x < m) t[p].ls = add(t[p].ls, l, m, x, v);
    else t[p].rs = add(t[p].rs, m, r, x, v);
    up(p);
    return p;
  }
  void add(int& p, int x, LL v) {
    assert(0 <= x && x < n);
    p = add(p, 0, n, x, v);
  }
  LL sum(int p, int l, int r, int ql, int qr) {
    if (!p || qr <= l || r <= ql) return 0;
    if (ql <= l && r <= qr) return t[p].sum;
    int m = (l + r) / 2;
    return sum(t[p].ls, l, m, ql, qr)
        + sum(t[p].rs, m, r, ql, qr);
  }
  LL sum(int p, int l, int r) {
    assert(0 <= l && l <= r && r <= n);
    return sum(p, 0, n, l, r);
  }
  int merge(int a, int b, int l, int r) {
    if (!a || !b) return a + b;
    if (r - l == 1) {
      t[a].sum += t[b].sum;
      return a;
    }
    int m = (l + r) / 2;
    t[a].ls = merge(t[a].ls, t[b].ls, l, m);
    t[a].rs = merge(t[a].rs, t[b].rs, m, r);
    up(a);
    return a;
  }
  int merge(int a, int b) { return merge(a, b, 0, n); }
  pair<int, int> split(int p, int l, int r, int ql, int qr) {
    if (!p || qr <= l || r <= ql) return {p, 0};
    if (ql <= l && r <= qr) return {0, p};
    int m = (l + r) / 2;
    auto [al, bl] = split(t[p].ls, l, m, ql, qr);
    auto [ar, br] = split(t[p].rs, m, r, ql, qr);
    t[p].ls = al;
    t[p].rs = ar;
    up(p);
    if (!al && !ar) p = 0;
    if (!bl && !br) return {p, 0};
    int q = node();
    t[q].ls = bl;
    t[q].rs = br;
    up(q);
    return {p, q};
  }
  int split(int& p, int l, int r) {
    assert(0 <= l && l <= r && r <= n);
    auto [a, b] = split(p, 0, n, l, r);
    p = a;
    return b;
  }
  int kth(int p, LL k) {
    assert(p && 0 <= k && k < t[p].sum);
    int l = 0, r = n;
    while (r - l > 1) {
      int m = (l + r) / 2;
      LL s = t[t[p].ls].sum;
      if (k < s) {
        p = t[p].ls;
        r = m;
      } else {
        k -= s;
        p = t[p].rs;
        l = m;
      }
    }
    return l;
  }
};
