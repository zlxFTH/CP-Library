constexpr int P = 998244353;
template <class T> T qp(T a, LL b) {
  assert(b >= 0);
  T r{1};
  for (; b; b >>= 1, a *= a) if (b & 1) r *= a;
  return r;
}
struct Mint {
  int v;
  Mint(LL x = 0) : v(int((x % P + P) % P)) {}
  int val() const { return v; }
  Mint operator-() const { return Mint(-v); }
  Mint& operator+=(const Mint& b) {
    if ((v += b.v) >= P) v -= P;
    return *this;
  }
  Mint& operator-=(const Mint& b) {
    if ((v -= b.v) < 0) v += P;
    return *this;
  }
  Mint& operator*=(const Mint& b) {
    v = int(LL(v) * b.v % P);
    return *this;
  }
  Mint& operator/=(const Mint& b) { return *this *= b.inv(); }
  friend Mint operator+(Mint a, const Mint& b) { return a += b; }
  friend Mint operator-(Mint a, const Mint& b) { return a -= b; }
  friend Mint operator*(Mint a, const Mint& b) { return a *= b; }
  friend Mint operator/(Mint a, const Mint& b) { return a /= b; }
  Mint inv() const {
    assert(v);
    return qp(*this, P - 2);
  }
  friend istream& operator>>(istream& is, Mint& a) {
    LL x;
    is >> x;
    return a = Mint(x), is;
  }
  friend ostream& operator<<(ostream& os, const Mint& a) {
    return os << a.v;
  }
};
using mint = Mint;
