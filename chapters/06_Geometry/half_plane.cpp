ps hpi(vector<L> a) {
  sort(ALL(a), [](L a, L b) { return cmp(a.v, b.v); });
  auto q = a;
  int h = 0, t = 0;
  for (L l : a) {
    while (t - h > 1 && l.out(inter(q[t - 2], q[t - 1]))) --t;
    while (t - h > 1 && l.out(inter(q[h], q[h + 1]))) ++h;
    if (t > h && !sgn(q[t - 1].v % l.v)) {
      if (q[t - 1].v * l.v < 0) return {};
      if (!l.out(q[t - 1].p)) continue;
      --t;
    }
    q[t++] = l;
  }
  while (t - h > 2 && q[h].out(inter(q[t - 2], q[t - 1]))) --t;
  if (t - h < 3 || sgn(q[t - 1].v % q[h].v) <= 0) return {};
  ps p;
  for (int i = h; i < t; i++) p.pb(inter(q[i], q[i + 1 < t ? i + 1 : h]));
  db s = 0;
  for (int i = 1; i + 1 < SZ(p); i++) s += side(p[0], p[i], p[i + 1]);
  return sgn(s) > 0 ? p : ps{};
}
