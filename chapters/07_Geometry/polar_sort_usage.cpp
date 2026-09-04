sort(ALL(v), cmp);
for (int l = 0, r; l < SZ(v); l = r) {
  for (r = l + 1; r < SZ(v) && cmp_eq(v[l], v[r]); ++r);
  // [l, r) 内向量同向
}
int order = cmp_ct(a, b, c); // 1: 逆时针，0: 否，-1: 同向退化
