// Write a program that opens the text.txt file (with the `fopen()` library call) located in this directory
// and then calls `fork()` to create a new process. Can both the child and parent access the file descriptor
// returned by `fopen()`? What happens when they are written to the file concurrently?

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
    FILE *fp = fopen("text.txt", "w");
    fprintf(fp, "%d Parent 1 \n", getpid());
    //what up with dis???!?
    fflush(fp);
    int rc = fork();

    if (rc < 0)
    {
        fprintf(stderr, "Fork failed.\n");
        exit(1);
    }
    else if (rc == 0)
    {
        fprintf(fp, "Child\n");
        fclose(fp);
    }
    else
    {
        int wc = waitpid(rc, NULL, 0);
        fprintf(fp, "Parent 2\n");
        fclose(fp);
    }

    return 0;
}
