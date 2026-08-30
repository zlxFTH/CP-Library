template <class T>
struct FHQTreap {
  struct Node {
    int ch[2]{}, sz = 0;
    uint32_t pri = 0;
    T val{};
    bool rev = false;
    Node() = default;
    Node(const T& v, uint32_t p) : sz(1), pri(p), val(v) {}
  };
  vector<Node> t{{}};
  vector<int> bin;
  int rt = 0;
  uint32_t seed = chrono::steady_clock::now().time_since_epoch().count();
  uint32_t rnd() {
    uint32_t z = (seed += 0x9e3779b9);
    z = (z ^ (z >> 16)) * 0x21f0aaad;
    z = (z ^ (z >> 15)) * 0x735a2d97;
    return z ^ (z >> 15);
  }
  int size(int p) { return t[p].sz; }
  int size() { return size(rt); }
  void up(int p) {
    t[p].sz = size(t[p].ch[0]) + size(t[p].ch[1]) + 1;
  }
  void apply_rev(int p) {
    if (p) swap(t[p].ch[0], t[p].ch[1]), t[p].rev ^= 1;
  }
  void down(int p) {
    if (!t[p].rev) return;
    apply_rev(t[p].ch[0]), apply_rev(t[p].ch[1]);
    t[p].rev = false;
  }
  int node(const T& v) {
    if (bin.empty()) {
      t.emplace_back(v, rnd());
      return SZ(t) - 1;
    }
    int p = bin.back();
    bin.pop_back(), t[p] = Node(v, rnd());
    return p;
  }
  void split(int p, int k, int& x, int& y) {
    if (!p) return x = y = 0, void();
    down(p);
    if (k <= size(t[p].ch[0]))
      y = p, split(t[p].ch[0], k, x, t[y].ch[0]);
    else
      x = p, split(t[p].ch[1], k - size(t[p].ch[0]) - 1, t[x].ch[1], y);
    up(p);
  }
  int merge(int x, int y) {
    if (!x || !y) return x | y;
    if (t[x].pri < t[y].pri) {
      down(x), t[x].ch[1] = merge(t[x].ch[1], y), up(x);
      return x;
    }
    down(y), t[y].ch[0] = merge(x, t[y].ch[0]), up(y);
    return y;
  }
  int insert(int p, int k, int x) {
    if (!p) return x;
    down(p);
    if (t[x].pri < t[p].pri) {
      split(p, k, t[x].ch[0], t[x].ch[1]), up(x);
      return x;
    }
    int d = k > size(t[p].ch[0]);
    if (d) k -= size(t[p].ch[0]) + 1;
    t[p].ch[d] = insert(t[p].ch[d], k, x), up(p);
    return p;
  }
  void insert(int p, const T& v) {
    assert(0 <= p && p <= size());
    rt = insert(rt, p, node(v));
  }
  int erase(int p, int k, int& x) {
    down(p);
    int s = size(t[p].ch[0]);
    if (k == s) return x = p, merge(t[p].ch[0], t[p].ch[1]);
    int d = k > s;
    if (d) k -= s + 1;
    t[p].ch[d] = erase(t[p].ch[d], k, x), up(p);
    return p;
  }
  T erase(int p) {
    assert(0 <= p && p < size());
    int x;
    rt = erase(rt, p, x);
    T v = move(t[x].val);
    t[x] = {}, bin.push_back(x);
    return v;
  }
  void reverse(int l, int r) {
    assert(0 <= l && l <= r && r <= size());
    int x, y, z;
    split(rt, r, x, z), split(x, l, x, y);
    apply_rev(y), rt = merge(merge(x, y), z);
  }
  int kth(int p, int k) {
    while (true) {
      down(p);
      int s = size(t[p].ch[0]);
      if (k == s) return p;
      if (k < s) p = t[p].ch[0];
      else k -= s + 1, p = t[p].ch[1];
    }
  }
  T& operator[](int p) {
    assert(0 <= p && p < size());
    return t[kth(rt, p)].val;
  }
  void clear() {
    t.assign(1, {}), bin.clear(), rt = 0;
  }
  void build(const vector<T>& a) {
    clear(), t.reserve(SZ(a) + 1);
    vector<int> st;
    st.reserve(SZ(a));
    for (const T& v : a) {
      int p = node(v), q = 0;
      while (!st.empty() && t[p].pri < t[st.back()].pri)
        up(st.back()), q = st.back(), st.pop_back();
      t[p].ch[0] = q;
      if (!st.empty()) t[st.back()].ch[1] = p;
      st.push_back(p);
    }
    while (!st.empty()) up(st.back()), rt = st.back(), st.pop_back();
  }
  void dfs(int p, vector<T>& a) {
    if (!p) return;
    down(p), dfs(t[p].ch[0], a), a.push_back(t[p].val), dfs(t[p].ch[1], a);
  }
  vector<T> get_all() {
    vector<T> a;
    a.reserve(size()), dfs(rt, a);
    return a;
  }
};
