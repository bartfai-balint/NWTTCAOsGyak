#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define SEMKEY 123L

int main(void)
{
	int n = 5;
    	int semID = semget(SEMKEY, 0, 0);

    	if (semID == -1)
	{
   	     perror("Hiba tortent a lekerdezeskor!\n");
       	     exit(-1);
   	}

   	for (int i = 0; i < n; i++)
	{
      	     semctl(semID, i, IPC_RMID);
	}
}
