template <int C = 26>
struct PAM {
  struct Node {
    array<int, C> ch{};
    int fail = 0, len = 0, cnt = 0, num = 0;
  };
  vector<Node> t;
  vector<int> s;
  int las;
  LL tot;
  void init(int n) {
    t.assign(2, {});
    t.reserve(n + 2);
    t[0].fail = t[1].fail = 1;
    t[1].len = -1;
    s.assign(1, -1);
    s.reserve(n + 1);
    las = 0;
    tot = 0;
  }
  int get_fail(int p, int c) {
    int n = SZ(s) - 1;
    while (s[n - t[p].len - 1] != c) p = t[p].fail;
    return p;
  }
  int add(int c) {
    assert(0 <= c && c < C);
    s.pb(c);
    int p = get_fail(las, c);
    if (!t[p].ch[c]) {
      int q = get_fail(t[p].fail, c);
      Node x;
      x.len = t[p].len + 2;
      x.fail = t[q].ch[c];
      x.num = t[x.fail].num + 1;
      t[p].ch[c] = SZ(t);
      t.pb(x);
    }
    las = t[p].ch[c];
    t[las].cnt++;
    tot += t[las].num;
    return las;
  }
  int size() { return SZ(t) - 2; }
  int suf_cnt() { return t[las].num; }
  LL count() { return tot; }
  void calc() {
    for (int p = SZ(t) - 1; p >= 2; p--) t[t[p].fail].cnt += t[p].cnt;
  }
};
