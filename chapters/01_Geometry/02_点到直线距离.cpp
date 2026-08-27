// 点到直线距离
db toL(p2 p, p2 a, p2 b) { return abs((b - a) % (p - a)) / (b - a).len(); }
