整除偏序上的两种反演为

$$
F(n)=\sum_{d\mid n}f(d)
\iff
f(n)=\sum_{d\mid n}\mu(n/d)F(d),
$$

$$
F(n)=\sum_{n\mid d}f(d)
\iff
f(n)=\sum_{n\mid d}\mu(d/n)F(d).
$$

核心恒等式是

$$
[\gcd(a_1,\ldots,a_k)=1]=\sum_{d\mid\gcd(a_1,\ldots,a_k)}\mu(d).
$$

设 $c_d$ 为序列中 $d$ 的倍数个数，则选 $k$ 个数且 `gcd=1` 的方案数为

$$
\sum_{d\ge1}\mu(d)\binom{c_d}{k};
$$

`gcd=g` 时将 $c_d$ 换成 $c_{gd}$。若要所有精确 `gcd`，从大到小计算

$$
e_d=\binom{c_d}{k}-\sum_{j\ge2}e_{jd}.
$$

精确 `lcm` 对偶地处理：令 $c_d$ 为值能整除 $d$ 的元素数，从小到大用 $e_d=\binom{c_d}{k}-\sum_{t\mid d,t<d}e_t$。有序选取或允许重复时，把组合数换成对应的幂或排列数。`mu` 复用 Math 的线性筛；值域为 $N$ 时通常为 $O(N\log N)$。若只围绕一个数且互异质因子很少，直接枚举质因子子集往往更短。
