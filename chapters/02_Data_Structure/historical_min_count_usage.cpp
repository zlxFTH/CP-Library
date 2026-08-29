SGT seg;
vector<SGT::V> b(n);
for (int i = 0; i < n; i++) b[i] = {a[i], 1, a[i], 1};
seg = {};
seg.build(b);
seg.mdf(l, r, {x, x, 1});
LL ans = seg.qry(l, r).chmn;
