pai() {
  mk a; mk bf; mk gen
  while true; do
    ./gen > 1.in
    ./bf < 1.in > 1.ans
    ./a < 1.in > 1.out
    if diff -Zq 1.out 1.ans; then echo ac; else echo wa; break; fi
  done
}
