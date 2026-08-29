int fnd_left(int ql, int qr, int p = 1, int l = 0, int r = -1) {
  if (r < 0) r = n;
  if (r <= ql || qr < l) return -1;
  if () return -1;
  if (r - l == 1) return l;
  down(p, l, r);
  int m = (l + r) / 2;
  int q = fnd_left(ql, qr, ls, l, m);
  return q < 0 ? fnd_left(ql, qr, rs, m, r) : q;
}
int fnd_right(int ql, int qr, int p = 1, int l = 0, int r = -1) {
  if (r < 0) r = n;
  if (r <= ql || qr < l) return -1;
  if () return -1;
  if (r - l == 1) return l;
  down(p, l, r);
  int m = (l + r) / 2;
  int q = fnd_right(ql, qr, rs, m, r);
  return q < 0 ? fnd_right(ql, qr, ls, l, m) : q;
}
