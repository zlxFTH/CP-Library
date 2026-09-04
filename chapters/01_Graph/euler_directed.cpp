// 有向图：每条边在 G 中出现一次，会清空 G；答案需有 m+1 个点且首尾相同。
vector<int> euler(int s) {
  vector<int> st{s}, ans;
  while (SZ(st)) {
    int u = st.back();
    if (SZ(G[u])) {
      int v = G[u].back();
      G[u].pop_back(), st.pb(v);
    } else {
      ans.pb(u), st.pop_back();
    }
  }
  reverse(ALL(ans));
  return ans;
}
