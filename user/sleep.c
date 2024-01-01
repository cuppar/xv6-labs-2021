#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(2, "sleep: should have only one argument\n");
    }
    int time = atoi(argv[1]);
    sleep(time);
    exit(0);
}
