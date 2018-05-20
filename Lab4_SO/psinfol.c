/**
 *	 \file psinfo-l.c
 *	 \brief base code for the program psinfo-l
 *
 *	This program prints some basic information for a given
 *	list of processes.
 *	You can use this code as a basis for implementing parallelization
 *	through the pthreads library.
 *
 *	 \author: Danny Munera - Sistemas Operativos UdeA
 *	 \modified by: AlukardSins and stefannytoror
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_BUFFER 100

//#define DEBUG

typedef struct p_ {
	int pid;
	char name[MAX_BUFFER];
	char state[MAX_BUFFER];
	char vmsize[MAX_BUFFER];
	char vmdata[MAX_BUFFER];
	char vmexe[MAX_BUFFER];
	char vmstk[MAX_BUFFER];
	int voluntary_ctxt_switches;
	int nonvoluntary_ctxt_switches;
} proc_info;

//Size of buffer [10]
#define PROC_BUFF_SIZE 10

//Shared Buffer
proc_info shrdBuff[PROC_BUFF_SIZE];

//Global Pos
int pos = 0;

//Total # proc
int numProc = 0;

//Sem var def
sem_t full;
sem_t empty;
sem_t mutex;

/**
 *	\brief load_info
 *
 *	Load process information from status file in proc fs
 *
 *	\param pid (in) process id
 *	\param myinfo (out) process info struct to be filled
 */
void load_info(int pid, proc_info* myinfo){
	FILE *fpstatus;
	char buffer[MAX_BUFFER];
	char path[MAX_BUFFER];
	char* token;

	sprintf(path, "/proc/%d/status", pid);
	fpstatus = fopen(path, "r");
	assert(fpstatus != NULL);
	#ifdef DEBUG
		printf("%s\n", path);
	#endif // DEBUG
	myinfo->pid = pid;
	while (fgets(buffer, MAX_BUFFER, fpstatus)) {
		token = strtok(buffer, ":\t");
		if (strstr(token, "Name")){
			token = strtok(NULL, ":\t");
			#ifdef DEBUG
				printf("%s\n", token);
			#endif // DEBUG
			strcpy(myinfo->name, token);
		}else if (strstr(token, "State")){
			token = strtok(NULL, ":\t");
			strcpy(myinfo->state, token);
		}else if (strstr(token, "VmSize")){
			token = strtok(NULL, ":\t");
			strcpy(myinfo->vmsize, token);
		}else if (strstr(token, "VmData")){
			token = strtok(NULL, ":\t");
			strcpy(myinfo->vmdata, token);
		}else if (strstr(token, "VmStk")){
			token = strtok(NULL, ":\t");
			strcpy(myinfo->vmstk, token);
		}else if (strstr(token, "VmExe")){
			token = strtok(NULL, ":\t");
			strcpy(myinfo->vmexe, token);
		}else if (strstr(token, "nonvoluntary_ctxt_switches")){
			token = strtok(NULL, ":\t");
			myinfo->nonvoluntary_ctxt_switches = atoi(token);
		}else if (strstr(token, "voluntary_ctxt_switches")){
			token = strtok(NULL, ":\t");
			myinfo->voluntary_ctxt_switches = atoi(token);
		}
		#ifdef DEBUG
			printf("%s\n", token);
		#endif
	}
	fclose(fpstatus);
}

void *produce(void* vPid) {
	int *pid = (int*)vPid;

	//Sem waits
	sem_wait(&empty);
	sem_wait(&mutex);
	//Critical seccion
	load_info(*pid, &shrdBuff[pos % PROC_BUFF_SIZE]);
	pos++;
	//Sem posts
	sem_post(&mutex);
	sem_post(&full);
	return 0;
}

/**
 *	\brief print_info
 *
 *	Print process information to stdout stream
 *
 *	\param pi (in) process info struct
 */
void print_info(proc_info* pi) {
	printf("PID: %d \n", pi->pid);
	printf("Nombre del proceso: %s", pi->name);
	printf("Estado: %s", pi->state);
	printf("TamaÃ±o total de la imagen de memoria: %s", pi->vmsize);
	printf("TamaÃ±o de la memoria en la regiÃ³n TEXT: %s", pi->vmexe);
	printf("TamaÃ±o de la memoria en la regiÃ³n DATA: %s", pi->vmdata);
	printf("TamaÃ±o de la memoria en la regiÃ³n STACK: %s", pi->vmstk);
	printf("NÃºmero de cambios de contexto realizados (voluntarios - no voluntarios): \t%d\t-\t%d\n", pi->voluntary_ctxt_switches, pi->nonvoluntary_ctxt_switches);
}


void *consume() {
	for (int i = 0; i < numProc; i++)
	{
		//Sem waits
		sem_wait(&full);
		sem_wait(&mutex);
		//Critical seccion
		int location = i % PROC_BUFF_SIZE;
		print_info(&shrdBuff[location]);
		//Sem posts
		sem_post(&mutex);
		sem_post(&empty);
	}
	return 0;
}



int main(int argc, char *argv[]){
	//Sem init
	//Full, starts empty
	sem_init(&full, 0, 0);
	//Empty, starts full [PROC_BUFF_SIZE]
	sem_init(&empty, 0, PROC_BUFF_SIZE);
	//Mutex, allow only 1 in critical seccion
	sem_init(&mutex, 0, 1);

	//Thread init
	pthread_t threads[numProc + 1];

	//Var to use on For(s)
	int i;

	// number of process ids passed as command line parameters
	// (first parameter is the program name)
	numProc = argc - 1;

	if(argc < 2){
		printf("Error: # Args < 2\n");
		exit(1);
	}

	for (i = 0; i < numProc; i++)
	{
		//Get proc PID
		int pid = atoi(argv[i + 1]);
		//Thread starts producing proc_info to shrdBuff
		pthread_create(&threads[i], NULL, &produce, &pid);
	}

	//Thread starts consuming proc_info from shrdBuff
	pthread_create(&threads[numProc], NULL, &consume,NULL);

	//Threads join
	for (i = 0; i <= numProc; i++)
	{
		pthread_join(threads[i],NULL);
	}

	//Sem destroy
	sem_destroy(&full);
	sem_destroy(&empty);
	sem_destroy(&mutex);

	return 0;
}
