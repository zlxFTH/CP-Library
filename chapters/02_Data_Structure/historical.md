以下均基于 3.2，只列出需要替换的 `V`、`merge`、`L` 和 `apply`。

**历史版本和**

令 $A_i$ 为当前值，$B_i$ 为各版本之和，`t` 为已经记录的版本数。维护 $B_i=A_i t+C_i$，线段树中每个节点保存区间对应一次函数的系数和。初始不计原数组时 `t=0`、叶子为 `{A[i],0}`；若初始数组也算一个版本，改为 `t=1`。

```cpp
struct V {
  LL a = 0, b = 0;
};
struct L {
  LL a = 0, b = 0;
  bool operator==(L x) { return a == x.a && b == x.b; }
};
V merge(V x, V y) {
  return {x.a + y.a, x.b + y.b};
}
void apply(int p, int l, int r, L x) {
  t[p].a += x.a * (r - l);
  t[p].b += x.b * (r - l);
  lz[p].a += x.a;
  lz[p].b += x.b;
}
```

当前为旧时间 `t` 时，区间加 `x` 使 $C_i\leftarrow C_i-tx$；先修改再令 `t++`。未修改的位置会由 $A_i t$ 自动补上这一版。同一版本有多次修改时共用旧 `t`，全部完成后只增加一次时间。

```cpp
seg.mdf(l, r, {x, -1LL * t * x});
++t;
auto v = seg.qry(l, r);
LL ans = v.a * t + v.b;
```

**历史最小值**

令 $B_i$ 为 $A_i$ 出现过的最小值，查询区间 $min B_i$。把节点上尚未下传的区间加看作一个序列；`add` 为总和，`pre` 为包含空前缀的最小前缀和。`merge(L x,L y)` 表示先执行 `x`，再执行 `y`。

```cpp
struct V {
  LL mn = INF, hmn = INF;
};
struct L {
  LL add = 0, pre = 0;
  bool operator==(L x) { return add == x.add && pre == x.pre; }
};
V merge(V x, V y) {
  return {min(x.mn, y.mn), min(x.hmn, y.hmn)};
}
L merge(L x, L y) {
  return {x.add + y.add, min(x.pre, x.add + y.pre)};
}
void apply(int p, int l, int r, L x) {
  t[p].hmn = min(t[p].hmn, t[p].mn + x.pre);
  t[p].mn += x.add;
  lz[p] = merge(lz[p], x);
}
```

叶子初始化为 `{A[i],A[i]}`；一次区间加 `x` 使用 `L{x,min(0LL,x)}`，查询答案为 `qry(l,r).hmn`。历史最大值把所有 `min` 换为 `max` 即可。单次修改、查询均为 $O(\log n)$。

**历史最小值之和**

若查询的是 $\sum B_i$，上面的 `hmn` 无法合并。令 $C_i=A_i-B_i\geq0$，区间加 `x` 等价于

$$A_i\mathrel{+}=x,\qquad C_i\leftarrow\max(C_i+x,0),$$

答案为 $\sum A_i-\sum C_i$。`V` 维护 `sa/sc/mn/se/cmn`：前两项分别为 $A/C$ 的和，其余为 $C$ 的最小值、严格次小值及最小值个数；`merge` 对和相加，并照常合并后三项。Lazy Tag `(add,low)` 表示 $c\mapsto\max(c+add,low)$，空标记为 `(0,-INF)`，一次修改为 `(x,0)`。若 `x` 在前、`y` 在后，则

$$\operatorname{merge}(x,y)=(x.add+y.add,\max(x.low+y.add,y.low)).$$

只有 `low <= mn` 或 `low < se` 时整段打标记，否则递归。$m$ 次操作总复杂度 $O(m\log^2 n)$。
