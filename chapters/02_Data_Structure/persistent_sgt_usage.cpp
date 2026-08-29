SGT seg{n};
vector<int> rt(q + 1);
rt[i] = seg.mdf(x, v, rt[k]);
auto ans = seg.qry(l, r, rt[i]);
