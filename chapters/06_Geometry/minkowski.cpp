void norm(ps &a) {
  int k = 0;
  for (int i = 1; i < SZ(a); i++)
    if (pair(a[i].y, a[i].x) < pair(a[k].y, a[k].x)) k = i;
  rotate(a.begin(), a.begin() + k, a.end());
}
ps minkowski(ps a, ps b) {
  norm(a), norm(b);
  int n = SZ(a), m = SZ(b), i = 0, j = 0;
  a.pb(a[0]), b.pb(b[0]);
  ps c{a[0] + b[0]};
  while (i < n || j < m) {
    p2 x = i < n ? a[i + 1] - a[i] : p2{};
    p2 y = j < m ? b[j + 1] - b[j] : p2{};
    int z = i == n ? -1 : j == m ? 1 : sgn(x % y);
    p2 v{};
    if (z >= 0) i++, v = v + x;
    if (z <= 0) j++, v = v + y;
    c.pb(c.back() + v);
  }
  c.pop_back();
  return c;
}
