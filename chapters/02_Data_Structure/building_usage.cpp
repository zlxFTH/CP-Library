SGT seg;
seg = {n};
while (m--) {
  int x;
  LL y;
  cin >> x >> y;
  --x;
  seg.mdf(x, {y, x + 1});
  cout << seg.t[1].cnt << '\n';
}
