`exlucas(n,k,mod)` 返回 $\binom nk\bmod mod$，`mod` 可为任意正整数，依赖前面的 `linear_congruence` 与 `excrt`。代码将 `mod` 分解为互质的质数幂，分别求组合数后用 CRT 合并；$k<0$ 或 $k>n$ 时返回 $0$。

每个质数幂 $p^q$ 会预处理 $O(p^q)$ 个数，总时间复杂度为 $O(\sqrt{mod}+\sum p^q+\omega(mod)\log^2n)$，空间复杂度为 $O(\max p^q)$，适用于最大质数幂可预处理的情况。
