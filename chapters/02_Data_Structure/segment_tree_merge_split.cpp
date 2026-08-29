int merge(int p, int q, int l = 0, int r = -1) {
  if (r < 0) r = n;
  if (!p || !q) return p | q;
  if (r - l == 1) {
    t[p].v = merge(t[p].v, t[q].v);
    return p;
  }
  int m = (l + r) / 2;
  ls(p) = merge(ls(p), ls(q), l, m);
  rs(p) = merge(rs(p), rs(q), m, r);
  up(p);
  return p;
}
pair<int, int> split(int ql, int qr, int p, int l = 0, int r = -1) {
  if (r < 0) r = n;
  if (!p || qr <= l || r <= ql) return {p, 0};
  if (ql <= l && r <= qr) return {0, p};
  int m = (l + r) / 2;
  int al = ls(p), ar = rs(p), bl = 0, br = 0;
  if (ql < m) tie(al, bl) = split(ql, qr, al, l, m);
  if (m < qr) tie(ar, br) = split(ql, qr, ar, m, r);
  ls(p) = al, rs(p) = ar;
  if (al || ar) up(p);
  else p = 0;
  if (!bl && !br) return {p, 0};
  int q = node();
  ls(q) = bl, rs(q) = br;
  up(q);
  return {p, q};
}
