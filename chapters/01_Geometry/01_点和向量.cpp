using db = long double;
struct p2 {
  db x, y;
  db abs() { return hypot(x, y); }
  p2 operator+(p2 b) { return {x + b.x, y + b.y}; }
  p2 operator-(p2 b) { return {x - b.x, y - b.y}; }
  p2 operator*(db k) { return {x * k, y * k}; }
  p2 operator/(db k) { return {x / k, y / k}; }
  db operator*(p2 b) { return x * b.x + y * b.y; } // 点积
  db operator%(p2 b) { return x * b.y - y * b.x; } // 叉积
};
using ps = vector<p2>;
