`floor_sum(n,m,a,b)` 计算
$$
\sum_{i=0}^{n-1}\left\lfloor\frac{ai+b}{m}\right\rfloor.
$$
要求 $n,a,b\ge 0,m>0$ 且答案不超过 `LL`，复杂度为 $O(\log\max(a,m))$。
