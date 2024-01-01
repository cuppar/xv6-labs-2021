#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void)
{

    int pid = getpid();
    int p[2];
    pipe(p);

    if (fork() == 0)
    {
        // child
        pid = getpid();
        char buf[2];

        if (read(p[0], buf, 1) != 1)
        {
            fprintf(2, "failed to read in child\n");
            exit(1);
        }

        close(p[0]);
        printf("%d: received ping\n", pid);
        printf("%d: received %s\n", pid, buf);

        buf[0] += 1;

        if (write(p[1], buf, 1) != 1)
        {
            fprintf(2, "failed to write in child\n");
            exit(1);
        }
        close(p[1]);
        exit(0);
    }
    else
    {
        // parent
        char buf[] = "a";

        if (write(p[1], buf, 1) != 1)
        {
            fprintf(2, "failed to write in parent\n");
            exit(1);
        }
        close(p[1]);

        wait(0);
        if (read(p[0], buf, 1) != 1)
        {
            fprintf(2, "failed to read in parent\n");
            exit(1);
        }
        close(p[0]);

        printf("%d: received pong\n", pid);
        printf("%d: received %s\n", pid, buf);
        exit(0);
    }
}