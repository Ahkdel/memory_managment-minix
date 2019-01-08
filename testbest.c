#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#define INT_MAX 32767

struct ids_nodes {
	pid_t id_child;
	struct ids_nodes *next;
};

typedef struct ids_nodes ids;

ids* newNode (pid_t new_id) {
	ids *p_ids;

	p_ids = (ids*) malloc(sizeof(ids));
	p_ids->id_child = new_id;
	p_ids->next = NULL;

	return p_ids;
}

ids* add_pid (ids *list, pid_t new_id) {
	ids *node = newNode(new_id);

	if (!node) {
		fprintf(stderr, "Error newNode: node = NULL\n");
		exit(1);
	}
	if (!list)
		return node;
	else {
		node->next = list;
		return node;
	}
}

void printList (ids *list) {
	while (list) {
		printf ("%d\t", list->id_child);
		list = list->next;
	}
	printf("\n");
}

pid_t higgest (ids *list) {
	pid_t high = INT_MAX;
	while (list) {
		pid_t possible = list->id_child;

		if (possible < high)
			high = possible;
		list = list->next;
	}
}

int check_id (ids *list, pid_t checker) {
	while ((list) && (checker != list->id_child))
		list = list->next;
	if (list) return 1;
	return 0;
}

pid_t randomizer (ids *list) {

	time_t seed_randomizer;
	seed_randomizer = time(NULL);
	seed_randomizer = seed_randomizer % 32767;
	srand (seed_randomizer);

	pid_t random_id = rand() % higgest(list);

	while (check_id(list, random_id) == 0)
		random_id++;

	return random_id;
}

ids* delete_node (ids *list, pid_t id) {

	ids *aux = list;

	while ((aux) && (aux->next)) {

		if ((aux == list) && (aux->id_child == id)) {
			list = list->next;
			free(aux);
			return list;
		}

		else if ((aux != list) && (aux->next->id_child == id)) {
			aux->next = aux->next->next;
			free(aux->next);
			return list;
		}

		aux = aux->next;
	}
}

int main( int argc, char **argv)
{
	ids *list = NULL;
	pid_t id;
	id = 0;	
	int contador = 0;

	while(id >= 0) {
		id = fork();

		if (id == 0) {
			contador++; 
			while(1) { }
		}

		else if (id > 0) {
			list = add_pid(list, id);
		} 
		else break;	
	}
	printf("\tCantidad de Procesos Activos : %i \n\n",contador);
	printf("\tLista de procesos activos: \n");
	printList(list);
	printf("Cada 10 segundos se eliminara un proceso\n");
	while (list) {
		sleep(10);
		pid_t id = randomizer (list);
		if (kill(id, SIGKILL) > 0)
			list = delete_node(list, id);
		else
			fprintf(stderr, "Child didn't die");
	}

	return 0;
}