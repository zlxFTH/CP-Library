SGT seg;
fill(begin(seg.lz), end(seg.lz), SGT::L{});
seg.build(a);
seg.mdf(l, r, x);
auto ans = seg.qry(l, r);
