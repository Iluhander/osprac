#include <stdio.h>
#include <signal.h>
#include <unistd.h>

const int bits_count = 33;
int pid_receiver = 0;
int bit_id = 0;
int number = 0;
int negative = 0;

// Signal handler for message.
void send_bit(int nsig) {
    int cur_bit;

    if (bit_id < bits_count - 1) {
        int mask = 1 << bit_id;
        int masked_n = number & mask;
        cur_bit = masked_n >> bit_id;
    } else {
        cur_bit = negative;
    }

    ++bit_id;

    if (cur_bit) {
        kill(pid_receiver, SIGUSR1);
    } else {
        kill(pid_receiver, SIGUSR2);
    }
}

int main(void) {
    // Getting receiver PID.
    printf("Enter receiver PID: ");
    scanf("%i", &pid_receiver);

    // Getting number.
    printf("Enter number: ");
    scanf("%i", &number);

    if (number < 0) {
        number *= -1;
        negative = 1;
    }

    // Setting sending function bits.
    (void)signal(SIGUSR1, send_bit);

    printf("Sender PID: %i\n", getpid());

    while (bit_id < bits_count) {

    }

    return 0;
}
