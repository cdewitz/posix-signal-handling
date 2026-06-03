#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

/* Child 1 handler*/
void handler_child1(int signum) {
    printf("[Child #1] Received SIGUSR1 → Good bye!\n");
    fflush(stdout);
    exit(0);
}

/* Child 2 Handler */
void handler_child2(int signum) {
    printf("[Child #2] Received SIGUSR1 → Good bye!\n");
    fflush(stdout);
    exit(0);
}

int main() {
    pid_t cpid1, cpid2;

    /* Forks Child 1 */
    cpid1 = fork();

    if (cpid1 < 0) {
        perror("fork #1 failed");
        exit(1);
    }

    if (cpid1 == 0) {
        /* CHILD 1 register SIGUSR1 handler */
        signal(SIGUSR1, handler_child1);
        while (1) {
            printf("[Child #1] PID=%d is running...\n", getpid());
            fflush(stdout);
            sleep(2);
        }
        exit(0);
    }

    /* Fork Child 2 */
    cpid2 = fork();

    if (cpid2 < 0) {
        perror("fork #2 failed");
        exit(1);
    }

    if (cpid2 == 0) {
        /* CHILD 2 register SIGUSR1 handler */
        signal(SIGUSR1, handler_child2);
        while (1) {
            printf("[Child #2] PID=%d is running...\n", getpid());
            fflush(stdout);
            sleep(2);
        }
        exit(0);
    }

    sleep(5);

    printf("[Parent]  Sending SIGUSR1 → Child #1 (PID=%d)\n", cpid1);
    kill(cpid1, SIGUSR1);

    printf("[Parent]  Sending SIGUSR1 → Child #2 (PID=%d)\n", cpid2);
    kill(cpid2, SIGUSR1);

    /* Wait for children to prevent zombie processes */
    waitpid(cpid1, NULL, 0);
    waitpid(cpid2, NULL, 0);

    printf("[Parent]  Both children exited. Parent done.\n");
    return 0;
}
