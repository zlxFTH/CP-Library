vector<int> Manacher(const string& s) {
  string t = "#";
  for (char c : s) t += c, t += '#';
  int n = t.size();
  vector<int> p(n);
  for (int i = 0, l = 0, r = 0; i < n; i++) {
    p[i] = i < r ? min(p[2 * l - i], r - i) : 0;
    while (i + p[i] < n && i - p[i] >= 0
        && t[i + p[i]] == t[i - p[i]]) p[i]++;
    if (i + p[i] > r) l = i, r = i + p[i];
  }
  return p;
}
