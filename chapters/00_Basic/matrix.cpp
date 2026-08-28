template <class T>
struct Mat {
  int n, m;
  vector<T> a;
  Mat(int n = 0, int m = 0, T v = {}) : n(n), m(m), a(n * m, v) {}
  T& operator()(int i, int j) { return a[i * m + j]; }
};

using M = Mat<LL>;
M mul(M a, M b) {
  M c(a.n, b.m);
  for (int i = 0; i < a.n; i++) {
    for (int j = 0; j < b.m; j++) {
      for (int k = 0; k < a.m; k++) {
        c(i, j) = max(c(i, j), a(i, k) + b(k, j));
      }
    }
  }
  return c;
}
