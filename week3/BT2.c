#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#define SIG_OK 0
#define SIG_NG -1
#define LOOP_ON 0
#define LOOP_OFF 1

int loopFlag = LOOP_ON;
void sigHandleSighup(int sigNo);
void sigHandleSigalrm(int sigNo);
void sigHandleSigint(int sigNo);
int main(int argc, char *argv[]) {
    if(argc < 2) {
        return SIG_NG;
    }
    int time = atoi(argv[1]);
    printf("main : start\n");
    signal(SIGHUP, sigHandleSighup);
    signal(SIGALRM, sigHandleSigalrm);
    signal(SIGINT, sigHandleSigint);
    alarm(time);
    while(loopFlag == LOOP_ON) {
        printf("Looping\n");
        sleep(1);
    }
    printf("main : end\n");
    return SIG_OK;
}

void sigHandleSighup(int sigNo) {
    printf("Signal No %d\n", sigNo);
    loopFlag = LOOP_OFF;
    return;
}

void sigHandleSigalrm(int sigNo) {
    printf("Time up\n");
    loopFlag = LOOP_OFF;
    return;
}

void sigHandleSigint(int sigNo) {
    printf("Interrupted\n");
    loopFlag = LOOP_OFF;
    return;
}