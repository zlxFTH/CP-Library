#define ls(p) t[p].ch[0]
#define rs(p) t[p].ch[1]
struct FHQTreap {
  struct V {
  };
  struct Node {
    int ch[2]{}, sz = 0;
    ULL pri = 0;
    V v;
    bool rev = false;
  };
  vector<Node> t = {{}};
  int rt = 0;
  int size(int p) { return t[p].sz; }
  int size() { return size(rt); }
  void up(int p) {
    t[p].sz = size(ls(p)) + size(rs(p)) + 1;
  }
  void apply_rev(int p) {
    if (p) swap(ls(p), rs(p)), t[p].rev ^= 1;
  }
  void down(int p) {
    if (!t[p].rev) return;
    apply_rev(ls(p)), apply_rev(rs(p));
    t[p].rev = false;
  }
  int node(V v) {
    t.push_back({{}, 1, rnd(), v});
    return SZ(t) - 1;
  }
  void split(int p, int k, int& x, int& y) {
    if (!p) return x = y = 0, void();
    down(p);
    if (k <= size(ls(p))) y = p, split(ls(p), k, x, ls(y));
    else x = p, split(rs(p), k - size(ls(p)) - 1, rs(x), y);
    up(p);
  }
  int merge(int p, int q) {
    if (!p || !q) return p | q;
    if (t[p].pri < t[q].pri) {
      down(p), rs(p) = merge(rs(p), q), up(p);
      return p;
    }
    down(q), ls(q) = merge(p, ls(q)), up(q);
    return q;
  }
  int insert(int p, int k, int q) {
    if (!p) return q;
    if (t[q].pri < t[p].pri) {
      split(p, k, ls(q), rs(q)), up(q);
      return q;
    }
    down(p);
    if (k <= size(ls(p))) ls(p) = insert(ls(p), k, q);
    else rs(p) = insert(rs(p), k - size(ls(p)) - 1, q);
    up(p);
    return p;
  }
  void insert(int k, V v) {
    rt = insert(rt, k, node(v));
  }
  int erase(int p, int k) {
    down(p);
    int s = size(ls(p));
    if (k == s) return merge(ls(p), rs(p));
    if (k < s) ls(p) = erase(ls(p), k);
    else rs(p) = erase(rs(p), k - s - 1);
    up(p);
    return p;
  }
  void erase(int k) {
    rt = erase(rt, k);
  }
  void reverse(int l, int r) {
    int x, y, z;
    split(rt, r, x, z), split(x, l, x, y);
    apply_rev(y), rt = merge(merge(x, y), z);
  }
  int kth(int p, int k) {
    down(p);
    int s = size(ls(p));
    if (k == s) return p;
    if (k < s) return kth(ls(p), k);
    return kth(rs(p), k - s - 1);
  }
  void clear() {
    t.assign(1, {}), rt = 0;
  }
};
#undef ls
#undef rs
