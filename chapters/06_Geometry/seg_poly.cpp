// pa 到 pb 的叉积，p 在 a->b 左侧为正
db side(p2 p, p2 a, p2 b) { return (a - p) % (b - p); }
bool onL(p2 p, p2 a, p2 b) { return !sgn(side(p, a, b)); }
bool onS(p2 p, p2 a, p2 b) {
  return onL(p, a, b) && sgn((p - a) * (p - b)) <= 0;
}
// 直线要求 a != b
db toL(p2 p, p2 a, p2 b) { return abs(side(p, a, b)) / (b - a).len(); }
p2 foot(p2 p, p2 a, p2 b) {
  p2 v = b - a;
  return a + v * ((p - a) * v / (v * v));
}
db toS(p2 p, p2 a, p2 b) {
  p2 x = p - a, y = p - b, v = b - a;
  if (x * v <= 0) return x.len();
  if (y * v >= 0) return y.len();
  return toL(p, a, b);
}
// 两直线交点，要求不平行
p2 inter(p2 a, p2 b, p2 c, p2 d) {
  p2 x = b - a, y = d - c;
  return a + x * (((c - a) % y) / (x % y));
}
struct L {
  p2 p, v;
  L(p2 a, p2 b) : p(a), v(b - a) {}
  bool out(p2 a) { return sgn(v % (a - p)) < 0; }
};
p2 inter(L a, L b) { return inter(a.p, a.p + a.v, b.p, b.p + b.v); }
