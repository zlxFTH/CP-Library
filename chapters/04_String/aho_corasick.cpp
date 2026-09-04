int ins(const string& s) {
  int p = 0;
  for (char x : s) {
    int c = x - 'a';
    if (!tr[p][c]) tr[p][c] = ++tot;
    p = tr[p][c];
  }
  return p;
}
void get_f() {
  queue<int> q;
  for (int c = 0; c < 26; c++) if (tr[0][c]) q.push(tr[0][c]);
  while (SZ(q)) {
    int u = q.front();
    q.pop();
    for (int c = 0; c < 26; c++) {
      int v = tr[u][c];
      if (v) fail[v] = tr[fail[u]][c], q.push(v);
      else tr[u][c] = tr[fail[u]][c];
    }
  }
}
