#include <bits/extc++.h>
using namespace __gnu_pbds;
struct V {
  int x;
  bool operator<(V b) const {
    return x < b.x;
  }
};
using PQ = __gnu_pbds::priority_queue<V, std::less<V>, pairing_heap_tag>;
