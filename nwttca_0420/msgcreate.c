#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MSGKEY 832712L

struct msgbuf1 {
	long mtype;
	char mtext[512];
} sendbuf, *msgp;

int main(void)
{
	key_t key = MSGKEY;
	int msgid;
	int msgflg;
	int ret, msgsz;

	msgflg = 00666 | IPC_CREAT;
	msgid = msgget(key, msgflg);
 	if (msgid == -1) {
                perror(": msgget() nem sikerult!");
                exit(-1);
	}
	printf("Az msgid letrejott: %d, %x\n", msgid,msgid);

	msgp = &sendbuf;
	msgp->mtype = 1;
 	strcpy(msgp->mtext,"Az elso uzenetet itt lehet latni.");
	msgsz = strlen(msgp->mtext) + 1;

     ret = msgsnd(msgid,(struct msgbuf *)msgp, msgsz, msgflg);

	strcpy(msgp->mtext,"Masik uzenet is elobujt.");
	msgsz = strlen(msgp->mtext) + 1;
	ret = msgsnd(msgid,(struct msgbuf *) msgp, msgsz, msgflg);
	exit(0);
}
