以下公式覆盖最常见的直接套用场景，约定非法组合数为 $0$。

- 有界插板：$x_i\ge0$、$\sum x_i=m$、$x_i\le b_i$ 的方案数为

$$
\sum_{S\subseteq[n]}(-1)^{|S|}
\binom{m-\sum_{i\in S}(b_i+1)+n-1}{n-1}.
$$

若所有上界均为 $b$，按 $|S|=j$ 合并即可。

- 满射：$n$ 个不同元素映到 $m$ 个有标号且非空的集合，方案数为

$$
\sum_{j=0}^m(-1)^j\binom mj(m-j)^n=m!\,S(n,m).
$$

其中 $S(n,m)$ 是第二类 Stirling 数。

- 错排：$D_n=\sum_{j=0}^n(-1)^j\binom nj(n-j)!=n!\sum_{j=0}^n(-1)^j/j!$。

- 禁止位置排列：若 $r_j$ 是从禁止格中选出 $j$ 个不同行、不同列格子的方案数，则合法排列数为 $\sum_j(-1)^jr_j(n-j)!$；错排是禁止格恰为主对角线的特例。

- 至少被一个数整除：区间 $[1,R]$ 内是某个 $a_i$ 倍数的数有

$$
\sum_{\varnothing\ne S\subseteq[n]}(-1)^{|S|+1}
\left\lfloor\frac R{\operatorname{lcm}_{i\in S}a_i}\right\rfloor.
$$

先删除被更小 $a_i$ 整除的冗余数；`lcm>R` 后该分支贡献为零，并须在乘法前判溢出。

- 图的合法染色：$chi_G(q)=\sum_{A\subseteq E}(-1)^{|A|}q^{c(V,A)}$，其中 $c(V,A)$ 是生成子图 $(V,A)$ 的连通块数；适合边数很少或子集连通块可快速维护时使用。
