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
// 绕原点逆时针旋转 p 弧度，负角为顺时针
p2 rot(p2 a, db p) { return a * cos(p) + p2{-a.y, a.x} * sin(p); }
// 非零向量 a->b 的有向角 [-pi,pi]，逆时针为正，绝对值为无向角
db arg(p2 a, p2 b) { return atan2(a % b, a * b); }
// 非零向量：1 同向，-1 反向，0 不平行
int dir(p2 a, p2 b) { return sgn(a % b) ? 0 : sgn(a * b); }
