// 求最小值；nxt(x, T) 随机生成温度 T 下的邻居。
auto SA = [&](auto x, double T) {
  auto bx = x;
  double v = calc(x), bv = v;
  for (; T > 1e-9; T *= .995) {
    auto y = nxt(x, T);
    double w = calc(y), d = w - v;
    if (d < 0 || double(rnd()) / rnd.max() < exp(-d / T)) x = y, v = w;
    if (v < bv) bx = x, bv = v;
  }
  return pair{bx, bv};
};
