#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <csignal>

#include <son.h>

using namespace std;

int child_pid=0;

//Pipe
int mypipe[2];

void trata_signal(int signal)
{
	switch(signal)
	{
		case SIGINT:
			cout << "\rMatando filho" <<endl;
			//kill(child_pid, SIGTERM);

		case SIGSEGV:

		case SIGABRT:
			kill(child_pid, SIGTERM);

			sleep(3);
		case SIGTERM:
			cout << "Dead" << endl;
			exit(0);
			break;
		default:
			cout << "Unexpected error [" << signal << ']' <<  endl;
			exit(3);
			break;
	}
}


void *listener_dad()
{
	string message;
	int idQueue;

	idQueue = msgget(KEY_UP_DOWN, IPC_CREAT|0666);

	while(true)
	{
		getline(cin, message);
		//info->new_mesage = true;
		if(message.size()>MAX_SIZE)
			message.resize(MAX_SIZE);
		msgsnd(idQueue, message.c_str(), message.size(), 0);
		sleep(1);
	}
}

void *whisper_dad()
{

	char message[MAX_SIZE+1];
	int idQueue;

	idQueue = msgget(KEY_DOWN_UP, IPC_CREAT|0666);

	cout << "pai rodando" << endl;
	while(true)
	{
		msgrcv(idQueue, message, MAX_SIZE*sizeof(char), 0,0);
		cout <<  message << endl;
		sleep(1);
	}

}

int main(int argc, char const *argv[])
{

	signal(SIGINT, trata_signal);	// sinal de alarme
	signal(SIGSEGV, trata_signal);	// falha de segmentação!

	

	//cria pipe para comunicação pai-filho
	if (pipe (mypipe))
	{
		cout << "Pipe failed." << endl;
		return EXIT_FAILURE;
	}

	//cria filho
	child_pid = fork();

	//pai
	if(child_pid)
	{
		thread ouvido(listener_dad);
		thread dalando(whisper_dad);

		ouvido.join();
		kill(child_pid, SIGTERM);
	}
	//filho
	else
	{
		run_son();
	}

	//give time to child die
	sleep(1);
	return EXIT_SUCCESS;
}