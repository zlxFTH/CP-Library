\noindent 以下均基于 3.2，只列出需要替换的 `V`、`merge`、`L`、`apply` 和 `mdf`。

\noindent\textbf{历史版本和}

\noindent 令 $A_i$ 为当前值，$B_i$ 为各版本之和，`t` 为已经记录的版本数。维护 $B_i=A_i t+C_i$，线段树中每个节点保存区间对应一次函数的系数和。初始不计原数组时 `t=0`、叶子为 `{A[i],0}`；若初始数组也算一个版本，改为 `t=1`。

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

\noindent 当前为旧时间 `t` 时，区间加 `x` 使 $C_i\leftarrow C_i-tx$；先修改再令 `t++`。未修改的位置会由 $A_i t$ 自动补上这一版。同一版本有多次修改时共用旧 `t`，全部完成后只增加一次时间。

```cpp
seg.mdf(l, r, {x, -1LL * t * x});
++t;
auto v = seg.qry(l, r);
LL ans = v.a * t + v.b;
```
