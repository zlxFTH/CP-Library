pai() {
  mk a && mk bf && mk gen || return
  cnt=0
  while true; do
    ./gen > 1.in
    ./bf < 1.in > bf.out
    ./a < 1.in > a.out
    if diff -Zq a.out bf.out; then
      echo "$((++cnt)) AC"
    else
      echo WA
      break
    fi
  done
}
