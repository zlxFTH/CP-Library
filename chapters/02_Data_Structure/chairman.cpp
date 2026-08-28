struct Chairman {
  struct Node {
    int ls, rs, sum;
  };
  int n;
  vector<Node> t = {{0, 0, 0}};
  vector<int> rt = {0};
  Chairman(int n) : n(n) { assert(n > 0); }
  int copy(int p) {
    t.push_back(t[p]);
    return SZ(t) - 1;
  }
  int add(int p, int l, int r, int x, int v) {
    int q = copy(p);
    t[q].sum += v;
    if (r - l == 1) return q;
    int m = (l + r) / 2;
    if (x < m) t[q].ls = add(t[q].ls, l, m, x, v);
    else t[q].rs = add(t[q].rs, m, r, x, v);
    return q;
  }
  void add(int x, int v = 1) {
    assert(0 <= x && x < n);
    rt.push_back(add(rt.back(), 0, n, x, v));
  }
  int count(int a, int b, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) return 0;
    if (ql <= l && r <= qr) return t[b].sum - t[a].sum;
    int m = (l + r) / 2;
    return count(t[a].ls, t[b].ls, l, m, ql, qr)
        + count(t[a].rs, t[b].rs, m, r, ql, qr);
  }
  int count(int l, int r, int ql, int qr) {
    assert(0 <= l && l <= r && r < SZ(rt));
    assert(0 <= ql && ql <= qr && qr <= n);
    return count(rt[l], rt[r], 0, n, ql, qr);
  }
  int kth(int a, int b, int l, int r, int k) {
    if (r - l == 1) return l;
    int m = (l + r) / 2;
    int s = t[t[b].ls].sum - t[t[a].ls].sum;
    if (k < s) return kth(t[a].ls, t[b].ls, l, m, k);
    return kth(t[a].rs, t[b].rs, m, r, k - s);
  }
  int kth(int l, int r, int k) {
    assert(0 <= l && l <= r && r < SZ(rt));
    assert(0 <= k && k < t[rt[r]].sum - t[rt[l]].sum);
    return kth(rt[l], rt[r], 0, n, k);
  }
};
