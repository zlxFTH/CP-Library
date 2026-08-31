不使用路径压缩，按大小合并；`find`、`merge` 单次 $O(\log n)$。

用 `t = dsu.time()` 保存状态，`dsu.rollback(t)` 撤销此后的所有成功合并。点为 0-index；`init(n)` 可初始化并用于多测清空。
