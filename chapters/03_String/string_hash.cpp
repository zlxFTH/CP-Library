struct StringHash {
  using H = pair<LL, LL>;
  static constexpr LL P1 = 2034452107, P2 = 2013074419;
  static constexpr LL B1 = 137, B2 = 149;
  int n;
  vector<LL> pw1, pw2, h1, h2;
  StringHash(const string& s) : n(s.size()),
      pw1(n + 1, 1), pw2(n + 1, 1), h1(n + 1), h2(n + 1) {
    for (int i = 0; i < n; i++) {
      int x = (unsigned char)s[i] + 1;
      pw1[i + 1] = pw1[i] * B1 % P1;
      pw2[i + 1] = pw2[i] * B2 % P2;
      h1[i + 1] = (h1[i] * B1 + x) % P1;
      h2[i + 1] = (h2[i] * B2 + x) % P2;
    }
  }
  H get(int l, int r) {
    assert(0 <= l && l <= r && r <= n);
    LL x = (h1[r] - h1[l] * pw1[r - l] % P1 + P1) % P1;
    LL y = (h2[r] - h2[l] * pw2[r - l] % P2 + P2) % P2;
    return {x, y};
  }
};
