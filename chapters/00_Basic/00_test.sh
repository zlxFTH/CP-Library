export fsan="-fsanitize=address,undefined"
mk() { g++ -o $1 $1.cpp -O2; }
