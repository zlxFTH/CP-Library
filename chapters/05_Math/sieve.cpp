vector<int> pr;
int mn[N], phi[N], mu[N];
void sieve(int n) {
  phi[1] = mu[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!mn[i]) pr.pb(i), mn[i] = i, phi[i] = i - 1, mu[i] = -1;
    for (int p : pr) {
      if (p > n / i) break;
      int x = i * p; mn[x] = p;
      if (i % p == 0) { phi[x] = phi[i] * p; break; }
      phi[x] = phi[i] * (p - 1), mu[x] = -mu[i];
    }
  }
}
