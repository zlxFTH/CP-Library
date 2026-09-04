using db = long double;
const db eps = 1e-10;
int sgn(db x) { return x < -eps ? -1 : x > eps; }
bool eq(db x, db y) { return !sgn(x - y); }
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
db arg(p2 a, p2 b) { return atan2(a % b, a * b); }
int dir(p2 a, p2 b) { return sgn(a % b) ? 0 : sgn(a * b); }
