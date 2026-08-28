// pa 到 pb 的叉积，逆时针转为正
db side(p2 p, p2 a, p2 b) { return (a - p) % (b - p); }
db toL(p2 p, p2 a, p2 b) { return abs(side(p, a, b)) / (b - a).len(); }
