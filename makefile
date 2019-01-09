all: show_vm new_best lru_matrix test_best

show_vm:	./dmp.c ./dmp_vm.c
	cp ./dmp.c ./dmp_vm.c /usr/src/minix/servers/is/

new_best:	./alloc.c
	cp ./alloc.c /usr/src/minix/servers/vm/

lru_matrix:		./matrix.c
	touch ./matrix.c
	cc -o ./lru ./matrix.c

test_best:	./testbest.c ./sys_config.h
	cp ./sys_config.h /usr/src/minix/include/minix/
	touch ./testbest.c
	cc -o ./testbest ./testbest.c
	clear
