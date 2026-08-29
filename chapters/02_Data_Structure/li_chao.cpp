#define ls(p) t[p].ls
#define rs(p) t[p].rs
struct SGT {
  static constexpr LL INF = (LL)4e18;
  struct V {
    LL k = 0, b = INF;
    I get(LL x) { return (I)k * x + b; }
  };
  struct Node {
    int ls, rs;
    V v;
  };
  int n;
  vector<Node> t = {{}};
  int node() {
    t.push_back({});
    return SZ(t) - 1;
  }
  int add(V v, int p, int l = 0, int r = -1) {
    if (r < 0) r = n;
    if (!p) p = node();
    int m = (l + r) / 2;
    if (v.get(m) < t[p].v.get(m)) swap(v, t[p].v);
    if (r - l == 1) return p;
    if (v.get(l) < t[p].v.get(l)) ls(p) = add(v, ls(p), l, m);
    else if (v.get(r - 1) < t[p].v.get(r - 1)) rs(p) = add(v, rs(p), m, r);
    return p;
  }
  int add(int ql, int qr, V v, int p, int l = 0, int r = -1) {
    if (r < 0) r = n;
    if (ql <= l && r <= qr) return add(v, p, l, r);
    if (!p) p = node();
    int m = (l + r) / 2;
    if (ql < m) ls(p) = add(ql, qr, v, ls(p), l, m);
    if (m < qr) rs(p) = add(ql, qr, v, rs(p), m, r);
    return p;
  }
  int merge(int p, int q, int l = 0, int r = -1) {
    if (r < 0) r = n;
    if (!p || !q) return p | q;
    p = add(t[q].v, p, l, r);
    if (r - l == 1) return p;
    int m = (l + r) / 2;
    ls(p) = merge(ls(p), ls(q), l, m);
    rs(p) = merge(rs(p), rs(q), m, r);
    return p;
  }
  LL qry(int x, int p, int l = 0, int r = -1) {
    if (r < 0) r = n;
    if (!p) return INF;
    LL ans = clamp<I>(t[p].v.get(x), -INF, INF);
    if (r - l == 1) return ans;
    int m = (l + r) / 2;
    if (x < m) return min(ans, qry(x, ls(p), l, m));
    return min(ans, qry(x, rs(p), m, r));
  }
};
#undef ls
#undef rs
