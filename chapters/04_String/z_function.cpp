vector<int> ZFunc(string s) {
  int n = SZ(s), l = 0, r = 0;
  vector<int> z(n);
  if (n) z[0] = n;
  for (int i = 1; i < n; i++) {
    if (i <= r) z[i] = min(z[i - l], r - i + 1);
    while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
    if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
  }
  return z;
}
vector<int> exKMP(string s, string t, vector<int> z) {
  int n = SZ(s), m = SZ(t), l = 0, r = -1;
  vector<int> p(n);
  for (int i = 0; i < n; i++) {
    if (i <= r) p[i] = min(z[i - l], r - i + 1);
    while (i + p[i] < n && p[i] < m && s[i + p[i]] == t[p[i]]) p[i]++;
    if (i + p[i] - 1 > r) l = i, r = i + p[i] - 1;
  }
  return p;
}
