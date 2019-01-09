all: show_vm new_best test_best lru

show_vm:	dmp.c dmp_vm.c
	cp ./dmp.c ./dmp_vm.c /usr/src/minix/servers/is/

new_best:	alloc.c
	cp ./alloc.c /usr/src/minix/servers/vm/

test_best:	testbest.c sys_config.h
	cp ./sys_config.h /usr/src/minix/include/minix/
	touch testbest.c
	cc -o ./testbest ./testbest.c

lru:	matrix.c
	touch matrix.c
	cc -o ./lru ./matrix.c
	clear