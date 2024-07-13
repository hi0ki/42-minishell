#include <unistd.h>
#include <stdio.h>

int main() {
    // Change the current working directory to "/tmp"
    if (chdir("joker") == 0) {
        printf("Changed directory successfully.\n");
    } else {
        perror("chdir");
    }

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
    } else {
        perror("getcwd");
    }

    return 0;
}