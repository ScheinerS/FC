
alarm(){
for i in 1 #2 3 4 5
do
	echo '\a'
	sleep 1

done
}

run () {
	echo '\n'
	echo $1
	echo '\n'
	gcc -Wall -o $1.e $1.c -lm
	./$1.e
}

#################################
# PROGRAMAS A CORRER:

#run Percolacion
run ising

#################################

# Para apagar la máquina al finalizar:
alarm
#shutdown
