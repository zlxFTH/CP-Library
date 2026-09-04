当直接枚举坏性质为 $2^k$，但坏点有偏序或非法结构能唯一拆分时，可把容斥吸收到减法 DP 中。

单调路径避开少量障碍是标准模型。按可达偏序排列障碍点，并把终点放在最后；令 $W(a,b)$ 为不管障碍时从 $a$ 到 $b$ 的方案数，则

$$
dp_i=W(s,p_i)-\sum_{j<i,\,p_j\preceq p_i}dp_jW(p_j,p_i).
$$

每条非法路径按遇到的第一个障碍唯一归类，终点的 `dp` 即答案，复杂度通常为 $O(k^2)$。

统计一张固定图的连通生成子图时，固定一个代表元可消除重复。对顶点集 $S$ 固定 $r\in S$，设 `all[S]` $=2^{e(S)}$ 为 $S$ 内任意选边的方案数，`con[S]` 为连通方案数，则按 $r$ 所在连通块 $T$ 分类：

$$
\operatorname{con}(S)=\operatorname{all}(S)-
\sum_{\substack{r\in T\subsetneq S}}\operatorname{con}(T)\operatorname{all}(S\setminus T).
$$

其中 $e(S)$ 是 $S$ 内边数；对所有子集计算通常为 $O(3^n)$。对 $n$ 个标号点的任意简单图按大小合并，可化为

$$
c_n=2^{\binom n2}-\sum_{k=1}^{n-1}\binom{n-1}{k-1}c_k2^{\binom{n-k}{2}},
$$

复杂度 $O(n^2)$。类似地，每个 DAG 至少有一个源点，钦定非空源点集可得

$$
d_n=\sum_{k=1}^n(-1)^{k-1}\binom nk2^{k(n-k)}d_{n-k},\qquad d_0=1.
$$
