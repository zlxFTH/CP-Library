LL det(vector<vector<LL>> a) {
  int n = SZ(a); LL ans = 1;
  for (int i = 0; i < n; i++) {
    int p = i;
    while (p < n && !a[p][i]) p++;
    if (p == n) return 0;
    if (p != i) swap(a[p], a[i]), ans = P - ans;
    ans = Mul(ans, a[i][i]);
    LL iv = qp(a[i][i]);
    for (int j = i + 1; j < n; j++) {
      LL w = Mul(a[j][i], iv);
      for (int k = i; k < n; k++) {
        LL v = Mul(w, a[i][k]);
        a[j][k] = a[j][k] >= v ? a[j][k] - v : a[j][k] - v + P;
      }
    }
  }
  return ans;
}
