template<class T>
struct Heap {
  std::priority_queue<T> p, q;
  void fix() {
    while (!q.empty() && p.top() == q.top()) p.pop(), q.pop();
  }
  void push(T x) { p.push(x); }
  void pop() { p.pop(), fix(); }
  void pop(T x) { q.push(x), fix(); } // 删除一个已存在的 x
  T top() { return p.top(); }
  bool empty() { return p.empty(); }
};
