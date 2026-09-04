struct SA {
  vector<int> sa, rk, ht;
  SA(const string& s) : sa(SZ(s)), rk(SZ(s)), ht(SZ(s)) {
    int n = SZ(s);
    if (!n) return;
    iota(ALL(sa), 0);
    sort(ALL(sa), [&](int a, int b) { return s[a] < s[b]; });
    for (int i = 1; i < n; i++) rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
    vector<int> old(n), cnt(n);
    for (int w = 1; rk[sa.back()] < n - 1; w *= 2) {
      int m = 0;
      for (int i = n - w; i < n; i++) old[m++] = i;
      for (int x : sa) if (x >= w) old[m++] = x - w;
      fill(ALL(cnt), 0);
      for (int x : rk) cnt[x]++;
      partial_sum(ALL(cnt), cnt.begin());
      for (int i = n; i--;) sa[--cnt[rk[old[i]]]] = old[i];
      swap(rk, old);
      rk[sa[0]] = 0;
      for (int i = 1; i < n; i++) {
        int a = sa[i - 1], b = sa[i];
        rk[b] = rk[a] + (old[a] != old[b]
            || (a + w < n ? old[a + w] : -1) != (b + w < n ? old[b + w] : -1));
      }
    }
    for (int i = 0, k = 0; i < n; i++) {
      if (!rk[i]) { k = 0; continue; }
      if (k) k--;
      int j = sa[rk[i] - 1];
      while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
      ht[rk[i]] = k;
    }
  }
};
