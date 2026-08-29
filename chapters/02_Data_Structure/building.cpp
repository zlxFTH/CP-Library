#define ls (p << 1)
#define rs (p << 1 | 1)
struct SGT {
  struct K {
    LL y = 0, x = 1;
    bool operator<=(K b) {
      return (I)y * b.x <= (I)b.y * x;
    }
  };
  struct V {
    K mx;
    int cnt = 0;
  };
  int n;
  V t[N << 2];
  int calc(int p, K k, int l, int r) {
    if (t[p].mx <= k) return 0;
    if (r - l == 1) return 1;
    int m = (l + r) / 2;
    if (t[ls].mx <= k) return calc(rs, k, m, r);
    return calc(ls, k, l, m) + t[p].cnt - t[ls].cnt;
  }
  void up(int p, int l, int r) {
    int m = (l + r) / 2;
    t[p].mx = t[ls].mx <= t[rs].mx ? t[rs].mx : t[ls].mx;
    t[p].cnt = t[ls].cnt + calc(rs, t[ls].mx, m, r);
  }
  void mdf(int x, K k, int p = 1, int l = 0, int r = -1) {
    if (r < 0) r = n;
    if (r - l == 1) {
      t[p] = {k, 1};
      return;
    }
    int m = (l + r) / 2;
    if (x < m) mdf(x, k, ls, l, m);
    else mdf(x, k, rs, m, r);
    up(p, l, r);
  }
};
#undef ls
#undef rs
