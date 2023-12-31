#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <pthread.h>

#include "dllist.h"
#include "jval.h"
#include "dllist.c"
#include "jval.c"

#define MSGSIZE 100
#define KEYFILE_PATH "filepath"
#define ID 'M'
#define MSGQ_OK 0
#define MSGQ_NG -1

int main(int argc, char **argv)
{
  struct msgbuff
  {
    long mtype;
    pid_t pid;
  } message;

  pid_t pid, npid;
  int i;

  int msqid;
  key_t keyx;
  struct msqid_ds msq;

  Dllist q = new_dllist();
  Dllist n;

  keyx = ftok(KEYFILE_PATH, (int)ID);

  msqid = msgget(keyx, 0666 | IPC_CREAT);

  if (msqid == -1)
  {
    perror("msgget");
    exit(1);
  }

  while (1)
  {
    if ((msgrcv(msqid, &message, sizeof(pid_t), 1, 0)) ==
        MSGQ_NG)
    {
      perror("msgrcv");
      exit(1);
    }
    pid = message.pid;
    if (pid != 1)
    {
      if (dll_empty(q))
        kill(pid, SIGUSR1);
      else
      {
        n = dll_first(q);
        npid = jval_i(dll_val(n));
        if (pid == npid)
        {
          kill(pid, SIGUSR1);
          dll_delete_node(n);
        }
        else
          dll_append(q, new_jval_i(pid));
      }
    }
    else
    {
      if (!dll_empty(q))
      {
        n = dll_first(q);
        npid = jval_i(dll_val(n));
        kill(npid, SIGUSR1);
        dll_delete_node(n);
      }
    }
  }

  return 0;
}