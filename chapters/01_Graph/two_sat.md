对 $u_a\lor v_b$，加入两条边

$$
u_{a\oplus1}\to v_b,\qquad
v_{b\oplus1}\to u_a.
$$

常见限制的建边方式如下：

- $u_a\Rightarrow v_b$：加入 $u_a\to v_b$ 和 $v_{b\oplus1}\to u_{a\oplus1}$。
- 强制 $u=a$：加入 $u_{a\oplus1}\to u_a$。
- 禁止 $u=a$ 与 $v=b$ 同时成立：加入 $u_a\to v_{b\oplus1}$ 和 $v_b\to u_{a\oplus1}$。
- $u=v$：加入 $u_0\leftrightarrow v_0$ 和 $u_1\leftrightarrow v_1$。
- $u\ne v$：加入 $u_0\leftrightarrow v_1$ 和 $u_1\leftrightarrow v_0$。

其中每个 $\leftrightarrow$ 都表示正反两条有向边。

建图后运行 Tarjan。若存在 $u$ 满足 $u_0,u_1$ 在同一强连通分量中，则无解。

前一节的 Tarjan 按分量出栈顺序从小到大编号，因此缩点后的边总是从较大编号指向较小编号。构造方案时，对每个 $u$ 选择强连通分量编号较小的状态：

$$
\operatorname{ans}_u=[\operatorname{bel}_{u_0}>\operatorname{bel}_{u_1}].
$$
