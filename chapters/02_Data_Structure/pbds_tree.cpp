#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
template <class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag,
                  tree_order_statistics_node_update>;
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, id = 0;
  cin >> n;
  Tree<pair<int, int>> s;
  while (n--) {
    int op, x;
    cin >> op >> x;
    if (op == 1) s.insert({x, ++id});
    else if (op == 2) s.erase(s.lower_bound({x, 0}));
    else if (op == 3) cout << s.order_of_key({x, 0}) + 1 << '\n';
    else if (op == 4) cout << s.find_by_order(x - 1)->first << '\n';
    else if (op == 5) cout << prev(s.lower_bound({x, 0}))->first << '\n';
    else cout << s.upper_bound({x, id})->first << '\n';
  }
  return 0;
}
