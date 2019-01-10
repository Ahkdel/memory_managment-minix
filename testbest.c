#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#define INT_MAX 32767
#define NR_PROCS 20

int randomizer (int *pids, int *index) {

	time_t time_randomizer;
	time_randomizer = time(NULL);
	int seed_randomizer = time_randomizer % INT_MAX;
	srand (seed_randomizer);

	int rand_ = rand();
	int random_id = rand_ % NR_PROCS;

	while (pids[random_id] == 0) {
		random_id++;
		if (random_id == NR_PROCS)
			random_id = 0;
	}
	*index = random_id;
	return pids[random_id];
}

int main(int argc, char **argv)
{
	int pids[NR_PROCS];
	int i = 0;
	pid_t id = 0;

	while ((id >= 0) && (i < NR_PROCS)) {
		id = fork();

		if (id == 0) {
			while (1)
				;
		}
		else if (id > 0) {
			if (i == 0)
				printf("I'm the father. ");
			else
				printf("I'm still the father. ");
			pids[i] = id;
			i++;
			printf("Added: %d \n", id);
		} 
	}
	if (id != 0) {
		printf("----Every second, a process will die----\nDeleted process': \n");
		int index;
		while (i > 0) {
			id = randomizer (pids, &index);
			
			if (kill(id, SIGKILL) >= 0) {
				sleep(1);
				printf("%d, ", id);
				pids[index] = 0;
			}
			else {
				fprintf(stderr, "Child didn't die (id: %d)", id);
				exit(1);
			}
			i--;
		} 
	}
	printf("\n");
	return 0;
}
