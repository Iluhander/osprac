#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

#define LAST_MESSAGE 255

int main() {
    int msqid;
    char pathname[] = "task11-3-server";
    key_t key;
    int len, maxlen;

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

    maxlen = sizeof(mybuf.info);

    while (1) {

        printf("sdsdfsdf");
        if (( len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 0, 0)) < 0) {
            printf("Can\'t receive message from queue\n");
            exit(-1);
        }

        if (mybuf.mtype == LAST_MESSAGE) {
            msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
            break;
        }

        mybuf.info.mvalue = mybuf.info.mvalue * mybuf.info.mvalue;

        if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) {
            printf("Can\'t send message to queue\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(-1);
        }
    }

    printf("Hello, World!\n");
    return 0;
}
