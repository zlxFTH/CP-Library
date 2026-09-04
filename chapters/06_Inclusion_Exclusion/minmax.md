对非空有限集合 $S$，有

$$
\max_{i\in S}x_i=\sum_{\varnothing\ne T\subseteq S}(-1)^{|T|-1}\min_{i\in T}x_i,
$$

$$
\min_{i\in S}x_i=\sum_{\varnothing\ne T\subseteq S}(-1)^{|T|-1}\max_{i\in T}x_i.
$$

更一般地，第 $k$ 大可由子集最小值表示：

$$
x_{(k)\downarrow}=\sum_{|T|\ge k}(-1)^{|T|-k}\binom{|T|-1}{k-1}\min_{i\in T}x_i,
$$

第 $k$ 小则把右侧的 `min` 换成 `max`。这些等式逐个样本成立，所以两边同时取期望仍成立，不需要随机变量独立。

当“全部完成时间”是若干时间的最大值，而一个子集的最早完成时间容易计算时使用第一式；求至少/第 $k$ 个完成时使用推广式。对非负整数变量还可用 $\mathbb E X=\sum_{t\ge0}\Pr(X>t)$，把子集最小值转成若干事件同时未发生的概率。若子集答案只与大小或某个合并状态有关，应先分组再容斥。
