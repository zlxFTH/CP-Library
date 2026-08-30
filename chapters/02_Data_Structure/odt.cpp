struct ODT {
  struct Node {
    int l, r, c;
    bool operator<(Node x) const {
      return l < x.l;
    }
  };
  set<Node> s;
  using IT = set<Node>::iterator;
  IT split(int x) {
    auto it = s.lower_bound({x});
    if (it != s.end() && it->l == x) return it;
    auto p = prev(it);
    if (p->r == x) return it;
    Node a = *p;
    s.erase(p);
    s.insert({a.l, x, a.c});
    return s.insert({x, a.r, a.c}).first;
  }
  IT merge(IT it) {
    Node a = *it;
    if (it != s.begin() && prev(it)->c == a.c) {
      a.l = prev(it)->l;
      s.erase(prev(it));
    }
    auto q = next(it);
    if (q != s.end() && q->c == a.c) {
      a.r = q->r;
      s.erase(q);
    }
    s.erase(it);
    return s.insert(a).first;
  }
  void mdf(int l, int r, int c) {
    auto R = split(r), L = split(l);
    for (auto it = L; it != R; ++it) {
    }
    s.erase(L, R);
    merge(s.insert({l, r, c}).first);
  }
};
