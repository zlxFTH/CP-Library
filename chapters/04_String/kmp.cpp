vector<int> kmp(string s) {
  int n = SZ(s);
  vector<int> f(n + 1);
  for (int i = 1, j = 0; i < n; i++) {
    while (j && s[i] != s[j]) j = f[j];
    if (s[i] == s[j]) j++;
    f[i + 1] = j;
  }
  return f;
}
