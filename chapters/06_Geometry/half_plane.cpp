struct L {
  p2 p, v;
  L(p2 a, p2 b) : p(a), v(b - a) {}
};
bool out(L a, p2 p) { return sgn(a.v % (p - a.p)) < 0; }
p2 inter(L a, L b) {
  return a.p + a.v * (((b.p - a.p) % b.v) / (a.v % b.v));
}
int hhalf(p2 a) { return a.y < -eps || (abs(a.y) < eps && a.x < 0); }
ps hpi(vector<L> a) {
  sort(ALL(a), [](L a, L b) {
    int A = hhalf(a.v), B = hhalf(b.v);
    if (A != B) return A < B;
    db z = a.v % b.v;
    return z ? z > 0 : a.v % (b.p - a.p) < 0;
  });
  vector<L> b;
  for (L l : a) {
    if (b.empty() || sgn(b.back().v % l.v)) b.pb(l);
    else if (out(l, b.back().p)) b.back() = l;
  }
  deque<L> q;
  for (L l : b) {
    while (SZ(q) > 1 && out(l, inter(q[SZ(q) - 2], q.back()))) q.pop_back();
    while (SZ(q) > 1 && out(l, inter(q[0], q[1]))) q.pop_front();
    q.pb(l);
  }
  while (SZ(q) > 2 && out(q[0], inter(q[SZ(q) - 2], q.back()))) q.pop_back();
  while (SZ(q) > 2 && out(q.back(), inter(q[0], q[1]))) q.pop_front();
  if (SZ(q) < 3) return {};
  ps p;
  for (int i = 0; i < SZ(q); i++) p.pb(inter(q[i], q[(i + 1) % SZ(q)]));
  db s = 0;
  for (int i = 1; i + 1 < SZ(p); i++) s += (p[i] - p[0]) % (p[i + 1] - p[0]);
  return sgn(s) > 0 ? p : ps{};
}
