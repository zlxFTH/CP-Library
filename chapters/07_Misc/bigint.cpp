struct BI {
  vector<int> a;
  BI(LL x = 0) { do a.pb(x % 10); while (x /= 10); }
  BI(string s) { for (int i = SZ(s); i--;) a.pb(s[i] - '0'); trim(); }
  BI& trim() { while (SZ(a) > 1 && !a.back()) a.pop_back(); return *this; }
  friend istream& operator>>(istream& in, BI& x) {
    string s; if (in >> s) x = BI(s); return in;
  }
  friend ostream& operator<<(ostream& out, BI x) {
    for (int i = SZ(x.a); i--;) out << x.a[i];
    return out;
  }
  int cmp(BI b) const {
    if (SZ(a) != SZ(b.a)) return SZ(a) < SZ(b.a) ? -1 : 1;
    for (int i = SZ(a); i--;)
      if (a[i] != b.a[i]) return a[i] < b.a[i] ? -1 : 1;
    return 0;
  }
  bool operator<(BI b) const { return cmp(b) < 0; }
  bool operator>(BI b) const { return cmp(b) > 0; }
  bool operator<=(BI b) const { return cmp(b) <= 0; }
  bool operator>=(BI b) const { return cmp(b) >= 0; }
  bool operator==(BI b) const { return cmp(b) == 0; }
  bool operator!=(BI b) const { return cmp(b) != 0; }
  BI add(BI b, int k = 1) const {
    BI c = *this; c.a.resize(max(SZ(a), SZ(b.a)) + 1);
    for (int i = 0, t = 0; i < SZ(c.a); i++) {
      t += c.a[i] + (i < SZ(b.a) ? k * b.a[i] : 0);
      c.a[i] = (t + 10) % 10, t = (t - c.a[i]) / 10;
    }
    return c.trim();
  }
  BI operator+(BI b) const { return add(b); }
  BI operator-(BI b) const { return add(b, -1); }
  BI operator*(BI b) const {
    BI c; c.a.assign(SZ(a) + SZ(b.a), 0);
    for (int i = 0; i < SZ(a); i++)
      for (int j = 0, t = 0; j < SZ(b.a) || t; j++) {
        t += c.a[i + j] + (j < SZ(b.a) ? a[i] * b.a[j] : 0);
        c.a[i + j] = t % 10, t /= 10;
      }
    return c.trim();
  }
  pair<BI, LL> div(LL b) const {
    BI c = *this; I r = 0;
    for (int i = SZ(a); i--;) {
      r = r * 10 + a[i], c.a[i] = r / b, r %= b;
    }
    return {c.trim(), (LL)r};
  }
  BI operator/(LL b) const { return div(b).first; }
  LL operator%(LL b) const { return div(b).second; }
};
