const db pi = acos(-1.L);
struct C { p2 p; db r; };
// 点在圆内 / 圆上 / 圆外：-1 / 0 / 1
int side(C c, p2 p) { return sgn((p - c.p).len() - c.r); }
// 圆与直线交点，按 l.v 方向排序；相切返回一个点，l.v != 0
ps inter(C c, L l) {
  p2 p = foot(c.p, l.p, l.p + l.v);
  db d = (p - c.p).len();
  if (sgn(d - c.r) > 0) return {};
  if (!sgn(d - c.r)) return {p};
  p2 v = l.v * (sqrt(max(db(0), c.r * c.r - d * d)) / l.v.len());
  return {p - v, p + v};
}
// 圆与线段交点，按 a->b 排序
ps interS(C c, p2 a, p2 b) {
  if (!sgn((a - b).len())) return !side(c, a) ? ps{a} : ps{};
  ps v;
  for (p2 p : inter(c, L(a, b)))
    if (sgn((p - a) * (p - b)) <= 0) v.pb(p);
  return v;
}
// 两圆交点；同心返回空，重合圆需单独判断
ps inter(C a, C b) {
  p2 v = b.p - a.p;
  db d = v.len();
  if (!sgn(d)) return {};
  p2 p = a.p + v * ((d * d + a.r * a.r - b.r * b.r) / (2 * d * d));
  return inter(a, L(p, p + r90(v)));
}
// 点到圆的切点：圆外两个，圆上一个，圆内无解
ps tang(C c, p2 p) {
  int z = side(c, p);
  if (z < 0) return {};
  if (!z) return {p};
  p2 v = p - c.p, q = c.p + v * (c.r * c.r / (v * v));
  return inter(c, L(q, q + r90(v)));
}
// 以 ab 为直径的圆
C cir(p2 a, p2 b) { return {(a + b) / 2, (a - b).len() / 2}; }
// 三角形外接圆，三点不共线
C circum(p2 a, p2 b, p2 c) {
  p2 u = b - a, v = c - a;
  p2 p = a + r90(u * (v * v) - v * (u * u)) / (2 * (u % v));
  return {p, (a - p).len()};
}
// 三角形内切圆，三点不共线
C incircle(p2 a, p2 b, p2 c) {
  db x = (b - c).len(), y = (c - a).len(), z = (a - b).len();
  return {(a * x + b * y + c * z) / (x + y + z), abs(side(a, b, c)) / (x + y + z)};
}
// 最小圆覆盖，期望 O(n)，复用 Basic 的 rnd；空集返回半径 0
C mincircle(ps a) {
  if (a.empty()) return {{}, 0};
  shuffle(ALL(a), rnd);
  C c{a[0], 0};
  for (int i = 1; i < SZ(a); i++) if (side(c, a[i]) > 0) {
    c = {a[i], 0};
    for (int j = 0; j < i; j++) if (side(c, a[j]) > 0) {
      c = cir(a[i], a[j]);
      for (int k = 0; k < j; k++) if (side(c, a[k]) > 0)
        c = circum(a[i], a[j], a[k]);
    }
  }
  return c;
}
// 两圆交面积
db area(C a, C b) {
  if (a.r > b.r) swap(a, b);
  db d = (a.p - b.p).len();
  if (d >= a.r + b.r) return 0;
  if (d <= b.r - a.r) return pi * a.r * a.r;
  auto f = [&](C a, C b) {
    db t = acos(clamp((d * d + a.r * a.r - b.r * b.r) / (2 * d * a.r), -1.L, 1.L));
    return a.r * a.r * (t - sin(2 * t) / 2);
  };
  return f(a, b) + f(b, a);
}
// 三角形 (圆心,a,b) 与圆交的有向面积
db area(C c, p2 a, p2 b) {
  a = a - c.p, b = b - c.p, c.p = {};
  bool x = side(c, a) <= 0, y = side(c, b) <= 0;
  if (x && y) return (a % b) / 2;
  ps v = interS(c, a, b);
  db r = c.r * c.r;
  if (v.empty()) return arg(a, b) * r / 2;
  db s = x ? a % v[0] : arg(a, v[0]) * r;
  s += y ? v.back() % b : arg(v.back(), b) * r;
  if (SZ(v) > 1) s += v[0] % v[1];
  return s / 2;
}
// 圆与简单多边形交面积，O(n)
db area(C c, ps &a) {
  db s = 0;
  for (int i = 0; i < SZ(a); i++) s += area(c, a[i], a[(i + 1) % SZ(a)]);
  return abs(s);
}
