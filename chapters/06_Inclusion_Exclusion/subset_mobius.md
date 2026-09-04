对子集格的下闭包求和与反演为

$$
F(S)=\sum_{T\subseteq S}f(T)
\iff
f(S)=\sum_{T\subseteq S}(-1)^{|S|-|T|}F(T).
$$

原地做子集 zeta 变换时，依次枚举每一位 $i$，对所有含 $i$ 的 $S$ 执行 $F(S)\mathrel{+}=F(S\setminus\{i\})$；Möbius 逆变换把加号改成减号。上闭包版本

$$
F(S)=\sum_{T\supseteq S}f(T)
$$

则对所有不含 $i$ 的 $S$ 执行 $F(S)\mathrel{+}=F(S\cup\{i\})$，反演仍把加号改成减号。两者均为 $O(k2^k)$，最常见错误是把子集和、超集和的方向写反。

OR 卷积 $h(S)=\sum_{A\cup B=S}f(A)g(B)$ 使用子集 zeta，AND 卷积使用超集 zeta：分别变换两数组、逐点相乘、再反演。若要求不交并 $A\mathbin{\dot\cup}B=S$，需按 `popcount` 分层做 zeta、卷积层数后再反演，复杂度为 $O(k^2 2^k)$。
