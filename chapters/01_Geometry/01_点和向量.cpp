using db = long double;

struct p2 {
    db x, y;
    p2 operator+(p2 p) const { return {x + p.x, y + p.y}; }
    p2 operator-(p2 p) const { return {x - p.x, y - p.y}; }
    p2 operator*(db k) const { return {x * k, y * k}; }
    p2 operator/(db k) const { return {x / k, y / k}; }
};

db operator*(p2 a, p2 b) { return a.x * b.y - a.y * b.x; } // 叉积
db operator%(p2 a, p2 b) { return a.x * b.x + a.y * b.y; } // 点积
