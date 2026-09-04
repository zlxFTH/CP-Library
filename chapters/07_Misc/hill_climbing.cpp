// 求最小值；near(x, d) 枚举步长 d 下的邻居。
auto climb = [&](auto x, double d) {
  double v = calc(x);
  for (; d > 1e-9; d *= .5) while (1) {
    auto bx = x;
    double bv = v;
    for (auto y : near(x, d)) {
      double w = calc(y);
      if (w < bv) bx = y, bv = w;
    }
    if (bv == v) break;
    x = bx, v = bv;
  }
  return pair{x, v};
};
