#include <bits/extc++.h>
using namespace __gnu_pbds;
template <class T>
using Tree = tree<T, null_type, std::less<T>, rb_tree_tag,
                  tree_order_statistics_node_update>;
