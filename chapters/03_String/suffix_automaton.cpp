template <int C = 26>
struct SAM {
  vector<array<int, C>> ch;
  vector<int> fa, len;
  SAM(int n = 0) : ch(2), fa(2), len(2) {
    ch.reserve(2 * n + 2);
    fa.reserve(2 * n + 2);
    len.reserve(2 * n + 2);
  }
  int node() {
    ch.push_back({});
    fa.pb(0);
    len.pb(0);
    return SZ(ch) - 1;
  }
  int ins(int p, int c) {
    assert(0 <= c && c < C);
    int cur = node();
    len[cur] = len[p] + 1;
    for (; p && !ch[p][c]; p = fa[p]) ch[p][c] = cur;
    if (!p) fa[cur] = 1;
    else {
      int q = ch[p][c];
      if (len[q] == len[p] + 1) fa[cur] = q;
      else {
        int cl = node();
        len[cl] = len[p] + 1;
        ch[cl] = ch[q];
        fa[cl] = fa[q];
        fa[q] = fa[cur] = cl;
        for (; p && ch[p][c] == q; p = fa[p]) ch[p][c] = cl;
      }
    }
    return cur;
  }
};
