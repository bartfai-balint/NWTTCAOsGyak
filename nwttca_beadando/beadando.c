#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> //pid_t

int main(){
	int parent_fds1[2], child_fds2[2]; //parent_fds a szulo csove
					 //child_fds a gyerek csove
	int writemessage = 0;

	if(pipe(parent_fds1) == -1){ //pipe ellenorzes
		printf("Nem lehet letrehozni az elso csovet \n");
		return 1;
	}

	if(pipe(child_fds2) == -1){
		printf("Nem lehet letrehozni a masodik csovet \n");
		return 1;
	}

	pid_t pid = fork(); //elforkol

	if(pid != 0){ // szulo processz
		close(parent_fds1[0]); //kimenet 

		writemessage = getppid();

		write(parent_fds1[1], &writemessage,sizeof(writemessage));

		close(parent_fds1[1]); //bemenet

	}else { // gyerek processz

		close(child_fds2[0]); //kimenet

		read(parent_fds1[0], &writemessage, sizeof(writemessage));

		printf("A gyermek megkapta pid-et a szulotol: %d\n", writemessage);

		close(child_fds2[0]); // kimenet
	}


	if(pid ==0){ // gyerek processz
		close(child_fds2[0]); // kimenet

		writemessage = getpid();

		write(child_fds2[1], &writemessage, sizeof(writemessage));

		close(child_fds2[1]); //bemenet
	}
	else // szulo processz
	{
		close(parent_fds1[0]); //kimenet

		read(child_fds2[0], &writemessage, sizeof(writemessage));

		printf("Megkapta a szulo a gyerek pid-jet: %d\n", writemessage);

		close(parent_fds1[0]); //kimenet
	}

	return 0;
}
