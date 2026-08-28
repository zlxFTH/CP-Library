struct Node {
  int u;
  LL d;
  bool operator<(const Node& o) const {
    return d > o.d;
  }
};
priority_queue<Node> q;
vector<LL> D(n, INF);
D[0] = 0;
q.push({0, 0});
while (SZ(q)) {
  auto [u, d] = q.top();
  q.pop();
  if (d != D[u]) continue;
  for (auto [v, w] : G[u]) {
    if (D[v] > d + w) {
      D[v] = d + w;
      q.push({v, D[v]});
    }
  }
}
