求积性函数 $f$ 的前缀和模 `P`。要求 $f(p)=c_0+c_1p+c_2p^2$，且 $f(p^e)$ 能快速计算；分别写在 `coef` 和 `fpk(p,e)` 中。代码默认 $f=\varphi$，故 `min25(n)` 返回 $\sum_{i=1}^n\varphi(i)\bmod P$。

使用前通过前面的线性筛一次性求出 $\sqrt n$ 内的质数。时间复杂度为 $O(n^{3/4}/\log n)$，空间复杂度为 $O(\sqrt n)$。
