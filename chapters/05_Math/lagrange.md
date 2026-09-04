`lag(y,x)` 要求 $y_i=f(i)$（0-index）且 $\deg f<|y|<P$，返回 $f(x)$。调用前先 `initComb(SZ(y))`，单次 $O(n)$。

`coef(x,y)` 要求横坐标两两不同，返回系数 $[a_0,\ldots,a_{n-1}]$，其中
$f(t)=\sum_{i=0}^{n-1}a_it^i$。复杂度 $O(n^2)$。
