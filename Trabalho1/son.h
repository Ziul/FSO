
#ifndef __SON_H__
#define __SON_H__

#include <sys/ipc.h>            /* for all IPC function calls */
#include <sys/shm.h>            /* for shmget(), shmat(), shmctl() */
#include <signal.h>				/* kill() and signal macros */
#include <exception>			/* catch some std exceptions */
#include <sys/sem.h>			/* semaphore */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>				/* perror() */
#include <cstdlib>
#include <iostream>
//#include <pthread.h>
#include <thread>

// definição da chave desejada
#define KEY 0xfaca
#define KEY_UP_DOWN 0x4321
#define KEY_DOWN_UP 0x1234
#define MAX_SIZE 100

using namespace std;

int run_son(void);


typedef 
struct _info
{
	bool new_mesage;
	char message[MAX_SIZE+10];
}Info;

#endif