struct PAM {
  vector<array<int, 26>> ch;
  vector<int> fail, len, cnt, num, s;
  int sz = 2, las = 0;
  LL tot = 0;
  PAM(int n) : ch(n + 2), fail(n + 2), len(n + 2),
      cnt(n + 2), num(n + 2), s(1, -1) {
    fail[0] = fail[1] = 1, len[1] = -1;
  }
  int add(int c) {
    s.pb(c);
    int n = SZ(s) - 1, p = las;
    while (s[n - len[p] - 1] != c) p = fail[p];
    if (!ch[p][c]) {
      int q = fail[p], x = sz++;
      while (s[n - len[q] - 1] != c) q = fail[q];
      len[x] = len[p] + 2, fail[x] = ch[q][c];
      num[x] = num[fail[x]] + 1, ch[p][c] = x;
    }
    las = ch[p][c], cnt[las]++, tot += num[las];
    return las;
  }
  void calc() {
    for (int p = sz - 1; p > 1; p--) cnt[fail[p]] += cnt[p];
  }
};
