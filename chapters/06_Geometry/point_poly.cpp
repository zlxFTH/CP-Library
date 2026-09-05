// 逆时针旋转 90 度
p2 r90(p2 a) { return {-a.y, a.x}; }
// 关于直线 ab 对称，a != b
p2 refl(p2 p, p2 a, p2 b) { return foot(p, a, b) * 2 - p; }
// 过 p 作 l 的平行线 / 垂线
L para(L l, p2 p) { return {p, p + l.v}; }
L perp(L l, p2 p) { return {p, p + r90(l.v)}; }
bool is_para(L a, L b) { return !sgn(a.v % b.v); }
bool is_perp(L a, L b) { return !sgn(a.v * b.v); }
// 线段相交，含端点、重合及零长线段
bool isSS(p2 a, p2 b, p2 c, p2 d) {
  if (onS(a, c, d) || onS(b, c, d) || onS(c, a, b) || onS(d, a, b)) return 1;
  return sgn(side(a, c, d)) * sgn(side(b, c, d)) < 0 &&
         sgn(side(c, a, b)) * sgn(side(d, a, b)) < 0;
}
// 两线段距离
db toS(p2 a, p2 b, p2 c, p2 d) {
  return isSS(a, b, c, d) ? 0 :
    min({toS(a, c, d), toS(b, c, d), toS(c, a, b), toS(d, a, b)});
}
// 多边形均不重复首点；有向面积，逆时针为正
db area(ps &a) {
  db s = 0;
  for (int i = 1; i + 1 < SZ(a); i++) s += side(a[0], a[i], a[i + 1]);
  return s / 2;
}
// 简单多边形是否凸，strict=0 允许边上共线点
bool convex(ps &a, bool strict = 1) {
  int n = SZ(a), z = 0;
  if (n < 3) return 0;
  for (int i = 0; i < n; i++) {
    int s = sgn(side(a[i], a[(i + 1) % n], a[(i + 2) % n]));
    if ((!s && strict) || (s && z && s != z)) return 0;
    if (s) z = s;
  }
  return z != 0;
}
// O(n)，简单多边形：0 外部，1 内部，2 边界
int inPoly(ps &a, p2 p) {
  bool in = 0;
  for (int i = 0; i < SZ(a); i++) {
    p2 x = a[i], y = a[(i + 1) % SZ(a)];
    if (onS(p, x, y)) return 2;
    if (x.y > y.y) swap(x, y);
    if (sgn(x.y - p.y) <= 0 && sgn(y.y - p.y) > 0 &&
        sgn(side(p, x, y)) > 0) in ^= 1;
  }
  return in;
}
// O(log n)，逆时针凸包，无共线中间点；返回值同上
int inConvex(ps &a, p2 p) {
  int n = SZ(a), l = 1, r = n - 1;
  if (n < 3) return inPoly(a, p);
  if (sgn(side(p, a[0], a[1])) < 0 || sgn(side(p, a[0], a.back())) > 0) return 0;
  if (onS(p, a[0], a[1]) || onS(p, a[0], a.back())) return 2;
  while (l + 1 < r) {
    int m = (l + r) / 2;
    if (sgn(side(p, a[0], a[m])) >= 0) l = m;
    else r = m;
  }
  int z = sgn(side(p, a[l], a[r]));
  return z < 0 ? 0 : z ? 1 : 2;
}
// O(n)，凸多边形保留有向直线 l 的左侧（含边界）
ps cut(ps &a, L l) {
  ps b;
  for (int i = 0; i < SZ(a); i++) {
    p2 x = a[i], y = a[(i + 1) % SZ(a)];
    int u = sgn(l.v % (x - l.p)), v = sgn(l.v % (y - l.p));
    if (u >= 0) b.pb(x);
    if (u * v < 0) b.pb(inter(L(x, y), l));
  }
  return b;
}
// O(n)，逆时针凸包直径
db diameter(ps &a) {
  int n = SZ(a);
  if (n < 2) return 0;
  db ans = 0;
  for (int i = 0, j = 1; i < n; i++) {
    p2 x = a[i], y = a[(i + 1) % n];
    while (side(a[(j + 1) % n], x, y) > side(a[j], x, y)) j = (j + 1) % n;
    ans = max({ans, (a[j] - x).len(), (a[j] - y).len()});
  }
  return ans;
}
// O(n log n)，最近点对距离；不足两个点返回 inf
db mindist(ps a) {
  db ans = numeric_limits<db>::infinity();
  sort(ALL(a), [](p2 a, p2 b) { return a.x < b.x; });
  ps b = a;
  auto dfs = [&](auto &&dfs, int l, int r) -> void {
    if (r - l < 2) return;
    int m = (l + r) / 2;
    db x = a[m].x;
    dfs(dfs, l, m), dfs(dfs, m, r);
    merge(a.begin() + l, a.begin() + m, a.begin() + m, a.begin() + r,
          b.begin() + l, [](p2 a, p2 b) { return a.y < b.y; });
    copy(b.begin() + l, b.begin() + r, a.begin() + l);
    int k = 0;
    for (int i = l; i < r; i++) if (abs(a[i].x - x) < ans) {
      for (int j = k - 1; j >= 0 && a[i].y - b[j].y < ans; j--)
        ans = min(ans, (a[i] - b[j]).len());
      b[k++] = a[i];
    }
  };
  dfs(dfs, 0, SZ(a));
  return ans;
}
