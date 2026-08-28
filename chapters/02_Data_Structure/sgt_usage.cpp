struct S {
  LL mx = -INF;
};
S operator+(S a, S b) {
  return {max(a.mx, b.mx)};
}
