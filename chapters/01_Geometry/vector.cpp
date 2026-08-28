using db = long double;
struct p2 {
  db x, y;
  db len() { return hypot(x, y); }
  p2 operator+(p2 b) { return {x + b.x, y + b.y}; }
  p2 operator-(p2 b) { return {x - b.x, y - b.y}; }
  p2 operator*(db k) { return {x * k, y * k}; }
  p2 operator/(db k) { return {x / k, y / k}; }
  db operator*(p2 b) { return x * b.x + y * b.y; }
  db operator%(p2 b) { return x * b.y - y * b.x; }
};
using ps = vector<p2>;
