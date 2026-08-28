template <class T>
vector<pair<int, int>> Duval(const T& s) {
  int n = s.size(), i = 0;
  vector<pair<int, int>> a;
  while (i < n) {
    int j = i, k = i + 1;
    while (k < n && s[j] <= s[k]) {
      if (s[j] < s[k]) j = i;
      else j++;
      k++;
    }
    while (i <= j) {
      int r = i + k - j;
      a.push_back({i, r});
      i = r;
    }
  }
  return a;
}
template <class T> int min_rep(const T& s) {
  int n = s.size(), i = 0, j = 1, k = 0;
  if (!n) return 0;
  while (i < n && j < n && k < n) {
    if (s[(i + k) % n] == s[(j + k) % n]) k++;
    else {
      if (s[(i + k) % n] > s[(j + k) % n]) i += k + 1;
      else j += k + 1;
      if (i == j) j++;
      k = 0;
    }
  }
  return min(i, j);
}
