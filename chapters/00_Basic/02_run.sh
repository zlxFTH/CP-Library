shopt -s nullglob # 没有匹配到任何文件时，让它返回空
ulimit -s 1024000
g++ $1.cpp -o $1 -std=c++20 -O2 -fsanitize=address,undefined || exit
for f in "$2"/*.in; do
  x=${f%.in}
  \time -f "$x: %es %MKB" ./$1 < $x.in > $1.out
  diff -Zq $1.out $x.ans
done
