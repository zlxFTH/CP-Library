vector<int> xs = a;
sort(ALL(xs));
xs.erase(unique(ALL(xs)), xs.end());
Chairman seg(SZ(xs));
for (int x : a) {
  seg.add(lower_bound(ALL(xs), x) - xs.begin());
}
int p = seg.kth(l, r, k);
int ans = xs[p];
