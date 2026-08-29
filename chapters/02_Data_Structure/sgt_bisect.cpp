#define ls (p << 1)
#define rs (p << 1 | 1)
template <class G>
int max_right(int ql, G& g, V& x, int p, int l, int r) {
  if (r <= ql) return r;
  if (ql <= l) {
    V y = merge(x, t[p]);
    if (g(y)) {
      x = y;
      return r;
    }
    if (r - l == 1) return l;
  }
  down(p, l, r);
  int m = (l + r) / 2;
  int q = max_right(ql, g, x, ls, l, m);
  if (q < m) return q;
  return max_right(ql, g, x, rs, m, r);
}
template <class G> int max_right(int l, G g) {
  V x{};
  return max_right(l, g, x, 1, 0, n);
}
template <class G>
int min_left(int qr, G& g, V& x, int p, int l, int r) {
  if (qr <= l) return l;
  if (r <= qr) {
    V y = merge(t[p], x);
    if (g(y)) {
      x = y;
      return l;
    }
    if (r - l == 1) return r;
  }
  down(p, l, r);
  int m = (l + r) / 2;
  int q = min_left(qr, g, x, rs, m, r);
  if (q > m) return q;
  return min_left(qr, g, x, ls, l, m);
}
template <class G> int min_left(int r, G g) {
  V x{};
  return min_left(r, g, x, 1, 0, n);
}
#undef ls
#undef rs
