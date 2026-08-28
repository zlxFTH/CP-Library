namespace Factor {
using U128 = __uint128_t;
ULL mul_mod(ULL a, ULL b, ULL m) {
  return ULL(U128(a) * b % m);
}
ULL add_mod(ULL a, ULL b, ULL m) {
  return ULL((U128(a) + b) % m);
}
ULL pow_mod(ULL a, ULL b, ULL m) {
  ULL r = 1 % m;
  for (; b; b >>= 1, a = mul_mod(a, a, m))
    if (b & 1) r = mul_mod(r, a, m);
  return r;
}
bool prime(ULL n) {
  if (n < 2) return false;
  for (ULL p : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL,
      19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {
    if (n % p == 0) return n == p;
  }
  int s = __builtin_ctzll(n - 1);
  ULL d = (n - 1) >> s;
  for (ULL a : {2ULL, 325ULL, 9375ULL, 28178ULL,
      450775ULL, 9780504ULL, 1795265022ULL}) {
    if (a % n == 0) continue;
    ULL x = pow_mod(a % n, d, n);
    if (x == 1 || x == n - 1) continue;
    bool ok = false;
    for (int r = 1; r < s; r++) {
      x = mul_mod(x, x, n);
      if (x == n - 1) {
        ok = true;
        break;
      }
    }
    if (!ok) return false;
  }
  return true;
}
ULL diff(ULL a, ULL b) { return a > b ? a - b : b - a; }
ULL rho(ULL n) {
  if (n % 2 == 0) return 2;
  if (n % 3 == 0) return 3;
  static mt19937_64 rng(chrono::steady_clock::now()
      .time_since_epoch().count());
  while (true) {
    ULL y = rng() % (n - 2) + 2;
    ULL c = rng() % (n - 1) + 1;
    auto f = [&](ULL x) { return add_mod(mul_mod(x, x, n), c, n); };
    ULL g = 1, x = 0, z = 0;
    for (ULL r = 1; g == 1; r <<= 1) {
      x = y;
      for (ULL i = 0; i < r; i++) y = f(y);
      for (ULL k = 0; k < r && g == 1; k += 128) {
        z = y;
        ULL q = 1;
        for (ULL i = 0; i < min<ULL>(128, r - k); i++) {
          y = f(y);
          q = mul_mod(q, diff(x, y), n);
        }
        g = gcd(q, n);
      }
    }
    if (g == n) {
      do z = f(z), g = gcd(diff(x, z), n);
      while (g == 1);
    }
    if (g != n) return g;
  }
}
void factor(ULL n, vector<ULL>& f) {
  if (n == 1) return;
  if (prime(n)) return f.push_back(n);
  ULL d = rho(n);
  factor(d, f);
  factor(n / d, f);
}
vector<ULL> factor(ULL n) {
  assert(n > 0);
  vector<ULL> f;
  factor(n, f);
  sort(f.begin(), f.end());
  return f;
}
vector<pair<ULL, int>> factor_count(ULL n) {
  vector<ULL> a = factor(n);
  vector<pair<ULL, int>> f;
  for (ULL p : a) {
    if (f.empty() || f.back().first != p) f.push_back({p, 1});
    else f.back().second++;
  }
  return f;
}
}
