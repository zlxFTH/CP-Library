设共有 $m$ 个性质，$F(S)$ 表示钦定 $S$ 中性质全部成立的方案数，$F(\varnothing)$ 为总方案数。普通容斥为

$$
N_0=\sum_{S\subseteq[m]}(-1)^{|S|}F(S),\qquad
N_{\ge1}=\sum_{\varnothing\ne S\subseteq[m]}(-1)^{|S|+1}F(S).
$$

记 $H_j=\sum_{|S|=j}F(S)$，则恰好、至少满足 $k$ 个性质的方案数分别为

$$
E_k=\sum_{j=k}^m(-1)^{j-k}\binom jkH_j,\qquad
G_k=\sum_{j=k}^m(-1)^{j-k}\binom{j-1}{k-1}H_j\quad(k\ge1).
$$

二项式反演：

$$
g_n=\sum_{k=0}^n\binom nkf_k
\iff
f_n=\sum_{k=0}^n(-1)^{n-k}\binom nkg_k.
$$

子集与超集 Möbius 反演：

$$
\begin{aligned}
F(S)=\sum_{T\subseteq S}f(T)
&\iff f(S)=\sum_{T\subseteq S}(-1)^{|S|-|T|}F(T),\\
F(S)=\sum_{T\supseteq S}f(T)
&\iff f(S)=\sum_{T\supseteq S}(-1)^{|T|-|S|}F(T).
\end{aligned}
$$

整除 Möbius 反演：

$$
\begin{aligned}
F(n)=\sum_{d\mid n}f(d)
&\iff f(n)=\sum_{d\mid n}\mu(n/d)F(d),\\
F(n)=\sum_{n\mid d}f(d)
&\iff f(n)=\sum_{n\mid d}\mu(d/n)F(d).
\end{aligned}
$$

Min-Max 容斥：

$$
\max_{i\in S}x_i=
\sum_{\varnothing\ne T\subseteq S}(-1)^{|T|-1}\min_{i\in T}x_i,
\qquad
\min_{i\in S}x_i=
\sum_{\varnothing\ne T\subseteq S}(-1)^{|T|-1}\max_{i\in T}x_i.
$$

第 $k$ 大与第 $k$ 小的推广式为

$$
x_{(k)\downarrow}=
\sum_{\substack{T\subseteq S\\|T|\ge k}}
(-1)^{|T|-k}\binom{|T|-1}{k-1}\min_{i\in T}x_i,
\qquad
x_{(k)\uparrow}=
\sum_{\substack{T\subseteq S\\|T|\ge k}}
(-1)^{|T|-k}\binom{|T|-1}{k-1}\max_{i\in T}x_i.
$$
