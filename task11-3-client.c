#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int msqid;
    char pathname[]="task11-3-server";

    key_t key;
    int len;

    struct mymsgbuf
    {
        long mtype;

        struct {
            float mvalue;
        } info;

    } mybuf;
    if ((key = ftok(pathname,0)) < 0) {
        printf("Can\'t generate key\n");
        exit(-1);
    }

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
        printf("Can\'t get msqid\n");
        exit(-1);
    }

    mybuf.mtype = getpid();
    scanf("%f", &mybuf.info.mvalue);

    // Filling with values;

    len = sizeof(mybuf.info);
    //
    // Send the message. If there is an error,
    // report it and delete the message queue from the system.
    //
    if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) {
        printf("Can\'t send message to queue\n");
        msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
        exit(-1);
    }

    if (( len = msgrcv(msqid, (struct msgbuf *) &mybuf, len, mybuf.mtype, 0)) < 0) {
        printf("Can\'t receive message from queue\n");
        exit(-1);
    }

    printf("%f", mybuf.info.mvalue);

    return 0;
}