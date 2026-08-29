SGT seg;
memset(&seg, 0, sizeof seg);
seg.build(a);
seg.mdf(l, r, x);
auto ans = seg.qry(l, r);
