#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    printf("Welcome to the Enchanted Fork and Exec Journey!\n");
    printf("Choose an element to transform into:\n");
    printf("1. Fire\n2. Water\n3. Earth\n4. Air\n");
    
    int choice;
    scanf("%d", &choice);

    pid_t pid;
    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process created with PID: %d\n", getpid());
        
        char *element;
        switch(choice) {
            case 1:
                element = "fire_elemental";
                break;
            case 2:
                element = "water_elemental";
                break;
            case 3:
                element = "earth_elemental";
                break;
            case 4:
                element = "air_elemental";
                break;
            default:
                printf("Invalid choice\n");
                exit(1);
        }
        
        execl(element, element, NULL);
        perror("exec");
        exit(1);
    } else {
        // Parent process
        wait(NULL);
        printf("Parent process with PID: %d waiting...\n", getpid());
    }

    return 0;
}
