#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#define INT_MAX 32767
#define NR_PROCS 100

int randomizer (int *pids, int *index) {

	time_t seed_randomizer;
	seed_randomizer = time(NULL);
	seed_randomizer = seed_randomizer % 32767;
	srand (seed_randomizer);

	int random_id = rand() % NR_PROCS;

	while (pids[random_id] == 0) {
		random_id++;
		if (random_id == NR_PROCS + 1)
			random_id = 0;
	}
	*index = random_id;
	return pids[random_id];
}

int main( int argc, char **argv)
{
	int pids[NR_PROCS];
	int i = 0;
	pid_t id = 1;

	while (id >= 0) {
		id = fork();

		if (id == 0) 
			while(1);
				//printf("Soy el hijo\n");

		else if (id > 0) {
			printf("Soy el padre\n");
			pids[i] = id;
			i++;
			printf("Added :%d ", id);
		} 
	}
	if (id != 0) {
		printf("Cada 10 segundos se eliminara un proceso\n");
		int index;
		while (i > 0) {
			pid_t id = randomizer (pids, &index);
			if (kill(id, SIGKILL) > 0)
				pids[index] = 0;
			else
				fprintf(stderr, "Child didn't die");
			i--;
		} 
	}
	return 0;
}
