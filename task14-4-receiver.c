#include <stdio.h>
#include <signal.h>
#include <unistd.h>

const int bits_count = 33;
int number = 0;
int last_bit = 0;
int pid_sender;

// Signal handler for zero.
void add_zero(int nsig) {
    ++last_bit;

    if (last_bit < bits_count) {
        kill(pid_sender, SIGUSR1);
    }
}

// Signal handler for one.
void add_one(int nsig) {
    if (last_bit < bits_count - 1) {
        number |= 1 << (last_bit);
    } else {
        number = -1 * number;
    }

    ++last_bit;

    if (last_bit < bits_count) {
        kill(pid_sender, SIGUSR1);
    }
}

int main(void) {
    printf("Receiver PID: %i\n", getpid());

    // Getting sender PID.
    printf("Enter sender PID: ");
    scanf("%i", &pid_sender);

    (void)signal(SIGUSR1, add_zero);
    (void)signal(SIGUSR2, add_one);

    // Getting bits.
    kill(pid_sender, SIGUSR1);

    while (last_bit < bits_count) {}

    if (number < 0) {
        number += 1;
    } else {
        number -= 1;
    }

    // Printing result.
    printf("Number was received: %i", number);

    return 0;
}
