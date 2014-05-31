#include <son.h>
#include <cstring>

//id do semaforo
int sem_id;

//id da memoria compartilhada
int	memory_id;

//semaforo operator
struct sembuf sop;

//informação compartilhada
Info *info;
string txt;

void tratasignal(int signal)
{
	int coringa;
	msqid_ds *buffer;

	switch(signal)
	{
		case SIGINT:
			cout << "\rInterrupção externa" <<endl;

		case SIGTERM:
		//case SIGSEGV:
		case SIGABRT:
			cout << "Memoria liberada" << endl;
			//libera memoria compartilhada
			shmctl(memory_id, IPC_RMID, NULL);
			// libera semaforo
			semctl(sem_id, 0, IPC_RMID, 0);
			cout << "fila liberada" << endl;
			coringa = msgget(KEY_UP_DOWN, IPC_CREAT|0666);
			msgctl(coringa, IPC_RMID, buffer);
			coringa = msgget(KEY_DOWN_UP, IPC_CREAT|0666);
			msgctl(coringa, IPC_RMID, buffer);
			exit(0);
			break;
		default:
			cout << "Unexpected error [" << signal << ']' <<  endl;
			//libera memoria compartilhada
			shmctl(memory_id, IPC_RMID, NULL);
			// libera semaforo
			semctl(sem_id, 0, IPC_RMID, 0);

			exit(3);
			break;
	}
}

int setup_shared_memory()
{

	// id da memoria compartilhada
	memory_id   = shmget (KEY, sizeof(Info), IPC_CREAT | 0666);
	if (memory_id < 0) {
        perror("Could not obtain shared memory");
        exit(3);
    }

    info  = (Info *) shmat(memory_id, NULL, 0);

    // define id do semaforo
	sem_id = semget( KEY, 1, IPC_CREAT | 0666 );
	if (sem_id < 0) {
        perror("Could not obtain shemaphore");
        exit(3);
    }

    // define valores do controlador do semaforo
	sop.sem_num = 0;
	sop.sem_op = 0;
	sop.sem_flg = 0;

	// 0 if no problens
    return sop.sem_num | sop.sem_op | sop.sem_flg;
}

void *listener_son()
{
	char message[MAX_SIZE+1];
	int idQueue;

	idQueue = msgget(KEY_UP_DOWN, IPC_CREAT|0666);

	while(true)
	{
		msgrcv(idQueue, message, MAX_SIZE*sizeof(char), 0,0);

		txt = message;
		sleep(1);
	}

}

void *whisper_son()
{
	int idQueue;

	idQueue = msgget(KEY_DOWN_UP, IPC_CREAT|0666);

	while(true)
	{
		semop (sem_id, &sop, 1); // bloqueia
		if(info->new_mesage && strlen(info->message))
		{
			msgsnd(idQueue, info->message, strlen(info->message), 0);
			info->message[0] = '\0';
			info->new_mesage = false;
		}
		semop (sem_id, &sop, -1); // desbloqueia
		sleep(1);
	}
}

int 
run_son(void)
{

	signal(SIGTERM, tratasignal);	// sinal de alarme
	signal(SIGABRT, tratasignal);	// sinal de alarme
	signal(SIGSEGV, tratasignal);	// falha de segmentação!
	setup_shared_memory();

	semop (sem_id, &sop, 1); // bloqueia
	info->message[0] = '\0';
	semop (sem_id, &sop, -1); // desbloqueia

	thread ouvido(listener_son);
	thread dalando(whisper_son);

	cout << "filho rodando..." << endl;
	while(true)
	{
		
		semop (sem_id, &sop, 1); // bloqueia
		if(!txt.empty())
		{
			strcpy(info->message, txt.c_str());
			info->new_mesage = true;
			txt.erase();
		}
		semop (sem_id, &sop, -1); // desbloqueia
		sleep(1);
	}

	//libera memoria compartilhada
	shmctl(memory_id, IPC_RMID, NULL);
	// libera semaforo
	semctl(sem_id, 0, IPC_RMID, 0);
		
	return 0;
}