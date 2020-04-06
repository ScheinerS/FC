run () {
echo '\n'
echo $1
echo '\n'
gcc -Wall -o $1.e $1.c -lm
./$1.e
}

run 1-1
run clusters


