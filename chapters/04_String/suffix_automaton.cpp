vector<array<int, 26>> ch(2 * n + 2);
vector<int> fa(2 * n + 2), len(2 * n + 2);
int tot = 1;
auto ins = [&](int p, int c) {
  int cur = ++tot;
  len[cur] = len[p] + 1;
  for (; p && !ch[p][c]; p = fa[p]) ch[p][c] = cur;
  if (!p) fa[cur] = 1;
  else {
    int q = ch[p][c];
    if (len[q] == len[p] + 1) fa[cur] = q;
    else {
      int cl = ++tot;
      ch[cl] = ch[q], fa[cl] = fa[q], len[cl] = len[p] + 1;
      for (; p && ch[p][c] == q; p = fa[p]) ch[p][c] = cl;
      fa[q] = fa[cur] = cl;
    }
  }
  return cur;
};
