Mo mo;
for (int i = 0; i < q; i++) {
  int l, r;
  cin >> l >> r;
  mo.ask(l, r);
}
mo.solve(n);
mo = {}; // 多测清空
