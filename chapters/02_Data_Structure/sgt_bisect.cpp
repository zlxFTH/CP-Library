int find_l(int ql, int qr, int p = 1, int l = 0, int r = -1) {
  if (r < 0) r = n;
  if (r <= ql || qr <= l) return -1;
  if () return -1;
  if (r - l == 1) return l;
  down(p, l, r);
  int m = (l + r) / 2;
  int q = find_l(ql, qr, ls, l, m);
  return q < 0 ? find_l(ql, qr, rs, m, r) : q;
}
int find_r(int ql, int qr, int p = 1, int l = 0, int r = -1) {
  if (r < 0) r = n;
  if (r <= ql || qr <= l) return -1;
  if () return -1;
  if (r - l == 1) return l;
  down(p, l, r);
  int m = (l + r) / 2;
  int q = find_r(ql, qr, rs, m, r);
  return q < 0 ? find_r(ql, qr, ls, l, m) : q;
}
