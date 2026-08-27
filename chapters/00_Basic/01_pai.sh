pai() {
  mk a && mk bf && mk gen || return
  while true; do
    ./gen > 1.in
    ./bf < 1.in > ans
    ./a < 1.in > out
    if diff -Zq out ans; then echo ac; else echo wa; break; fi
  done
}
