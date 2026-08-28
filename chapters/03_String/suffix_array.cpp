struct SuffixArray {
  int n;
  vector<int> sa, rk, lc;
  SuffixArray(const string& s) : n(s.size()), sa(n), rk(n), lc(max(0, n - 1)) {
    if (!n) return;
    iota(ALL(sa), 0);
    sort(ALL(sa), [&](int a, int b) { return s[a] < s[b]; });
    rk[sa[0]] = 0;
    for (int i = 1; i < n; i++) {
      rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
    }
    vector<int> tmp, cnt(n);
    tmp.reserve(n);
    for (int w = 1; rk[sa[n - 1]] < n - 1; w *= 2) {
      tmp.clear();
      for (int i = max(0, n - w); i < n; i++) tmp.pb(i);
      for (int i = 0; i < n; i++) if (sa[i] >= w) tmp.pb(sa[i] - w);
      fill(ALL(cnt), 0);
      for (int i = 0; i < n; i++) cnt[rk[i]]++;
      partial_sum(ALL(cnt), cnt.begin());
      for (int i = n - 1; i >= 0; i--) sa[--cnt[rk[tmp[i]]]] = tmp[i];
      swap(rk, tmp);
      rk[sa[0]] = 0;
      for (int i = 1; i < n; i++) {
        int a = sa[i - 1], b = sa[i];
        int x = a + w < n ? tmp[a + w] : -1;
        int y = b + w < n ? tmp[b + w] : -1;
        rk[b] = rk[a] + (tmp[a] != tmp[b] || x != y);
      }
    }
    for (int i = 0, k = 0; i < n; i++) {
      int j = rk[i];
      if (!j) {
        k = 0;
        continue;
      }
      if (k) k--;
      int p = sa[j - 1];
      while (i + k < n && p + k < n && s[i + k] == s[p + k]) k++;
      lc[j - 1] = k;
    }
  }
};
