// O(n log n)，逆时针，不重复首点，不保留边上共线中间点
ps hull(ps a) {
  sort(ALL(a), [](p2 a, p2 b) { return pair(a.x, a.y) < pair(b.x, b.y); });
  a.erase(unique(ALL(a), [](p2 a, p2 b) {
    return a.x == b.x && a.y == b.y;
  }), a.end());
  int n = SZ(a), k = 0;
  if (n <= 1) return a;
  ps b(2 * n);
  for (int i = 0; i < n; b[k++] = a[i++])
    while (k > 1 && sgn(side(a[i], b[k - 2], b[k - 1])) <= 0) --k;
  for (int i = n - 2, t = k; i >= 0; b[k++] = a[i--])
    while (k > t && sgn(side(a[i], b[k - 2], b[k - 1])) <= 0) --k;
  b.resize(k - 1);
  return b;
}
