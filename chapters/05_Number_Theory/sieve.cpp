struct Sieve {
  int n;
  vector<int> pr, minp, phi, mu;
  Sieve(int n_) : n(n_), minp(n + 1), phi(n + 1), mu(n + 1) {
    assert(n >= 1);
    phi[1] = mu[1] = 1;
    for (int i = 2; i <= n; i++) {
      if (!minp[i]) {
        pr.push_back(i);
        minp[i] = i;
        phi[i] = i - 1;
        mu[i] = -1;
      }
      for (int p : pr) {
        if (LL(i) * p > n) break;
        minp[i * p] = p;
        if (i % p == 0) {
          phi[i * p] = phi[i] * p;
          break;
        }
        phi[i * p] = phi[i] * (p - 1);
        mu[i * p] = -mu[i];
      }
    }
  }
  vector<pair<int, int>> factor(int x) const {
    assert(1 <= x && x <= n);
    vector<pair<int, int>> f;
    while (x > 1) {
      int p = minp[x], c = 0;
      do x /= p, c++;
      while (x > 1 && minp[x] == p);
      f.push_back({p, c});
    }
    return f;
  }
};
