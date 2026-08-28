struct ACAM {
  struct Node {
    array<int, 26> ch{};
    int fail = 0;
  };
  vector<Node> t = {{}};
  vector<int> ord;
  ACAM(int n = 0) { t.reserve(n + 1); }
  int add(const string& s) {
    int p = 0;
    for (char x : s) {
      int c = x - 'a';
      assert(0 <= c && c < 26);
      if (!t[p].ch[c]) {
        t[p].ch[c] = t.size();
        t.push_back({});
      }
      p = t[p].ch[c];
    }
    return p;
  }
  void build() {
    queue<int> q;
    ord.clear();
    for (int c = 0; c < 26; c++) {
      if (t[0].ch[c]) q.push(t[0].ch[c]);
    }
    while (SZ(q)) {
      int u = q.front();
      q.pop();
      ord.pb(u);
      for (int c = 0; c < 26; c++) {
        int v = t[u].ch[c];
        if (v) {
          t[v].fail = t[t[u].fail].ch[c];
          q.push(v);
        } else {
          t[u].ch[c] = t[t[u].fail].ch[c];
        }
      }
    }
  }
  vector<LL> count(const string& s) {
    vector<LL> cnt(t.size());
    int p = 0;
    for (char x : s) {
      int c = x - 'a';
      assert(0 <= c && c < 26);
      p = t[p].ch[c];
      cnt[p]++;
    }
    for (int i = SZ(ord) - 1; i >= 0; i--) {
      int u = ord[i];
      cnt[t[u].fail] += cnt[u];
    }
    return cnt;
  }
};
