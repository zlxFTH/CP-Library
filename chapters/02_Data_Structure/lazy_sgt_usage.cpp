struct S {
  LL sum;
  int len;
};
S op(S a, S b) { return {a.sum + b.sum, a.len + b.len}; }
S e() { return {0, 0}; }
using F = LL;
S FS(F f, S x) { return {x.sum + f * x.len, x.len}; }
F FF(F f, F g) { return f + g; }
F id() { return 0; }
using Seg = LazySGT<S, op, e, F, FS, FF, id>;
vector<S> a(n, {0, 1});
Seg seg(a);
seg.apply(l, r, x);
LL ans = seg.prod(l, r).sum;
