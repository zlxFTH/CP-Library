int half(p2 a) { return a.y < 0 || (a.y == 0 && a.x <= 0); } // 精确版
// int half(p2 a) { return a.y < -eps || (fabs(a.y) < eps && a.x < eps); } // eps 版
bool cmp(p2 a, p2 b) { return half(a) == half(b) ? a % b > 0 : half(b); }
bool cmp_eq(p2 a, p2 b) { return half(a) == half(b) && !sgn(a % b); }
int cmp_ct(p2 a, p2 b, p2 c) {
  if (cmp_eq(a, b) || cmp_eq(c, b)) return -1;
  return cmp(a, b) ? cmp(b, c) || cmp(c, a) : cmp(b, c) && cmp(c, a);
}
