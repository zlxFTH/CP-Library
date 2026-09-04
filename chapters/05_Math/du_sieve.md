狄利克雷卷积定义为 $(f*g)(n)=\sum_{d\mid n}f(d)g(n/d)$。设 $f*g=h$，$F,G,H$ 分别为 $f,g,h$ 的前缀和，则

$$H(n)=\sum_{d=1}^n g(d)F(\lfloor n/d\rfloor).$$

当 $g(1)=1$ 时可分离出 $F(n)$，再对 $\lfloor n/d\rfloor$ 数论分块。代码中 `G(n)`、`H(n)` 分别返回 $g$、$h$ 的前缀和，`sf` 保存预处理范围内 $F$，`du(n)` 返回 $F(n)$。取预处理上界 $B\approx n^{2/3}$ 时，单次复杂度为 $O(n^{2/3})$。

默认求莫比乌斯函数前缀和：先保证 `sieve(B)` 已完成，再调用 `initDu(B)`。求欧拉函数前缀和时，将 `initDu` 中的 `mu[i]` 改为 `phi[i]`，并令 `H(n)=n(n+1)/2`。所有中间结果须在 `LL` 范围内。
