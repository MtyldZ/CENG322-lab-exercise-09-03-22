#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>

char *numToCharArray(int number);

int main() {
    pid_t pID = fork();
//    printf("P=%d\n", p);
// // Test numToCharArray
//    int number = 14530;
//    char *string = numToCharArray(number);
//    printf("%d, %s\n", number, string);

    if (pID == 0) {
//        printf("PID=%d, PPID=%d\n", getpid(), getppid());
        execl("./hello.out", "hello.out", NULL);
    } else {
        char *string = numToCharArray(pID);
        // since after execl The old process gets replaced,
        // we do not have to free the dynamically allocated memory space.
        // No need for "free(string);"
        sleep(3);
//        printf("PID=%d, PPID=%d\n", getpid(), getppid());
        execl("/bin/kill", "", string, NULL);
    }


    return 0;
}


char *numToCharArray(int number) {
    int digitCount = log10(number) + 1;
    char *string = calloc(digitCount, sizeof(char));
    for (int i = digitCount - 1; i >= 0; --i) {
        string[i] = (number % 10) + '0';
        number /= 10;
    }
    return string;
}