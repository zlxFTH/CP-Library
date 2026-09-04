ULL salt = rnd();
ULL mix(ULL x) {
  x += salt;
  x ^= x << 13;
  x ^= x >> 7;
  return x ^ (x << 17);
}
ULL tree_hash(int u, int f = -1) {
  ULL h = 1;
  for (int v : G[u]) if (v != f) h += mix(tree_hash(v, u));
  return h;
}
