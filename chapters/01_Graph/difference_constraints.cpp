vector<LL> d(n);
vector<int> len(n), in(n, 1);
queue<int> q;
for (int u = 0; u < n; u++) q.push(u);
bool ok = 1;
while (SZ(q) && ok) {
  int u = q.front();
  q.pop(), in[u] = 0;
  for (auto [v, w] : G[u]) if (d[v] > d[u] + w) {
    d[v] = d[u] + w, len[v] = len[u] + 1;
    if (len[v] >= n) {
      ok = 0;
      break;
    }
    if (!in[v]) q.push(v), in[v] = 1;
  }
}
