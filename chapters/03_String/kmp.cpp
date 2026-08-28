template <class T> vector<int> kmp(const T& s) {
  int n = s.size();
  vector<int> f(n + 1);
  for (int i = 1, j = 0; i < n; i++) {
    while (j && s[i] != s[j]) j = f[j];
    if (s[i] == s[j]) j++;
    f[i + 1] = j;
  }
  return f;
}
