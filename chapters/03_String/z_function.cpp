template <class T> vector<int> ZFunc(const T& s) {
  int n = s.size(), l = 0, r = 0;
  vector<int> z(n);
  if (!n) return z;
  z[0] = n;
  for (int i = 1; i < n; i++) {
    if (i <= r && z[i - l] < r - i + 1) z[i] = z[i - l];
    else {
      z[i] = max(0, r - i + 1);
      while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
      if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
  }
  return z;
}
template <class T>
vector<int> exKMP(const T& s, const T& t, const vector<int>& z) {
  int n = s.size(), m = t.size(), l = 0, r = 0;
  vector<int> p(n);
  if (!n) return p;
  while (p[0] < n && p[0] < m && s[p[0]] == t[p[0]]) p[0]++;
  for (int i = 1; i < n; i++) {
    if (i <= r && z[i - l] < r - i + 1) p[i] = z[i - l];
    else {
      p[i] = max(0, r - i + 1);
      while (i + p[i] < n && p[i] < m && s[i + p[i]] == t[p[i]]) p[i]++;
      if (i + p[i] - 1 > r) l = i, r = i + p[i] - 1;
    }
  }
  return p;
}
