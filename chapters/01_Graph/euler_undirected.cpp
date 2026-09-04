// 无向图：G[u] 存 {v,id}，两端同 id；答案需有 m+1 个点且首尾相同。
vector<int> euler(int s, int m) {
  vector<int> st{s}, ans;
  vector<char> used(m);
  while (SZ(st)) {
    int u = st.back();
    while (SZ(G[u]) && used[G[u].back().second]) G[u].pop_back();
    if (SZ(G[u])) {
      auto [v, id] = G[u].back();
      G[u].pop_back(), used[id] = 1, st.pb(v);
    } else {
      ans.pb(u), st.pop_back();
    }
  }
  reverse(ALL(ans));
  return ans;
}
